#include "dataManager.h"
#include "configManager.h"

#include "uuid.h" // stduuid lib
#include "sqlite3.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

sqlite3* DataMan::selectedDB;

// #############
// #   Paths   #
// #############
namespace fs = std::filesystem;
const std::string DataMan::PATH_BASE = []() -> std::string {
    #ifdef _WIN32
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    return std::filesystem::path(path).parent_path().string();
    #elif __linux__
    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
    if (count == -1) throw std::runtime_error("Failed to read executable path");
    return std::filesystem::path(std::string(path, count)).parent_path().string();
    #else
    throw std::runtime_error("Unsupported platform");
    #endif
}() + "/";
const std::string DataMan::PATH_DIR_DATA =    PATH_BASE +     "data/";
const std::string DataMan::PATH_DIR_DB =      PATH_DIR_DATA + "db/";
const std::string DataMan::PATH_FILE_CONFIG = PATH_DIR_DATA + "grimoire.config";
void DataMan::ValidateDefaultPaths() {
    std::function<void(const std::string&, bool)> check = [](const std::string path, bool isDir) {
        if (fs::exists(path)) {
            return;
        }

        if (isDir) {
            fs::create_directory(path);
            return;
        } else {
            std::ofstream file(path);
            file.close();
            return;
        }
    };

    check(PATH_DIR_DATA, true);
    check(PATH_DIR_DB, true);
    check(PATH_FILE_CONFIG, false);
}
std::string DataMan::Path_File_SelectedDB;


bool DataMan::Get_FilePathExists(std::string path) {
    return (fs::exists(path)) ? true : false;
}
std::string DataMan::Get_NameFromPath(std::string path) {
    fs::path p = path;
    return p.filename();
}
std::string DataMan::Get_StemFromPath(std::string path) {
    fs::path p = path;
    return p.stem();
}
std::string DataMan::GetPath_Config() {
    return PATH_FILE_CONFIG;
}
std::string DataMan::GetPath_DB() {
    return PATH_DIR_DB;
}
std::vector<std::string> DataMan::Get_DBFilePaths() {
    std::vector<std::string> entries;
    for (const std::filesystem::directory_entry& entry : fs::directory_iterator(DataMan::GetPath_DB())) {
        if (entry.path().extension() == ".db") {
            entries.push_back(entry.path().filename());
        }
    }
    return entries;
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

// ##########
// #   DB   #
// ##########
std::string DataMan::DB_GetSelectedDB() {
    return Path_File_SelectedDB;
}
void DataMan::DB_Load(std::string path) {
    Path_File_SelectedDB = path;
}
bool DataMan::DB_Create(std::string path) {
    const char* cpath = path.c_str();
    int dbCode = sqlite3_open(cpath, &selectedDB);
    sqlite3_close(selectedDB);
    if (dbCode != SQLITE_OK) {
        return false;
    }
    return true;
}
void DataMan::DB_Rename(std::string oldPath, std::string newPath) {
    fs::rename(oldPath, newPath);
}
void DataMan::DB_Delete(std::string path) {
    if (fs::is_directory(path)) {
        return;
    }
    fs::remove(path);
}
