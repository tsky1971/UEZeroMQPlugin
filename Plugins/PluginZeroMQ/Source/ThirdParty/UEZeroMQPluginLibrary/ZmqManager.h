#pragma once

#if defined DLL_LIBRARY
#define ZMQ_LIB_API __declspec(dllimport)
#else
#define ZMQ_LIB_API __declspec(dllexport)
#endif

class ZMQ_LIB_API ZmqManager
{
public:
	ZmqManager();
	virtual ~ZmqManager();
};

