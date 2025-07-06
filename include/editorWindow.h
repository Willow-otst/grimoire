#pragma once
#include <wx/wx.h>

class GApp : public wxApp {
public:
    virtual bool OnInit() override;
};

class EditorWindow : public wxFrame {
private:
public:
    EditorWindow();
    ~EditorWindow();

    int Start(int argc, char **argv);
    void About(wxCommandEvent &event);
    void Quit(wxCommandEvent &event);

    // Text Menu
    void Text_Bold(wxCommandEvent &event);
    void Text_Italic(wxCommandEvent &event);
    void Text_Strikethrough(wxCommandEvent &event);

};

//Controll IDs
enum {
    // menu items

    //wx standard operations
    CONTROL_STANDARD_QUIT = wxID_EXIT,
    CONTROL_STANDARD_ABOUT = wxID_ABOUT
};
