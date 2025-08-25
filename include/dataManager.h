#pragma once
#include "uuid.h" // stduuid lib

class DataMan {
private:
    DataMan() = delete;
    ~DataMan() = delete;

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
     * CREATE GRIMOIRE
     * SAVE GRIMOIRE
     * LOAD GRIMOIRE
     * DELETE GRIMOIRE
     */

    static void Test();

};
