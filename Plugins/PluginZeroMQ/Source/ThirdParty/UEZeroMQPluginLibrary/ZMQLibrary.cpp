#if defined _WIN32 || defined _WIN64
    #include <Windows.h>

    #define DLLEXPORT __declspec(dllexport)
#else
    #include <stdio.h>
#include "ZMQLibrary.h"
#endif

#ifndef DLLEXPORT
    #define DLLEXPORT
#endif

#include "ZmqManager.h"

DLLEXPORT void ZMQLibraryFunction()
{
#if defined _WIN32 || defined _WIN64
	MessageBox(NULL, TEXT("Hello world!"), NULL, MB_OK);
#else
    printf("Hello World");
#endif
}

DLLEXPORT ZmqManager * ZMQ_GetManager()
{
	ZmqManager *m = new ZmqManager();
	return m;
}
