#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "StringList.h"
#include "QFile"
#include "QTextStream"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowElem(ListNode *temp, QTableWidget *table, int capacity)
{
    int i = 0;
    string int_;
    table->setColumnCount(2);//задаём количество столбиков
    table->setHorizontalHeaderLabels(QStringList() << "elem" << "id" );//названия для столбиков
    table->setColumnWidth(0, 100);//ширина первого столбика
    table->setColumnWidth(1, 60);//ширина второго столбика

    table->setRowCount(capacity);//задаём количество ячеек на основе количества эл. дека

    //выводим поэлементно
    while (temp != nullptr)
    {
        int_.clear();
        int_ = to_string(temp->id);
        table->setItem(i, 0, new QTableWidgetItem((QString)temp->str));
        table->setItem(i, 1, new QTableWidgetItem((QString)int_.c_str()));
        i++;

        temp = temp->next;
    }
}

void MainWindow::ShowAll(Lexical *Proc)
{
    if (Proc->isError())
    {
        ui->textBrowser_Error->setText( Proc->GetErrorM() );
        return;
    }
    else
    {
        ui->textBrowser_Error->setText( (QString) "No Errors" );
    }

    /*~~~~~~~~~~~~KeyWords~~~~~~~~~~~~~*/

    ShowElem((ListNode*)Proc->All.Keywords.GetHead(), ui->tableWidget_KeyWords, Proc->All.Keywords.Getsize());

    /*~~~~~~~~~~~~Identificators~~~~~~~*/

    ShowElem((ListNode*)Proc->All.Identifiers.GetHead(), ui->tableWidget_Identificators, Proc->All.Identifiers.Getsize());

    /*~~~~~~~~~~~~Symbols~~~~~~~~~~~~~~*/

    ShowElem((ListNode*)Proc->All.SingleChar.GetHead(), ui->tableWidget_Symbols, Proc->All.SingleChar.Getsize());

    /*~~~~~~~~~~~~Tokens~~~~~~~~~~~~~~*/

    int i = 0;
    string int_;

    ui->tableWidget_Tokens->setColumnCount(4);
    ui->tableWidget_Tokens->setHorizontalHeaderLabels(QStringList() << "elem" << "id" << "ipos" << "jpos");
    ui->tableWidget_Tokens->setColumnWidth(0, 100);
    ui->tableWidget_Tokens->setColumnWidth(1, 60);
    ui->tableWidget_Tokens->setColumnWidth(2, 70);
    ui->tableWidget_Tokens->setColumnWidth(3, 70);

    ui->tableWidget_Tokens->setRowCount(Proc->All.Data.Getsize());

    ListNode *temp = (ListNode*) Proc->All.Data.GetHead();

    while (temp != nullptr)
    {

        ui->tableWidget_Tokens->setItem(i, 0, new QTableWidgetItem((QString)temp->str));
        int_.clear();
        int_ = to_string(temp->id);
        ui->tableWidget_Tokens->setItem(i, 1, new QTableWidgetItem((QString)int_.c_str()));
        int_.clear();
        int_ = to_string(temp->ipos);
        ui->tableWidget_Tokens->setItem(i, 2, new QTableWidgetItem((QString)int_.c_str()));
        int_.clear();
        int_ = to_string(temp->jpos);
        ui->tableWidget_Tokens->setItem(i, 3, new QTableWidgetItem((QString)int_.c_str()));
        i++;

        temp = temp->next;
    }


    /*~~~~~~~~~~~~input_Data~~~~~~~~~~~~~~*/



    /**************************/
}

void MainWindow::on_start_button_clicked()
{
    string input_file_name = ui->textEdit_Input->toPlainText().toUtf8().constData();
    string ErrorM;
    int in = ui->textEdit_Data->document()->blockCount();
    if (in < 2)
    {
        ErrorM = "No Data input";
        ui->textBrowser_Error->setText( (QString) ErrorM.c_str() );
        return;
    }
    QFile file(input_file_name.c_str());
    if(!file.open(QIODevice::WriteOnly))
    {
        ErrorM = "File Doesn't exist :" + input_file_name;
        ui->textBrowser_Error->setText( (QString) ErrorM.c_str() );
        file.close();
    }

    file.write(ui->textEdit_Data->toPlainText().toUtf8());
    file.close();

    Lexical Proc = Lexical(input_file_name);
    ShowAll(&Proc);
}

void MainWindow::on_start_button_2_clicked()
{
    string input_file_name = ui->textEdit_Input->toPlainText().toUtf8().constData();
    string ErrorM;

    QFile file(input_file_name.c_str());

    if (!file.open(QIODevice::ReadOnly))
    {
        ErrorM = "File Doesn't exist :" + input_file_name;
        ui->textBrowser_Error->setText( (QString) ErrorM.c_str() );
        file.close();
    }
    else
    {
        ui->textBrowser_Error->setText( "No Errors" );
    }

    QTextStream stream(&file);

    ui->textEdit_Data->setText(stream.readAll());
    file.close();
}

