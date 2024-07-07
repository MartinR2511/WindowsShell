#include <vector>
#include <string>

std::string getCurrentWorkingDirectory();
void printHelpMenu();
void showLastError();
void changeDirectory(const std::vector<std::string>& tokens);
void deleteFiles(const std::vector<std::string>& tokens);
void moveFile(const std::vector<std::string>& tokens);
void copyFile(const std::vector<std::string>& tokens);
void listDirectory(const std::vector<std::string>& tokens);