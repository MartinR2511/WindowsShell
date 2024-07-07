#include "commands.hpp"
#include <string>
#include <windows.h>
#include <iostream>

std::string getCurrentWorkingDirectory()
{
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    return std::string(buffer);
}

void printHelpMenu()
{
    std::cout << "exit - exit the shell" << std::endl;

    std::cout << "cd - change directory" << std::endl;
    std::cout << "? - show last error" << std::endl;
    std::cout << "rm - delete file" << std::endl;
    std::cout << "mv - move file" << std::endl;
    std::cout << "cp - copy file" << std::endl;
    std::cout << "dir - list directory" << std::endl;

    std::cout << "help - show this message" << std::endl << std::endl;
}

void changeDirectory(const std::vector<std::string>& tokens)
{
    if (tokens.size() != 2)
        std::cout << "Usage: cd <directory>" << std::endl;
    else if (!SetCurrentDirectoryA(tokens[1].c_str()))
        showLastError();
}

void showLastError()
{
    LPSTR messageBuffer = nullptr;
    //Get the error message ID, if any.
    DWORD errorMessageID = GetLastError();
 
    if(errorMessageID != 0)
    {

        //Ask Win32 to give us the string version of that message ID.
        //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                    NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
        
        //Copy the error message into a std::string.
        std::cout << "Error: " << messageBuffer;
        
        //Free the Win32's string's buffer.
        LocalFree(messageBuffer);
    }
    else
        std::cout << "No error message has been recorded" << std::endl;

    
            
}
void deleteFiles(const std::vector<std::string>& tokens)
{
    for (long long unsigned int i = 1; i < tokens.size(); i++)
        if (!DeleteFile(tokens[i].c_str()))
            showLastError();
}

void moveFile(const std::vector<std::string>& tokens)
{
    if (tokens.size() != 3)
        std::cout << "Usage: mv <source> <destination>" << std::endl;
    else if (!MoveFile(tokens[1].c_str(), tokens[2].c_str()))
        showLastError();
}

void copyFile(const std::vector<std::string>& tokens)
{
    if (tokens.size() != 3)
        std::cout << "Usage: cp <source> <destination>" << std::endl;
    else if (!CopyFile(tokens[1].c_str(), tokens[2].c_str(), false))
        showLastError();
}

void listDirectory(const std::vector<std::string>& tokens)
{
    std::string directory;
    WIN32_FIND_DATA fileData;
    HANDLE hFind;
    
    if(tokens.size() > 2)
        std::cout << "Usage: dir [directory]" << std::endl;
    else
    {
        if(tokens.size() == 2)
            directory = tokens[1];
        else
            directory = getCurrentWorkingDirectory();

        std::string searchPath = directory + "\\*.*";
        hFind = FindFirstFileA(searchPath.c_str(), &fileData);

        std::cout << "Type\tSize\tName" << std::endl;
        std::cout << "----\t----\t----" << std::endl;

        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    std::cout << "FILE";
                else
                    std::cout << "DIR ";
                std::cout << "\t" << fileData.nFileSizeLow << "\t" << fileData.cFileName  << std::endl;
            } while (FindNextFileA(hFind, &fileData));

            FindClose(hFind);
        }
        else
        {
            std::cout << "Failed to list directory" << std::endl;
        }
    }
}