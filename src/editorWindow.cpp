#include <wx/richtext/richtextctrl.h>
#include <wx/wx.h>
#include "editorWindow.h"
#include <iostream>

bool GApp::OnInit() {
    EditorWindow *eWindow = new EditorWindow();  // Create the main frame window
    eWindow->Show(true);                         // Show the frame
    return true;
}
// Constructor
EditorWindow::EditorWindow() : wxFrame(nullptr, wxID_ANY, "Grimoire") {
    wxMenuBar *menuBar = new wxMenuBar;

    // File
    wxMenu *menuFile = new wxMenu();
        menuFile->Append(FILE_SAVE,         "Save", "Save file to Database.");
        menuFile->Append(FILE_LOAD,         "Load", "");
        menuFile->Append(FILE_NEW,          "New", "");
        menuFile->AppendSeparator();
        menuFile->Append(FILE_RENAME,       "Rename", "");
        menuFile->Append(FILE_HISTORY,      "History", "");
        menuFile->AppendSeparator();
        menuFile->Append(FILE_DETAILS,      "Details", "");
        menuFile->Append(FILE_DELETE_FILE,  "Delete File", "");
    menuBar->Append(menuFile, "&File");

    wxMenu *menuEdit = new wxMenu();
        menuEdit->Append(EDIT_UNDO,         "Undo", "");
        menuEdit->Append(EDIT_REDO,         "Redo", "");
        menuEdit->AppendSeparator();
        menuEdit->Append(EDIT_CUT,          "Cut", "");
        menuEdit->Append(EDIT_COPY,         "Copy", "");
        menuEdit->Append(EDIT_PASTE,        "Paste", "");
        menuEdit->AppendSeparator();
        menuEdit->Append(EDIT_SELECT_ALL,   "Select All", "");
        menuEdit->Append(EDIT_DELETE,       "Delete", "");
        menuEdit->AppendSeparator();
        menuEdit->Append(EDIT_FIND,         "Find", "");
        menuEdit->Append(EDIT_REPLACE,      "Replace", "");
    menuBar->Append(menuEdit, "&Edit");

    wxMenu *menuView = new wxMenu();
        menuView->Append(VIEW_ZOOM_IN,      "Zoom In", "");
        menuView->Append(VIEW_ZOOM_OUT,     "Zoom Out", "");
    menuBar->Append(menuView, "&View");

    wxMenu *menuFormat = new wxMenu();
        wxMenu *menuText = new wxMenu();
            menuText->Append(FORMAT_TEXT_BOLD,          "Bold", "");
            menuText->Append(FORMAT_TEXT_ITALIC,        "Italic", "");
            menuText->Append(FORMAT_TEXT_UNDERLINE,     "Underline", "");
            menuText->Append(FORMAT_TEXT_STIKETHROUGH,  "Strikethrough", "");
        menuFormat->AppendSubMenu(menuText, "Text");

        wxMenu *menuList = new wxMenu();
            menuList->Append(FORMAT_LIST_BULLET,        "Bullet", "");
            menuList->Append(FORMAT_LIST_NUMBER,        "Number", "");
            menuList->Append(FORMAT_LIST_PLAIN,         "Plain", "");
        menuFormat->AppendSubMenu(menuList, "List");

        wxMenu *menuIndent = new wxMenu();
            menuIndent->Append(FORMAT_INDENT_INCREASE,  "Increase", "");
            menuIndent->Append(FORMAT_INDENT_DECREASE,  "Decrease", "");
        menuFormat->AppendSubMenu(menuIndent, "Indent");
    menuBar->Append(menuFormat, "For&mat");

    wxMenu *menuSearch = new wxMenu();
        menuSearch->Append(SEARCH_FILE,             "Search File", "");
        menuSearch->Append(SEARCH_FILE_ARCHIVE,     "Search File Archive", "");
        menuSearch->Append(SEARCH_GRIMOIRE,         "Search Grimoire", "");
        menuSearch->Append(SEARCH_GRIMOIRE_ARCHIVE, "Search Grimoire Archive", "");
    menuBar->Append(menuSearch, "&Search");


    SetMenuBar(menuBar);

    wxRichTextCtrl *richTextCtrl = new wxRichTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE);
}
// Deconstructor
EditorWindow::~EditorWindow() {

}

// FORMAT -> TEXT Functions
void EditorWindow::Text_Bold(wxCommandEvent &event) {
    std::cout << "B" << std::endl;
}
void EditorWindow::Text_Italic(wxCommandEvent &event) {
    std::cout << "I" << std::endl;
}
void EditorWindow::Text_Strikethrough(wxCommandEvent &event) {
    std::cout << "S" << std::endl;
}
