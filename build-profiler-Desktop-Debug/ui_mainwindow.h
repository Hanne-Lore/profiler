/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionMemcheck;
    QAction *actionHelgrind;
    QAction *actionGprof;
    QAction *actionOpen_File;
    QAction *actionOpen_Project;
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QTreeView *treeView;
    QPlainTextEdit *plainTextEdit;
    QPushButton *gprofButton;
    QMenuBar *menuBar;
    QMenu *menuProfiler;
    QMenu *menuHelp;
    QMenu *menuOptions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(997, 600);
        actionMemcheck = new QAction(MainWindow);
        actionMemcheck->setObjectName(QString::fromUtf8("actionMemcheck"));
        actionHelgrind = new QAction(MainWindow);
        actionHelgrind->setObjectName(QString::fromUtf8("actionHelgrind"));
        actionGprof = new QAction(MainWindow);
        actionGprof->setObjectName(QString::fromUtf8("actionGprof"));
        actionOpen_File = new QAction(MainWindow);
        actionOpen_File->setObjectName(QString::fromUtf8("actionOpen_File"));
        actionOpen_Project = new QAction(MainWindow);
        actionOpen_Project->setObjectName(QString::fromUtf8("actionOpen_Project"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 40, 241, 491));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        treeView = new QTreeView(horizontalLayoutWidget_2);
        treeView->setObjectName(QString::fromUtf8("treeView"));

        horizontalLayout_2->addWidget(treeView);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(240, 40, 581, 491));
        gprofButton = new QPushButton(centralWidget);
        gprofButton->setObjectName(QString::fromUtf8("gprofButton"));
        gprofButton->setGeometry(QRect(20, 0, 97, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 997, 27));
        menuProfiler = new QMenu(menuBar);
        menuProfiler->setObjectName(QString::fromUtf8("menuProfiler"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuProfiler->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuProfiler->addAction(actionOpen_File);
        menuOptions->addAction(actionMemcheck);
        menuOptions->addAction(actionHelgrind);
        menuOptions->addAction(actionGprof);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Profiler", 0, QApplication::UnicodeUTF8));
        actionMemcheck->setText(QApplication::translate("MainWindow", "Memcheck", 0, QApplication::UnicodeUTF8));
        actionHelgrind->setText(QApplication::translate("MainWindow", "Helgrind", 0, QApplication::UnicodeUTF8));
        actionGprof->setText(QApplication::translate("MainWindow", "Gprof", 0, QApplication::UnicodeUTF8));
        actionOpen_File->setText(QApplication::translate("MainWindow", "Open Executable", 0, QApplication::UnicodeUTF8));
        actionOpen_Project->setText(QApplication::translate("MainWindow", "Open Project", 0, QApplication::UnicodeUTF8));
        gprofButton->setText(QApplication::translate("MainWindow", "gprof", 0, QApplication::UnicodeUTF8));
        menuProfiler->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
