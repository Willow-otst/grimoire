#pragma once

#include <string>
#include "toml.h"

class ConfigMan {
private:
    ConfigMan() = delete;
    ~ConfigMan() = delete;

    static std::string cfgPath;
    static toml::table cfgTable;

    static void CheckTable(const std::string &name);
    static std::string CheckValue(
        const std::string &tableName,
        const std::string &valueName,
        const std::string &value);
    static int CheckValue(
        const std::string &tableName,
        const std::string &valueName,
        int value);
public:
    static void LoadConfig();
    static void SaveConfig();

    // CONFIG -> TAB
    static int TAB_SIZE;
    static std::string TAB_CHARACTER;

    // CONFIG -> LIST
    static std::string LIST_CHARACTERS;
    static std::string LIST_DEFAULT_BULLET;
    static std::string LIST_DEFAULT_PLAIN;

    // CONFIG -> SHORTCUTS
    static std::string SHORTCUT_SAVE;
    static std::string SHORTCUT_LOAD;
    static std::string SHORTCUT_NEW;
    static std::string SHORTCUT_RENAME;
    static std::string SHORTCUT_HISTORY;
    static std::string SHORTCUT_DETAILS;
    static std::string SHORTCUT_DELETE_FILE;
    static std::string SHORTCUT_UNDO;
    static std::string SHORTCUT_REDO;
    static std::string SHORTCUT_CUT;
    static std::string SHORTCUT_COPY;
    static std::string SHORTCUT_PASTE;
    static std::string SHORTCUT_SELECT_ALL;
    static std::string SHORTCUT_DELETE;
    static std::string SHORTCUT_FIND;
    static std::string SHORTCUT_REPLACE;
    static std::string SHORTCUT_ZOOM_IN;
    static std::string SHORTCUT_ZOOM_OUT;
    static std::string SHORTCUT_BOLD;
    static std::string SHORTCUT_ITALIC;
    static std::string SHORTCUT_UNDERLINE;
    static std::string SHORTCUT_STRIKETHROUGH;
    static std::string SHORTCUT_LIST_BULLET;
    static std::string SHORTCUT_LIST_NUMBER;
    static std::string SHORTCUT_LIST_PLAIN;
    static std::string SHORTCUT_INCREASE_INDENT;
    static std::string SHORTCUT_DECREASE_INDENT;
    static std::string SHORTCUT_SEARCH_FILE;
    static std::string SHORTCUT_SEARCH_FILE_ARCHIVE;
    static std::string SHORTCUT_SEARCH_GRIMOIRE;
    static std::string SHORTCUT_SEARCH_GRIMOIRE_ARCHIVE;

};
