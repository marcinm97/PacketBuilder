#ifndef PACKETBUILDER_PACKETBUILDER_H
#define PACKETBUILDER_PACKETBUILDER_H

#include <array>
#include <functional>
#include <algorithm>
#include <iostream>

// TODO: fold expression for adding arguments
// TODO: more flexible way to add data (inserter)

enum class PacketSlot{
    HEADER,
    PAYLOAD,
    CRC
};

/* using to determine type of std::array elements */
template<typename T>
using element_type_t = std::remove_reference_t<decltype(*std::begin(std::declval<T&>()))>;


template<PacketSlot slot, typename Container>
class PacketBuilder;

template<>
template<typename Container>
class PacketBuilder<PacketSlot::HEADER, Container>;

template<>
template<typename Container>
class PacketBuilder<PacketSlot::CRC, Container>{
private:
    std::reference_wrapper<Container> frame;

    PacketBuilder(Container& packet): frame {packet} {}

    friend class PacketBuilder<PacketSlot::PAYLOAD, Container>;
public:

    template<size_t bits>
    auto attachCRC() -> void{

        std::cout << "\nCRC FILLING";

    }
};

template<typename Container>
class PacketBuilder<PacketSlot::HEADER, Container>;

template<>
template<typename Container>
class PacketBuilder<PacketSlot::PAYLOAD, Container>{
private:
    std::reference_wrapper<Container> frame;
    size_t lastEnd;

    PacketBuilder(Container& packet, size_t lastIdx): frame {packet}, lastEnd{lastIdx} {}

    friend class PacketBuilder<PacketSlot::HEADER, Container>;
public:

    template<size_t  bits,
            typename ...Args>
    [[nodiscard]] auto attachPayload(Args ...args) -> PacketBuilder<PacketSlot::CRC, Container>{

        static_assert(sizeof...(Args) == bits);
        static_assert((std::is_same_v<element_type_t<Container>, Args> && ...));

        ((frame.get().at(lastEnd++) = args), ...);

        std::cout << "\nPAYLOAD FILLING";
        return {frame.get()};
    }
};

template<>
template<typename Container>
class PacketBuilder<PacketSlot::HEADER, Container>{
public:

    template<size_t   bits,
            typename  ...Args>
    [[nodiscard]] auto attachHeader(Container& packet, Args ...args) -> PacketBuilder<PacketSlot::PAYLOAD, Container>{

        static_assert(sizeof...(Args) == bits, "Number of values is not equal given in template param");
        static_assert((std::is_same_v<element_type_t<Container>, Args> && ...), "Given values are not the same type");

        size_t idx = 0;

        ((packet.at(idx++) = args), ...);

        std::cout << "\nHEADER FILLING";

        return {packet, idx};
    }

};



#endif //PACKETBUILDER_PACKETBUILDER_H
