#include <iostream>
#include <bits/stdc++.h>
#include "commands.hpp"

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
    std::vector<std::string> tokens = tokenizeCommand(command);

    if (tokens[0] == "exit")
        return true;
    else if (tokens[0] == "help")
        printHelpMenu();
    else if(tokens[0] == "cd") 
        changeDirectory(tokens);
    else if(tokens[0] == "?") 
        showLastError();
    else if(tokens[0] == "rm")
        deleteFiles(tokens);
    else if(tokens[0] == "mv") 
        moveFile(tokens);
    else if(tokens[0] == "cp") 
        copyFile(tokens);
    else if(tokens[0] == "dir")
        listDirectory(tokens);
    else
        std::cout << "Command not found. Type 'help' for help." << std::endl;
    return false;
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