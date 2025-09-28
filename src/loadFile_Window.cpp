#include "loadFile_Window.h"
#include "dataManager.h"
#include <wx/gbsizer.h>

LoadFile_Window::LoadFile_Window(wxWindow* parent)
: wxDialog(parent, wxID_ANY, "Select File", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
currentPage(1), entriesPerPage(10) {
    SetMinSize(wxSize(400, 300)); // Adjust dimensions as needed

    // Main vertical layout
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Search bar + Search button
    wxBoxSizer* searchSizer = new wxBoxSizer(wxHORIZONTAL);
    searchBar = new wxTextCtrl(this, wxID_ANY);
    searchButton = new wxButton(this, wxID_ANY, "Search");
    searchSizer->Add(searchBar, 1, wxEXPAND | wxALL, 5);
    searchSizer->Add(searchButton, 0, wxALL, 5);
    mainSizer->Add(searchSizer, 0, wxEXPAND);

    // Viewer
    entryViewer = new wxListBox(this, wxID_ANY);
    mainSizer->Add(entryViewer, 1, wxEXPAND | wxALL, 5);

    // Bottom buttons layout
    wxBoxSizer* navSizer = new wxBoxSizer(wxHORIZONTAL);

    // Left: Cancel
    cancelButton = new wxButton(this, wxID_ANY, "Cancel");
    navSizer->Add(cancelButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    // Spacer to push center group
    navSizer->AddStretchSpacer(1);

    // Center group: Prev + Page Counter + Next
    prevPageButton = new wxButton(this, wxID_ANY, "Prev");
    nextPageButton = new wxButton(this, wxID_ANY, "Next");
    pageCounter = new wxStaticText(this, wxID_ANY, "Page 1 / 1", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);

    wxBoxSizer* centerNavSizer = new wxBoxSizer(wxHORIZONTAL);
    centerNavSizer->Add(prevPageButton, 0, wxALL, 5);
    centerNavSizer->Add(pageCounter, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);
    centerNavSizer->Add(nextPageButton, 0, wxALL, 5);
    navSizer->Add(centerNavSizer, 0, wxALIGN_CENTER_VERTICAL);

    // Spacer to push Confirm right
    navSizer->AddStretchSpacer(1);

    // Right: Confirm
    confirmButton = new wxButton(this, wxID_ANY, "Confirm");
    navSizer->Add(confirmButton, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

    mainSizer->Add(navSizer, 0, wxEXPAND);

    SetSizer(mainSizer);
    mainSizer->SetSizeHints(this);
    mainSizer->Fit(this);
    SetMinSize(wxSize(450, 350));


    // Bind Events
    searchButton->Bind(wxEVT_BUTTON, &LoadFile_Window::OnSearch, this);
    confirmButton->Bind(wxEVT_BUTTON, &LoadFile_Window::OnConfirm, this);
    cancelButton->Bind(wxEVT_BUTTON, &LoadFile_Window::OnCancel, this);
    nextPageButton->Bind(wxEVT_BUTTON, &LoadFile_Window::OnNextPage, this);
    prevPageButton->Bind(wxEVT_BUTTON, &LoadFile_Window::OnPrevPage, this);

    maxPages = (DataMan::Get_EntryCount() + entriesPerPage - 1) / entriesPerPage;
    LoadEntries(currentPage); // Load initial entries
}


LoadFile_Window::~LoadFile_Window() {}

void LoadFile_Window::OnSearch(wxCommandEvent& event) {
    currentSearchTerm = searchBar->GetValue().ToStdString();
    LoadEntries(1);
}

void LoadFile_Window::OnConfirm(wxCommandEvent& event) {
    int selectedIndex = entryViewer->GetSelection();
    if (selectedIndex == wxNOT_FOUND) {
        wxMessageBox("Please select an entry before confirming.", "No Selection", wxICON_WARNING);
        return;
    }
    std::vector<DataMan::DocData> entries = Get_Entries();
    result = entries[selectedIndex];
    EndModal(wxID_OK);
}

void LoadFile_Window::OnCancel(wxCommandEvent& event) {
    EndModal(wxID_CANCEL);
}

void LoadFile_Window::OnNextPage(wxCommandEvent& event) {
    currentPage = (currentPage >= maxPages) ? 1 : ++currentPage;
    LoadEntries(currentPage);
}

void LoadFile_Window::OnPrevPage(wxCommandEvent& event) {
    currentPage = (currentPage <= 1) ? maxPages : --currentPage;
    LoadEntries(currentPage);
}

void LoadFile_Window::LoadEntries(int page) {
    entryViewer->Clear();
    currentPage = page;
    int offset = (currentPage - 1) * entriesPerPage;

    for (DataMan::DocData doc : Get_Entries()) {
        entryViewer->Append(doc.Title);
    }
    pageCounter->SetLabel("Page " + std::to_string(currentPage) + " / " + std::to_string(maxPages));
}
std::vector<DataMan::DocData> LoadFile_Window::Get_Entries() {
    int offset = (currentPage - 1) * entriesPerPage;

    std::string query;
    if (currentSearchTerm != "") {
        query = "SELECT DocData.*, bm25(DocData_fts) AS rank FROM DocData_fts "
        "JOIN DocData ON DocData_fts.rowid = DocData.rowid "
        "WHERE DocData_fts MATCH '" + currentSearchTerm + "*' "
        "ORDER BY rank, DocUUID "
        "LIMIT " + std::to_string(entriesPerPage) +
        " OFFSET " + std::to_string(offset) + ";";
    } else {
        query = "SELECT * FROM DocData "
        "ORDER BY DocUUID "
        "LIMIT " + std::to_string(entriesPerPage) +
        " OFFSET " + std::to_string(offset) + ";";
    }

    std::vector<DataMan::DocData> Table = DataMan::ProcessQuery(query);

    return Table;
}
