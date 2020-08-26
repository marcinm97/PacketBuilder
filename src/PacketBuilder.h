#ifndef PACKETBUILDER_PACKETBUILDER_H
#define PACKETBUILDER_PACKETBUILDER_H
#include <array>
#include <functional>

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

    [[nodiscard]]auto attachCRC() -> PacketBuilder<PacketSlot::CRC, V>{
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

    PacketBuilder(Container<V>& packet): frame {packet} {}

    friend class PacketBuilder<PacketSlot::HEADER, V>;
public:

    [[nodiscard]]auto attachPayload() -> PacketBuilder<PacketSlot::CRC>{
        std::cout << "\nPAYLOAD FILLING";
        return {frame.get()};
    }
};

template<>
template<typename V>
class PacketBuilder<PacketSlot::HEADER, V>{
public:

    [[nodiscard]]auto attachHeader(Container<V>& packet) -> PacketBuilder<PacketSlot::PAYLOAD, V>{
        std::cout << "\nHEADER FILLING";
        return {packet};
    }

};

#endif //PACKETBUILDER_PACKETBUILDER_H
