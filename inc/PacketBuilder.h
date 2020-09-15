#ifndef PACKETBUILDER_PACKETBUILDER_H
#define PACKETBUILDER_PACKETBUILDER_H

#include <array>
#include <functional>
#include <algorithm>
#include <iostream>

// TODO: fold expression for adding arguments

struct ConfigOptions{
    static constexpr int packetSize = 16;
};

template<typename T>
using Container = std::array<T, ConfigOptions::packetSize>;


enum class PacketSlot{
    HEADER,
    PAYLOAD,
    CRC
};

template<PacketSlot slot, typename T = int>
class PacketBuilder;

template<>
template<typename V>
class PacketBuilder<PacketSlot::HEADER, V>;

template<>
template<typename V>
class PacketBuilder<PacketSlot::CRC, V>{
private:
    std::reference_wrapper<Container<V>> frame;

    PacketBuilder(Container<V>& packet): frame {packet} {}

    friend class PacketBuilder<PacketSlot::PAYLOAD, V>;
public:
    template<size_t bits>
    auto attachCRC() -> PacketBuilder<PacketSlot::CRC, V>{

        std::cout << "\nCRC FILLING";
        return {frame.get()};
    }
};

template<typename V>
class PacketBuilder<PacketSlot::HEADER, V>;

template<>
template<typename V>
class PacketBuilder<PacketSlot::PAYLOAD, V>{
private:
    std::reference_wrapper<Container<V>> frame;
    size_t lastEnd;

    PacketBuilder(Container<V>& packet, size_t lastIdx): frame {packet}, lastEnd{lastIdx} {}

    friend class PacketBuilder<PacketSlot::HEADER, V>;
public:
    template<size_t bits,
            typename ...Args>
    [[nodiscard]]auto attachPayload(Args ...args) -> PacketBuilder<PacketSlot::CRC>{
        static_assert(sizeof...(Args) == bits);
        static_assert((std::is_same_v<V, Args> && ...));

        ((frame.get()[lastEnd++] = args), ...);

        std::cout << "\nPAYLOAD FILLING";
        return {frame.get()};
    }
};

template<>
template<typename V>
class PacketBuilder<PacketSlot::HEADER, V>{
public:
    template<size_t bits,
            typename ...Args>
    [[nodiscard]]auto attachHeader(Container<V>& packet, Args ...args) -> PacketBuilder<PacketSlot::PAYLOAD, V>{
        static_assert(sizeof...(Args) == bits);
        static_assert((std::is_same_v<V, Args> && ...));
        size_t idx = 0;

        ((packet[idx++] = args), ...);

        std::cout << "\nHEADER FILLING";

        return {packet, idx};
    }

};


#endif //PACKETBUILDER_PACKETBUILDER_H
