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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mainwindow.h"
#include "mymutebutton.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_left;
    QScrollArea *scrollArea_frame;
    QWidget *scrollAreaWidgetContents;
    QTreeWidget *treeWidget;
    QFrame *verticalFrame_right;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *language_layout;
    QSpacerItem *horizontalSpacer_language;
    QPushButton *pushButton_french;
    QPushButton *pushButton_english;
    QPushButton *pushButton_german;
    QFrame *frame_info;
    QLineEdit *lineEdit;
    QFrame *frame_song;
    QLCDNumber *lcdNumber_time;
    MySlider *horizontalSlider_song;
    QLCDNumber *lcdNumber_length;
    QGridLayout *gridLayout_buttons;
    QPushButton *pushButton_back;
    QPushButton *pushButton_pause;
    QPushButton *pushButton_next;
    QPushButton *pushButton_play;
    QPushButton *pushButton_stop;
    QFrame *frame_sound;
    MySlider *horizontalSlider_sound;
    QLabel *label;
    QLabel *label_2;
    MyMuteButton *pushButton_mute;
    QFrame *visible_border_frame;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(902, 624);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 10, 341, 541));
        verticalLayout_left = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_left->setSpacing(6);
        verticalLayout_left->setContentsMargins(11, 11, 11, 11);
        verticalLayout_left->setObjectName(QStringLiteral("verticalLayout_left"));
        verticalLayout_left->setContentsMargins(0, 0, 0, 0);
        scrollArea_frame = new QScrollArea(verticalLayoutWidget);
        scrollArea_frame->setObjectName(QStringLiteral("scrollArea_frame"));
        scrollArea_frame->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 337, 537));
        treeWidget = new QTreeWidget(scrollAreaWidgetContents);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(15, 11, 311, 511));
        scrollArea_frame->setWidget(scrollAreaWidgetContents);

        verticalLayout_left->addWidget(scrollArea_frame);

        verticalFrame_right = new QFrame(centralWidget);
        verticalFrame_right->setObjectName(QStringLiteral("verticalFrame_right"));
        verticalFrame_right->setGeometry(QRect(370, 10, 511, 543));
        verticalFrame_right->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(verticalFrame_right);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        language_layout = new QHBoxLayout();
        language_layout->setSpacing(6);
        language_layout->setObjectName(QStringLiteral("language_layout"));
        language_layout->setSizeConstraint(QLayout::SetMinimumSize);
        language_layout->setContentsMargins(-1, -1, 10, -1);
        horizontalSpacer_language = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        language_layout->addItem(horizontalSpacer_language);

        pushButton_french = new QPushButton(verticalFrame_right);
        pushButton_french->setObjectName(QStringLiteral("pushButton_french"));
        pushButton_french->setMaximumSize(QSize(40, 16777215));

        language_layout->addWidget(pushButton_french);

        pushButton_english = new QPushButton(verticalFrame_right);
        pushButton_english->setObjectName(QStringLiteral("pushButton_english"));
        pushButton_english->setMaximumSize(QSize(40, 16777215));

        language_layout->addWidget(pushButton_english);

        pushButton_german = new QPushButton(verticalFrame_right);
        pushButton_german->setObjectName(QStringLiteral("pushButton_german"));
        pushButton_german->setMaximumSize(QSize(40, 16777215));

        language_layout->addWidget(pushButton_german);


        verticalLayout_2->addLayout(language_layout);

        frame_info = new QFrame(verticalFrame_right);
        frame_info->setObjectName(QStringLiteral("frame_info"));
        frame_info->setMinimumSize(QSize(0, 200));
        frame_info->setFrameShape(QFrame::StyledPanel);
        frame_info->setFrameShadow(QFrame::Raised);
        lineEdit = new QLineEdit(frame_info);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(22, 14, 451, 171));
        lineEdit->setReadOnly(true);

        verticalLayout_2->addWidget(frame_info);

        frame_song = new QFrame(verticalFrame_right);
        frame_song->setObjectName(QStringLiteral("frame_song"));
        frame_song->setMinimumSize(QSize(0, 80));
        frame_song->setStyleSheet(QStringLiteral(""));
        frame_song->setFrameShape(QFrame::StyledPanel);
        frame_song->setFrameShadow(QFrame::Raised);
        lcdNumber_time = new QLCDNumber(frame_song);
        lcdNumber_time->setObjectName(QStringLiteral("lcdNumber_time"));
        lcdNumber_time->setGeometry(QRect(40, 40, 64, 23));
        lcdNumber_time->setFrameShape(QFrame::Box);
        lcdNumber_time->setFrameShadow(QFrame::Plain);
        lcdNumber_time->setLineWidth(2);
        lcdNumber_time->setSmallDecimalPoint(true);
        horizontalSlider_song = new MySlider(frame_song);
        horizontalSlider_song->setObjectName(QStringLiteral("horizontalSlider_song"));
        horizontalSlider_song->setGeometry(QRect(20, 10, 451, 31));
        horizontalSlider_song->setOrientation(Qt::Horizontal);
        lcdNumber_length = new QLCDNumber(frame_song);
        lcdNumber_length->setObjectName(QStringLiteral("lcdNumber_length"));
        lcdNumber_length->setGeometry(QRect(390, 40, 64, 23));

        verticalLayout_2->addWidget(frame_song);

        gridLayout_buttons = new QGridLayout();
        gridLayout_buttons->setSpacing(6);
        gridLayout_buttons->setObjectName(QStringLiteral("gridLayout_buttons"));
        gridLayout_buttons->setHorizontalSpacing(10);
        gridLayout_buttons->setVerticalSpacing(30);
        gridLayout_buttons->setContentsMargins(-1, 30, -1, 10);
        pushButton_back = new QPushButton(verticalFrame_right);
        pushButton_back->setObjectName(QStringLiteral("pushButton_back"));
        pushButton_back->setMinimumSize(QSize(50, 50));
        pushButton_back->setMaximumSize(QSize(50, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/resource/back.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_back->setIcon(icon);
        pushButton_back->setIconSize(QSize(32, 32));

        gridLayout_buttons->addWidget(pushButton_back, 0, 0, 1, 1);

        pushButton_pause = new QPushButton(verticalFrame_right);
        pushButton_pause->setObjectName(QStringLiteral("pushButton_pause"));
        pushButton_pause->setMinimumSize(QSize(50, 50));
        pushButton_pause->setMaximumSize(QSize(50, 16777215));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/prefix1/resource/pause_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_pause->setIcon(icon1);
        pushButton_pause->setIconSize(QSize(44, 44));

        gridLayout_buttons->addWidget(pushButton_pause, 0, 3, 1, 1);

        pushButton_next = new QPushButton(verticalFrame_right);
        pushButton_next->setObjectName(QStringLiteral("pushButton_next"));
        pushButton_next->setMinimumSize(QSize(50, 50));
        pushButton_next->setMaximumSize(QSize(50, 16777215));
        pushButton_next->setAutoFillBackground(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/prefix1/resource/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_next->setIcon(icon2);
        pushButton_next->setIconSize(QSize(32, 32));

        gridLayout_buttons->addWidget(pushButton_next, 0, 4, 1, 1);

        pushButton_play = new QPushButton(verticalFrame_right);
        pushButton_play->setObjectName(QStringLiteral("pushButton_play"));
        pushButton_play->setMinimumSize(QSize(50, 50));
        pushButton_play->setMaximumSize(QSize(50, 16777215));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/prefix1/resource/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_play->setIcon(icon3);
        pushButton_play->setIconSize(QSize(32, 32));

        gridLayout_buttons->addWidget(pushButton_play, 0, 2, 1, 1);

        pushButton_stop = new QPushButton(verticalFrame_right);
        pushButton_stop->setObjectName(QStringLiteral("pushButton_stop"));
        pushButton_stop->setMinimumSize(QSize(50, 50));
        pushButton_stop->setMaximumSize(QSize(50, 16777215));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/prefix1/resource/stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_stop->setIcon(icon4);
        pushButton_stop->setIconSize(QSize(32, 32));

        gridLayout_buttons->addWidget(pushButton_stop, 0, 1, 1, 1);

        frame_sound = new QFrame(verticalFrame_right);
        frame_sound->setObjectName(QStringLiteral("frame_sound"));
        frame_sound->setMinimumSize(QSize(200, 60));
        frame_sound->setMaximumSize(QSize(16777215, 60));
        frame_sound->setFrameShape(QFrame::StyledPanel);
        frame_sound->setFrameShadow(QFrame::Raised);
        horizontalSlider_sound = new MySlider(frame_sound);
        horizontalSlider_sound->setObjectName(QStringLiteral("horizontalSlider_sound"));
        horizontalSlider_sound->setGeometry(QRect(60, 10, 211, 41));
        horizontalSlider_sound->setOrientation(Qt::Horizontal);
        label = new QLabel(frame_sound);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(6, 9, 41, 41));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/resource/sound_low_2.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(frame_sound);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(280, 10, 41, 41));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/resource/sound_high_2.png")));
        label_2->setScaledContents(true);

        gridLayout_buttons->addWidget(frame_sound, 1, 1, 1, 4);

        pushButton_mute = new MyMuteButton(verticalFrame_right);
        pushButton_mute->setObjectName(QStringLiteral("pushButton_mute"));
        pushButton_mute->setMaximumSize(QSize(16777215, 50));

        gridLayout_buttons->addWidget(pushButton_mute, 1, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_buttons);

        visible_border_frame = new QFrame(centralWidget);
        visible_border_frame->setObjectName(QStringLiteral("visible_border_frame"));
        visible_border_frame->setGeometry(QRect(369, 9, 511, 541));
        visible_border_frame->setFrameShape(QFrame::StyledPanel);
        visible_border_frame->setFrameShadow(QFrame::Raised);
        MainWindow->setCentralWidget(centralWidget);
        visible_border_frame->raise();
        verticalLayoutWidget->raise();
        verticalFrame_right->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 902, 22));
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
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Media", Q_NULLPTR));
        pushButton_french->setText(QApplication::translate("MainWindow", "FRA", Q_NULLPTR));
        pushButton_english->setText(QApplication::translate("MainWindow", "ENG", Q_NULLPTR));
        pushButton_german->setText(QApplication::translate("MainWindow", "GER", Q_NULLPTR));
        lineEdit->setText(QString());
        pushButton_back->setText(QString());
        pushButton_pause->setText(QString());
        pushButton_next->setText(QString());
        pushButton_play->setText(QString());
        pushButton_stop->setText(QString());
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
