#include <wx/richtext/richtextctrl.h>
#include <wx/richtext/richtextxml.h>
#include <wx/sstream.h>
#include <wx/wx.h>
#include <wx/fdrepdlg.h>

#include "editorWindow.h"
#include "findReplace_Window.h"
#include "loadFile_Window.h"
#include "configManager.h"
#include "dataManager.h"

#include <string>
#include <iostream>
#include <format>

bool GApp::OnInit() {
    DataMan::ValidateDefaultPaths();

    ConfigMan::LoadConfig(DataMan::GetPath_Config());
    ConfigMan::SaveConfig(DataMan::GetPath_Config());

    EditorWindow *eWindow = new EditorWindow();  // Create the main frame window
    eWindow->Show(true);                         // Show the frame
    return true;
}

wxTextCtrl* titleBox;
wxRichTextCtrl *richTextBox;
std::string currentDocUUID;

// #################
// #  Constructor  #
// #################
EditorWindow::EditorWindow() : wxFrame(nullptr, wxID_ANY, "Grimoire", wxDefaultPosition, wxSize(500, 500)) {
    wxMenuBar *menuBar = new wxMenuBar;

    // File
    wxMenu *menuFile = new wxMenu();
        menuFile->Append(FILE_SAVE,         "Save\t" + ConfigMan::SHORTCUT_SAVE, "Save file to Database.");
        Bind(wxEVT_MENU, &EditorWindow::File_Manager, this, FILE_SAVE);
        menuFile->Append(FILE_LOAD,         "Load\t" + ConfigMan::SHORTCUT_LOAD, "");
        Bind(wxEVT_MENU, &EditorWindow::File_Manager, this, FILE_LOAD);
        menuFile->Append(FILE_NEW,          "New\t" + ConfigMan::SHORTCUT_NEW, "");
        Bind(wxEVT_MENU, &EditorWindow::File_Manager, this, FILE_NEW);
        menuFile->AppendSeparator();
        //menuFile->Append(FILE_RENAME,       "Rename\t" + ConfigMan::SHORTCUT_RENAME, "");
        menuFile->Append(FILE_HISTORY,      "History\t" + ConfigMan::SHORTCUT_HISTORY, "");
        menuFile->AppendSeparator();
        menuFile->Append(FILE_DETAILS,      "Details\t" + ConfigMan::SHORTCUT_DETAILS, "");
        menuFile->Append(FILE_DELETE_FILE,  "Delete File\t" + ConfigMan::SHORTCUT_DELETE_FILE);
        Bind(wxEVT_MENU, &EditorWindow::File_Manager, this, FILE_DELETE_FILE);
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
        Bind(wxEVT_MENU, &EditorWindow::Edit_FindReplace, this, EDIT_FIND);
        menuEdit->Append(EDIT_REPLACE,      "Replace\t" + ConfigMan::SHORTCUT_REPLACE, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_FindReplace, this, EDIT_REPLACE);
    menuBar->Append(menuEdit, "&Edit");
    // View
    wxMenu *menuView = new wxMenu();
        menuView->Append(VIEW_ZOOM_IN,      "Zoom In\t" + ConfigMan::SHORTCUT_ZOOM_IN, "");
        Bind(wxEVT_MENU, &EditorWindow::View_Zoom, this, VIEW_ZOOM_IN);
        menuView->Append(VIEW_ZOOM_OUT,     "Zoom Out\t" + ConfigMan::SHORTCUT_ZOOM_OUT, "");
        Bind(wxEVT_MENU, &EditorWindow::View_Zoom, this, VIEW_ZOOM_OUT);
    menuBar->Append(menuView, "&View");
    // insert
    wxMenu *menuInsert = new wxMenu();
        wxMenu *menuHeader = new wxMenu();
            menuHeader->Append(INSERT_HEADING_1,    "Header #\t" + ConfigMan::SHORTCUT_HEADER_1, "");
            Bind(wxEVT_MENU, &EditorWindow::Insert_Heading, this, INSERT_HEADING_1);
            menuHeader->Append(INSERT_HEADING_2,    "Header #\t" + ConfigMan::SHORTCUT_HEADER_2, "");
            Bind(wxEVT_MENU, &EditorWindow::Insert_Heading, this, INSERT_HEADING_2);
            menuHeader->Append(INSERT_HEADING_3,    "Header #\t" + ConfigMan::SHORTCUT_HEADER_3, "");
            Bind(wxEVT_MENU, &EditorWindow::Insert_Heading, this, INSERT_HEADING_3);
            menuHeader->Append(INSERT_HEADING_4,    "Header #\t" + ConfigMan::SHORTCUT_HEADER_4, "");
            Bind(wxEVT_MENU, &EditorWindow::Insert_Heading, this, INSERT_HEADING_4);
            menuHeader->Append(INSERT_HEADING_5,    "Header #\t" + ConfigMan::SHORTCUT_HEADER_5, "");
            Bind(wxEVT_MENU, &EditorWindow::Insert_Heading, this, INSERT_HEADING_5);
            menuHeader->Append(INSERT_HEADING_6,    "Header #\t" + ConfigMan::SHORTCUT_HEADER_6, "");
            Bind(wxEVT_MENU, &EditorWindow::Insert_Heading, this, INSERT_HEADING_6);
        menuInsert->AppendSubMenu(menuHeader, "Header");
    menuBar->Append(menuInsert, "&Insert");
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
            Bind(wxEVT_MENU, &EditorWindow::Format_Indent, this, FORMAT_INDENT_INCREASE);
            menuIndent->Append(FORMAT_INDENT_DECREASE,  "Decrease\t" + ConfigMan::SHORTCUT_DECREASE_INDENT, "");
            Bind(wxEVT_MENU, &EditorWindow::Format_Indent, this, FORMAT_INDENT_DECREASE);
        menuFormat->AppendSubMenu(menuIndent, "Indent");
    menuBar->Append(menuFormat, "For&mat");
    // Search
    wxMenu *menuSearch = new wxMenu();
        menuSearch->Append(SEARCH_FILE,             "Search File\t" + ConfigMan::SHORTCUT_SEARCH_FILE, "");
        Bind(wxEVT_MENU, &EditorWindow::Edit_FindReplace, this, SEARCH_FILE);
        menuSearch->Append(SEARCH_FILE_ARCHIVE,     "Search File Archive\t" + ConfigMan::SHORTCUT_SEARCH_FILE_ARCHIVE, "");
        menuSearch->Append(SEARCH_GRIMOIRE,         "Search Grimoire\t" + ConfigMan::SHORTCUT_SEARCH_GRIMOIRE, "");
        menuSearch->Append(SEARCH_GRIMOIRE_ARCHIVE, "Search Grimoire Archive\t" + ConfigMan::SHORTCUT_SEARCH_GRIMOIRE_ARCHIVE, "");
    menuBar->Append(menuSearch, "&Search");

    // Grimoire
    wxMenu *menuGrimoire = new wxMenu();
        menuGrimoire->Append(GRIMOIRE_LOAD,     "Load Grimoire\t" + ConfigMan::SHORTCUT_GRIMOIRE_LOAD, "");
        Bind(wxEVT_MENU, &EditorWindow::Grimoire, this, GRIMOIRE_LOAD);
        menuGrimoire->Append(GRIMOIRE_NEW,     "New Grimoire\t" + ConfigMan::SHORTCUT_GRIMOIRE_NEW, "");
        Bind(wxEVT_MENU, &EditorWindow::Grimoire, this, GRIMOIRE_NEW);
        menuGrimoire->AppendSeparator();
        menuGrimoire->Append(GRIMOIRE_RENAME,     "Rename Grimoire\t" + ConfigMan::SHORTCUT_GRIMOIRE_RENAME, "");
        Bind(wxEVT_MENU, &EditorWindow::Grimoire, this, GRIMOIRE_RENAME);
        menuGrimoire->AppendSeparator();
        menuGrimoire->Append(GRIMOIRE_DELETE,     "Delete Grimoire\t" + ConfigMan::SHORTCUT_GRIMOIRE_DELETE, "");
        Bind(wxEVT_MENU, &EditorWindow::Grimoire, this, GRIMOIRE_DELETE);
    menuBar->Append(menuGrimoire, "&Grimoire");

    SetMenuBar(menuBar);

    // Default Style
    wxFont courierFont(wxFontInfo(12).FaceName("Courier New").Family(wxFONTFAMILY_MODERN));
    wxTextAttr textAttr;
    textAttr.SetFont(courierFont);
    textAttr.SetFontWeight(wxFONTWEIGHT_NORMAL);
    textAttr.SetFontStyle(wxFONTSTYLE_NORMAL);
    textAttr.SetFontUnderlined(wxTEXT_ATTR_UNDERLINE_NONE);
    textAttr.SetBackgroundColour(wxTransparentColour);

    // Title bar
    titleBox = new wxTextCtrl(this, wxID_ANY, "untitled entry", wxDefaultPosition, wxDefaultSize);
    titleBox->SetDefaultStyle(textAttr);

    // main edidor
    richTextBox = new wxRichTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxRE_MULTILINE);
    richTextBox->SetDefaultStyle(textAttr);
    richTextBox->SetFocus();

    // richTextCtrl Custom KEY/Shortcut Behaviour
    richTextBox->Bind(wxEVT_KEY_DOWN, &EditorWindow::KeyDown, this);
    richTextBox->SetAcceleratorTable(wxNullAcceleratorTable);

    // Layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(titleBox, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(richTextBox, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);

    this->SetSizerAndFit(mainSizer);
    this->SetSize(wxSize(450, 500));
}
// #################
// # Deconstructor #
// #################
EditorWindow::~EditorWindow() {
}

