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

    void ShowTree();

    void ShowAsm();

    void ShowElem(ListNode *temp,  QTableWidget *table, int capacity);

    void on_pull_button_clicked();

    void on_browse_button_clicked();

    void setPath(QString);

    void tryToOpen();

    friend class WayToFile;

    void ClearAll();

    void on_textEdit_Data_cursorPositionChanged();

    void on_treeORasm_button_clicked();

private:

    Ui::MainWindow *ui;

    WayToFile *f;

    QString FilePath;

    bool isF;

    bool treeORasm;

    QString Tree;

    QString ASM;

};


#endif // MAINWINDOW_H
