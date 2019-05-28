#include "waytofile.h"
#include "ui_waytofile.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QProcess>

WayToFile::WayToFile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WayToFile)
{
    ui->setupUi(this);

    // DIRECTORIES

    dirModel = new QFileSystemModel(this);

    // Set filter
    dirModel->setFilter(QDir::NoDotAndDotDot |
                        QDir::AllDirs);

    WayToFile::start();

}

WayToFile::~WayToFile()
{
    delete ui;
}


void WayToFile::start()
{

    QString rootPath = ("");

    model.setRootPath("");
    ui->treeView->setModel(&model);
    if (!rootPath.isEmpty())
    {
        const QModelIndex rootIndex = model.index(QDir::cleanPath(rootPath));
        if (rootIndex.isValid())
            ui->treeView->setRootIndex(rootIndex);
    }

    // Demonstrating look and feel features
    ui->treeView->setAnimated(false);
    ui->treeView->setIndentation(20);
    ui->treeView->setSortingEnabled(true);
    const QSize availableSize = QApplication::desktop()->availableGeometry(ui->treeView).size();
    ui->treeView->resize(availableSize / 2);
    ui->treeView->setColumnWidth(0, ui->treeView->width() / 3);
    ui->treeView->show();
}

void WayToFile::on_treeView_doubleClicked(const QModelIndex &index)
{
    QFileSystemModel *foolist = new QFileSystemModel;
        foolist->setRootPath(QDir::rootPath());

    QModelIndexList selectedIndexes = ui->treeView->selectionModel()->selectedIndexes();
    QStringList selectedTexts;

    foreach(const QModelIndex &idx, selectedIndexes)
    {
       selectedTexts << idx.data(Qt::DisplayRole).toString();
    }
    std::string temp = selectedTexts[0].toUtf8().constData();

    if ((int)temp.find(".txt") == -1)
    {
        QMessageBox::information(this, "Error","invalid file extention (only .txt format)" );

    }
    else
    {
        FilePath = dirModel->fileInfo(index).absoluteFilePath();
        QFile file("C:\\Users\\0137\\Desktop\\SignalTranslator\\Resource\\PathToFile.txt");

        if (!file.open(QIODevice::WriteOnly))
        {
            cout << "Файл не открыт\n\n";
            file.close();
            return;
        }

        QTextStream Outstream(&file);

        Outstream << FilePath;

        file.close();

        qApp->quit();
        QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        QWidget::close();
    }

}
