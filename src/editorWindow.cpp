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

// Change Default wxRichTextCtrl Behaviour to use user defined Shortcuts
wxBEGIN_EVENT_TABLE(wxRichTextCtrl, wxControl)
    EVT_PAINT(wxRichTextCtrl::OnPaint)
    EVT_ERASE_BACKGROUND(wxRichTextCtrl::OnEraseBackground)
    EVT_IDLE(wxRichTextCtrl::OnIdle)
    EVT_SCROLLWIN(wxRichTextCtrl::OnScroll)
    EVT_LEFT_DOWN(wxRichTextCtrl::OnLeftClick)
    EVT_MOTION(wxRichTextCtrl::OnMoveMouse)
    EVT_LEFT_UP(wxRichTextCtrl::OnLeftUp)
    EVT_RIGHT_DOWN(wxRichTextCtrl::OnRightClick)
    EVT_MIDDLE_DOWN(wxRichTextCtrl::OnMiddleClick)
    EVT_LEFT_DCLICK(wxRichTextCtrl::OnLeftDClick)
    EVT_CHAR(wxRichTextCtrl::OnChar)
    EVT_KEY_DOWN(wxRichTextCtrl::OnChar)
    EVT_SIZE(wxRichTextCtrl::OnSize)
    EVT_SET_FOCUS(wxRichTextCtrl::OnSetFocus)
    EVT_KILL_FOCUS(wxRichTextCtrl::OnKillFocus)
    EVT_MOUSE_CAPTURE_LOST(wxRichTextCtrl::OnCaptureLost)
    EVT_CONTEXT_MENU(wxRichTextCtrl::OnContextMenu)
    EVT_SYS_COLOUR_CHANGED(wxRichTextCtrl::OnSysColourChanged)
    EVT_TIMER(wxID_ANY, wxRichTextCtrl::OnTimer)
    //EVT_MENU(wxID_UNDO, wxRichTextCtrl::OnUndo)
    //EVT_UPDATE_UI(wxID_UNDO, wxRichTextCtrl::OnUpdateUndo)
    //EVT_MENU(wxID_REDO, wxRichTextCtrl::OnRedo)
    //EVT_UPDATE_UI(wxID_REDO, wxRichTextCtrl::OnUpdateRedo)
    //EVT_MENU(wxID_COPY, wxRichTextCtrl::OnCopy)
    //EVT_UPDATE_UI(wxID_COPY, wxRichTextCtrl::OnUpdateCopy)
    //EVT_MENU(wxID_PASTE, wxRichTextCtrl::OnPaste)
    //EVT_UPDATE_UI(wxID_PASTE, wxRichTextCtrl::OnUpdatePaste)
    //EVT_MENU(wxID_CUT, wxRichTextCtrl::OnCut)
    //EVT_UPDATE_UI(wxID_CUT, wxRichTextCtrl::OnUpdateCut)
    //EVT_MENU(wxID_CLEAR, wxRichTextCtrl::OnClear)
    //EVT_UPDATE_UI(wxID_CLEAR, wxRichTextCtrl::OnUpdateClear)
    //EVT_MENU(wxID_SELECTALL, wxRichTextCtrl::OnSelectAll)
    //EVT_UPDATE_UI(wxID_SELECTALL, wxRichTextCtrl::OnUpdateSelectAll)
    EVT_MENU(wxID_RICHTEXT_PROPERTIES1, wxRichTextCtrl::OnProperties)
    EVT_UPDATE_UI(wxID_RICHTEXT_PROPERTIES1, wxRichTextCtrl::OnUpdateProperties)
    EVT_MENU(wxID_RICHTEXT_PROPERTIES2, wxRichTextCtrl::OnProperties)
    EVT_UPDATE_UI(wxID_RICHTEXT_PROPERTIES2, wxRichTextCtrl::OnUpdateProperties)
    EVT_MENU(wxID_RICHTEXT_PROPERTIES3, wxRichTextCtrl::OnProperties)
    EVT_UPDATE_UI(wxID_RICHTEXT_PROPERTIES3, wxRichTextCtrl::OnUpdateProperties)
