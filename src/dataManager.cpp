#include "dataManager.h"
#include "configManager.h"

#include "uuid.h" // stduuid lib

#include <iostream>
#include <string>
#include <filesystem>

// #############
// #   Paths   #
// #############
namespace fs = std::filesystem;
const std::string DataMan::PATH_DIR_DATA =    "data/";
const std::string DataMan::PATH_DIR_DB =      PATH_DIR_DATA + "db/";
const std::string DataMan::PATH_FILE_CONFIG = PATH_DIR_DATA + "grimoire.config";
void DataMan::ValidateDataPaths() {
    std::function<void(const std::string&, bool)> check = [](const std::string path, bool isDir) {
        if (fs::exists(path)) {
            // std::cout << "Path Exists: " + path << std::endl;
            return;
        }

        if (isDir) {
            fs::create_directory(path);
            // std::cout << "Created Dir: " + path << std::endl;
            return;
        } else {
            std::ofstream file(path);
            file.close();
            // std::cout << "Created File: " + path << std::endl;
            return;
        }
        // std::cout << "Failed Path Creation: " + path << std::endl;
    };

    check(PATH_DIR_DATA, true);
    check(PATH_DIR_DB, true);
    check(PATH_FILE_CONFIG, false);
}

std::string DataMan::GetPath_Config() {
    return PATH_FILE_CONFIG;
}
std::string DataMan::GetPath_DB() {
    return PATH_DIR_DB;
}

// ############
// #   UUID   #
// ############
std::string DataMan::CreateUUIDString() {
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19937::state_size> {};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    std::mt19937 generator(seq);
    uuids::uuid_random_generator gen{generator};

    return uuids::to_string(gen());
}




void DataMan::Test() {

}
