#include <wx/richtext/richtextctrl.h>
#include <wx/wx.h>

#include "editorWindow.h"
#include "configManager.h"

#include <iostream>
#include <format>

bool GApp::OnInit() {
    ConfigMan::LoadConfig();
    ConfigMan::SaveConfig();

    EditorWindow *eWindow = new EditorWindow();  // Create the main frame window
    eWindow->Show(true);                         // Show the frame
    return true;
}

wxRichTextCtrl *richTextBox;

// Constructor
EditorWindow::EditorWindow() : wxFrame(nullptr, wxID_ANY, "Grimoire", wxDefaultPosition, wxSize(500, 500)) {
    wxMenuBar *menuBar = new wxMenuBar;

    // File
    wxMenu *menuFile = new wxMenu();
        menuFile->Append(FILE_SAVE,         "Save\t" + ConfigMan::SHORTCUT_SAVE, "Save file to Database.");
        menuFile->Append(FILE_LOAD,         "Load\t" + ConfigMan::SHORTCUT_LOAD, "");
        menuFile->Append(FILE_NEW,          "New\t" + ConfigMan::SHORTCUT_NEW, "");
        menuFile->AppendSeparator();
        menuFile->Append(FILE_RENAME,       "Rename\t" + ConfigMan::SHORTCUT_RENAME, "");
        menuFile->Append(FILE_HISTORY,      "History\t" + ConfigMan::SHORTCUT_HISTORY, "");
        menuFile->AppendSeparator();
        menuFile->Append(FILE_DETAILS,      "Details\t" + ConfigMan::SHORTCUT_DETAILS, "");
        menuFile->Append(FILE_DELETE_FILE,  "Delete File\t" + ConfigMan::SHORTCUT_DELETE_FILE, "");
    menuBar->Append(menuFile, "&File");

    wxMenu *menuEdit = new wxMenu();
        menuEdit->Append(EDIT_UNDO,         "Undo\t" + ConfigMan::SHORTCUT_UNDO, "");
        menuEdit->Append(EDIT_REDO,         "Redo\t" + ConfigMan::SHORTCUT_REDO, "");
        menuEdit->AppendSeparator();
        menuEdit->Append(EDIT_CUT,          "Cut\t" + ConfigMan::SHORTCUT_CUT, "");
        menuEdit->Append(EDIT_COPY,         "Copy\t" + ConfigMan::SHORTCUT_COPY, "");
        menuEdit->Append(EDIT_PASTE,        "Paste\t" + ConfigMan::SHORTCUT_PASTE, "");
        menuEdit->AppendSeparator();
        menuEdit->Append(EDIT_SELECT_ALL,   "Select All\t" + ConfigMan::SHORTCUT_SELECT_ALL, "");
        menuEdit->Append(EDIT_DELETE,       "Delete\t" + ConfigMan::SHORTCUT_DELETE, "");
        menuEdit->AppendSeparator();
        menuEdit->Append(EDIT_FIND,         "Find\t" + ConfigMan::SHORTCUT_FIND, "");
        menuEdit->Append(EDIT_REPLACE,      "Replace\t" + ConfigMan::SHORTCUT_REPLACE, "");
    menuBar->Append(menuEdit, "&Edit");

    wxMenu *menuView = new wxMenu();
        menuView->Append(VIEW_ZOOM_IN,      "Zoom In\t" + ConfigMan::SHORTCUT_ZOOM_IN, "");
        menuView->Append(VIEW_ZOOM_OUT,     "Zoom Out\t" + ConfigMan::SHORTCUT_ZOOM_OUT, "");
    menuBar->Append(menuView, "&View");

    wxMenu *menuFormat = new wxMenu();
        wxMenu *menuText = new wxMenu();
            menuText->Append(FORMAT_TEXT_BOLD,          "Bold\t" + ConfigMan::SHORTCUT_BOLD, "");
            Bind(wxEVT_MENU, &EditorWindow::FormatText, this, FORMAT_TEXT_BOLD);
            menuText->Append(FORMAT_TEXT_ITALIC,        "Italic\t" + ConfigMan::SHORTCUT_ITALIC, "");
            Bind(wxEVT_MENU, &EditorWindow::FormatText, this, FORMAT_TEXT_ITALIC);
            menuText->Append(FORMAT_TEXT_UNDERLINE,     "Underline\t" + ConfigMan::SHORTCUT_UNDERLINE, "");
            Bind(wxEVT_MENU, &EditorWindow::FormatText, this, FORMAT_TEXT_UNDERLINE);
            menuText->Append(FORMAT_TEXT_STIKETHROUGH,  "Strikethrough\t" + ConfigMan::SHORTCUT_STRIKETHROUGH, "");
            Bind(wxEVT_MENU, &EditorWindow::FormatText, this, FORMAT_TEXT_STIKETHROUGH);
        menuFormat->AppendSubMenu(menuText, "Text");

        wxMenu *menuList = new wxMenu();
            menuList->Append(FORMAT_LIST_BULLET,        "Bullet\t" + ConfigMan::SHORTCUT_LIST_BULLET, "");
            menuList->Append(FORMAT_LIST_NUMBER,        "Number\t" + ConfigMan::SHORTCUT_LIST_NUMBER, "");
            menuList->Append(FORMAT_LIST_PLAIN,         "Plain\t" + ConfigMan::SHORTCUT_LIST_PLAIN, "");
        menuFormat->AppendSubMenu(menuList, "List");

        wxMenu *menuIndent = new wxMenu();
            menuIndent->Append(FORMAT_INDENT_INCREASE,  "Increase\t" + ConfigMan::SHORTCUT_INCREASE_INDENT, "");
            menuIndent->Append(FORMAT_INDENT_DECREASE,  "Decrease\t" + ConfigMan::SHORTCUT_DECREASE_INDENT, "");
        menuFormat->AppendSubMenu(menuIndent, "Indent");
    menuBar->Append(menuFormat, "For&mat");

    wxMenu *menuSearch = new wxMenu();
        menuSearch->Append(SEARCH_FILE,             "Search File\t" + ConfigMan::SHORTCUT_SEARCH_FILE, "");
        menuSearch->Append(SEARCH_FILE_ARCHIVE,     "Search File Archive\t" + ConfigMan::SHORTCUT_SEARCH_FILE_ARCHIVE, "");
        menuSearch->Append(SEARCH_GRIMOIRE,         "Search Grimoire\t" + ConfigMan::SHORTCUT_SEARCH_GRIMOIRE, "");
        menuSearch->Append(SEARCH_GRIMOIRE_ARCHIVE, "Search Grimoire Archive\t" + ConfigMan::SHORTCUT_SEARCH_GRIMOIRE_ARCHIVE, "");
    menuBar->Append(menuSearch, "&Search");


    SetMenuBar(menuBar);

    richTextBox = new wxRichTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE);
    wxTextAttr textAttr;
    textAttr.SetFontWeight(wxFONTWEIGHT_NORMAL);
    textAttr.SetFontStyle(wxFONTSTYLE_NORMAL);
    textAttr.SetFontUnderlined(wxTEXT_ATTR_UNDERLINE_NONE);
    textAttr.SetBackgroundColour(wxTransparentColour);
    richTextBox->SetDefaultStyle(textAttr);
}
// Deconstructor
EditorWindow::~EditorWindow() {
}

