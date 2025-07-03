#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>


#include "editorWindow.h"

#include <iostream>


EditorWindow::EditorWindow() {
    mainWindow = new Fl_Double_Window(500, 500);

    // TODO: Move Shortcuts to a config file
    Fl_Menu_Bar *topBar = new Fl_Menu_Bar(0, 0, mainWindow->w(), 30);
    topBar->add("&File", FL_ALT + 'f', 0, 0, FL_SUBMENU);
        topBar->add("File/Save", 0, 0, 0, 0);
        topBar->add("File/Load", 0, 0, 0, 0);
        topBar->add("File/New", 0, 0, 0, FL_MENU_DIVIDER);
        topBar->add("File/Rename", 0, 0, 0, FL_MENU_DIVIDER);
        topBar->add("File/History", 0, 0, 0, 0);
        topBar->add("File/Details", 0, 0, 0, FL_MENU_DIVIDER);
        topBar->add("File/Delete File", 0, 0, 0, 0);

    topBar->add("Edit", 0, 0, 0, FL_SUBMENU);
        topBar->add("Edit/Undo", 0, 0, 0, 0);
        topBar->add("Edit/Redo", 0, 0, 0, FL_MENU_DIVIDER);
        topBar->add("Edit/Cut", 0, 0, 0, 0);
        topBar->add("Edit/Copy", 0, 0, 0, 0);
        topBar->add("Edit/Paste", 0, 0, 0, FL_MENU_DIVIDER);
        topBar->add("Edit/Select All", 0, 0, 0, 0);
        topBar->add("Edit/Delete", 0, 0, 0, FL_MENU_DIVIDER);
        topBar->add("Edit/Find", 0, 0, 0, 0);
        topBar->add("Edit/Replace", 0, 0, 0, 0);

    topBar->add("Format", 0, 0, 0, FL_SUBMENU);
    topBar->add("Format/Text", 0, 0, 0, FL_SUBMENU);
        topBar->add("Format/Text/Bold", FL_CTRL + 'b', Text_Bold, 0);
        topBar->add("Format/Text/Italic", FL_CTRL + 'i', Text_Italic, 0);
        topBar->add("Format/Text/Strikethrough", FL_CTRL + '5', Text_Strikethrough, 0);
    topBar->add("Format/List", 0, 0, 0, FL_SUBMENU);
        topBar->add("Format/List/Bullet", 0, 0, 0, 0);
        topBar->add("Format/List/Number", 0, 0, 0, 0);
        topBar->add("Format/List/Plain", 0, 0, 0, 0);
    topBar->add("Format/Indent", 0, 0, 0, FL_SUBMENU);
        topBar->add("Format/Indent/Increase", 0, 0, 0, 0);
        topBar->add("Format/Indent/Decrease", 0, 0, 0, 0);

    topBar->add("Search", 0, 0, 0, FL_SUBMENU);
        topBar->add("Search/File", 0, 0, 0, 0);
        topBar->add("Search/File Archive", 0, 0, 0, FL_MENU_DIVIDER);
        topBar->add("Search/Grimoire", 0, 0, 0, 0);
        topBar->add("Search/Grimoire Archive", 0, 0, 0, 0);

    Fl_Text_Editor *textBox = new Fl_Text_Editor(0, topBar->h(), mainWindow->w(), mainWindow->h()-30);
    textBox->buffer(new Fl_Text_Buffer());
    textBox->wrap_mode(Fl_Text_Editor::WRAP_AT_BOUNDS, 0);

    mainWindow->resizable(textBox);
}

int EditorWindow::Start(int argc, char **argv) {
    mainWindow->show(argc, argv);
    return Fl::run();
}

// FORMAT -> TEXT Functions
void EditorWindow::Text_Bold(Fl_Widget *, void *) {
    std::cout << "B" << std::endl;
}
void EditorWindow::Text_Italic(Fl_Widget *, void *) {
    std::cout << "I" << std::endl;
}
void EditorWindow::Text_Strikethrough(Fl_Widget *, void *) {
    std::cout << "S" << std::endl;
}
