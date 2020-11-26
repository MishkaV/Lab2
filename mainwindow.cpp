#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <stdlib.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_size_clicked()
{
    QMessageBox::information(this, "Size", "The size of the queue is " + QString::number(this->collection.size()));
}

int check_word(string word)
{
    int flag = 0;
    if(!word.size())
        return 0;
    for (int i = 0; i < word.size(); i++)
    {
        if (isdigit(word[i]))
            return 0;
        if(word[i] != ' ')
            flag = 1;
    }
    if(!flag)
        return 0;
    return 1;
}


void MainWindow::on_pushButton_add_ok_clicked()
{
    if(!check_word(ui->lineEdit_add->text().toStdString()))
        QMessageBox::critical(this, "Add word", "Please, write correct data"
                                                "without digits");
    else
    {
        if(!this->collection.in_dictionary(ui->lineEdit_add->text().toStdString()))
        {
            this->collection << ui->lineEdit_add->text().toStdString();
            ui->listWidget->addItem("Word: " + ui->lineEdit_add->text() +
                                "\nCount: " +
                                QString::number(this->collection[ui->
                                    lineEdit_add->text().toStdString()]));
        }
        else
        {
            this->collection << ui->lineEdit_add->text().toStdString();
            int row = -1;
            for(int i = 0; i < ui->listWidget->count(); i++)
            {
                QListWidgetItem* item = ui->listWidget->item(i);
                char *str = (char *)item->text().toStdString().c_str();
                if(strstr(str, ui->lineEdit_add->text().toLocal8Bit().data()))
                {
                    row = i;
                    break;
                }
            }
            if(row != -1)
            {
               ui->listWidget->item(row)->setText("Word: " + ui->lineEdit_add->text() +
                                         "\nCount: " +
                                         QString::number(this->
                                         collection.get_count(ui->
                                         lineEdit_add->text().toStdString())));
                ui->listWidget->update();
            }
        }
    }
    ui->lineEdit_add->setText("");
}

void MainWindow::on_pushButton_delete_all_clicked()
{
    collection.clear();
    ui->listWidget->clear();
}

void MainWindow::on_pushButton_delete_clicked()
{
    char *curr = ui->listWidget->currentItem()->text().toLocal8Bit().data();
    string word(strchr(curr,' '),1, strchr(curr,'\n') - strchr(curr,' ') - 1);
    this->collection.delete_word(word);
    ui->listWidget->takeItem(ui->listWidget->currentRow());
}

void MainWindow::on_pushButton_file_input_ok_clicked()
{
    string name = ui->lineEdit_file_input_name->text().toStdString();
    if(name.size())
    {
        this->collection.clear();
        this->collection.input_from_file(name);
        for(auto &i: this->collection.get())
            for(auto &j: i)
                ui->listWidget->addItem("Word: " +
                                    QString::fromStdString(j.first) +
                                    "\nCount: " +
                                    QString::number(j.second));
    }
    QMessageBox::information(this, "Input data", "Successful input data from file");
    ui->lineEdit_file_input_name->clear();
}

void MainWindow::on_pushButton_file_output_ok_clicked()
{
    string name = ui->lineEdit_file_output_name->text().toStdString();
    if(name.size())
        this->collection.output_to_file(name);
    QMessageBox::information(this, "Output data", "Successful output data to file");
    ui->lineEdit_file_output_name->clear();
}

void MainWindow::on_pushButton_nor_ok_clicked()
{
    int count;
    count = atoi(ui->lineEdit_nor->text().toStdString().c_str());
    QMessageBox::information(this, "Number of repetition",
                             "There are " +
                             QString::number(this->collection.count(count)) +
                             " words with such count or bigger(Count = " +
                             ui->lineEdit_nor->text() + ")");
    ui->lineEdit_nor->clear();
}

void MainWindow::on_pushButton_find_ok_clicked()
{
    string word = ui->lineEdit_find->text().toStdString();
    if (!check_word(word))
        QMessageBox::critical(this, "Find word", "Please, write correct data"
                                                "without digits");
    else
        if (this->collection.in_dictionary(word))
            QMessageBox::information(this, "Find word",
                                     "This word (" +
                                     QString::fromStdString(word) +
                                     ") is in dictionary with count " +
                                     QString::number(this->collection[word]));
        else
            QMessageBox::information(this, "Find word",
                                     "Sorry, but there is"
                                     " no such word in dictionary");
}
