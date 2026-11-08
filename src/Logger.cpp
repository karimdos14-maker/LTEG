#include <iostream>
#include <fstream>
#include <string>

void Log(const std::string &message, const std::string &debug)
{
    std::ofstream file("Log.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cerr << "Failed to open Log.txt\n";
        return;
    }

    file << "[INFO] " << message << '\n';
    file << "[DEBUG]" << debug << '\n';
}