#pragma once
#include <wx/wx.h>

class GApp : public wxApp {
public:
    virtual bool OnInit() override;
};

class EditorWindow : public wxFrame {
private:
public:
    EditorWindow();
    ~EditorWindow();

    int Start(int argc, char **argv);
    void About(wxCommandEvent &event);
    void Quit(wxCommandEvent &event);

    // Text Menu
    void Text_Bold(wxCommandEvent &event);
    void Text_Italic(wxCommandEvent &event);
    void Text_Strikethrough(wxCommandEvent &event);

};

//Controll IDs
enum {
    // menu items

    // File
    BAR_FILE_SAVE,
    BAR_FILE_LOAD,
    BAR_FILE_NEW,
    BAR_FILE_RENAME,
    BAR_FILE_HISTORY,
    BAR_FILE_DETAILS,
    BAR_FILE_DELETE_FILE,

    // Edit
    BAR_EDIT_UNDO,
    BAR_EDIT_REDO,
    BAR_EDIT_CUT,
    BAR_EDIT_COPY,
    BAR_EDIT_PASTE,
    BAR_EDIT_SELECT_ALL,
    BAR_EDIT_DELETE,
    BAR_EDIT_FIND,
    BAR_EDIT_REPLACE,

    //wx standard operations
    BAR_STANDARD_QUIT = wxID_EXIT,
    BAR_STANDARD_ABOUT = wxID_ABOUT
};
