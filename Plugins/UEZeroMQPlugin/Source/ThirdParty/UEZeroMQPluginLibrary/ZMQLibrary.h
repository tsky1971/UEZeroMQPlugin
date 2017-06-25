#if defined _WIN32 || defined _WIN64
#define DLLIMPORT __declspec(dllimport)
#else
#define DLLIMPORT
#endif

#include "ZmqManager.h"

DLLIMPORT void ZMQLibraryFunction();

DLLIMPORT ZmqManager * ZMQ_GetManager();