#pragma once
#include "uuid.h" // stduuid lib

class DataMan {
private:
    DataMan() = delete;
    ~DataMan() = delete;

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
     *
     * NEW GRIMOIRE
     * LOAD GRIMOIRE
     * DELETE GRIMOIRE
     */

    static void Test();

    // PATHS
    static void ValidateDataPaths();
    static std::string GetPath_DB();
    static std::string GetPath_Config();
};
