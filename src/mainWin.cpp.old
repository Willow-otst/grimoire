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
    mainWindow_UI->textEdit->setMarkdown("B.I.S. -> **Text** *Text* ~~Text~~ ~~***Text***~~");

    // Set font size
    mainWindow_UI->textEdit->selectAll();
    QTextCursor cursor = mainWindow_UI->textEdit->textCursor();
    QFont font = mainWindow_UI->textEdit->font(); // Get the current font
    font.setPointSize(15);                        // Set the new point size
    mainWindow_UI->textEdit->setFont(font);       // Apply the font to the QTextEdit

    cursor.movePosition(QTextCursor::Start);
    mainWindow_UI->textEdit->setTextCursor(cursor);

    // ======= Hook UI action Signals to class functions ============
    // FORMAT -> TEXT
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

// Helper -> applies formatting to selection or cursor position
void EditorWindow::ApplyFormat(QTextCursor cursor, QTextCharFormat format) {
    if (cursor.hasSelection()) {
        cursor.mergeCharFormat(format);
    } else {
        mainWindow_UI->textEdit->setCurrentCharFormat(format);
    }
}
// FORMAT -> TEXT Functions
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