// Custom Key Behaviour
void EditorWindow::KeyDown(wxKeyEvent& event) {
    // ############################
    // #   Custom TAB Behaviour   #
    // ############################
    if (event.GetKeyCode() == WXK_TAB) {
        wxCommandEvent IndentEvent(wxEVT_MENU,
                       (event.ShiftDown()) ? FORMAT_INDENT_DECREASE : FORMAT_INDENT_INCREASE);
        ProcessEvent(IndentEvent);
        return;
    }

    // #####################################
    // #   Custom ENTER/RETURN Behaviour   #
    // #####################################
    if (event.GetKeyCode() == WXK_RETURN) {
        // Delete Selected Text
        if (richTextBox->HasSelection()) {
            richTextBox->DeleteSelection();
        }

        // Process caret
        long insertPos, tabLength, line, startCol, endCol;
        insertPos = richTextBox->GetInsertionPoint();
        richTextBox->PositionToXY(insertPos, &startCol, &line);
        tabLength = 0;  // set to 0 for later use

        // Check current line's indentation & properties
        wxString lineText = richTextBox->GetLineText(line);
        std::string listNumber = "";
        std::string appendProperties = "";
        for (wxString::const_iterator i = lineText.begin(); i != lineText.end(); ++i) {
            char c = *i;
            std::string charStr = std::string(1, c);
            if (ConfigMan::LIST_CHARACTERS.find(charStr) != std::string::npos) {
                appendProperties += charStr;
                break;
            } else if (!std::isdigit(charStr[0]) && listNumber != "") {
                break;
            }
            if (std::isdigit(charStr[0])) {
                listNumber += charStr;
                continue;
            }
            if (charStr != ConfigMan::TAB_CHARACTER) {
                break;
            }
            if (listNumber == "") {
                tabLength++;
            }
        }

        // process 'return' (newline)
        richTextBox->WriteText("\n");

        // write indentation from previous line
        while (tabLength > 0) {
            richTextBox->WriteText(ConfigMan::TAB_CHARACTER);
            tabLength--;
        }
        if (listNumber != "") {
            listNumber = std::to_string(std::stoi(listNumber) + 1);
            appendProperties = appendProperties + listNumber;
        }
        if (appendProperties != "") {
            richTextBox->WriteText(appendProperties + " ");
        }

        richTextBox->ShowPosition(richTextBox->GetInsertionPoint());

        return;             // exit so we dont replay default Behaviour
    }

    // Pass on all other Keys
    event.Skip();
}

