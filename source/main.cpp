// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <map>

// Include the main libnx system header, for Switch development
#include <switch.h>

// Include headers from other parts of the program
#include "controller.hpp"
#include "script_provider.hpp"
#include "script_populator.hpp"
#include "script_runner.hpp"

// Initialize frame counter variable
int frameCount = 0;

extern "C"
{
    // Sysmodules should not use applet*.
    u32 __nx_applet_type = AppletType_None;

    // Adjust size as needed.
    #define INNER_HEAP_SIZE 0x180000
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
        fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_SM));

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
        fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_HID));

    rc = fsInitialize();
    if (R_FAILED(rc))
        fatalThrow(MAKERESULT(Module_Libnx, LibnxError_InitFail_FS));

    fsdevMountSdmc();

    rc = hiddbgInitialize();
    if (R_FAILED(rc))
        fatalThrow(rc);

    // vsync
    rc = viInitialize(ViServiceType_System);
    if(R_FAILED(rc))
        fatalThrow(rc);
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
    // Init other services
    ViDisplay disp;
    Result rc = viOpenDefaultDisplay(&disp);
    if(R_FAILED(rc))
        fatalThrow(rc);

    Event vsync;

    rc = viGetDisplayVsyncEvent(&disp, &vsync);
    if(R_FAILED(rc))
        fatalThrow(rc);

    // Initialization code can go here.
    std::map<HidKeyboardScancode, std::string> scriptKeys;
    scriptKeys[KBD_F1] = "sdmc:/scripts/script1.txt";
    scriptKeys[KBD_F2] = "sdmc:/scripts/script2.txt";
    scriptKeys[KBD_F3] = "sdmc:/scripts/script3.txt";
    scriptKeys[KBD_F4] = "sdmc:/scripts/script4.txt";
    scriptKeys[KBD_F5] = "sdmc:/scripts/script5.txt";
    scriptKeys[KBD_F6] = "sdmc:/scripts/script6.txt";
    scriptKeys[KBD_F7] = "sdmc:/scripts/script7.txt";
    scriptKeys[KBD_F8] = "sdmc:/scripts/script8.txt";
    scriptKeys[KBD_F9] = "sdmc:/scripts/script9.txt";
    scriptKeys[KBD_F10] = "sdmc:/scripts/script10.txt";
    scriptKeys[KBD_F11] = "sdmc:/scripts/script11.txt";
    scriptKeys[KBD_F12] = "sdmc:/scripts/script12.txt";

    // Attach Work Buffer
    rc = hiddbgAttachHdlsWorkBuffer();
    if (R_FAILED(rc))
        fatalThrow(rc);

    // Start thread for populating script providers
    startPopulatorThread();

    // Your code / main loop goes here.
    while(true)
    {
        hidScanInput();

        for(std::map<HidKeyboardScancode, std::string>::iterator it = scriptKeys.begin(); it != scriptKeys.end(); ++it) {
            if(hidKeyboardDown(it->first)) {
                runScript(vsync, it->second);
                break;
            }
        }

        svcSleepThread(6250000);
    }

    rc = hiddbgReleaseHdlsWorkBuffer();

    hiddbgExit();
	
    return 0;
}
