#include <iostream>
#include "PacketBuilder.h"

int main() {

    auto packet_array = std::array<int, ConfigOptions::packetSize>{};

    PacketBuilder<PacketSlot::HEADER, int> build;

    build.attachHeader<5>(packet_array, 1,2,2,3,1)
            .attachPayload<10>(1,2,3,4,5,6,7,8,9,10)
            .attachCRC<1>();

    int ctr = 0;
    for(auto p_val: packet_array){

        std::cout << "\nFIELD NR [" << ctr << "] -> " << p_val;
        ctr++;
    }




    return 0;
}