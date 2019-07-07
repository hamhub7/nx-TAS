// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

// Include the main libnx system header, for Switch development
#include <switch.h>

// Include headers from other parts of the program
#include "controller.hpp"

extern "C"
{
    // Sysmodules should not use applet*.
    u32 __nx_applet_type = AppletType_None;

    // Adjust size as needed.
    #define INNER_HEAP_SIZE 0x80000
    size_t nx_inner_heap_size = INNER_HEAP_SIZE;
    char   nx_inner_heap[INNER_HEAP_SIZE];

    void __libnx_init_time(void);
    void __libnx_initheap(void);
    void __appInit(void);
    void __appExit(void);
}

void __libnx_initheap(void)
{
	void*  addr = nx_inner_heap;
	size_t size = nx_inner_heap_size;

	// Newlib
	extern char* fake_heap_start;
	extern char* fake_heap_end;

	fake_heap_start = (char*)addr;
	fake_heap_end   = (char*)addr + size;
}

// Init/exit services, update as needed.
void __attribute__((weak)) __appInit(void)
{
    Result rc;

    // Initialize default services.
    rc = smInitialize();
    if (R_FAILED(rc))
        fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));

    rc = setsysInitialize();
    if (R_SUCCEEDED(rc)) {
        SetSysFirmwareVersion fw;
        rc = setsysGetFirmwareVersion(&fw);
        if (R_SUCCEEDED(rc))
            hosversionSet(MAKEHOSVERSION(fw.major, fw.minor, fw.micro));
        setsysExit();
    }

    // HID
    rc = hidInitialize();
    if (R_FAILED(rc))
        fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_HID));

    rc = fsInitialize();
    if (R_FAILED(rc))
        fatalSimple(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

    fsdevMountSdmc();

    rc = hiddbgInitialize();
    if (R_FAILED(rc))
        fatalSimple(rc);
}

void __attribute__((weak)) userAppExit(void);

void __attribute__((weak)) __appExit(void)
{
    // Cleanup default services.
    fsdevUnmountAll();
    fsExit();
    hidExit();
    smExit();
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    // Initialization code can go here.
    std::vector<TasController*> controllers;

    // Your code / main loop goes here.
    // If you need threads, you can use threadCreate etc.
    while(true)
    {
        hidScanInput();

        if(hidKeyboardDown(KBD_0))
        {
            controllers.push_back(new TasController());
        }

        if(hidKeyboardDown(KBD_9))
        {
            delete controllers.back();
            controllers.pop_back();
        }

        svcSleepThread(6250000);
    }

    // Deinitialization and resources clean up code can go here.
    return 0;
}