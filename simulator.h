#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QWidget>

namespace Ui {
class simulator;
}

class simulator : public QWidget
{
    Q_OBJECT

public:
    explicit simulator(QWidget *parent = nullptr);
    ~simulator();

private slots:
    void on_run_clicked();

    void on_pushButton_clicked();

private:
    Ui::simulator *ui;
    void get_data();// saves the register file data
    void compare_results(); // compare testcases like online judge
};

#endif // SIMULATOR_H
