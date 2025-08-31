#pragma once
#include "uuid.h" // stduuid lib
#include "sqlite3.h"
#include <vector>

class DataMan {
private:
    DataMan() = delete;
    ~DataMan() = delete;

    static sqlite3* selectedDB;
    static std::string Path_File_SelectedDB;

    static const std::string PATH_BASE;
    static const std::string PATH_DIR_DATA;
    static const std::string PATH_DIR_DB;
    static const std::string PATH_FILE_CONFIG;

    struct DocData {
        enum enum_EncodeType {
            NONE
        };

        std::string DocUUID;
        std::string Title;
        std::string PlainText;
        enum_EncodeType EncodeType;
        std::string EncodeKey;
        std::string MetaData;
    };
    struct HistoryData {
        std::string HistoryUUID;
        DocData Data;
    };

    static std::string CreateUUIDString();
public:
    /*
     * CREATE FILE
     * SAVE FILE
     * LOAD FILE
     * DELETE FILE
     */

    // PATHS
    static void ValidateDefaultPaths();
    static bool Get_FilePathExists(std::string path);
    static std::string Get_NameFromPath(std::string path);
    static std::string Get_StemFromPath(std::string path);
    static std::string GetPath_DB();
    static std::vector<std::string> Get_DBFilePaths();
    static std::string GetPath_Config();

    //GRIMOIRE (DB)
    static std::string DB_GetSelectedDB();
    static void DB_Load(std::string path);
    static bool DB_Create(std::string path);
    static void DB_Delete(std::string path);
    static void DB_Rename(std::string oldPath, std::string newPath);
};
