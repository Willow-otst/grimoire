#pragma once

#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>

#include <wx/dialog.h>

class FindReplace_Window : public wxDialog {
private:
    wxRichTextCtrl* richTextBox;

    wxButton* okButton;  // A pointer to the OK button
public:
    FindReplace_Window(wxWindow* parent, wxRichTextCtrl* richTextPointer);
    ~FindReplace_Window();

    void OnOkButtonClicked(wxCommandEvent& event);
};

enum {
  FIND_NEXT,
  FIND_PREVIOUS,
  REPLACE,
  REPLACE_ALL
};
