#include "simulator.h"
#include "ui_simulator.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include <QCoreApplication>
QString to_binary(QString code);
int zero = 0;
int const at = 1;
int const v = 2;
int const a=4;
int const s = 16;
int const t = 8;
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

QString register_number(QString reg){

    int num;
    if(reg =="zero")return "0";
    else if (reg =="ra")return "1";
    else if (reg[0]=='a')num = a;
    else if(reg[0]=='v')num = v;
     else if(reg[0]=='s')num = s;
     else if(reg[0]=='t')num = t;

    num += reg[1].digitValue();


    return  decimal_to_binary(num,5);


}

QString to_binary(QString code){
QString binary = "";
QString rs,rd,rt,shamt,funct,immediate;


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

    binary += decimal_to_binary(0,6);

    rs= register_number(list[2]);
    rt= register_number(list[3]);
    rd= register_number(list[1]);
    shamt = decimal_to_binary(0,5);
    funct = decimal_to_binary(32,6);

    binary += rs + rt+ rd + shamt + funct ;




}
else if ( list[0]== "sw"){
    //Sw


    binary += decimal_to_binary(43,6);

    rs= register_number(list[3]);
    rt= register_number(list[1]);
    immediate = decimal_to_binary(list[2].toInt(),16);


    binary += rs + rt+ immediate ;


}
else if ( list[0]== "lw"){
    //Lw
    binary += decimal_to_binary(35,6);

    rs= register_number(list[3]);
    rt= register_number(list[1]);
    immediate = decimal_to_binary(list[2].toInt(),16);


    binary += rs + rt + immediate ;


}
else if ( list[0]== "sll"){
    //Sll
    binary += decimal_to_binary(0,6);
    rs=  decimal_to_binary(0,5);
    rt= register_number(list[2]);
    rd= register_number(list[1]);

    shamt = decimal_to_binary(list[3].toInt(),5);
    funct = decimal_to_binary(0,6);

    binary += rs + rt+ rd + shamt + funct ;
}

else if ( list[0]== "slt"){
    //SetLessThan
    binary += decimal_to_binary(0,6);
    rs= register_number(list[2]);
    rt= register_number(list[3]);
    rd= register_number(list[1]);

    shamt = decimal_to_binary(0,5);
    funct = decimal_to_binary(42,6);

    binary += rs + rt+ rd + shamt + funct ;
}


else if ( list[0]== "and"){
    //And

    binary += decimal_to_binary(0,6);

    rs= register_number(list[2]);
    rt= register_number(list[3]);
    rd= register_number(list[1]);

    shamt = decimal_to_binary(0,5);
    funct = decimal_to_binary(36,6);

    binary += rs + rt+ rd + shamt + funct ;

}
else if ( list[0]== "or"){
    //Or

    binary += decimal_to_binary(0,6);

    rs= register_number(list[2]);
    rt= register_number(list[3]);
    rd= register_number(list[1]);

    shamt = decimal_to_binary(0,5);
    funct = decimal_to_binary(37,6);

    binary += rs + rt+ rd + shamt + funct ;

}
else if ( list[0]== "beq"){
    //Beq

    binary += decimal_to_binary(4,6);

    rs= register_number(list[1]);
    rt= register_number(list[2]);

    immediate = decimal_to_binary(list[3].toInt(),16);

    binary += rs + rt + immediate ;

}
else if ( list[0]== "jr"){
    //Jr

    binary += decimal_to_binary(0,6);

    rs= decimal_to_binary(list[1].toInt(),5);
    rt= decimal_to_binary(0,5);
    rd= decimal_to_binary(0,5);
    shamt = decimal_to_binary(0,5);
    funct = decimal_to_binary(8,6);

    binary += rs + rt+ rd + shamt + funct ;


}
else if ( list[0]== "addi"){
    //AddImmidiate


    binary += decimal_to_binary(8,6);

    rs= register_number(list[2]);
    rt= register_number(list[1]);

    immediate = decimal_to_binary(list[3].toInt(),16);

    binary += rs + rt+ immediate ;
}
else if ( list[0]== "ori"){
    //OrImmidiate

    binary += decimal_to_binary(13,6);

    rs= register_number(list[2]);
    rt= register_number(list[1]);

    immediate = decimal_to_binary(list[3].toInt(),16);

    binary += rs + rt+  immediate ;
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

  QFile file ("C:\\Users\\BodaSadalla\\Desktop\\qt\\out.txt");

  QStringList strList = code.split(QRegExp("[\n]"),QString::SkipEmptyParts);

  if (file.open(QIODevice::ReadWrite))
  {
      QTextStream stream(&file);
      for(auto i : strList){
      QString convertedString=  to_binary(i);

      stream<< convertedString<<endl;


      }

  }

}


