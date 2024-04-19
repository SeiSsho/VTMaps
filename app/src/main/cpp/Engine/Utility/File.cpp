#include "File.h"

bool Engine::Utility::File::ReadContentFromFile(const std::filesystem::path &path,
                                                std::string &content) {
    if (!std::filesystem::exists(path))
        return false;
    std::ifstream file(path, std::ios::binary | std::ios::in);
    uintmax_t fileSize = std::filesystem::file_size(path);
    content.assign(fileSize, '\0');
    file.read(&content[0], fileSize);
    return true;
}
