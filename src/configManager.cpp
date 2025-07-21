#include "configManager.h"

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "toml.h"

#include <stdexcept>

namespace fs = std::filesystem;

//
// CONFIG MANAGER
//
std::string ConfigMan::cfgPath = "grimoire.config";
toml::table ConfigMan::cfgTable;

// CONFIG -> TAB
int ConfigMan::TAB_SIZE;
std::string ConfigMan::TAB_CHARACTER;

// CONFIG -> LIST
std::string ConfigMan::LIST_CHARACTERS;
std::string ConfigMan::LIST_DEFAULT_BULLET;
std::string ConfigMan::LIST_DEFAULT_PLAIN;

// CONFIG -> SHORTCUTS
std::string ConfigMan::SHORTCUT_SAVE;
std::string ConfigMan::SHORTCUT_LOAD;
std::string ConfigMan::SHORTCUT_NEW;
std::string ConfigMan::SHORTCUT_RENAME;
std::string ConfigMan::SHORTCUT_HISTORY;
std::string ConfigMan::SHORTCUT_DETAILS;
std::string ConfigMan::SHORTCUT_DELETE_FILE;
std::string ConfigMan::SHORTCUT_UNDO;
std::string ConfigMan::SHORTCUT_REDO;
std::string ConfigMan::SHORTCUT_CUT;
std::string ConfigMan::SHORTCUT_COPY;
std::string ConfigMan::SHORTCUT_PASTE;
std::string ConfigMan::SHORTCUT_SELECT_ALL;
std::string ConfigMan::SHORTCUT_DELETE;
std::string ConfigMan::SHORTCUT_FIND;
std::string ConfigMan::SHORTCUT_REPLACE;
std::string ConfigMan::SHORTCUT_ZOOM_IN;
std::string ConfigMan::SHORTCUT_ZOOM_OUT;
std::string ConfigMan::SHORTCUT_BOLD;
std::string ConfigMan::SHORTCUT_ITALIC;
std::string ConfigMan::SHORTCUT_UNDERLINE;
std::string ConfigMan::SHORTCUT_STRIKETHROUGH;
std::string ConfigMan::SHORTCUT_LIST_BULLET;
std::string ConfigMan::SHORTCUT_LIST_NUMBER;
std::string ConfigMan::SHORTCUT_LIST_PLAIN;
std::string ConfigMan::SHORTCUT_INCREASE_INDENT;
std::string ConfigMan::SHORTCUT_DECREASE_INDENT;
std::string ConfigMan::SHORTCUT_SEARCH_FILE;
std::string ConfigMan::SHORTCUT_SEARCH_FILE_ARCHIVE;
std::string ConfigMan::SHORTCUT_SEARCH_GRIMOIRE;
std::string ConfigMan::SHORTCUT_SEARCH_GRIMOIRE_ARCHIVE;

