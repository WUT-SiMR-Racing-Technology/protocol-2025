#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>
#include <array>

#include "../CANNotWork/canthing.h"

namespace wsrt{
	class SocketWrap;
}

class wsrt::SocketWrap : public wsrt::CAN{
private:
	int sock;
	sockaddr_can addr;
	ifreq ifr;
	std::string name;
	bool initialized;
public:
	SocketWrap(const char[]);
	virtual auto init(const int & timeout) -> int override;
	virtual auto sendFrame(const uint32_t &, const std::vector<uint8_t> & ) -> int override;
	virtual auto readBlockingFrame(uint32_t &, std::vector<uint8_t> &) -> int override;
	virtual auto setFilter(const uint32_t &, const uint32_t &) -> int override;
	virtual ~SocketWrap();
};