#include <wx/wx.h>
#include "editorWindow.h"

#include <iostream>

int main(int argc, char *argv[]){
    wxApp::SetInstance(new GApp());
    wxEntry(argc, argv);
}
