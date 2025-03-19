#pragma once
#include <vector>

#define CAN_OK 0
#define CAN_ERR 1

#define UUID_MASK 0b11111111111111111

namespace wsrt
{
    class CAN {
        public:
        virtual int sendFrame(const uint32_t & header, const std::vector<uint8_t> & data) = 0;
        virtual int readBlockingFrame(uint32_t & header, std::vector<uint8_t> & data) = 0;
        virtual int setFilter(const uint32_t &, const uint32_t &) = 0;
        virtual int init(const int & timeout) = 0;

        virtual ~CAN() = default;
    };
} 
