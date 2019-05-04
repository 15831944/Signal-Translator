#ifndef WAYTOFILE_H
#define WAYTOFILE_H

#include <QMainWindow>
#include <QDialog>
#include <QFileSystemModel>

#include <QtWidgets>
#include <QtGui>
#include <QApplication>
#include <QDesktopWidget>
#include <QFileSystemModel>
#include <QFileIconProvider>
#include <QTreeView>

namespace Ui {
class WayToFile;
}

class WayToFile : public QMainWindow
{
    Q_OBJECT

public:
    explicit WayToFile(QWidget *parent = nullptr);
    ~WayToFile();

    QString FilePath;

private slots:

    void start();

    void on_treeView_doubleClicked(const QModelIndex &index);

    private:
    Ui::WayToFile *ui;

    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;

    QFileSystemModel model;


};

#endif // WAYTOFILE_H
