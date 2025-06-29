#pragma once
#include "ui_mainWin.h"

// Forward declaration UI
namespace Ui {
    class MainWindow;  // Forward declaration of MainWindow class
}

class EditorWindow {
private:
    Ui::MainWindow *mainWindow_UI;
    void ApplyFormat(QTextCursor cursor, QTextCharFormat format);
public:
    int CreateWindow(int argc, char *argv[]);

    // Text Menu
    void Text_Bold();
    void Text_Italic();
    void Text_Strikethrough();

};
