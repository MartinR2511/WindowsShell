#include <windows.h>
#include <iostream>

#define MAX_PATH_LENGTH 1024

void printInitMessage()
{
    // TODO: Print version of windows
    std::cout << "(c) Ruby Corporation. All rights reserved." << std::endl;
}

bool handleCommand(std::string command)
{
    if (command == "exit")
    {
        return true;
    }
    else if (command == "help")
    {
        std::cout << "exit - exit the shell" << std::endl;
        std::cout << "help - show this message" << std::endl;
    }
    else
    {
        std::cout << "Command not found. Type 'help' for help." << std::endl;
    }
    return false;
}

int main()
{
    bool exit = false;

    printInitMessage();
    //get current working directory
    char cwd[MAX_PATH_LENGTH];
    GetCurrentDirectoryA(MAX_PATH_LENGTH, cwd);

    //mainloop
    while (!exit)
    {
        std::string command;
        std::cout << "RS " << cwd << "> ";
        std::getline(std::cin, command);
        exit = handleCommand(command);
    }
    return 0;
}