wxEND_EVENT_TABLE()

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
    // Edit
    wxMenu *menuEdit = new wxMenu();
        menuEdit->Append(EDIT_UNDO,         "Undo\t" + ConfigMan::SHORTCUT_UNDO, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_Undo, this, EDIT_UNDO);
        menuEdit->Append(EDIT_REDO,         "Redo\t" + ConfigMan::SHORTCUT_REDO, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_Redo, this, EDIT_REDO);
        menuEdit->AppendSeparator();
        menuEdit->Append(EDIT_CUT,          "Cut\t" + ConfigMan::SHORTCUT_CUT, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_Cut, this, EDIT_CUT);
        menuEdit->Append(EDIT_COPY,         "Copy\t" + ConfigMan::SHORTCUT_COPY, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_Copy, this, EDIT_COPY);
        menuEdit->Append(EDIT_PASTE,        "Paste\t" + ConfigMan::SHORTCUT_PASTE, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_Paste, this, EDIT_PASTE);
        menuEdit->AppendSeparator();
        menuEdit->Append(EDIT_SELECT_ALL,   "Select All\t" + ConfigMan::SHORTCUT_SELECT_ALL, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_SelectAll, this, EDIT_SELECT_ALL);
        menuEdit->Append(EDIT_DELETE,       "Delete\t" + ConfigMan::SHORTCUT_DELETE, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_Delete, this, EDIT_DELETE);
        menuEdit->AppendSeparator();
        menuEdit->Append(EDIT_FIND,         "Find\t" + ConfigMan::SHORTCUT_FIND, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_Find, this, EDIT_FIND);
        menuEdit->Append(EDIT_REPLACE,      "Replace\t" + ConfigMan::SHORTCUT_REPLACE, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_Replace, this, EDIT_REPLACE);
    menuBar->Append(menuEdit, "&Edit");
    // View
    wxMenu *menuView = new wxMenu();
        menuView->Append(VIEW_ZOOM_IN,      "Zoom In\t" + ConfigMan::SHORTCUT_ZOOM_IN, "");
        Bind(wxEVT_MENU, &EditorWindow::View_Zoom, this, VIEW_ZOOM_IN);
        menuView->Append(VIEW_ZOOM_OUT,     "Zoom Out\t" + ConfigMan::SHORTCUT_ZOOM_OUT, "");
        Bind(wxEVT_MENU, &EditorWindow::View_Zoom, this, VIEW_ZOOM_OUT);
    menuBar->Append(menuView, "&View");
    //Format
    wxMenu *menuFormat = new wxMenu();
        // Text
        wxMenu *menuText = new wxMenu();
            menuText->Append(FORMAT_TEXT_BOLD,          "Bold\t" + ConfigMan::SHORTCUT_BOLD, "");
            Bind(wxEVT_MENU, &EditorWindow::Format_Text, this, FORMAT_TEXT_BOLD);
            menuText->Append(FORMAT_TEXT_ITALIC,        "Italic\t" + ConfigMan::SHORTCUT_ITALIC, "");
            Bind(wxEVT_MENU, &EditorWindow::Format_Text, this, FORMAT_TEXT_ITALIC);
            menuText->Append(FORMAT_TEXT_UNDERLINE,     "Underline\t" + ConfigMan::SHORTCUT_UNDERLINE, "");
            Bind(wxEVT_MENU, &EditorWindow::Format_Text, this, FORMAT_TEXT_UNDERLINE);
            menuText->Append(FORMAT_TEXT_STIKETHROUGH,  "Strikethrough\t" + ConfigMan::SHORTCUT_STRIKETHROUGH, "");
            Bind(wxEVT_MENU, &EditorWindow::Format_Text, this, FORMAT_TEXT_STIKETHROUGH);
        menuFormat->AppendSubMenu(menuText, "Text");
        // List
        wxMenu *menuList = new wxMenu();
            menuList->Append(FORMAT_LIST_BULLET,        "Bullet\t" + ConfigMan::SHORTCUT_LIST_BULLET, "");
            Bind(wxEVT_MENU, &EditorWindow::Format_List, this, FORMAT_LIST_BULLET);
            menuList->Append(FORMAT_LIST_NUMBER,        "Number\t" + ConfigMan::SHORTCUT_LIST_NUMBER, "");
            Bind(wxEVT_MENU, &EditorWindow::Format_List, this, FORMAT_LIST_NUMBER);
            menuList->Append(FORMAT_LIST_PLAIN,         "Plain\t" + ConfigMan::SHORTCUT_LIST_PLAIN, "");
            Bind(wxEVT_MENU, &EditorWindow::Format_List, this, FORMAT_LIST_PLAIN);
        menuFormat->AppendSubMenu(menuList, "List");
        // Indent
        wxMenu *menuIndent = new wxMenu();
            menuIndent->Append(FORMAT_INDENT_INCREASE,  "Increase\t" + ConfigMan::SHORTCUT_INCREASE_INDENT, "");
            menuIndent->Append(FORMAT_INDENT_DECREASE,  "Decrease\t" + ConfigMan::SHORTCUT_DECREASE_INDENT, "");
        menuFormat->AppendSubMenu(menuIndent, "Indent");
    menuBar->Append(menuFormat, "For&mat");
    // Search
    wxMenu *menuSearch = new wxMenu();
        menuSearch->Append(SEARCH_FILE,             "Search File\t" + ConfigMan::SHORTCUT_SEARCH_FILE, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_Find, this, SEARCH_FILE);
        menuSearch->Append(SEARCH_FILE_ARCHIVE,     "Search File Archive\t" + ConfigMan::SHORTCUT_SEARCH_FILE_ARCHIVE, "");
        menuSearch->Append(SEARCH_GRIMOIRE,         "Search Grimoire\t" + ConfigMan::SHORTCUT_SEARCH_GRIMOIRE, "");
        menuSearch->Append(SEARCH_GRIMOIRE_ARCHIVE, "Search Grimoire Archive\t" + ConfigMan::SHORTCUT_SEARCH_GRIMOIRE_ARCHIVE, "");
    menuBar->Append(menuSearch, "&Search");

    SetMenuBar(menuBar);


    richTextBox = new wxRichTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE);
    // Default Style
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

