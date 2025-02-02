#include <iostream>
#include <string>


#include "../Common/socketWrap.hpp"

auto main(int argc, char * argv[]) -> int
{
    using namespace wsrt;
    if (argc < 2){
        std::cout << "Provide CAN name";
        return 1;
    }
    auto senderSocket = SocketWrap(argv[1]);
    senderSocket.socketInit();

    auto id_res = uint32_t();
    auto data_res = std::vector<uint8_t>(8);

    senderSocket.readBlockingFrame(id_res, data_res);
    printf("Received id 0x%x 0x%x 0x%x\n", (id_res >> 25) & 0xF, (id_res >> 17) & 0xFF, id_res & 0b11111111111111111);
    for (auto data : data_res){
        std::cout << data;
    }
    std::cout << std::endl;

    auto uuid  = uint32_t(0x52EE2D8  & 0b11111111111111111);
    auto id_hello = uint32_t((0x4 << 25) | (0xFF << 17) | uuid);
    auto data_hello = std::vector<uint8_t>{0x12};

    senderSocket.sendFrame(id_hello, data_hello);
    printf("Sent id 0x%x 0x%x 0x%x\n", (id_hello >> 25) & 0xF, (id_hello >> 17) & 0xFF, id_hello & 0b11111111111111111);

    return 0;
}