#include "editorWindow.h"
#include <iostream>

EditorWindow::EditorWindow() {

}

int EditorWindow::Start(int argc, char **argv) {

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
