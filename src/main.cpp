#include <iostream>
#include "PacketBuilder.h"



int main() {

    auto packet_array = std::array<int, ConfigOptions::packetSize>{};

    PacketBuilder<PacketSlot::HEADER, int> build;

    auto ready_frame = build.attachHeader(packet_array)
         .attachPayload()
         .attachCRC();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}