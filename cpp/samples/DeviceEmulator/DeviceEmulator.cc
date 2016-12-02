/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include <iostream>
#include <qcc/String.h>

#include <alljoyn/cdm/util/CdmSystem.h>
#include <alljoyn/cdm/util/CdmAnnouncer.h>
#include <alljoyn/cdm/util/CdmSecurity.h>

#include "Config.h"
#include "Commands.h"
#include "SuperControllee.h"
#include "../Utils/HAL.h"

using namespace qcc;
using namespace ajn;
using namespace services;

using std::string;
typedef std::vector<std::string> StringVec;

//======================================================================

static bool s_quit = false;

static bool HelpCommand(const string& key, const StringVec& args, CdmControllee&)
{
    for (auto& h : emulator::Commands::Instance().Help())
    {
        std::cout << h << "\n";
    }
    return true;
}



static bool QuitCommand(const string& key, const StringVec& args, CdmControllee&)
{
    s_quit = true;
    return true;
}



static void CommandLoop(Ref<emulator::SuperControllee> supercontrollee)
{
    auto& cmds = emulator::Commands::Instance();
    auto& clee = supercontrollee->GetControllee();

    cmds.Subscribe("help", HelpCommand, "help");
    cmds.Subscribe("h",    HelpCommand, "h - help");
    cmds.Subscribe("quit", QuitCommand, "quit");
    cmds.Subscribe("q",    QuitCommand, "q - quit");

    // testing cin detects an eof (^D)
    while (!s_quit && std::cin)
    {
        string line;
        std::cout << "emul> ";
        std::getline(std::cin, line);
        if (!line.empty() && !cmds.Publish(line, clee))
        {
            std::cout << "Failed\n";
        }
    }
}



int CDECL_CALL main(int argc, char** argv)
{
    std::string configFile;

    if (argc < 2)
    {
        std::cerr << "Usage: DeviceEmulator xml-file\n";
        return 1;
    }

    emulator::Config config(argv[1]);

    if (!config.IsValid())
    {
        std::cerr << "Invalid XML file: " << argv[1] << "\n";
        return 1;
    }

    HAL::SetRootDir("/tmp/dev_emul");

    CdmSystem system("DeviceEmulator");

    QStatus status = system.Start();

    if (status != ER_OK) {
        std::cerr << "Failed to start the DeviceEmulator " << QCC_StatusText(status) << "\n";
        return 1;
    }

    auto device = mkRef<emulator::SuperControllee>(system.GetBusAttachment(), config, "device_emulator_certs/security");

    status = device->Start();
    if (status != ER_OK) {
        std::cerr << "Failed to start the DeviceEmulator " << QCC_StatusText(status) << "\n";
        return 1;
    }

    CommandLoop(device);

    device->Stop();
    return 0;
}
