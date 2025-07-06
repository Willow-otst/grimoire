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
