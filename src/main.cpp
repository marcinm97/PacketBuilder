#include <iostream>
#include "PacketBuilder.h"

struct PacketSizes{
    static constexpr auto pingPacketSize = 16;
    static constexpr auto dataPacketSize = 20;
};


using PingArray = std::array<int, PacketSizes::pingPacketSize>;
using DataArray = std::array<int, PacketSizes::dataPacketSize>;


int main() {


    auto packet_array_ping = std::array<int, PacketSizes::pingPacketSize>{};
    auto packet_array_data = std::array<int, PacketSizes::dataPacketSize>{};


    PacketBuilder<PacketSlot::HEADER, PingArray>()
            .attachHeader<5>(packet_array_ping, 1,2,2,3,1)
            .attachPayload<10>(1,2,3,4,5,6,7,8,9,10)
            .attachCRC<1>();

    PacketBuilder<PacketSlot::HEADER, DataArray>()
            .attachHeader<5>(packet_array_data, 1,2,2,3,1)
            .attachPayload<10>(1,2,3,4,5,6,7,8,9,10)
            .attachCRC<1>();


    int ctr = 0;
    for(auto p_val: packet_array_ping){

        std::cout << "\nFIELD NR [" << ctr << "] -> " << p_val;
        ctr++;
    }


    return 0;
}