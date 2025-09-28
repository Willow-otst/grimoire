#include "dataManager.h"
#include "configManager.h"

#include "uuid.h" // stduuid lib
#include "sqlite3.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <map>

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

// ########################
// #   ENTRY PROCESSING   #
// ########################
DataMan::DocData DataMan::CreateDocData(
    std::string DocUUID,
    std::string Title,
    std::string plainText,
    DataMan::DocData::enum_EncodeType EncodeType,
    std::string encodeText,
    std::string metaData
) {
    DocData data{
        .DocUUID = DocUUID,
        .Title = Title,
        .PlainText = plainText,
        .EncodeType = EncodeType,
        .EncodeKey = "",
        .MetaData = metaData,
    };

    switch (EncodeType) {
        case DataMan::DocData::NONE: {
            // Do Nothing
            break; }
        case DataMan::DocData::DEFAULT: {
            // Set Key as Base XML
            data.EncodeKey = encodeText;
            break; }
        // TODO Other Encode Types
        default:
            std::cout << "ERROR - Incorrect ID passed: " << EncodeType << std::endl;
            break;
    }
    return data;
}

int GetReturnVal(void* data, int argc, char** argv, char** colNames) {
    std::vector<DataMan::DocData>* docList = static_cast<std::vector<DataMan::DocData>*>(data);

    DataMan::DocData doc;
    for (int i = 0; i < argc; ++i) {
        std::string colName = colNames[i];
        std::string value = argv[i] ? argv[i] : "";


        if (colName == "DocUUID") {
            doc.DocUUID = value;
        } else if (colName == "Title") {
            doc.Title = value;
        } else if (colName == "PlainText") {
            doc.PlainText = value;
        } else if (colName == "EncodeType") {
            doc.EncodeType = static_cast<DataMan::DocData::enum_EncodeType>(std::stoi(value));
        } else if (colName == "EncodeKey") {
            doc.EncodeKey = value;
        } else if (colName == "MetaData") {
            doc.MetaData = value;
        }
    }

    docList->push_back(doc);
    return 0;
}
std::vector<DataMan::DocData> DataMan::ProcessQuery(const std::string& query) {
    std::vector<DataMan::DocData> returnVal;

    sqlite3* selectedDB = nullptr;
    std::string dbPath = DataMan::DB_GetSelectedDB();
    const char* cpath = dbPath.c_str();
    int dbCode = sqlite3_open(cpath, &selectedDB);

    if (dbCode != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(selectedDB) << std::endl;
        return returnVal;
    }

    char* errMsg = nullptr;
    dbCode = sqlite3_exec(selectedDB, query.c_str(), GetReturnVal, &returnVal, &errMsg);

    if (!returnVal.empty()) {
        for (std::size_t i = 0; i < returnVal.size(); ++i) {
            const DataMan::DocData& doc = returnVal[i];
        }
    }

    if (dbCode != SQLITE_OK || errMsg) {
        sqlite3_free(errMsg);
    }

    sqlite3_close(selectedDB);
    return returnVal;
}

int GetCountVal(void* data, int argc, char** argv, char** colNames) {
    if (argc > 0 && argv[0]) {
        int* out = static_cast<int*>(data);
        *out = std::stoi(argv[0]);
    }
    return 0;
}
int DataMan::Get_EntryCount() {
    const std::string query = "SELECT COUNT(*) FROM DocData;";
    int returnVal = 0;

    sqlite3* selectedDB = nullptr;
    std::string dbPath = DataMan::DB_GetSelectedDB();
    int dbCode = sqlite3_open(dbPath.c_str(), &selectedDB);

    if (dbCode != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(selectedDB) << std::endl;
        sqlite3_close(selectedDB);
        return returnVal;
    }

    char* errMsg = nullptr;
    dbCode = sqlite3_exec(selectedDB, query.c_str(), GetCountVal, &returnVal, &errMsg);

    if (dbCode != SQLITE_OK || errMsg) {
        std::cerr << "Failed to execute query: " << (errMsg ? errMsg : "Unknown error") << std::endl;
        sqlite3_free(errMsg);
        sqlite3_close(selectedDB);
        return 0;
    }

    sqlite3_close(selectedDB);
    return returnVal;
}

void DataMan::Entry_Save(DocData data) {
    const std::string insert = R"(
        INSERT OR REPLACE INTO DocData (
            DocUUID, Title, PlainText, EncodeType, EncodeKey, MetaData
        ) VALUES (
            ')" + data.DocUUID + R"(',
            ')" + data.Title + R"(',
            ')" + data.PlainText + R"(',
            )" + std::to_string(data.EncodeType) + R"(,
            ')" + data.EncodeKey + R"(',
            ')" + data.MetaData + R"('
        );
    )";
    DataMan::ProcessQuery(insert);
}
void DataMan::Entry_Delete(std::string docUUID) {
    const std::string deleteQuery = R"(
        DELETE FROM DocData
        WHERE DocUUID = ')" + docUUID + R"(';
        )";
    DataMan::ProcessQuery(deleteQuery);
}


void DataMan::Table_Instanciate() {
    const std::string createTable = R"(
        CREATE TABLE IF NOT EXISTS DocData (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            DocUUID TEXT UNIQUE NOT NULL,
            Title TEXT,
            PlainText TEXT,
            EncodeType INTEGER,
            EncodeKey TEXT,
            MetaData TEXT
        );
    )";

    const std::string createFTS = R"(
        CREATE VIRTUAL TABLE IF NOT EXISTS DocData_fts
        USING fts5(Title, PlainText, content='DocData', content_rowid='id');
    )";

    const std::string insertTrigger = R"(
        CREATE TRIGGER IF NOT EXISTS DocData_ai
        AFTER INSERT ON DocData
        BEGIN
            INSERT INTO DocData_fts(rowid, Title, PlainText)
            VALUES (new.id, new.Title, new.PlainText);
        END;
    )";

    const std::string updateTrigger = R"(
        CREATE TRIGGER IF NOT EXISTS DocData_au
        AFTER UPDATE ON DocData
        BEGIN
            UPDATE DocData_fts
            SET Title = new.Title,
                PlainText = new.PlainText
            WHERE rowid = new.id;
        END;
    )";

    const std::string deleteTrigger = R"(
        CREATE TRIGGER IF NOT EXISTS DocData_ad
        AFTER DELETE ON DocData
        BEGIN
            DELETE FROM DocData_fts WHERE rowid = old.id;
        END;
    )";

    DataMan::ProcessQuery(createTable);
    DataMan::ProcessQuery(createFTS);
    DataMan::ProcessQuery(insertTrigger);
    DataMan::ProcessQuery(updateTrigger);
    DataMan::ProcessQuery(deleteTrigger);
}

void DataMan::Table_Print() {
     std::vector<DataMan::DocData> Table = DataMan::ProcessQuery("SELECT * FROM DocData;");
     for (DataMan::DocData doc : Table) {
        std::cout << doc.Title << " | " << doc.PlainText << std::endl;
    }
}


// ##########
// #   DB   #
// ##########
std::string DataMan::DB_GetSelectedDB() {
    return Path_File_SelectedDB;
}
void DataMan::DB_Load(std::string path) {
    Path_File_SelectedDB = path;
    DataMan::Table_Instanciate();
}
bool DataMan::DB_Create(std::string path) {
    sqlite3* selectedDB = nullptr;
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
