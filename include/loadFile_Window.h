#pragma once

#include "dataManager.h"

#include <wx/wx.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/listbox.h>
#include <wx/sizer.h>

class LoadFile_Window : public wxDialog {
private:
    wxTextCtrl* searchBar;
    std::string currentSearchTerm;
    wxButton* searchButton;
    wxListBox* entryViewer;
    wxButton* confirmButton;
    wxButton* cancelButton;
    wxButton* nextPageButton;
    wxButton* prevPageButton;
    wxStaticText* pageCounter;


    int currentPage;
    int entriesPerPage;
    int maxPages;

    void OnSearch(wxCommandEvent& event);
    void OnConfirm(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void OnNextPage(wxCommandEvent& event);
    void OnPrevPage(wxCommandEvent& event);
    void LoadEntries(int page);
    std::vector<DataMan::DocData> Get_Entries();

public:
    DataMan::DocData result;

    LoadFile_Window(wxWindow* parent);
    ~LoadFile_Window();
};
