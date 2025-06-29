#include <QApplication>
#include <QMainWindow>
#include "ui_mainWin.h"
#include "mainWin.h"

int EditorWindow::CreateWindow(int argc, char *argv[]) {
    QApplication app(argc, argv); // Create the application
    QMainWindow mainWindow; // Create the main window

    Ui::MainWindow mainWindow_UI; // Create the UI object
    mainWindow_UI.setupUi(&mainWindow); // Set up the UI in the main window

    mainWindow_UI.textEdit->setMarkdown("**Text**");

    mainWindow.show(); // Show the main window
    return app.exec(); // Start the event loop
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
        BOLD
        ITALIC
        STIKETHROUGH
    LIST:
        BULLET LIST
        NUMBER LIST
        PLAIN LIST
    INDENT:
        INCREASE INDENT
        DECREASE INDENT
*/
/* TODO: Editor Functions - SEARCH
    SEARCH FILE (Same as Find)
    SEARCH FILE ARCHIVE

    SEARCH GRIMOIRE
    SEARCH GRIMOIRE ARCHIVE
 */
