#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "StringList.h"
#include "QFile"
#include "QTextStream"
#include "waytofile.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    isF = true;
    ui->setupUi(this);
    MainWindow::tryToOpen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ClearAll()
{
    ui->textEdit_Tree->clear();
   // ui->textEdit_Input->clear();
    ui->tableWidget_Identificators->clear();
    ui->tableWidget_Tokens->clear();
    ui->tableWidget_Symbols->clear();
    ui->tableWidget_KeyWords->clear();
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
        ClearAll();
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
    ui->tableWidget_Tokens->setColumnWidth(2, 50);
    ui->tableWidget_Tokens->setColumnWidth(3, 50);

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

    //signal translator starts
    Lexical Proc = Lexical(input_file_name);

    if (!Proc.isError())
    {
        Syntax Proc2 = Syntax(Proc.All);
        ShowTree(&Proc2);
        if (!Proc2.isError())
        {
            ShowAll(&Proc);

        }
    }
}

void MainWindow::ShowTree(Syntax *Proc2)
{
    if (Proc2->isError())
    {
        ui->textBrowser_Error->setText( Proc2->GetErrorM() );
        ClearAll();
        return;
    }
    else
    {
        ui->textBrowser_Error->setText( (QString) "No Errors" );
        ui->textEdit_Tree->setText(Proc2->Tree);
    }

}

void MainWindow::on_pull_button_clicked()
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

void MainWindow::setPath(QString way)
{
    ui->textEdit_Input->setText(way);
    ui->textEdit_Input->show();
}


void MainWindow::on_browse_button_clicked()
{
    if (isF)
    {
        f = new WayToFile(this);
        f->show();
        isF = false;
    }
}

void MainWindow::tryToOpen()
{
    string temp_path =  SignalPath + "PathToFile.txt";
    QFile file(temp_path.c_str());

    if (!file.open(QIODevice::ReadOnly))
    {
        cout << "Файл не открыт\n\n";
        file.close();
        return;
    }

    QTextStream Outstream(&file);

    QString temp = file.readLine();
    if (temp.length() != 0)
    MainWindow::setPath(temp);

    file.close();
}

void MainWindow::on_textEdit_Data_cursorPositionChanged()
{
    QTextCursor cursor = ui->textEdit_Data->textCursor();
    QString Text = ui->textEdit_Data->toPlainText();

    int line = 0;

    for (int i = 0; i < cursor.position(); i++)
    {
        if(Text[i] == "\n")
        {
            line++;
        }
    }

    const int relativePos = cursor.position() - cursor.block().position();

    ui->label_pos->setText((const QString) ((to_string(line+1) + " "+ to_string(relativePos+1)).c_str()));
}