// FORMAT -> TEXT Functions
void EditorWindow::FormatText(wxCommandEvent &event) {
    long start, end;
    richTextBox->GetSelection(&start, &end);

    wxTextAttr textAttr;
    if (start == end) {
        start = richTextBox->GetInsertionPoint();
    }
    richTextBox->GetStyle(start, textAttr);

    switch (event.GetId()) {
        case FORMAT_TEXT_BOLD: {
            wxFontWeight newWeight = (textAttr.GetFontWeight() != wxFONTWEIGHT_BOLD) ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL;
            textAttr.SetFontWeight(newWeight);
            break; }
        case FORMAT_TEXT_ITALIC: {
            wxFontStyle newStyle = (textAttr.GetFontStyle() != wxFONTSTYLE_ITALIC) ? wxFONTSTYLE_ITALIC : wxFONTSTYLE_NORMAL;
            textAttr.SetFontStyle(newStyle);
            break; }
        case FORMAT_TEXT_UNDERLINE: {
            wxTextAttrUnderlineType newUnderline = (textAttr.GetUnderlineType() != wxTEXT_ATTR_UNDERLINE_SOLID) ? wxTEXT_ATTR_UNDERLINE_SOLID : wxTEXT_ATTR_UNDERLINE_NONE;
            textAttr.SetFontUnderlined(newUnderline);
            break; }
        case FORMAT_TEXT_STIKETHROUGH: {
            // wxWidgets Does not currently support Strikethrough
            // this currently substitues with font weight
            wxFontWeight newWeight = (textAttr.GetFontWeight() != wxFONTWEIGHT_THIN) ? wxFONTWEIGHT_THIN : wxFONTWEIGHT_NORMAL;
            textAttr.SetFontWeight(newWeight);
            break; }
        default:
            std::cout << "ERROR - Incorrect TextID passed: " << event.GetId() << std::endl;
            break;
    }

    if (start != end) {
        richTextBox->SetStyle(start, end, textAttr);
    }
    richTextBox->SetDefaultStyle(textAttr);
}
