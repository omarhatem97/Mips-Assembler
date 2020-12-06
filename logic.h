#include "simulator.h"
#include "ui_simulator.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include <QCoreApplication>
#include <stdint.h>
QString to_binary(QString code);
void save_binarycode(QString code);
int zero = 0;
int const at = 1;
int const v = 2;
int const a=4;
int const s = 16;
int const t = 8;




uint16_t twos_complement(uint16_t val)
{
    return -(unsigned int)val;
}

void run_verilog ()
{
    system("cd C:\\Modeltech_pe_edu_10.4a\\examples & vsim -c fMips -do commands.txt" );
}

QString decimal_to_binary(int num, int digits){

    QString ans = "";
    QString zeros= "";
    if(num>=0)
    {
    while(num!=0) {ans=(num%2==0 ?"0":"1")+ans; num/=2;}
    for(int i=0;i< digits-ans.size();i++)zeros+= "0";
    }
    else {
       int temp = twos_complement(-num);
       while(temp!=0) {ans=(temp%2==0 ?"0":"1")+ans; temp/=2;}
    }

    return zeros + ans ;

}

QString register_number(QString reg){

    int num;
    if(reg =="$zero")num =  0;
    else if (reg =="$at")num =1 ;
    else if (reg =="$ra")num =31 ;
    else
    {
     if (reg[1]=='a')num = a;
    else if(reg[1]=='v')num = v;
     else if(reg[1]=='s')num = s;
     else if(reg[1]=='t')num = t;
     if(reg[1]=='t' &&reg[2].digitValue() >7 )num+=8;
    num += reg[2].digitValue();
}

    return  decimal_to_binary(num,5);


}

QString to_binary(QString code){
QString binary = "";
QString rs,rd,rt,shamt,funct,immediate;


QStringList list = code.split(QRegExp("[\\s , (]+"), QString::SkipEmptyParts);

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
    list[3].remove('(');
     list[3].remove(')');


    rs= register_number(list[3]);
    rt= register_number(list[1]);
    immediate = decimal_to_binary(list[2].toInt(),16);


    binary += rs + rt+ immediate ;


}
else if ( list[0]== "lw"){
    //Lw
    binary += decimal_to_binary(35,6);
    list[3].remove('(');
     list[3].remove(')');

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

    rs= register_number(list[1]);
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
  //  int omar = list[3].toInt();

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



//---------------------
// in the last bonus you should get the instructions from external files not from the editor itself
void get_inst(QString i)
{

    QFile file_reg ("D:\\testCasetxt/" +i);
    file_reg.open(QIODevice::ReadOnly);

    /*if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }*/

    QTextStream textStream1 (&file_reg);
    QString code = textStream1.readAll();
    file_reg.close();
    save_binarycode(code);
}


//---------------------------------
void save_binarycode(QString code)
{


    QFile file ("D:\\testCase/1.txt");

    QStringList strList = code.split(QRegExp("[\n]"),QString::SkipEmptyParts);

    if (file.open(QIODevice::ReadWrite))
     {
      QTextStream stream(&file);
      for(auto i : strList){
      QString convertedString=  to_binary(i);

      stream<< convertedString<<endl;
      }

  }
    run_verilog();
    file.resize(0);
}




//---------------------
