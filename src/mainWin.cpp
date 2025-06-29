#include <QApplication>
#include <QMainWindow>
#include <QAction>
#include <QObject>
#include "ui_mainWin.h"
#include "mainWin.h"

#include <iostream>

Ui::MainWindow *mainWindow_UI = nullptr;

int EditorWindow::CreateWindow(int argc, char *argv[]) {
    QApplication app(argc, argv);               // Create the application
    QMainWindow mainWindow;                     // Create the main window
    mainWindow_UI = new Ui::MainWindow();       // Create the UI object
    if (!mainWindow_UI) {                       // Exit if point was not made
        return -1;
    }
    mainWindow_UI->setupUi(&mainWindow);        // Set up the UI in the main window

    //Test Text
    mainWindow_UI->textEdit->setMarkdown("Text");

    // Set font size
    mainWindow_UI->textEdit->selectAll();
    QTextCursor cursor = mainWindow_UI->textEdit->textCursor();
    QTextCharFormat format = cursor.charFormat();
    format.setFontPointSize(15);
    ApplyFormat(cursor, format);

    // Hook UI action Signals to class functions
    QObject::connect(mainWindow_UI->actionBold, &QAction::triggered, [this]() {
        this->Text_Bold();
    });
    QObject::connect(mainWindow_UI->actionItalic, &QAction::triggered, [this]() {
        this->Text_Italic();
    });
    QObject::connect(mainWindow_UI->actionStrikethrough, &QAction::triggered, [this]() {
        this->Text_Strikethrough();
    });

    mainWindow.show();                      // Show the main window
    return app.exec();                      // Start the event loop
}
/* TODO: Editor Functions - FILE:
    SAVE
    LOAD
    NEW

    RENAME

    HISTORY
    DETAILS

    DELETE FILE
*/
/* TODO: Editor Functions - EDIT:
    UNDO
    REDO

    CUT
    COPY
    PASTE

    SELECT ALL
    DELETE

    FIND
    FIND AND REPLACE
*/
/* TODO: Editor Functions - FORMAT:
    TEXT:
        COMPLETE - BOLD
        COMPLETE - ITALIC
        COMPLETE - STIKETHROUGH
    LIST:
        BULLET LIST
        NUMBER LIST
        PLAIN LIST
    INDENT:
        INCREASE INDENT
        DECREASE INDENT
*/
// Helper -> applies formatting to selection or cursor position
void EditorWindow::ApplyFormat(QTextCursor cursor, QTextCharFormat format) {
    if (cursor.hasSelection()) {
        cursor.mergeCharFormat(format);
    } else {
        mainWindow_UI->textEdit->setCurrentCharFormat(format);
    }
}
void EditorWindow::Text_Bold() {
    QTextCursor cursor = mainWindow_UI->textEdit->textCursor();
    QTextCharFormat format = cursor.charFormat();

    int newWeight = (format.fontWeight() == QFont::Bold) ? QFont::Normal : QFont::Bold;
    format.setFontWeight(newWeight);

    ApplyFormat(cursor, format);
}
void EditorWindow::Text_Italic() {
    QTextCursor cursor = mainWindow_UI->textEdit->textCursor();
    QTextCharFormat format = cursor.charFormat();

    format.setFontItalic(!format.fontItalic());

    ApplyFormat(cursor, format);
}

void EditorWindow::Text_Strikethrough() {
    QTextCursor cursor = mainWindow_UI->textEdit->textCursor();
    QTextCharFormat format = cursor.charFormat();

    format.setFontStrikeOut(!format.fontStrikeOut());

    ApplyFormat(cursor, format);
}

/* TODO: Editor Functions - SEARCH
    SEARCH FILE (Same as Find)
    SEARCH FILE ARCHIVE

    SEARCH GRIMOIRE
    SEARCH GRIMOIRE ARCHIVE
 */
