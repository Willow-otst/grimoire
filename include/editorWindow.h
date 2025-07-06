#pragma once
#include <wx/wx.h>

class EditorWindow {
private:
public:
    EditorWindow(); // Constuctor
    int Start(int argc, char **argv);
    // Text Menu
    void Text_Bold();
    void Text_Italic();
    void Text_Strikethrough();

};
