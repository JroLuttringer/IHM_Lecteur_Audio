#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QDir>
#include <QDirIterator>
#include <QCloseEvent>
#include <QMessageBox>
#include "server.h"
#include "automate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Du tree widget

    QTreeWidgetItem * topLevel;
    QFileDialog *test;


    //Autre
    QProcess *myProcess;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
//    server *s_test;
signals:
    void signal_on();
    void change_song(QString);
    //To server
    void signalUI(signalType, QVariantMap);
    //To machine
    void signalSave(signalType, QVariantMap);

public slots:
    void message(signalType, QVariantMap);
    void closeEvent(QCloseEvent*);
    void send_pressed();

    void find_path(QString, QVariantMap);
    void search_file();
    void search_list();
    void load_tree_from_file();
    void load_children_from_file(QTextStream* in, QTreeWidgetItem* parent);
    void save_tree_to_file();
    QStringList visitTree(QTreeWidget *tree);
    void visitTree(QStringList &list, QTreeWidgetItem *item);
    void reset_tree();
    void add_directory(QDir* dir, QTreeWidgetItem *parent);
    void print_name(QTreeWidgetItem *item, int col);
};

#endif // MAINWINDOW_H