// ############
// #   FILE   #
// ############
// FIXME
void EditorWindow::File_Manager(wxCommandEvent &event) {
    switch (event.GetId()) {
        case FILE_SAVE: {
            if (titleBox->GetValue() == "") {
                wxTextEntryDialog getNameDialog(this,
                                                 "Enter a name for the File:",
                                                 "File name Request");
                if (getNameDialog.ShowModal() != wxID_OK) {
                    wxMessageBox("Could not Save File!\n"
                                 "File must have a name!", "Error");
                    return;
                }
                titleBox->SetValue(getNameDialog.GetValue());
            }
            if (currentDocUUID == "") {
                currentDocUUID = DataMan::CreateUUIDString();
            }



            wxRichTextXMLHandler* handler = new wxRichTextXMLHandler;
            handler->SetFlags(handler->GetFlags() | wxRICHTEXT_HANDLER_INCLUDE_STYLESHEET);

            // Register the handler with the buffer
            richTextBox->GetBuffer().AddHandler(handler);

            // Prepare output stream
            wxStringOutputStream out;

            // Save the buffer as XML
            richTextBox->GetBuffer().SaveFile(out, wxRICHTEXT_TYPE_XML);

            // Get the result as wxString
            wxString richTextString = out.GetString();


            DataMan::DocData data = DataMan::CreateDocData(currentDocUUID,
                                                           titleBox->GetValue().ToStdString(),
                                                           richTextBox->GetValue().ToStdString(),
                                                           DataMan::DocData::DEFAULT,
                                                           richTextString.ToStdString(),
                                                           "");
            DataMan::Entry_Save(data);
            std::cout << "FILE_SAVE" << std::endl;
            break; }
        case FILE_LOAD: {
            // FIXME
            LoadFile_Window lfWin(this);
            if (lfWin.ShowModal() == wxID_OK) {
                DataMan::DocData doc = lfWin.result;

                currentDocUUID = doc.DocUUID;
                titleBox->SetValue(doc.Title);
                richTextBox->SetValue(doc.PlainText);

                if (doc.EncodeType == DataMan::DocData::DEFAULT) {
                    wxStringInputStream in{doc.EncodeKey};
                    wxRichTextXMLHandler handler;
                    if(!handler.LoadFile(&richTextBox->GetBuffer(), in)) {
                        throw std::runtime_error{"Failed to set the contents of wxRichTextCtrl!"};
                    }
                }

            }
            std::cout << "FILE_LOAD" << std::endl;
            break; }
        case FILE_NEW: {
            wxMessageDialog promptSave(
                this,
                "Do you want to save the Current Document?",
                "Save",
                wxYES_NO | wxYES_DEFAULT | wxICON_QUESTION
            );
            if (promptSave.ShowModal() != wxID_YES) {
                // FIXME Save Doc
                std::cout << "SAVE on NEW" << std::endl;
            }

            currentDocUUID = DataMan::CreateUUIDString();
            titleBox->SetValue("untitled entry");
            richTextBox->SetValue("");

            std::cout << "FILE_NEW" << std::endl;
            break; }
        case FILE_DELETE_FILE: {
            wxMessageDialog confirmDelete(
                this,
                "Are you Sure You want to delete the current Document?",
                "Confirm Deletion",
                wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION
            );
            if (confirmDelete.ShowModal() == wxID_YES) {
                DataMan::Entry_Delete(currentDocUUID);
                // FIXME NEW File
                // TODO Delete History
            }
            std::cout << "FILE_DELETE_FILE" << std::endl;
            break; }
        default: {
            std::cout << "ERROR - Incorrect TextID passed: " << event.GetId() << std::endl;
            break; }
    }
}

