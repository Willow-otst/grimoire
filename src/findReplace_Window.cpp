#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/gbsizer.h>

#include "findReplace_Window.h"
#include <iostream>



FindReplace_Window::FindReplace_Window(wxWindow* parent, wxRichTextCtrl* richTextPointer)
    : wxDialog(parent, wxID_ANY, "Find & Replace", wxDefaultPosition, wxDefaultSize) {

    // Set Pointer to TextCtrl for Find/Replace
    richTextBox = richTextPointer;

    // ##############
    // #  Setup UI  #
    // ##############
    wxBoxSizer* OuterSizer = new wxBoxSizer(wxVERTICAL);
    wxGridBagSizer* Sizer = new wxGridBagSizer(5, 5);

    // Member CheckBox Fields
    CHBX_MatchCase = new wxCheckBox(        this, wxID_ANY, "Match Case", wxDefaultPosition);
    CHBX_AllowNullReplace = new wxCheckBox( this, wxID_ANY, "Allow Replacing with no Text", wxDefaultPosition);

    wxStaticText* LBL_Find = new wxStaticText(          this, wxID_ANY, "Find:", wxDefaultPosition);
    wxStaticText* LBL_Replace = new wxStaticText(       this, wxID_ANY, "Replace:", wxDefaultPosition);
    // Member Text Fields
    TBX_FindInput = new wxTextCtrl(                     this, wxID_ANY, "", wxDefaultPosition);
    TBX_ReplaceInput = new wxTextCtrl(                  this, wxID_ANY, "", wxDefaultPosition);

    wxSize ButtonSize(80,30);
    wxButton* BTN_Replace = new wxButton(               this, wxID_OK, "&Replace", wxDefaultPosition, ButtonSize);
    wxButton* BTN_ReplaceAll = new wxButton(            this, wxID_OK, "Replace &All", wxDefaultPosition, ButtonSize);
    wxButton* BTN_FindPrevious = new wxButton(          this, wxID_OK, "&Previous", wxDefaultPosition, ButtonSize);
    wxButton* BTN_FindNext = new wxButton(              this, wxID_OK, "&Next", wxDefaultPosition, ButtonSize);

    Sizer->Add(CHBX_MatchCase,          wxGBPosition(0, 0), wxGBSpan(1, 3), wxALIGN_CENTER_HORIZONTAL);
    Sizer->Add(CHBX_AllowNullReplace,   wxGBPosition(0, 3), wxGBSpan(1, 5), wxALIGN_CENTER_HORIZONTAL);

    Sizer->Add(LBL_Find,                wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_RIGHT);
    Sizer->Add(LBL_Replace,             wxGBPosition(2, 0), wxGBSpan(1, 1), wxALIGN_RIGHT);

    Sizer->Add(TBX_FindInput,           wxGBPosition(1, 1), wxGBSpan(1, 7), wxEXPAND);
    Sizer->Add(TBX_ReplaceInput,        wxGBPosition(2, 1), wxGBSpan(1, 7), wxEXPAND);

    Sizer->Add(BTN_Replace,             wxGBPosition(3, 0), wxGBSpan(1, 2), wxALIGN_CENTER_HORIZONTAL);
    Sizer->Add(BTN_ReplaceAll,          wxGBPosition(3, 2), wxGBSpan(1, 2), wxALIGN_CENTER_HORIZONTAL);
    Sizer->Add(BTN_FindNext,            wxGBPosition(3, 6), wxGBSpan(1, 2), wxALIGN_CENTER_HORIZONTAL);
    Sizer->Add(BTN_FindPrevious,        wxGBPosition(3, 4), wxGBSpan(1, 2), wxALIGN_CENTER_HORIZONTAL);

    OuterSizer->Add(Sizer, 1, wxALL | wxEXPAND, 10);
    SetSizerAndFit(OuterSizer);

    BTN_FindNext->SetId(FIND_NEXT);
    BTN_FindNext->Bind(wxEVT_BUTTON, &FindReplace_Window::FindText, this);

    BTN_FindPrevious->SetId(FIND_PREVIOUS);
    BTN_FindPrevious->Bind(wxEVT_BUTTON, &FindReplace_Window::FindText, this);

    this->Show();
}
FindReplace_Window::~FindReplace_Window() {}

void FindReplace_Window::FindText(wxCommandEvent& event) {
    wxString searchTerm = TBX_FindInput->GetValue();
    if (searchTerm == "") {
        wxMessageBox("ERROR! - 'Find' Field Cannot be Blank!", "Null Value Error", wxOK);
        return;
    }
    int termLength = searchTerm.length();

    wxString content = richTextBox->GetValue();

    bool matchCase = CHBX_MatchCase->GetValue();
    if (!matchCase) {
        searchTerm.MakeLower();
        content.MakeLower();
    }

    int foundPosition = wxNOT_FOUND;
    LOOP_START:
    switch (event.GetId()) {
        case FIND_PREVIOUS: {
            if (richTextBox->HasSelection()){
                richTextBox->SelectNone();
                richTextBox->SetInsertionPoint(richTextBox->GetInsertionPoint() - termLength);
            }
            foundPosition = content.rfind(wxString(searchTerm), richTextBox->GetInsertionPoint() - 1);
            break; }
        case FIND_NEXT: {
            foundPosition = content.find(wxString(searchTerm), richTextBox->GetInsertionPoint());
            break; }
        default:
            std::cout << "ERROR - Incorrect ID passed: " << event.GetId() << std::endl;
            break;
    }

    if (foundPosition != wxNOT_FOUND) {
        richTextBox->SetInsertionPoint(foundPosition);
        richTextBox->SetSelection(foundPosition, foundPosition+termLength);
        richTextBox->ShowPosition(foundPosition);
    } else if (richTextBox->GetInsertionPoint() != 0) {
        richTextBox->SetInsertionPoint(0);
        goto LOOP_START;
    }

    if (foundPosition == wxNOT_FOUND) {
        wxMessageBox("Search term could not be found!\n"
                    "Term: '" + searchTerm + "'\n"
                    "Match Case: " + ((matchCase) ? "TRUE" : "FALSE"),
                    "Term not Found", wxOK);
    }
}
