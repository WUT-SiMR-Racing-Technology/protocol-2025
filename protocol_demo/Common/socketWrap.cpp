#include "socketWrap.hpp"



wsrt::SocketWrap::SocketWrap(const char _name[]) : sock{socket(PF_CAN, SOCK_RAW, CAN_RAW)}, addr{ }, ifr{ }, name{_name}, initialized{false}
	{
		if (sock < 0)
			throw std::runtime_error("Unable to create socket");
	}

auto wsrt::SocketWrap::init(const int & timeout) -> int
{
	strncpy(ifr.ifr_name, name.c_str(), IFNAMSIZ - 1);
	ioctl(sock, SIOCGIFINDEX, &ifr);
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;
	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
		throw std::runtime_error("Error binding socket");
	timeval tv = {};      
	tv.tv_sec = timeout;
	tv.tv_usec = 0;
	 if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
	 	throw std::runtime_error("Error setting timeout");
	initialized = true;
}
auto wsrt::SocketWrap::sendFrame(const uint32_t & identifier, const std::vector<uint8_t> & data) -> int
{
	if (not initialized)
		throw std::runtime_error("Socket not initialized");
	can_frame frame = { };
	frame.can_id = identifier;
	frame.can_id |= CAN_EFF_FLAG;
	if (data.size() > 8)
		throw std::runtime_error("Dataload too big (>8 bytes)");
	frame.can_dlc = data.size();
	std::copy(std::begin(data), std::end(data), std::begin(frame.data));
	if (write(sock, &frame, sizeof(can_frame)) != sizeof(can_frame))
		throw std::runtime_error("Unable to write"); 
}
auto wsrt::SocketWrap::readBlockingFrame(uint32_t & id, std::vector<uint8_t> & data) -> int
{
	if (not initialized)
		throw std::runtime_error("Socket not initialized");
	auto readBytes = int();
	can_frame frame = { };
	readBytes = read(sock, &frame, sizeof(can_frame)); //Blocking read
	if (readBytes < 0)
		throw std::runtime_error("Unable to read");
	id = frame.can_id;
	data.resize(frame.can_dlc);
	data.assign(reinterpret_cast<uint8_t*>(frame.data),	reinterpret_cast<uint8_t*>(frame.data) + frame.can_dlc);
	
}
auto wsrt::SocketWrap::setFilter(const uint32_t & _filter, const uint32_t & mask) -> int
{
	can_filter filter;
	filter.can_id = _filter;
	filter.can_mask = mask;
	if (setsockopt(sock, SOL_CAN_RAW, CAN_RAW_FILTER, &filter, sizeof(can_filter)) < 0)
		throw std::runtime_error("Unable to set filter");
}
wsrt::SocketWrap::~SocketWrap()
{
	if (sock >= 0)
		close(sock);
}