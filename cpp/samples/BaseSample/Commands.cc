#include "Commands.h"
#include <iostream>
#include <limits>
#include <stdlib.h>

Commands::Commands()
{
}

Commands::~Commands()
{
    std::map<std::string, Commands*>::iterator itr = m_Children.begin();
    while (itr != m_Children.end()) {
        delete itr->second;
        ++itr;
    }
}

bool Commands::RegisterCommand(CommandFunc func, const std::string& command, const std::string& description)
{
    m_Commands[command].command = command;
    m_Commands[command].description = description;
    m_Commands[command].func = func;

    return true;
}

bool Commands::RegisterChildCommands(const std::string& key, Commands* commands)
{
    m_Children[key] = commands;
    return true;
}

bool Commands::UnregisterCommand(const std::string& name)
{
    uint32_t numErased = m_Commands.erase(name);
    return (numErased != 0);
}

bool Commands::UnregisterChildCommands(const std::string& key)
{
    uint32_t numErased = m_Children.erase(key);
    return (numErased != 0);
}

void Commands::PrintCommandList()
{
    CommandFuncMap::const_iterator itr = m_Commands.begin();

    std::cout << "==============================================================" << std::endl;
    while (itr != m_Commands.end()) {
        std::cout << itr->first << " : " << itr->second.description << std::endl;
        ++itr;
    }
    std::cout << "==============================================================" << std::endl;
}

std::string Commands::GetCommandToken(std::string& cmd, std::string& remain)
{
    std::string::size_type pos = cmd.find_first_of(' ');
    std::string token;
    if (pos == (std::string::size_type)-1) {
        token = cmd;
        remain = "";
    } else {
        token = cmd.substr(0, pos);
        remain = cmd.substr(pos + 1, cmd.length());
    }
    return token;
}

int Commands::GetCommandTokenInt(std::string& cmd, std::string& remain)
{
    std::string temp = GetCommandToken(cmd, remain);
    return atoi(temp.c_str());
}

int Commands::ReadIndex()
{
    int index = 0;
    std::cout << "select index: ";
    std::cin >> index;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return index;
}

Commands* Commands::GetChild(const std::string& key)
{
    if (m_Children.find(key) != m_Children.end()) {
        return m_Children[key];
    }
    return 0;
}

ChildCommandMap& Commands::GetChildren()
{
    return m_Children;
}