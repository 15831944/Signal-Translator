#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Lexical.h"
#include "Syntax.h"
#include <QTableWidget>
#include "waytofile.h"

namespace Ui
{
   class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_button_clicked();

    void ShowAll(Lexical *Proc);

    void ShowTree(Syntax *Proc2);

    void ShowElem(ListNode *temp,  QTableWidget *table, int capacity);

    void on_pull_button_clicked();

    void on_browse_button_clicked();

    void setPath(QString);

    void tryToOpen();

    friend class WayToFile;

    void ClearAll();

private:
    Ui::MainWindow *ui;

    WayToFile *f;

    QString FilePath;



};


#endif // MAINWINDOW_H
