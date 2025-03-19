#include "canthing.h"
#include "channel.h"

namespace wsrt
{
    class CANNotWork{
        CAN * _can;
        uint32_t _uuid;
        std::vector<uint8_t> _name;
        uint8_t _address;
        std::vector<uint8_t> dataBuff;
        uint32_t headBuff;


    public:
        int hello();
        int sendChannel(const std::vector<Channel> &);
        CANNotWork(CAN * can, const int & uuid, const std::vector<uint8_t> & name);
        ~CANNotWork();
    }
}