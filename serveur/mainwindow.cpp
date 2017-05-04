#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QString program = "mpv";
    QStringList arguments;

    arguments << "--idle" << "--quiet" << "--keep-open=yes" << "--keep-open=always"
              << "--input-ipc-server=/tmp/mpvsocket" << "--log-file=/home/cyrille/testlog"
              << "--ytdl-format=bestvideo+bestaudio/best";
    myProcess = new QProcess(this);
    myProcess->start(program, arguments);
    ui->setupUi(this);

    connect(ui->butto_serv, SIGNAL(pressed()), this, SLOT(send_pressed()));

    load_tree_from_file();
//    topLevel = new QTreeWidgetItem();
//    topLevel->setText(0, "This is top level");
//    ui->treeWidget->addTopLevelItem(topLevel);

    connect(ui->pushButton_file, SIGNAL(pressed()), this, SLOT(search_file()));
    connect(ui->pushButton_list, SIGNAL(pressed()), this, SLOT(search_list()));
    connect(ui->pushButton_save, SIGNAL(pressed()), this, SLOT(save_tree_to_file()));
    connect(ui->pushButton_reset, SIGNAL(pressed()), this, SLOT(reset_tree()));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(print_name(QTreeWidgetItem *, int)));

}

void MainWindow::send_pressed()
{
    ui->radioButton->setChecked(true);
    emit signal_on();
}


void MainWindow::print_name(QTreeWidgetItem *item, int col)
{
    QString test;
    qDebug() << "pressed the url";
    //and is not top level

    if(item->childCount() == 0 && item->parent() )
    {
        test = item->parent()->text(0) +"/"+item->text(0);
//        qDebug() << test;
        emit change_song(test) ;
    }
    else
        emit change_song(item->text(0));
}

void MainWindow::reset_tree()
{
    ui->treeWidget->clear();
}

void MainWindow::search_file()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open Directory"),
                                                 ".",
                                                tr("All Files (*.*)"));
    qDebug() << "chosen directory: " << file;
    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setText(0,file);
    ui->treeWidget->addTopLevelItem(item);
    save_tree_to_file();
    QVariantMap p;
    emit signalUI(kSignalTree, p);
}

void MainWindow::add_directory(QDir *dir, QTreeWidgetItem *parent)
{
    QStringList file_children = dir->entryList(QStringList() << "*.mp3" << "*.m4a",QDir::Files);
    for (int i=0; i<file_children.size(); i++)
    {
        QTreeWidgetItem * child = new QTreeWidgetItem();
        child->setText(0,file_children.at(i));
        parent->addChild(child);
    }

    QString directory = dir->path();
    QDirIterator directories(directory, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    while(directories.hasNext()){
        directories.next();
        QString dir_name = directories.filePath();

        QTreeWidgetItem * child = new QTreeWidgetItem();
        child->setText(0,dir_name);
        qDebug() << dir_name;
        QDir *dir = new QDir(dir_name);
        add_directory(dir, child);
        parent->addChild(child);
    }

}

void MainWindow::search_list()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     "/home",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    qDebug() << "chosen directory: " << directory;
    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setText(0,directory);
    QDir *dir = new QDir(directory);
    QStringList file_children = dir->entryList(QStringList() << "*.mp3" << "*.m4a",QDir::Files);
    for (int i=0; i<file_children.size(); i++)
    {
        QTreeWidgetItem * child = new QTreeWidgetItem();
        child->setText(0,file_children.at(i));
        item->addChild(child);
    }

    QDirIterator directories(directory, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    while(directories.hasNext()){
        directories.next();
        QString dir_name = directories.filePath();

        QTreeWidgetItem * child = new QTreeWidgetItem();
        child->setText(0,dir_name);
        qDebug() << dir_name;
        QDir *dir = new QDir(dir_name);
        add_directory(dir, child);
        item->addChild(child);
    }


    ui->treeWidget->addTopLevelItem(item);
    save_tree_to_file();
    QVariantMap p;
    emit signalUI(kSignalTree, p);

}

void MainWindow::load_children_from_file(QTextStream* in, QTreeWidgetItem* parent)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    while (!in->atEnd())
       {
          QString line = in->readLine();

//          QTreeWidgetItem *item = new QTreeWidgetItem();
          if (line == "dir")
          {
               load_children_from_file(in, item);
          }
          else if (line == "end_dir")
          {
              break;
          }
          else
          {
              item = new QTreeWidgetItem();
              item->setText(0,line);
          }
          parent->addChild(item);
       }
}

void MainWindow::load_tree_from_file()
{
    QFile file(SAVE_FILE);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QTreeWidgetItem *item = new QTreeWidgetItem();

    while (!in.atEnd())
       {
          QString line = in.readLine();

          if (line == "dir")
          {
              load_children_from_file(&in, item);

          }
          else
          {
              item = new QTreeWidgetItem();
              item->setText(0,line);
          }
          ui->treeWidget->addTopLevelItem(item);
       }
       file.close();



}

void MainWindow::save_tree_to_file()
{
    QStringList result = visitTree(ui->treeWidget);
    qDebug() << result;

    QFile file(SAVE_FILE);
    qDebug("1" );
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    //here
    for ( QStringList::Iterator it = result.begin(); it != result.end(); ++it )
    out << *it << "\n";
//    out << result;
    file.close();
}

void MainWindow::visitTree(QStringList &list, QTreeWidgetItem *item)
{
      list << item->text(0);
      if(item->childCount()) list << "dir";
      for(int i=0;i<item->childCount(); ++i)
        visitTree(list, item->child(i));
      if(item->childCount()) list << "end_dir";
}

QStringList MainWindow::visitTree(QTreeWidget *tree)
{
    QStringList list;
    for(int i=0;i<tree->topLevelItemCount();++i)
        visitTree(list, tree->topLevelItem(i));
    return list;
}

void MainWindow::find_path(QString name, QVariantMap p)
{
    QString test;
    QList<QTreeWidgetItem*> clist = ui->treeWidget->findItems(name, Qt::MatchContains|Qt::MatchRecursive);
    foreach(QTreeWidgetItem* item, clist)
    {
        if(item->childCount() == 0 && item->parent() )
        {
            test = item->parent()->text(0) +"/"+item->text(0);
            qDebug() << test;
//               emit change_song(test) ;
        }
    }
//    QVariantMap p;
    p["file_path"] = test;
    emit signalUI(kSignalPath, p);
}

void MainWindow::message(signalType sig, QVariantMap params)
{
    if (sig == kSignalPath)
    {
        qDebug() << "Server asked UI for a path";
        QString name = params["song_name"].toString();
        find_path(name, params);
    }
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    qDebug() << "In ui closeveent";
    QVariantMap p;
    emit signalSave(kSignalSave, p);
//    QThread::msleep(1000);
    myProcess->close();

    if(myProcess)
    {
    delete myProcess;
    myProcess = NULL;
    }
    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "Exit?", QMessageBox::Yes | QMessageBox::No))
    {
        event->accept();
    }
    delete ui;
}


MainWindow::~MainWindow()
{
    myProcess->close();

    if(myProcess)
    {
    delete myProcess;
    myProcess = NULL;
    }
//    myProcess->kill();
//    delete myProcess;
    delete ui;
}
