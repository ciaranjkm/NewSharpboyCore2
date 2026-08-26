#include <loader.h>

bool load_file(const std::filesystem::path& path, std::span<u8> buffer){
    //check file exists
    if(!std::filesystem::exists(path)){
        std::cerr << std::format("[ERROR @ load_file()] Failed to find {}\n", path.string());
        return false;
    }

    //check buffer size is correct to fit whole file
    size_t buffer_size = buffer.size();
    size_t file_size = std::filesystem::file_size(path);
    if(file_size > buffer_size){
        std::cerr << std::format("[ERROR @ load_file()] Buffer size exceeded, maximum {}, actual {}\n", buffer_size, file_size);
        return false;
    }

    //read file into buffer
    std::fstream target_file{path, std::fstream::in | std::fstream::binary};
    if(!target_file.is_open()){
        std::cerr << std::format("[ERROR @ load_file()] Failed to open file {}\n", path.string());
        return false;
    }

    target_file.read(reinterpret_cast<char*>(buffer.data()), file_size);
    return true;
}