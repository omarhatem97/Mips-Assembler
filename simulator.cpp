#include "simulator.h"
#include "ui_simulator.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>

simulator::simulator(QWidget *parent) : QWidget(parent),ui(new Ui::simulator)
{
    ui->setupUi(this);

}

simulator::~simulator()
{
    delete ui;
}



// reads data from file runned by iverilog and copy the data into the regfile and datamem plaintext
void simulator::get_data()
{

    QFile file ("D:/a.txt");
    file.open(QIODevice::ReadOnly);
    /*if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }*/

    QTextStream textStream (&file);
    QString line = textStream.readAll();
    file.close();
    ui->reg_file->setPlainText(line);
    //endreg

    QFile memory ("D:/b.txt");
    memory.open(QIODevice::ReadOnly);
    /*if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }*/

    QTextStream textStream2 (&memory);
    QString line2 = textStream2.readAll();
    memory.close();
    ui->data_memory->setPlainText(line2);

}

void simulator::on_run_clicked()
{
    get_data(); // get data from files runed by iverilog
}
