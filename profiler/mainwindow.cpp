#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpers.h"
#include "gprofparser.h"

#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include <QDir>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    /*
     * gprof --brief --no-demangle --no-graph profiler > tempfile
     * addr2line -a 0000000000405396 -e profiler
     *
     */
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString filename = QFileDialog::getOpenFileName();
    if(ui->treeView->selectionModel() != NULL){
        ui->treeView->selectionModel()->clear();
        ui->plainTextEdit->clear();
    }

    if( filename != "") {

        QString cmd = "readelf --debug-dump=decodedline "  + filename +
                      " | grep -v -E '(0x[0-9a-f]+)|(^File name)|(^$)|(^Decoded)' | sort | uniq | grep -o -P '.*(?=:(\\[\\+\\+\\])?$)'";
        QString result = executeCommand(cmd, exePath);

        if( result != ""){


            QStringList lines = result.split("\n");
            lines.pop_back();
            QString line;
            QDir exe(filename);
            exe.cdUp();

            QStringList absPaths;

            foreach (line, lines) {
                qDebug()<<"----" + line;
                if( line.mid(0,4) == "CU: "){
                    line.remove(0,4);
                }

                if( QDir::isAbsolutePath(line)){
                    qDebug()<<"PATH: "<<line;
                    absPaths.append(line);
                }
                else{
                    qDebug()<<"PATH: "<<QDir::cleanPath(exe.absolutePath() + "/" + line);
                    absPaths.append(QDir::cleanPath(exe.absolutePath() + "/" + line));
                }
            }

            this->standardModel = new QStandardItemModel ;
            QStandardItem *rootNode = standardModel->invisibleRootItem();

            QString path;

            foreach(path,absPaths){
                this->setUpPath(rootNode,path);
            }

            //register the model
            ui->treeView->setModel(standardModel);
            ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->treeView->setAnimated(true);

            //now expand view where entry point is
            expandMainFunc(filename);

            this->exeName = filename;
            this->exePath  = exe.absolutePath();
        }
    }
}

void MainWindow::setUpPath(QStandardItem *root, QString path)
{
    QStringList dirs = path.split("/");
    dirs.pop_front();
    QString dir;

    foreach(dir,dirs){
        int i;
        for(i = 0; root->child(i) != NULL; i++){
            if( root->child(i)->text() == dir)
                break;
        }

        if( root->child(i) != NULL){
            root = root->child(i);
        }else{
            QStandardItem *it = new QStandardItem(dir);
            root->appendRow(it);
            root = it;
        }
    }
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    if( index.child(0,0).isValid())
        return;

    QModelIndex item = index;
    QString path;

    while( item.isValid()){
        path = item.data(0).toString() +"/" + path;
        item = item.parent();
    }
    path = "/" + path.remove(path.length()-1,1);
    qDebug()<<"FILE clicked is: "<<path;
    openFile(path);

}

void MainWindow::expandMainFunc(QString filepath)
{
    QString main = executeCommand("readelf -Ws " + filepath +
                                  " | grep 'main$' | awk '{print $2}' | addr2line -e " +
                                  filepath, exePath);
    main.remove(main.length()-1,1);
    main = QDir::cleanPath(main);
    qDebug()<<"Main FUNC is: "<<main;
    QStringList dirs = main.split("/");
    dirs.pop_front();

    QString dir;
    QModelIndex root = ui->treeView->model()->index(0,0);


    foreach(dir,dirs){

        QModelIndex tmp = getMatch(root,dir);

        if( tmp.isValid()){
            root = tmp.child(0,0);
            qDebug()<<root.data(0).toString();
        }
        else{
            qDebug()<<"exp folder is: " + root.parent().data(0).toString();
            while(root.parent().isValid()) {
                ui->treeView->setExpanded(root.parent(), true);
                root = root.parent();
            }

            break;
        }

    }
}

QModelIndex MainWindow::getMatch(QModelIndex item, QString match){

    int i = 0;
    while( item.isValid()){
        qDebug()<<item.data(0).toString();
        if( item.data(0).toString() == match && item.child(0,0).isValid())
            return item;
        i++;
        item = item.sibling(i,0);
    }

    return QModelIndex();
}

void MainWindow::openFile(QString name)
{
    ui->plainTextEdit->clear();

    QFile file(name);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QString content;

    while (!in.atEnd()) {
        QString line = in.readLine();
        content+=line+"\n";
    }

    file.close();

    this->ui->plainTextEdit->appendPlainText(content);
    ui->plainTextEdit->moveCursor(QTextCursor::Start);
}

void MainWindow::on_gprofButton_clicked()
{
    GprofParser parser(exeName,exePath);
    if( this->exeName.size() > 0)
        parser.parseGprofFlatOutput();
    else
        qDebug()<<"no file specified!";
}
