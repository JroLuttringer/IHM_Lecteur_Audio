/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QRadioButton *radioButton;
    QPushButton *butto_serv;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_file;
    QPushButton *pushButton_list;
    QPushButton *pushButton;
    QPushButton *pushButton_save;
    QPushButton *pushButton_reset;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(632, 601);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        radioButton = new QRadioButton(centralWidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(560, 120, 31, 21));
        radioButton->setCheckable(false);
        butto_serv = new QPushButton(centralWidget);
        butto_serv->setObjectName(QStringLiteral("butto_serv"));
        butto_serv->setGeometry(QRect(520, 80, 89, 25));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 20, 461, 491));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeWidget(layoutWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton_file = new QPushButton(layoutWidget);
        pushButton_file->setObjectName(QStringLiteral("pushButton_file"));

        horizontalLayout->addWidget(pushButton_file);

        pushButton_list = new QPushButton(layoutWidget);
        pushButton_list->setObjectName(QStringLiteral("pushButton_list"));

        horizontalLayout->addWidget(pushButton_list);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_save = new QPushButton(layoutWidget);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));

        horizontalLayout->addWidget(pushButton_save);

        pushButton_reset = new QPushButton(layoutWidget);
        pushButton_reset->setObjectName(QStringLiteral("pushButton_reset"));

        horizontalLayout->addWidget(pushButton_reset);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 632, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        radioButton->setText(QString());
        butto_serv->setText(QApplication::translate("MainWindow", "ON / OFF", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Media", Q_NULLPTR));
        pushButton_file->setText(QApplication::translate("MainWindow", "Add File", Q_NULLPTR));
        pushButton_list->setText(QApplication::translate("MainWindow", "Add List", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Add Radio", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        pushButton_reset->setText(QApplication::translate("MainWindow", "Reset", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
