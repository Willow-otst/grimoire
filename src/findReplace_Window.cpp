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

    wxCheckBox* CHBX_MatchCase = new wxCheckBox(        this, wxID_ANY, "Match Case", wxDefaultPosition);
    wxCheckBox* CHBX_AllowNullReplace = new wxCheckBox( this, wxID_ANY, "Allow Replacing with no Text", wxDefaultPosition);

    wxStaticText* LBL_Find = new wxStaticText(          this, wxID_ANY, "Find:", wxDefaultPosition);
    wxStaticText* LBL_Replace = new wxStaticText(       this, wxID_ANY, "Replace:", wxDefaultPosition);
    wxTextCtrl* TBX_FindInput = new wxTextCtrl(         this, wxID_ANY, "", wxDefaultPosition);
    wxTextCtrl* TBX_ReplaceInput = new wxTextCtrl(      this, wxID_ANY, "", wxDefaultPosition);

    wxSize ButtonSize(80,30);
    wxButton* BTN_Replace = new wxButton(               this, wxID_OK, "Replace", wxDefaultPosition, ButtonSize);
    wxButton* BTN_ReplaceAll = new wxButton(            this, wxID_OK, "Replace All", wxDefaultPosition, ButtonSize);
    wxButton* BTN_FindPrevious = new wxButton(          this, wxID_OK, "Previous", wxDefaultPosition, ButtonSize);
    wxButton* BTN_FindNext = new wxButton(              this, wxID_OK, "Next", wxDefaultPosition, ButtonSize);

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









    //wxStaticText* label = new wxStaticText(this, wxID_ANY, "Hello, wxDialog!", wxDefaultPosition);
    //okButton = new wxButton(this, wxID_OK, "OK", wxDefaultPosition, wxSize(100, 100));

    // Set event handler for the OK button
    // //okButton->Bind(wxEVT_BUTTON, &FindReplace_Window::OnOkButtonClicked, this);

    // sizer->AddGrowableCol(0);
    // sizer->Add(label);
    // sizer->AddGrowableRow(1);
    // sizer->Add(b);
    // sizer->Add(okButton);

    this->Show();
}
FindReplace_Window::~FindReplace_Window() {}

void FindReplace_Window::OnOkButtonClicked(wxCommandEvent& event) {
    richTextBox->WriteText("Hello from dlg!!!");
    Destroy();
}
