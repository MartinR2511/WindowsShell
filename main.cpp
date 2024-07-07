#include <iostream>
#include <bits/stdc++.h>
#include <unordered_map>
#include <functional>
#include "commands.hpp"

// map of commands and their functions
std::unordered_map<std::string, std::function<void(std::vector<std::string>)>> commandMap = 
{
    {"cd", changeDirectory},
    {"?", [](std::vector<std::string> args){ static_cast<void>(args); showLastError(); }},
    {"rm", deleteFiles},
    {"mv", moveFile},
    {"cp", copyFile},
    {"dir", listDirectory},
    {"help", [](std::vector<std::string> args){ static_cast<void>(args); printHelpMenu(); }}
};

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
            // remove " from the start and the end of the token
            token.erase(0,1);
            token.pop_back();
        }
        tokens.push_back(token);
    }
    return tokens;
}



bool handleCommand(std::string command)
{
    bool isExit = false;
    std::vector<std::string> tokens = tokenizeCommand(command);

    //find command in the map and execute it
    auto it = commandMap.find(tokens[0]);
    if (it != commandMap.end())
        it->second(tokens);
    else if(tokens[0] == "exit")
        isExit = true;
    else
        std::cout << "Command not found. Type 'help' for help." << std::endl;

    return isExit;
}

int main()
{
    bool exit = false;

    std::cout << "(c) Ruby Corporation. All rights reserved." << std::endl;
    //get current working directory, MAX_PATH is defined by windows
    std::string command;

    //mainloop
    while (!exit)
    {
        std::cout << "RS " << getCurrentWorkingDirectory() << "> ";
        std::getline(std::cin, command);
        exit = handleCommand(command);
    }
    return 0;
}