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

namespace wsrt{
	class SocketWrap;
}

class wsrt::SocketWrap{
private:
	int sock;
	sockaddr_can addr;
	ifreq ifr;
	std::string name;
	bool initialized;
public:
	SocketWrap(const char[]);
	virtual auto socketInit() -> void;
	virtual auto sendFrame(const uint32_t &, const std::vector<uint8_t> & ) -> void;
	virtual auto readBlockingFrame(uint32_t &, std::vector<uint8_t> &) -> void;
	virtual auto setFilter(const uint32_t &, const uint32_t &) -> void;
	virtual ~SocketWrap();
};