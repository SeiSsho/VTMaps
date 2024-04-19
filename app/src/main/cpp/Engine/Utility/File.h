#ifndef VTMAPS_FILE_H
#define VTMAPS_FILE_H

#include <filesystem>
#include <string>
#include <fstream>

namespace Engine::Utility {
    class File {
    public:
        static bool ReadContentFromFile(const std::filesystem::path& path, std::string& content);
    };
}

#endif //VTMAPS_FILE_H
