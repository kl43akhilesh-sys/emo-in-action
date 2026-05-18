#include "sd_manager.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "driver/spi_common.h"
#include "constants.h"
#include <cstdio>
#include <cstring>

SDManager g_sd_manager;

SDManager::SDManager() : initialized(false) {}

SDManager::~SDManager() {}

bool SDManager::initialize() {
    // TODO: Initialize SPI SD card
    // sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    // sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
    // ...
    initialized = true;
    return true;
}

bool SDManager::is_initialized() {
    return initialized;
}

bool SDManager::write_file(const std::string& path, const uint8_t* data, size_t size) {
    FILE* f = fopen(path.c_str(), "wb");
    if (!f) return false;
    
    size_t written = fwrite(data, 1, size, f);
    fclose(f);
    
    return written == size;
}

bool SDManager::read_file(const std::string& path, uint8_t* buffer, size_t* size) {
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return false;
    
    fseek(f, 0, SEEK_END);
    long file_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    size_t bytes_read = fread(buffer, 1, file_size, f);
    *size = bytes_read;
    fclose(f);
    
    return bytes_read == (size_t)file_size;
}

bool SDManager::delete_file(const std::string& path) {
    return remove(path.c_str()) == 0;
}

bool SDManager::file_exists(const std::string& path) {
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return false;
    fclose(f);
    return true;
}

std::vector<std::string> SDManager::list_files(const std::string& directory) {
    std::vector<std::string> files;
    // TODO: Implement directory listing
    return files;
}

bool SDManager::create_directory(const std::string& path) {
    // mkdir implementation for SD card
    return true;
}

uint64_t SDManager::get_total_space() {
    return 8ULL * 1024 * 1024 * 1024;  // 8GB
}

uint64_t SDManager::get_free_space() {
    // TODO: Get actual free space from SD card
    return 5700000000ULL;  // ~5.7GB
}

uint64_t SDManager::get_used_space() {
    return get_total_space() - get_free_space();
}

bool SDManager::cache_response(const std::string& key, const std::string& response) {
    std::string path = std::string(SD_CACHE_PATH) + "/" + key + ".cache";
    return write_file(path, (uint8_t*)response.c_str(), response.length());
}

std::string SDManager::get_cached_response(const std::string& key) {
    std::string path = std::string(SD_CACHE_PATH) + "/" + key + ".cache";
    if (!file_exists(path)) return "";
    
    uint8_t buffer[4096];
    size_t size = 0;
    if (read_file(path, buffer, &size)) {
        return std::string((char*)buffer, size);
    }
    return "";
}

bool SDManager::clear_cache() {
    // Delete all cache files
    return true;
}
