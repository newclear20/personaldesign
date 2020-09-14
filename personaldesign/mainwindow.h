#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <QSize>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *);

public:
    explicit MainWindow(QWidget *parent = 0);
    void transto();
    void anssave(double a);
    void  yue(double a ,double b);



    bool judge1();
    bool judge2();
    bool judge3();
    bool judge4();
    bool judge5();
    bool judge6();
    bool judge7();
    bool judge8();
    bool judge9();

    double calcu( int a , int b);

    QString start();
    int YUE(double a, double b);
    int BEI(double a, double b);



    ~MainWindow();

private slots:


    void on_BT00_clicked();

    void on_BT01_clicked();

    void on_BT02_clicked();

    void on_BT03_clicked();

    void on_BT04_clicked();

    void on_BT05_clicked();

    void on_BT06_clicked();

    void on_BT07_clicked();

    void on_BT08_clicked();

    void on_BT09_clicked();

    void on_BTPOINT_clicked();

    void on_BTPLUS_clicked();

    void on_BTMINUS_clicked();

    void on_BTMULT_clicked();

    void on_BTDIV_clicked();

    void on_BTLEFT_clicked();

    void on_BTRIGHT_clicked();

    void on_BTDEL_clicked();

    void on_BTAC_clicked();

    void on_BTEQUAL_clicked();

    void on_BTTAN_clicked();

    void on_BTe_clicked();

    void on_BTpai_clicked();

    void on_BTA_clicked();

    void on_BTB_clicked();

    void on_BTC_clicked();

    void on_BTD_clicked();

    void on_BTE_clicked();

    void on_BTF_clicked();

    void on_BTG_clicked();

    void on_BTleft_clicked();

    void on_BTright_clicked();

    void on_BTlog_clicked();

    void on_BTln_clicked();

    void on_BTSIN_clicked();

    void on_BTCOS_clicked();

    void on_BTCOMP_clicked();

    void on_BTYUE_clicked();

    void on_BTdaoshu_clicked();

    void on_BTlg_clicked();

    void on_BTmi_clicked();

    void on_BTsqrt_clicked();

    void on_BTbei_clicked();

    void on_BTX_clicked();

    void on_BTXX_clicked();

    void on_BTAX_clicked();

    void on_BTANS_clicked();

private:
    Ui::MainWindow *ui;





};

#endif // MAINWINDOW_H
