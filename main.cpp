#include <windows.h>
#include <iostream>
#include <bits/stdc++.h>

void printInitMessage()
{
    // TODO: Print version of windows
    std::cout << "(c) Ruby Corporation. All rights reserved." << std::endl;
}

void printHelpMenu()
{
    std::cout << "exit - exit the shell" << std::endl;

    std::cout << "cd - change directory" << std::endl;
    std::cout << "? - show last error" << std::endl;
    std::cout << "rm - delete file" << std::endl;
    std::cout << "mv - move file" << std::endl;
    std::cout << "cp - copy file" << std::endl;
    std::cout << "dir - print directory" << std::endl;

    std::cout << "help - show this message" << std::endl;

}

std::vector<std::string> tokenizeCommand(std::string command)
{
    std::vector<std::string> tokens;
    std::stringstream stream(command);
    std::string token;

    // sepparate commands into tokens by space
    while (std::getline(stream, token, ' '))
    {
        if (token.empty())
            continue;
        // if token starts with " and does not end with " concatenate with next token untill it ends with "
        if (token.front() == '"' && token.back() != '"')
        {
            std::string nextToken;
            while (std::getline(stream, nextToken, ' '))
            {
                token += ' ' + nextToken;
                if (nextToken.back() == '"')
                    break;
            }
        }
        tokens.push_back(token);
    }
    return tokens;
}

bool handleCommand(std::string command)
{
    std::vector<std::string> tokens = tokenizeCommand(command);

    if (tokens[0] == "exit")
        return true;
    else if (tokens[0] == "help")
        printHelpMenu();
    else if(tokens[0] == "cd") {}
    else if(tokens[0] == "?") {}
    else if(tokens[0] == "rm") {}
    else if(tokens[0] == "mv") {}
    else if(tokens[0] == "cp") {}
    else if(tokens[0] == "dir") {}
    else
        std::cout << "Command not found. Type 'help' for help." << std::endl;
    return false;
}

int main()
{
    bool exit = false;

    printInitMessage();
    //get current working directory, MAX_PATH is defined by windows
    char cwd[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, cwd);

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