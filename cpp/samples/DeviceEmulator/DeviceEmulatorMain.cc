#include "DeviceEmulator.h"

int CDECL_CALL main(int argc, char** argv)
{
    if (argc != 2) {
        cout << "Argument(xml file path) is needed" << endl;
        return 0;
    }

    ajn::services::DeviceEmulator emulator(argv[1]);

    emulator.Startup();

    emulator.Shutdown();


    return 0;
}
