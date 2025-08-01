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

    // Custom Key Behaviour
    void KeyDown(wxKeyEvent& event);

    // EDIT
    void Edit_Undo(wxCommandEvent &event);
    void Edit_Redo(wxCommandEvent &event);
    void Edit_Cut(wxCommandEvent &event);
    void Edit_Copy(wxCommandEvent &event);
    void Edit_Paste(wxCommandEvent &event);
    void Edit_SelectAll(wxCommandEvent &event);
    void Edit_Delete(wxCommandEvent &event);
    void Edit_FindReplace(wxCommandEvent &event);

    // VIEW
    void View_Zoom(wxCommandEvent &event);

    // FORMAT -> TEXT
    void Format_Text(wxCommandEvent &event);
    // FORMAT -> LIST
    void Format_List(wxCommandEvent &event);

    // FORMAT -> INDENT
    void Format_Indent(wxCommandEvent &event);
};


//Controll IDs
enum {
    // menu items

    // File
    FILE_SAVE,
    FILE_LOAD,
    FILE_NEW,
    FILE_RENAME,
    FILE_HISTORY,
    FILE_DETAILS,
    FILE_DELETE_FILE,

    // Edit
    EDIT_UNDO,
    EDIT_REDO,
    EDIT_CUT,
    EDIT_COPY,
    EDIT_PASTE,
    EDIT_SELECT_ALL,
    EDIT_DELETE,
    EDIT_FIND,
    EDIT_REPLACE,

    // View
    VIEW_ZOOM_IN,
    VIEW_ZOOM_OUT,

    //Format
    FORMAT_TEXT_BOLD,
    FORMAT_TEXT_ITALIC,
    FORMAT_TEXT_UNDERLINE,
    FORMAT_TEXT_STIKETHROUGH,

    FORMAT_LIST_BULLET,
    FORMAT_LIST_NUMBER,
    FORMAT_LIST_PLAIN,

    FORMAT_INDENT_INCREASE,
    FORMAT_INDENT_DECREASE,

    //Search
    SEARCH_FILE,
    SEARCH_FILE_ARCHIVE,
    SEARCH_GRIMOIRE,
    SEARCH_GRIMOIRE_ARCHIVE,



    //wx standard operations
    STANDARD_APP_QUIT = wxID_EXIT,
    STANDARD_APP_ABOUT = wxID_ABOUT
};
