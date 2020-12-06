#include "simulator.h"
#include "ui_simulator.h"
#include "logic.h"
#include<string>
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

    QFile file ("D:\\vResults/1.txt");
    file.open(QIODevice::ReadOnly);
    /*if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }*/

    QTextStream textStream (&file);
    QString line = textStream.readAll();
    file.close();
    ui->reg_file->setPlainText(line);
    //endreg

    QFile memory ("D:\\vResults/2.txt");
    memory.open(QIODevice::ReadOnly);
    /*if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }*/

    QTextStream textStream2 (&memory);
    QString line2 = textStream2.readAll();
    memory.close();
    ui->data_memory->setPlainText(line2);

}


//---------------------------------
// run verilog file

/*void run_verilog ()
{
    system("cd C:\\Modeltech_pe_edu_10.4a\\examples & vsim -c fMips -do commands.txt" );
}*/








//takes the binary code and call iverilog to run the code , then compare the results with the
//expected output

void simulator::compare_results()
{
    QString res;
    QString num = ui->num_testcases->toPlainText();
    int n  = num.toInt();

    for (int i = 1 ; i<=n; i++)
    {
        QString s1 = QString::number(i) + ".txt";
        QString s2 = QString::number(i+10) + ".txt";

  //get instruction from txt file convert it to bin ,run verilog,dlete file contents
        get_inst(s1);

        //compare files with each other

        //reg result

        QFile file_reg ("D:\\vResults/1.txt");
        file_reg.open(QIODevice::ReadOnly);

        /*if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }*/

        QTextStream textStream1 (&file_reg);
        QString line1 = textStream1.readAll();
        file_reg.close();
//----
        //expected reg result
        QFile expected_reg ("D:\\expected_Res/" + s1);
        expected_reg.open(QIODevice::ReadOnly);

       /* if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }*/

        QTextStream textStream2 (&expected_reg);
        QString line2 = textStream2.readAll();
        expected_reg.close();
//-----
       //mem verilog result

        QFile file_mem ("D:\\vResults/2.txt");
        file_mem.open(QIODevice::ReadOnly);

        /*if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }*/

        QTextStream textStream3 (&file_mem);
        QString line3 = textStream3.readAll();
        file_mem.close();
 //----
        //mem expected result
        QFile expected_mem ("D:\\expected_Res/" + s2);
        expected_mem.open(QIODevice::ReadOnly);

        /*if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }*/

        QTextStream textStream4 (&expected_mem);
        QString line4 = textStream4.readAll();
        expected_mem.close();
 //------

        if((line1 == line2) && (line3 == line4))
        {
            res+="Test case "+ QString::number(i) + " : Accepted!\n";
        }
        else {
            res+="Test case "+ QString::number(i) + " : NO\n";
        }

    }


    ui->testcase->setTextColor(QColor("blue"));
    ui->testcase->setPlainText(res);

}




void simulator::on_run_clicked()
{
    QString code = ui->code_textedit->toPlainText();
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

   // save_binarycode(code);
    run_verilog();
    //delete file contets to be reused
    file.resize(0);

    get_data(); // get data from files runed by iverilog





}

void simulator::on_pushButton_clicked()
{
    compare_results();
}
