#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Syntax.h"
#include <QTableWidget>

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

    void ShowAll(Syntax *Proc);

    void ShowElem(ListNode *temp,  QTableWidget *table, int capacity);

    void on_start_button_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
