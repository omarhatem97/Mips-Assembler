#include "simulator.h"
#include "ui_simulator.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include <QCoreApplication>
QString to_binary(QString code);
simulator::simulator(QWidget *parent) : QWidget(parent),ui(new Ui::simulator)
{
    ui->setupUi(this);





}



QString decimal_to_binary(int num, int digits){
    QString ans = "";
    QString zeros= "";
    while(num!=0) {ans=(num%2==0 ?"0":"1")+ans; num/=2;}
    for(int i=0;i< digits- ans.size();i++)zeros+= "0";


    return zeros + ans ;

}

QString to_binary(QString code){
QString binary = "";

int zero = 0;
int at = 1;
int v = 2;
int a=4;
int s = 16;
int t = 8;
QStringList list = code.split(QRegExp("\\s+"), QString::SkipEmptyParts);

if(list[0]== "j" ){
    // Jump
  binary +=   decimal_to_binary(2,6);
  binary +=  decimal_to_binary(list[1].toInt(),26);


}
else if ( list[0]== "jal"){
    //Jal
    binary +=   decimal_to_binary(3,6);
    binary +=  decimal_to_binary(list[1].toInt(),26);

}
else if ( list[0]== "add"){
    //Add

}
else if ( list[0]== "sw"){
    //Sw

}
else if ( list[0]== "lw"){
    //Lw

}
else if ( list[0]== "sll"){
    //Sll

}
else if ( list[0]== "and"){
    //And

}
else if ( list[0]== "or"){
    //Or

}
else if ( list[0]== "beq"){
    //Beq

}
else if ( list[0]== "jr"){
    //Jr

}
else if ( list[0]== "addi"){
    //AddImmidiate

}
else if ( list[0]== "ori"){
    //OrImmidiate

}





return binary;
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
  //  get_data(); // get data from files runed by iverilog



    QString code = ui->code_textedit->toPlainText();
  QString convertedString=  to_binary(code);

  QFile file ("C:\\Users\\BodaSadalla\\Desktop\\qt\\out.txt");


    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream<< convertedString<<endl;
    }
}