// EDIT
void EditorWindow::Edit_Undo(wxCommandEvent &event)      { richTextBox->Undo(); }
void EditorWindow::Edit_Redo(wxCommandEvent &event)      { richTextBox->Redo(); }
void EditorWindow::Edit_Cut(wxCommandEvent &event)       { richTextBox->Cut(); }
void EditorWindow::Edit_Copy(wxCommandEvent &event)      { richTextBox->Copy(); }
void EditorWindow::Edit_Paste(wxCommandEvent &event)     { richTextBox->Paste(); }
void EditorWindow::Edit_SelectAll(wxCommandEvent &event) { richTextBox->SelectAll(); }
void EditorWindow::Edit_Delete(wxCommandEvent &event) {
    long start, end;
    richTextBox->GetSelection(&start, &end);

    wxTextAttr textAttr;
    if (start == end) {
        start = richTextBox->GetInsertionPoint();
        end = start;
        start -= 1;
    }

    richTextBox->Delete(wxRichTextRange(start, end));
}
void EditorWindow::Edit_Find(wxCommandEvent &event) {
    // FIXME
    std::cout << "Tiggered: Find" << std::endl;
}
void EditorWindow::Edit_Replace(wxCommandEvent &event) {
    // FIXME
    std::cout << "Tiggered: Replace" << std::endl;
}

// View
void EditorWindow::View_Zoom(wxCommandEvent &event) {
    long initial, start, end;
    initial = richTextBox->GetInsertionPoint();
    richTextBox->SelectAll();
    richTextBox->GetSelection(&start, &end);

    wxTextAttr textAttr;
    if (start == end) {
        start = richTextBox->GetInsertionPoint();
    }
    richTextBox->GetStyle(start, textAttr);

    int newSize = textAttr.GetFontSize();
    switch (event.GetId()) {
        case VIEW_ZOOM_IN: {
            newSize += 1;
            break;
        }
        case VIEW_ZOOM_OUT: {
            if (newSize == 1) { break; }
            newSize -= 1;
            break;
        }
        default:
            std::cout << "ERROR - Incorrect TextID passed: " << event.GetId() << std::endl;
            break;
    }

    textAttr.SetFontSize(newSize);

    if (start != end) {
        richTextBox->SetStyle(start, end, textAttr);
    }
    richTextBox->SetDefaultStyle(textAttr);
    richTextBox->SetInsertionPoint(initial);
}

// FORMAT -> TEXT
void EditorWindow::Format_Text(wxCommandEvent &event) {
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
// FORMAT -> LIST
void EditorWindow::Format_List(wxCommandEvent &event) {
    long start, end;
    richTextBox->GetSelection(&start, &end);

    wxTextAttr textAttr;
    if (start == end) {
        start = richTextBox->GetInsertionPoint();
        end = start + 1;
    }
    richTextBox->GetStyle(start, textAttr);

    switch (event.GetId()) {
        case FORMAT_LIST_BULLET: {
            wxTextAttrBulletStyle newBulletStyle = (textAttr.GetBulletStyle() != wxTEXT_ATTR_BULLET_STYLE_SYMBOL) ? wxTEXT_ATTR_BULLET_STYLE_SYMBOL : wxTEXT_ATTR_BULLET_STYLE_NONE;
            textAttr.SetBulletStyle(newBulletStyle);
            textAttr.SetBulletText("   * ");
            break; }
        case FORMAT_LIST_NUMBER: {
            std::cout << "FORMAT-LIST: Number" << std::endl;
            break; }
        case FORMAT_LIST_PLAIN: {
            wxTextAttrBulletStyle newBulletStyle = (textAttr.GetBulletStyle() != wxTEXT_ATTR_BULLET_STYLE_SYMBOL) ? wxTEXT_ATTR_BULLET_STYLE_SYMBOL : wxTEXT_ATTR_BULLET_STYLE_NONE;
            textAttr.SetBulletStyle(newBulletStyle);
            textAttr.SetBulletText("   - ");
            break; }
        default:
            std::cout << "ERROR - Incorrect ListID passed: " << event.GetId() << std::endl;
            break;
    }

    if (start != end) {
        richTextBox->SetStyle(start, end, textAttr);
    }
    richTextBox->SetDefaultStyle(textAttr);
}