void ConfigMan::LoadConfig() {
    if (!fs::exists(cfgPath)) {
        std::ofstream file(cfgPath);
        file.close();
    }
    cfgTable = toml::parse_file(cfgPath);

    CheckTable("TAB");
    TAB_SIZE =      CheckValue("TAB", "SIZE", 3);
    TAB_CHARACTER = CheckValue("TAB", "CHARACTER", " ");

    CheckTable("LIST");
    LIST_CHARACTERS =       CheckValue("TAB", "CHARACTERS", "*->.");
    LIST_DEFAULT_BULLET =   CheckValue("TAB", "DEFAULT BULLET", "*");
    LIST_DEFAULT_PLAIN =    CheckValue("TAB", "DEFAULT PLAIN", "-");

    CheckTable("SHORTCUTS");
    SHORTCUT_SAVE =                     CheckValue("SHORTCUTS", "SAVE",                     "CTRL+S");
    SHORTCUT_LOAD =                     CheckValue("SHORTCUTS", "LOAD",                     "");
    SHORTCUT_NEW =                      CheckValue("SHORTCUTS", "NEW",                      "CTRL+N");
    SHORTCUT_RENAME =                   CheckValue("SHORTCUTS", "RENAME",                   "");
    SHORTCUT_HISTORY =                  CheckValue("SHORTCUTS", "HISTORY",                  "CTRL+SHIFT+H");
    SHORTCUT_DETAILS =                  CheckValue("SHORTCUTS", "DETAILS",                  "");
    SHORTCUT_DELETE_FILE =              CheckValue("SHORTCUTS", "DELETE_FILE",              "");
    SHORTCUT_UNDO =                     CheckValue("SHORTCUTS", "UNDO",                     "CTRL+Z");
    SHORTCUT_REDO =                     CheckValue("SHORTCUTS", "REDO",                     "CTRL+SHIFT+Z");
    SHORTCUT_CUT =                      CheckValue("SHORTCUTS", "CUT",                      "CTRL+X");
    SHORTCUT_COPY =                     CheckValue("SHORTCUTS", "COPY",                     "CTRL+C");
    SHORTCUT_PASTE =                    CheckValue("SHORTCUTS", "PASTE",                    "CTRL+V");
    SHORTCUT_SELECT_ALL =               CheckValue("SHORTCUTS", "SELECT_ALL",               "CTRL+A");
    SHORTCUT_DELETE_FILE =              CheckValue("SHORTCUTS", "DELETE",                   "");
    SHORTCUT_FIND =                     CheckValue("SHORTCUTS", "FIND",                     "CTRL+F");
    SHORTCUT_REPLACE =                  CheckValue("SHORTCUTS", "REPLACE",                  "CTRL+R");
    SHORTCUT_ZOOM_IN =                  CheckValue("SHORTCUTS", "ZOOM_IN",                  "CTRL+=");
    SHORTCUT_ZOOM_OUT =                 CheckValue("SHORTCUTS", "ZOOM_OUT",                 "CTRL+-");
    SHORTCUT_BOLD =                     CheckValue("SHORTCUTS", "BOLD",                     "CTRL+B");
    SHORTCUT_ITALIC =                   CheckValue("SHORTCUTS", "ITALIC",                   "CTRL+I");
    SHORTCUT_UNDERLINE =                CheckValue("SHORTCUTS", "UNDERLINE",                "CTRL+U");
    SHORTCUT_STRIKETHROUGH =            CheckValue("SHORTCUTS", "STRIKETHROUGH",            "CTRL+SHIFT+B");
    SHORTCUT_LIST_BULLET =              CheckValue("SHORTCUTS", "LIST_BULLET",              "CTRL+SHIFT+*");
    SHORTCUT_LIST_NUMBER =              CheckValue("SHORTCUTS", "LIST_NUMBER",              "CTRL+SHIFT+#");
    SHORTCUT_LIST_PLAIN =               CheckValue("SHORTCUTS", "LIST_PLAIN",               "CTRL+SHIFT+_");
    SHORTCUT_INCREASE_INDENT =          CheckValue("SHORTCUTS", "INCREASE_INDENT",          "CTRL+ALT+=");
    SHORTCUT_DECREASE_INDENT =          CheckValue("SHORTCUTS", "DECREASE_INDENT",          "CTRL+ALT+-");
    SHORTCUT_SEARCH_FILE =              SHORTCUT_FIND; // CheckValue("SHORTCUTS", "SEARCH_FILE",              "CTRL+F"); //Redundant
    SHORTCUT_SEARCH_FILE_ARCHIVE =      CheckValue("SHORTCUTS", "SEARCH_FILE_ARCHIVE",      "");
    SHORTCUT_SEARCH_GRIMOIRE =          CheckValue("SHORTCUTS", "SEARCH_GRIMOIRE",          "");
    SHORTCUT_SEARCH_GRIMOIRE_ARCHIVE =  CheckValue("SHORTCUTS", "SEARCH_GRIMOIRE_ARCHIVE",  "");

    //std::cout << cfgTable << std::endl;
}
void ConfigMan::SaveConfig() {
    std::ofstream file(cfgPath);

    if (!file.is_open()) { return; }

    file << cfgTable << std::endl;
    file.close();
}

void ConfigMan::CheckTable(const std::string &name) {
    if (!cfgTable.contains(name)) {
        cfgTable.insert_or_assign(name, toml::table{});
    }
}
std::string ConfigMan::CheckValue(const std::string &tableName, const std::string &valueName, const std::string &value) {
    toml::table* table = cfgTable[tableName].as_table();
    if (!table->contains(valueName)) {
        table->insert_or_assign(valueName, value);
    }
    return table->get(valueName)->value<std::string>().value();
}
int ConfigMan::CheckValue(const std::string &tableName, const std::string &valueName, int value) {
    toml::table* table = cfgTable[tableName].as_table();
    if (!table->contains(valueName)) {
        table->insert_or_assign(valueName, value);
    }
    return table->get(valueName)->value<int>().value();
}
