#pragma once

#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>

#include <wx/dialog.h>

class FindReplace_Window : public wxDialog {
private:
    wxRichTextCtrl* richTextBox;

    wxCheckBox* CHBX_MatchCase;
    wxCheckBox* CHBX_AllowNullReplace;

    wxTextCtrl* TBX_FindInput;
    wxTextCtrl* TBX_ReplaceInput;

public:
    FindReplace_Window(wxWindow* parent, wxRichTextCtrl* richTextPointer);
    ~FindReplace_Window();

    void FindText(wxCommandEvent& event);
};

enum {
  FIND_NEXT,
  FIND_PREVIOUS,
  REPLACE,
  REPLACE_ALL
};
