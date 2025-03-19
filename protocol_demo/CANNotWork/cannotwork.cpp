#include "cannotwork.h"

wsrt::CANNotWork::CANNotWork(CAN * can, const int & uuid, const std::vector<uint8_t> & name)
 : _can{can}, _uuid{UUID_MASK & uuid}, _name{name}, _address{0} {}

int wsrt::CANNotWork::hello() {
    uint32_t header = uint32_t((0x3 << 25) | (0x00 << 17) | _uuid);
    for (auto i = 0; i < 3; i++){
        if (_can->sendFrame(header, _name) != CAN_OK)
            continue;
        if (_can->readBlockingFrame(headBuff, dataBuff) != CAN_OK)
            continue;
        if ((headBuff & UUID_MASK) == _uuid and dataBuff.size() >= 1){
            _address = dataBuff[0];
            break;
        }
    }
    return _address != 0 ? CAN_OK : CAN_ERR;
}

int wsrt::CANNotWork::sendChannel(const std::vector<Channel> & channels){
    uint32_t header = uint32_t(0);
    auto data = std::vector<uint8_t>();
    for (auto i = 0; i < 20; i++){
        header = uint32_t((0x6 << 25) | (_address << 17));
        data.resize(1);
        data[0] = channels.size();
        if (_can->sendFrame(header, data) != CAN_OK)
            continue;
        for (const auto & ch : channels){
            header = uint32_t((0x6 << 25) | (_address << 17) | (ch.number << 9));
            data.resize(1);
            data[0] = ch.datatype;
            if (_can->sendFrame(header, data) != CAN_OK)
                break;
            header |= 0b1;
            data.resize(8);
            memcpy(&data[0], &ch.maxFreq, sizeof(ch.maxFreq));
            memcpy(&data[0], &ch.maxFreq, sizeof(ch.currFreq));
            if (_can->sendFrame(header, data) != CAN_OK)
                break;
            
        }
    }
}