// #################
// #      EDIT     #
// #################
void EditorWindow::Edit_Undo(wxCommandEvent &event)      { richTextBox->Undo(); }
void EditorWindow::Edit_Redo(wxCommandEvent &event)      { richTextBox->Redo(); }
void EditorWindow::Edit_Cut(wxCommandEvent &event)       { richTextBox->Cut(); }
void EditorWindow::Edit_Copy(wxCommandEvent &event)      { richTextBox->Copy(); }
void EditorWindow::Edit_Paste(wxCommandEvent &event)     { richTextBox->Paste(); }
void EditorWindow::Edit_SelectAll(wxCommandEvent &event) {
    richTextBox->SetSelection(0, richTextBox->GetLastPosition());
}
void EditorWindow::Edit_Delete(wxCommandEvent &event) {
    long start, end;
    richTextBox->GetSelection(&start, &end);

    if (start == end) {
        start = richTextBox->GetInsertionPoint() - 1;
        if (start == -1) { // if we passed start of buffer (0)
            return;
        }

        end = richTextBox->GetInsertionPoint();
        richTextBox->SetSelection(start, end);
    }

    richTextBox->DeleteSelection();
}

long frWinID = 0;
void EditorWindow::Edit_FindReplace(wxCommandEvent &event) {
    FindReplace_Window* frWin = nullptr;
    if (FindWindowById(frWinID) != NULL) {
        frWin = dynamic_cast<FindReplace_Window*>(FindWindowById(frWinID));
    }

    if (frWin == nullptr) {
        frWin = new FindReplace_Window(this, richTextBox);
        frWinID = frWin->GetId();
    }

    frWin->Show();
    frWin->SetFocus();

    switch (event.GetId()) {
        case EDIT_FIND: // Fallthrough
        case SEARCH_FILE: {
            frWin->Populate(false);
            break;
        }
        case EDIT_REPLACE: {
            frWin->Populate(true);
            break;
        }
        default:
            std::cout << "ERROR - Incorrect TextID passed: " << event.GetId() << std::endl;
            break;
    }
}

