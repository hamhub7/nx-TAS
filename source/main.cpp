// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>

// Include the main libnx system header, for Switch development
#include <switch.h>

// Include headers from other parts of the program
#include "controller.hpp"
#include "script_provider.hpp"
#include "script_populator.hpp"

// Create VSync event
Event vsync_event;

// Initialize frame counter variable
int frameCount = 0;

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

void frameIncrement(void* _)
{
    while(true)
    {
        // Wait for a new frame...
        Result rc = eventWait(&vsync_event, U64_MAX);
        if(R_FAILED(rc))
            fatalThrow(rc);

        // ... Then increment the counter
        ++frameCount;
    }
}

uint8_t bodyR, bodyG, bodyB, buttonR, buttonG, buttonB;
void initConfig(std::string filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ifstream::in);

    // Just using 0 as the "Invalid File" exception
    try
    {
        if(!ifs.is_open) { throw 0; }

        //FIXME: This is kinda hardcoded, might fix later
        std::string line;
        // Line 1: "Body Colors: 255 255 255"
        std::getline(ifs, line);
        size_t pos = line.find(" ");
        std::string prefix = line.substr(0, pos);
        if(prefix != "Body Colors:") { throw 0; }
        line.erase(0, pos + 1);
        for(int i = 0; i < 3; i++)
        {
            //TODO: Add verifier that each of these is an valid number, then write them to bodyR, bodyG, and bodyB
        }
        //TODO: Add same thing, but for button colors
    }
    catch(int e)
    {
        // Create the file since it doesn't exist or won't open or in the wrong format
        std::ofstream ofs;
        ofs.open("sdmc:scripts/config/config.txt", std::ofstream::out | std::ofstream::trunc);
        ofs << "Body Colors: 255 255 255" << std::endl;
        ofs << "Button Colors: 0 0 0" << std::endl;
        ofs.close();
    }
}

// Main program entrypoint
int main(int argc, char* argv[])
{
    // Init other services
    ViDisplay disp;
    Result rc = viOpenDefaultDisplay(&disp);
    if(R_FAILED(rc))
        fatalThrow(rc);

    rc = viGetDisplayVsyncEvent(&disp, &vsync_event);
    if(R_FAILED(rc))
        fatalThrow(rc);

    // Initialization code can go here.
    std::vector<TasController*> controllers;
    //TODO: initConfig("sdmc:/scripts/config.txt");

    // Attach Work Buffer
    rc = hiddbgAttachHdlsWorkBuffer();
    if (R_FAILED(rc))
        fatalThrow(rc);

    // Create new thread for counting frames
    // Commented out as it was stealing vsync events from the script runner
    /*
    Thread countThread;
    rc = threadCreate(&countThread, frameIncrement, NULL, 0x4000, 49, 3);
    if(R_FAILED(rc))
        fatalThrow(rc);
    rc = threadStart(&countThread);
    if(R_FAILED(rc))
        fatalThrow(rc);
    */

    // Start thread for populating script providers
    startPopulatorThread();

    // Your code / main loop goes here.
    while(true)
    {
        hidScanInput();

        if(hidKeyboardDown(KBD_F1))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script1.txt");
            }
        }

        if(hidKeyboardDown(KBD_F2))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script2.txt");
            }
        }

        if(hidKeyboardDown(KBD_F3))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script3.txt");
            }
        }

        if(hidKeyboardDown(KBD_F4))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script4.txt");
            }
        }

        if(hidKeyboardDown(KBD_F5))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script5.txt");
            }
        }

        if(hidKeyboardDown(KBD_F6))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script6.txt");
            }
        }

        if(hidKeyboardDown(KBD_F7))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script7.txt");
            }
        }

        if(hidKeyboardDown(KBD_F8))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script8.txt");
            }
        }

        if(hidKeyboardDown(KBD_F9))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script9.txt");
            }
        }

        if(hidKeyboardDown(KBD_F10))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script10.txt");
            }
        }

        if(hidKeyboardDown(KBD_F11))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script11.txt");
            }
        }

        if(hidKeyboardDown(KBD_F12))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->runScript<LineFileScriptProvider>("sdmc:/scripts/script12.txt");
            }
        }

        if(hidKeyboardDown(KBD_Q))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->pressLR();
            }
        }

        if(hidKeyboardDown(KBD_W))
        {
            if(controllers.size() > 0)
            {
                controllers.front()->pressA();
            }
        }

        if(hidKeyboardDown(KBD_1))
        {
            if(controllers.size() < 8)
                controllers.push_back(new TasController(HidDeviceType_FullKey3, 255, 255, 255, 0, 0, 0));
        }

        if(hidKeyboardDown(KBD_2))
        {
            if(controllers.size() < 7)
            {
                controllers.push_back(new TasController(HidDeviceType_JoyLeft2, 255, 255, 255, 0, 0, 0));
                controllers.push_back(new TasController(HidDeviceType_JoyRight1, 0, 0, 0, 255, 255, 255));
            }
        }

        if(hidKeyboardDown(KBD_3))
        {
            if(controllers.size() < 8)
                controllers.push_back(new TasController(HidDeviceType_JoyLeft2, 0, 0, 0, 255, 255, 255));
        }

        if(hidKeyboardDown(KBD_4))
        {
            if(controllers.size() < 8)
                controllers.push_back(new TasController(HidDeviceType_JoyRight1, 0, 0, 0, 255, 255, 255));
        }

        if(hidKeyboardDown(KBD_5))
        {
            if(controllers.size() < 8)
                controllers.push_back(new TasController(HidDeviceType_LarkLeftHVC, 0, 0, 0, 255, 255, 255));
        }

        if(hidKeyboardDown(KBD_6))
        {
            if(controllers.size() < 8)
                controllers.push_back(new TasController(HidDeviceType_LarkRightHVC, 0, 0, 0, 255, 255, 255));
        }

        if(hidKeyboardDown(KBD_7))
        {
            if(controllers.size() < 8)
                controllers.push_back(new TasController(HidDeviceType_LarkLeftNES, 0, 0, 0, 255, 255, 255));
        }

        if(hidKeyboardDown(KBD_8))
        {
            if(controllers.size() < 8)
                controllers.push_back(new TasController(HidDeviceType_System19, 0, 0, 0, 255, 255, 255));
        }

        if(hidKeyboardDown(KBD_MINUS))
        {
            if(controllers.size() > 0)
            {
                delete controllers.back();
                controllers.pop_back();
            }
        }

        svcSleepThread(6250000);
    }

    rc = hiddbgReleaseHdlsWorkBuffer();

    hiddbgExit();
	
    return 0;
}
