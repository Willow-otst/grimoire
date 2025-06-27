#include <QApplication>
#include <QMainWindow>
#include "ui_mainWin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); // Create the application

    QMainWindow mainWindow; // Create the main window
    Ui::MainWindow ui; // Create the UI object

    ui.setupUi(&mainWindow); // Set up the UI in the main window

    mainWindow.show(); // Show the main window

    return app.exec(); // Start the event loop
}
