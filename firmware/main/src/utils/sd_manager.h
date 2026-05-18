#ifndef SD_MANAGER_H
#define SD_MANAGER_H

#include <string>
#include <vector>
#include <stdint.h>

class SDManager {
public:
    SDManager();
    ~SDManager();
    
    bool initialize();
    bool is_initialized();
    
    bool write_file(const std::string& path, const uint8_t* data, size_t size);
    bool read_file(const std::string& path, uint8_t* buffer, size_t* size);
    bool delete_file(const std::string& path);
    bool file_exists(const std::string& path);
    
    std::vector<std::string> list_files(const std::string& directory);
    bool create_directory(const std::string& path);
    
    uint64_t get_total_space();
    uint64_t get_free_space();
    uint64_t get_used_space();
    
    // Cache operations
    bool cache_response(const std::string& key, const std::string& response);
    std::string get_cached_response(const std::string& key);
    bool clear_cache();
    
private:
    bool initialized;
};

extern SDManager g_sd_manager;

#endif // SD_MANAGER_H
