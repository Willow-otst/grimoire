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
        menuFile->Append(BAR_FILE_SAVE,         "Save", "Save file to Database.");
        menuFile->Append(BAR_FILE_LOAD,         "Load", "");
        menuFile->Append(BAR_FILE_NEW,          "New", "");
        menuFile->AppendSeparator();
        menuFile->Append(BAR_FILE_RENAME,       "Rename", "");
        menuFile->Append(BAR_FILE_HISTORY,      "History", "");
        menuFile->AppendSeparator();
        menuFile->Append(BAR_FILE_DETAILS,      "Details", "");
        menuFile->Append(BAR_FILE_DELETE_FILE,  "Delete File", "");
    menuBar->Append(menuFile, "&File");

    wxMenu *menuEdit = new wxMenu();
        menuEdit->Append(BAR_EDIT_UNDO,          "Undo", "");
        menuEdit->Append(BAR_EDIT_REDO,          "Redo", "");
        menuEdit->AppendSeparator();
        menuEdit->Append(BAR_EDIT_CUT,           "Cut", "");
        menuEdit->Append(BAR_EDIT_COPY,          "Copy", "");
        menuEdit->Append(BAR_EDIT_PASTE,         "Paste", "");
        menuEdit->AppendSeparator();
        menuEdit->Append(BAR_EDIT_SELECT_ALL,    "Select All", "");
        menuEdit->Append(BAR_EDIT_DELETE,        "Delete", "");
        menuEdit->AppendSeparator();
        menuEdit->Append(BAR_EDIT_FIND,          "Find", "");
        menuEdit->Append(BAR_EDIT_REPLACE,       "Replace", "");
    menuBar->Append(menuEdit, "&Edit");





    SetMenuBar(menuBar);
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