// #################
// #     View      #
// #################
void EditorWindow::View_Zoom(wxCommandEvent &event) {
    switch (event.GetId()) {
        case VIEW_ZOOM_IN: {
            richTextBox->SetScale(richTextBox->GetScale() + 0.1);
            break;
        }
        case VIEW_ZOOM_OUT: {
            if (richTextBox->GetScale() <= 0.2) {return;}
            richTextBox->SetScale(richTextBox->GetScale() - 0.1);
            break;
        }
        default:
            std::cout << "ERROR - Incorrect TextID passed: " << event.GetId() << std::endl;
            return;
    }
    this->Refresh();
}

// ################
// #    Insert    #
// ################
void EditorWindow::Insert_Heading(wxCommandEvent &event) {
    long start, end;
    richTextBox->GetSelection(&start, &end);

    wxTextAttr textAttr;
    if (start == end) {
        start = richTextBox->GetInsertionPoint();
    }
    richTextBox->GetStyle(start, textAttr);

    int newSize = textAttr.GetFontSize();

    switch (event.GetId()) {
        case INSERT_HEADING_1: {
            std::cout << "Heading 1" << std::endl;
            newSize = 12 * 3;
            break;
        }
        case INSERT_HEADING_2: {
            std::cout << "Heading 2" << std::endl;
            newSize = 12 * 2.5;
            break;
        }
        case INSERT_HEADING_3: {
            std::cout << "Heading 3" << std::endl;
            newSize = 12 * 2;
            break;
        }
        case INSERT_HEADING_4: {
            std::cout << "Heading 4" << std::endl;
            newSize = 12 * 1.5;
            break;
        }
        case INSERT_HEADING_5: {
            std::cout << "Heading 5" << std::endl;
            newSize = 12 * 1;
            break;
        }
        case INSERT_HEADING_6: {
            std::cout << "Heading 6" << std::endl;
            newSize = 12 * 0.5;

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
}

// ####################
// #  FORMAT -> TEXT  #
// ####################
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

// ####################
// #  FORMAT -> LIST  #
// ####################
void EditorWindow::Format_List(wxCommandEvent &event) {
    long startPos, endPos, insertPos, startCol, startLine, endCol, endLine;
    std::string listCharacter = "*";
    int listCharacterInt = std::numeric_limits<int>::min();
    bool hasSelection;

    switch (event.GetId()) {
        case FORMAT_LIST_BULLET: {
            listCharacter = ConfigMan::LIST_DEFAULT_BULLET;
            break; }
        case FORMAT_LIST_NUMBER: {
            listCharacterInt = 0;
            listCharacter = std::to_string(listCharacterInt);
            break; }
        case FORMAT_LIST_PLAIN: {
            listCharacter = ConfigMan::LIST_DEFAULT_PLAIN;
            break; }
        default:
            std::cout << "ERROR - Incorrect ListID passed: " << event.GetId() << std::endl;
            break;
    }

    if (richTextBox->HasSelection()) {
        richTextBox->GetSelection(&startPos, &endPos);
        hasSelection = true;
    } else {
        startPos = richTextBox->GetInsertionPoint();
        endPos = startPos;
        hasSelection = false;
    }
    richTextBox->PositionToXY(startPos, &startCol, &startLine);
    richTextBox->PositionToXY(endPos, &endCol, &endLine);

    for (long line = startLine; line <= endLine; ++line) {
        insertPos = richTextBox->XYToPosition(0, line);
        richTextBox->SetInsertionPoint(insertPos);

        if (richTextBox->GetLineLength(line) == 0) {
            if (listCharacterInt != std::numeric_limits<int>::min()) {
                listCharacterInt += 1;
                listCharacter = std::to_string(listCharacterInt);
            }

            richTextBox->WriteText(listCharacter + " ");
            startPos += 1 + listCharacter.length();
            continue;
        }

        for (int charIndex = 0; charIndex < richTextBox->GetLineLength(line); ++charIndex) {
            richTextBox->SetSelection(insertPos, insertPos + 1);
            if(richTextBox->GetStringSelection() == ConfigMan::TAB_CHARACTER) {
                insertPos++;

                // end of line and no insertion made -> ie after several tab characters
                if (charIndex + 1 == richTextBox->GetLineLength(line)) {
                    goto FORCE_INSERT; // Jumps to force an insertion
                }
                continue;
            }

            if (std::isdigit(richTextBox->GetStringSelection()[0])) {
                richTextBox->GetSelection(&startCol, &endCol);

                while (std::isdigit(richTextBox->GetStringSelection()[0])) {
                    startCol++;
                    endCol++;
                    richTextBox->SetSelection(startCol, endCol);
                }
                if (richTextBox->GetStringSelection() == " ") {
                    endCol++;
                }
                richTextBox->SetSelection(insertPos, endCol -1);

                if (hasSelection) {
                    if (line == 0) {
                        startPos -= ((endCol - 1) - insertPos);
                    }
                    endPos -= ((endCol - 1) - insertPos);
                } else {
                    startPos -= ((endCol - 1) - insertPos);
                }
                richTextBox->DeleteSelection();
                break;
            } else if (ConfigMan::LIST_CHARACTERS.find(richTextBox->GetStringSelection()) != std::string::npos) {
                if (hasSelection) {
                    if (line == 0) {
                        startPos--;
                    }
                    endPos--;
                } else {
                    startPos--;
                }
                richTextBox->DeleteSelection();

                richTextBox->SetSelection(insertPos, insertPos + 1);
                if (richTextBox->GetStringSelection() == " ") {
                    richTextBox->DeleteSelection();
                    if (hasSelection) {
                        if (line == 0) {
                            startPos--;
                        }
                        endPos--;
                    } else {
                        startPos--;
                    }
                }
                break;
            }

            if (listCharacterInt != std::numeric_limits<int>::min()) {
                listCharacterInt += 1;
                listCharacter = std::to_string(listCharacterInt);
            }

            FORCE_INSERT: // Jump-Flag Used to force insertions

            richTextBox->SelectNone();
            richTextBox->SetInsertionPoint(insertPos);
            richTextBox->WriteText(listCharacter + " ");



            if (hasSelection) {
                if (line == 0) {
                    startPos += 1 + listCharacter.length();
                }
                endPos += 1 + listCharacter.length();
            } else {
                startPos += 1 + listCharacter.length();
            }
            break;
        }
    }
    if (startPos < 0) {
        startPos = 0;
    }
    if (hasSelection) {
        richTextBox->SetSelection(startPos, endPos);
    } else {
        richTextBox->SetInsertionPoint(startPos);
    }
}

// ######################
// #  FORMAT -> INDENT  #
// ######################
void EditorWindow::Format_Indent(wxCommandEvent &event) {
    long startPos, endPos, insertPos, startCol, startLine, endCol, endLine;

    richTextBox->GetSelection(&startPos, &endPos);
    richTextBox->PositionToXY(startPos, &startCol, &startLine);
    richTextBox->PositionToXY(endPos, &endCol, &endLine);

    switch (event.GetId()) {
        case FORMAT_INDENT_INCREASE: {
            if (startPos == endPos) {
                for (int i = 0; i < ConfigMan::TAB_SIZE; ++i) {
                    richTextBox->WriteText(ConfigMan::TAB_CHARACTER);
                }
                return;
            }

            startPos += ConfigMan::TAB_SIZE;
            for (long i = startLine; i <= endLine; ++i) {
                insertPos = richTextBox->XYToPosition(0, i);
                richTextBox->SetInsertionPoint(insertPos);
                for (int i = 0; i < ConfigMan::TAB_SIZE; ++i) {
                    richTextBox->WriteText(ConfigMan::TAB_CHARACTER);
                }
                endPos += ConfigMan::TAB_SIZE;
            }

            break; }
        case FORMAT_INDENT_DECREASE: {
            if (startPos == endPos) {
                for (int i = 0; i < ConfigMan::TAB_SIZE; ++i) {
                    insertPos = richTextBox->GetInsertionPoint();
                    if (insertPos == 0) {
                        continue;
                    }
                    richTextBox->SetSelection(insertPos - 1, insertPos);
                    if (richTextBox->GetStringSelection() != ConfigMan::TAB_CHARACTER) {
                        continue;
                    }
                    richTextBox->DeleteSelection();
                }
                richTextBox->SelectNone();
                return;
            }

            for (long i = startLine; i <= endLine; ++i) {
                insertPos = richTextBox->XYToPosition(0, i);
                for (int j = 0; j < ConfigMan::TAB_SIZE; ++j) {
                    richTextBox->SetInsertionPoint(insertPos);
                    richTextBox->SetSelection(insertPos, insertPos + 1);

                    if (richTextBox->GetStringSelection() != ConfigMan::TAB_CHARACTER) {
                        continue;
                    }

                    if (i == startLine) {
                        startPos -= 1;
                        if (startPos < 0) { startPos = 0; }
                    }
                    endPos -= 1;

                    richTextBox->DeleteSelection();
                }
            }
            break; }
        default:
            std::cout << "ERROR - Incorrect ListID passed: " << event.GetId() << std::endl;
            break;
    }

    richTextBox->SetSelection(startPos, endPos);
}

// ###############
// #   GIMOIRE   #
// ###############
void EditorWindow::Grimoire(wxCommandEvent &event) {
    enum DBManageState {
        LOAD_SELECTION,
        QUERY_SELECTION,
        CREATE_SELECTION,
        RENAME_SELECTION,
        DELETE_SELECTION,
        ABORT_SELECTION,
        COMPLETE_SELECTION
    };
    DBManageState state = LOAD_SELECTION;

    switch (event.GetId()) {
        case GRIMOIRE_LOAD: {
            state = QUERY_SELECTION;
            break; }
        case GRIMOIRE_NEW: {
            state = CREATE_SELECTION;
            break; }
        case GRIMOIRE_RENAME: {
            state = RENAME_SELECTION;
            break; }
        case GRIMOIRE_DELETE: {
            state = DELETE_SELECTION;
            break; }
        default:
            std::cout << "ERROR - Incorrect ID passed: " << event.GetId() << std::endl;
            break;
    }

    std::string DBSelection = "";
    this->Enable(false);
    do {
        switch (state) {
            case LOAD_SELECTION: {
                DataMan::DB_Load(DataMan::GetPath_DB() + DBSelection);
                wxMessageBox("You selected: " + DataMan::Get_NameFromPath(DataMan::DB_GetSelectedDB()), "Selection");
                state = COMPLETE_SELECTION;
                break; } ///////////////////////////////////////////////////////////////////////
            case QUERY_SELECTION: {
                wxArrayString knownDBs;
                knownDBs.Add("<Create New>");

                for (std::string entry : DataMan::Get_DBFilePaths()) {
                    knownDBs.Add(entry);
                }

                wxSingleChoiceDialog loadDialog(
                    this,
                    "Select a DB to Load:",
                    "Choose Option",
                    knownDBs
                );
                if (loadDialog.ShowModal() != wxID_OK) {
                    state = ABORT_SELECTION;
                    break;
                }
                DBSelection = loadDialog.GetStringSelection().ToStdString();
                if (DBSelection == "<Create New>") {
                    state = CREATE_SELECTION;
                    break;
                }
                state = LOAD_SELECTION;
                break; }///////////////////////////////////////////////////////////////////////
            case CREATE_SELECTION: {
                wxTextEntryDialog newEntryDialog(this,
                                         "Enter a name for the new DB:",
                                         "New DB");
                if (newEntryDialog.ShowModal() != wxID_OK) {
                    state = ABORT_SELECTION;
                    break;
                }
                std::string value = newEntryDialog.GetValue().ToStdString();
                if (newEntryDialog.GetValue() == "") {
                    wxMessageBox("DB Name Cannot be Blank!", "Error");
                    state = CREATE_SELECTION;
                    break;
                }
                if (value.length() < 4 || value.substr(value.length() -3, 3) != ".db") {
                    value += ".db";
                }
                wxMessageDialog validateCreation(
                    this,
                    "Is this Correct?\n"
                    "Name: " + DataMan::Get_NameFromPath(value),
                    "Confirm Creation",
                    wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION
                );
                if (validateCreation.ShowModal() != wxID_YES) {
                    state = CREATE_SELECTION;
                    break;
                }
                DBSelection = value;
                value = DataMan::GetPath_DB() + "/" + DBSelection;
                if (DataMan::Get_FilePathExists(value)) {
                    wxMessageDialog validateOverwrite(
                        this,
                        "File Already Exists! Do you want to Overwrite?\n"
                        "Name: " + DataMan::Get_NameFromPath(DBSelection),
                        "Confirm Overwrite",
                        wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION
                    );
                    if (validateOverwrite.ShowModal() != wxID_YES) {
                        state = CREATE_SELECTION;
                        break;
                    }
                    DataMan::DB_Delete(value);
                }
                if (!DataMan::DB_Create(value)) {
                    wxMessageBox("Could Not Create DB!\n"
                    "Name: " + DataMan::Get_NameFromPath(value), "Error");
                    state = CREATE_SELECTION;
                    break;
                }
                state = LOAD_SELECTION;
                break; }///////////////////////////////////////////////////////////////////////
            case RENAME_SELECTION: {
                if (DataMan::DB_GetSelectedDB() == "") {
                    wxMessageBox("No DB Selected to Rename!\n"
                    "This should Never have Happened,\n"
                    "but you must now Select or create a DB!", "Error");
                    state = QUERY_SELECTION;
                    break;
                }
                DBSelection = DataMan::DB_GetSelectedDB();
                wxTextEntryDialog renameDialog(this,
                                            "Enter a new name for:\n" + DataMan::Get_NameFromPath(DBSelection),
                                            "Rename DB");
                if (renameDialog.ShowModal() != wxID_OK) {
                    state = ABORT_SELECTION;
                    break;
                }
                std::string value = renameDialog.GetValue().ToStdString();
                if (renameDialog.GetValue() == "") {
                    wxMessageBox("DB Name Cannot be Blank!", "Error");
                    state = RENAME_SELECTION;
                    break;
                }
                if (value.length() < 4 || value.substr(value.length() -3, 3) != ".db") {
                    value += ".db";
                }
                wxMessageDialog validateRename(
                    this,
                    "Is this Correct?\n"
                    "From: " + DataMan::Get_NameFromPath(DBSelection) + "\n"
                    "To: " + DataMan::Get_NameFromPath(value),
                    "Confirm Rename",
                    wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION
                );
                if (validateRename.ShowModal() != wxID_YES) {
                    state = RENAME_SELECTION;
                    break;
                }
                //DBSelection = value;
                value = DataMan::GetPath_DB() + "/" + value;
                if (DataMan::Get_FilePathExists(value)) {
                    wxMessageDialog validateOverwrite(
                        this,
                        "File Already Exists! Do you want to Overwrite?\n"
                        "Name: " + DataMan::Get_NameFromPath(DBSelection),
                        "Confirm Overwrite",
                        wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION
                    );
                    if (validateOverwrite.ShowModal() != wxID_YES) {
                        state = RENAME_SELECTION;
                        break;
                    }
                    DataMan::DB_Delete(value);
                }
                if (!DataMan::DB_Create(value)) {
                    wxMessageBox("Could Not Rename DB!\n"
                    "Name: " + DataMan::Get_NameFromPath(value), "Error");
                    state = RENAME_SELECTION;
                    break;
                }
                DataMan::DB_Delete(value);
                DataMan::DB_Rename(DBSelection, value);
                DBSelection = DataMan::Get_NameFromPath(value);
                state = LOAD_SELECTION;
                break; }///////////////////////////////////////////////////////////////////////
            case DELETE_SELECTION: {
                if (DataMan::DB_GetSelectedDB() == "") {
                    wxMessageBox("No DB Selected to Delete!\n"
                    "This should Never have Happened,\n"
                    "but you must now Select or create a DB!", "Error");
                    state = QUERY_SELECTION;
                    break;
                }
                DBSelection = DataMan::DB_GetSelectedDB();
                wxMessageDialog validateDeletion(
                    this,
                    "Are you Sure you want to Delete this DB?\n"
                    "Name: " + DataMan::Get_NameFromPath(DBSelection),
                    "Confirm Deletion",
                    wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION
                );
                if (validateDeletion.ShowModal() != wxID_YES) {
                    state = ABORT_SELECTION;
                    break;
                }
                DataMan::DB_Delete(DBSelection);
                DataMan::DB_Load("");
                wxMessageBox("DB has been Deleted!\n"
                             "Select or Create a new one!", "Warning");
                state = QUERY_SELECTION;
                break; }///////////////////////////////////////////////////////////////////////
            case ABORT_SELECTION: {
                if (DataMan::DB_GetSelectedDB() == "") {
                    wxMessageBox("You Must Create or Select a DB!", "Error");
                    state = QUERY_SELECTION;
                    break;
                }
                wxMessageBox("Selected DB has Not Changed!", "Warning");
                state = COMPLETE_SELECTION;
                break; }///////////////////////////////////////////////////////////////////////
            case COMPLETE_SELECTION: {
                break; }///////////////////////////////////////////////////////////////////////
            default:
                std::cout << "ERROR - Incorrect ID passed: " << event.GetId() << std::endl;
                break;
        }
    } while (state != COMPLETE_SELECTION);
    this->SetTitle(DataMan::Get_StemFromPath(DataMan::DB_GetSelectedDB()));
    this->Enable(true);
}
