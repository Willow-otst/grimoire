/********************************************************************************
** Form generated from reading UI file 'mainWin.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_H
#define UI_MAINWIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionBold;
    QAction *actionItalic;
    QAction *actionStrikethrough;
    QAction *actionSize;
    QAction *actionBullet;
    QAction *actionNumber;
    QAction *actionPlain;
    QAction *action_Increase_Indent;
    QAction *action_Decrease_Indent;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionSelect_All;
    QAction *actionDelete;
    QAction *actionFind_and_Replace;
    QAction *actionUndo;
    QAction *actionSave;
    QAction *actionLoad;
    QAction *actionNew;
    QAction *actionRename;
    QAction *actionDetails;
    QAction *actionHistory;
    QAction *actionDelete_File;
    QAction *actionSearch_File;
    QAction *actionSearch_File_Archive;
    QAction *actionSearch_Grimoire;
    QAction *actionSearch_Grimoire_Archive;
    QAction *actionFind;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuFormat;
    QMenu *menuText;
    QMenu *menuList;
    QMenu *menuIndent;
    QMenu *menuSearch;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionBold = new QAction(MainWindow);
        actionBold->setObjectName("actionBold");
        actionItalic = new QAction(MainWindow);
        actionItalic->setObjectName("actionItalic");
        actionStrikethrough = new QAction(MainWindow);
        actionStrikethrough->setObjectName("actionStrikethrough");
        actionSize = new QAction(MainWindow);
        actionSize->setObjectName("actionSize");
        actionBullet = new QAction(MainWindow);
        actionBullet->setObjectName("actionBullet");
        actionNumber = new QAction(MainWindow);
        actionNumber->setObjectName("actionNumber");
        actionPlain = new QAction(MainWindow);
        actionPlain->setObjectName("actionPlain");
        action_Increase_Indent = new QAction(MainWindow);
        action_Increase_Indent->setObjectName("action_Increase_Indent");
        action_Decrease_Indent = new QAction(MainWindow);
        action_Decrease_Indent->setObjectName("action_Decrease_Indent");
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName("actionRedo");
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName("actionCut");
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName("actionPaste");
        actionSelect_All = new QAction(MainWindow);
        actionSelect_All->setObjectName("actionSelect_All");
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName("actionDelete");
        actionFind_and_Replace = new QAction(MainWindow);
        actionFind_and_Replace->setObjectName("actionFind_and_Replace");
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName("actionUndo");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName("actionLoad");
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName("actionNew");
        actionRename = new QAction(MainWindow);
        actionRename->setObjectName("actionRename");
        actionDetails = new QAction(MainWindow);
        actionDetails->setObjectName("actionDetails");
        actionHistory = new QAction(MainWindow);
        actionHistory->setObjectName("actionHistory");
        actionDelete_File = new QAction(MainWindow);
        actionDelete_File->setObjectName("actionDelete_File");
        actionSearch_File = new QAction(MainWindow);
        actionSearch_File->setObjectName("actionSearch_File");
        actionSearch_File_Archive = new QAction(MainWindow);
        actionSearch_File_Archive->setObjectName("actionSearch_File_Archive");
        actionSearch_Grimoire = new QAction(MainWindow);
        actionSearch_Grimoire->setObjectName("actionSearch_Grimoire");
        actionSearch_Grimoire_Archive = new QAction(MainWindow);
        actionSearch_Grimoire_Archive->setObjectName("actionSearch_Grimoire_Archive");
        actionFind = new QAction(MainWindow);
        actionFind->setObjectName("actionFind");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setAutoFormatting(QTextEdit::AutoFormattingFlag::AutoNone);

        verticalLayout->addWidget(textEdit);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 30));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuFormat = new QMenu(menubar);
        menuFormat->setObjectName("menuFormat");
        menuText = new QMenu(menuFormat);
        menuText->setObjectName("menuText");
        menuList = new QMenu(menuFormat);
        menuList->setObjectName("menuList");
        menuIndent = new QMenu(menuFormat);
        menuIndent->setObjectName("menuIndent");
        menuSearch = new QMenu(menubar);
        menuSearch->setObjectName("menuSearch");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuFormat->menuAction());
        menubar->addAction(menuSearch->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionNew);
        menuFile->addSeparator();
        menuFile->addAction(actionRename);
        menuFile->addSeparator();
        menuFile->addAction(actionHistory);
        menuFile->addAction(actionDetails);
        menuFile->addSeparator();
        menuFile->addAction(actionDelete_File);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelect_All);
        menuEdit->addAction(actionDelete);
        menuEdit->addSeparator();
        menuEdit->addAction(actionFind);
        menuEdit->addAction(actionFind_and_Replace);
        menuEdit->addSeparator();
        menuFormat->addAction(menuText->menuAction());
        menuFormat->addAction(menuList->menuAction());
        menuFormat->addAction(menuIndent->menuAction());
        menuText->addAction(actionBold);
        menuText->addAction(actionItalic);
        menuText->addAction(actionStrikethrough);
        menuText->addSeparator();
        menuText->addAction(actionSize);
        menuList->addAction(actionBullet);
        menuList->addAction(actionNumber);
        menuList->addAction(actionPlain);
        menuIndent->addAction(action_Increase_Indent);
        menuIndent->addAction(action_Decrease_Indent);
        menuSearch->addAction(actionSearch_File);
        menuSearch->addAction(actionSearch_File_Archive);
        menuSearch->addSeparator();
        menuSearch->addAction(actionSearch_Grimoire);
        menuSearch->addAction(actionSearch_Grimoire_Archive);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionBold->setText(QCoreApplication::translate("MainWindow", "Bold", nullptr));
#if QT_CONFIG(shortcut)
        actionBold->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+B", nullptr));
#endif // QT_CONFIG(shortcut)
        actionItalic->setText(QCoreApplication::translate("MainWindow", "Italic", nullptr));
#if QT_CONFIG(shortcut)
        actionItalic->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+I", nullptr));
#endif // QT_CONFIG(shortcut)
        actionStrikethrough->setText(QCoreApplication::translate("MainWindow", "Strikethrough", nullptr));
#if QT_CONFIG(shortcut)
        actionStrikethrough->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+5", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSize->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        actionBullet->setText(QCoreApplication::translate("MainWindow", "Bullet List", nullptr));
#if QT_CONFIG(shortcut)
        actionBullet->setShortcut(QCoreApplication::translate("MainWindow", "Alt+Shift+8", nullptr));
#endif // QT_CONFIG(shortcut)
        actionNumber->setText(QCoreApplication::translate("MainWindow", "Number List", nullptr));
#if QT_CONFIG(shortcut)
        actionNumber->setShortcut(QCoreApplication::translate("MainWindow", "Alt+Shift+1", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPlain->setText(QCoreApplication::translate("MainWindow", "Plain List", nullptr));
#if QT_CONFIG(shortcut)
        actionPlain->setShortcut(QCoreApplication::translate("MainWindow", "Alt+Shift+-", nullptr));
#endif // QT_CONFIG(shortcut)
        action_Increase_Indent->setText(QCoreApplication::translate("MainWindow", "Increase Indent", nullptr));
        action_Decrease_Indent->setText(QCoreApplication::translate("MainWindow", "Decrease Indent", nullptr));
        actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
#if QT_CONFIG(shortcut)
        actionRedo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Y, Ctrl+Shift+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSelect_All->setText(QCoreApplication::translate("MainWindow", "Select All", nullptr));
#if QT_CONFIG(shortcut)
        actionSelect_All->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDelete->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        actionFind_and_Replace->setText(QCoreApplication::translate("MainWindow", "Find and Replace", nullptr));
#if QT_CONFIG(shortcut)
        actionFind_and_Replace->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
#if QT_CONFIG(shortcut)
        actionUndo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLoad->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
#if QT_CONFIG(shortcut)
        actionNew->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionRename->setText(QCoreApplication::translate("MainWindow", "Rename", nullptr));
        actionDetails->setText(QCoreApplication::translate("MainWindow", "Details", nullptr));
        actionHistory->setText(QCoreApplication::translate("MainWindow", "History", nullptr));
#if QT_CONFIG(shortcut)
        actionHistory->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        actionDelete_File->setText(QCoreApplication::translate("MainWindow", "Delete File", nullptr));
        actionSearch_File->setText(QCoreApplication::translate("MainWindow", "Search File", nullptr));
        actionSearch_File_Archive->setText(QCoreApplication::translate("MainWindow", "Search File Archive", nullptr));
        actionSearch_Grimoire->setText(QCoreApplication::translate("MainWindow", "Search Grimoire", nullptr));
        actionSearch_Grimoire_Archive->setText(QCoreApplication::translate("MainWindow", "Search Grimoire Archive", nullptr));
        actionFind->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuFormat->setTitle(QCoreApplication::translate("MainWindow", "Format", nullptr));
        menuText->setTitle(QCoreApplication::translate("MainWindow", "Text", nullptr));
        menuList->setTitle(QCoreApplication::translate("MainWindow", "List", nullptr));
        menuIndent->setTitle(QCoreApplication::translate("MainWindow", "Indent", nullptr));
        menuSearch->setTitle(QCoreApplication::translate("MainWindow", "Search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H
