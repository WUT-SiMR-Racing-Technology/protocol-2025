#include <vector>

namespace wsrt
{
    struct Channel{
            uint8_t number;
            uint8_t datatype;
            uint32_t maxFreq;
            uint32_t currFreq;
            std::vector<uint8_t> name;
            uint16_t unit;
    };
}
