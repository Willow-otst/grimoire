#pragma once
#include "uuid.h" // stduuid lib
#include "sqlite3.h"
#include <vector>

#include <iostream>

class DataMan {
private:
    DataMan() = delete;
    ~DataMan() = delete;

    static std::string Path_File_SelectedDB;

    static const std::string PATH_BASE;
    static const std::string PATH_DIR_DATA;
    static const std::string PATH_DIR_DB;
    static const std::string PATH_FILE_CONFIG;

public:
    // std::cout << "=============| DocData |============\n"
    // << "DocUUID: " << data.DocUUID << "\n"
    // << "Title: " << data.Title << "\n"
    // << "PlainText: " << data.PlainText << "\n"
    // << "EncodeType: " << data.EncodeType << "\n"
    // << "EncodeKey: " << data.EncodeKey << "\n"
    // << "MetaData: " << data.MetaData << "\n"
    // << "====================================" << std::endl;
    struct DocData {
        enum enum_EncodeType {
            NONE = 0,
            DEFAULT = 1,
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

    // UUID
    static std::string CreateUUIDString();

    // ENTRY PROCESSING
    static DocData CreateDocData(
        std::string DocUUID,
        std::string Title,
        std::string plainText,
        DataMan::DocData::enum_EncodeType EncodeType,
        std::string encodeText,
        std::string metaData
    );
    static std::vector<DataMan::DocData> ProcessQuery(const std::string& query);
    static int Get_EntryCount();
    static void Entry_Save(DocData data);
    static void Entry_Delete(std::string docUUID);
    static void Table_Instanciate();
    static void Table_Print();

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
