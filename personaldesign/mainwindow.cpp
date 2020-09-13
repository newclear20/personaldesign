#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QLineEdit>
#include <QString>

#include <math.h>
#include <QDebug>

#define _USE_MATH_DEFINES

QT_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("计算器");

}

MainWindow::~MainWindow()
{
    delete ui;
}
class mycout   //定义新类  用于试别
{
public:
    double a=0;
    int b;
};
mycout cout[ 100 ];     //数组
int bcount = 0 ,acount = 0 ,apoint = 0;//工具
int j = 0;           //jishu
int c = 0,p = 0;     //yue
int count = 0 , count0 = 0;
double outc,spe[200] = {0};
double ans[5] = {0};       //ans
QString str,pre,temp;
QString MainWindow::start()   //最初的判定
{
    bool i = MainWindow::judge1();
    if ( i == 0 ) {  return  QString("ERROR"); }

    trans();

    i = judge2();
    if ( i == 0 ) {  return  QString("ERROR"); }

    outc = calcu(0 , bcount - 1);

    QString ot = QString::number(outc , 'g' , 10);
    anssave(outc);
     return ot;
}

void MainWindow::anssave(double a)              //save
{
    acount++;
    if(acount >= 5) acount -= 5;
    ans[acount] = a;
    apoint = acount;
}

double MainWindow::calcu(int a , int b)           //计算
{
    int x = 0, y = 0;
    bool jud = 0;
    for( int i = a ; i <= b ; i++ )
        if(cout[i].b == 4)
        {
            x=i+1;
            jud = 1;
            break;
        }
    for( int i = b ; i >= 0 ; i-- )
        if( cout[i].b == 5)
        {
            y = i-1;
            break;
        }
    if( jud == 1 )
    {
        calcu( x , y );
        cout[x-1].b = 0;
        cout[y+1].b = 0;
    }

    for(int i = a ; i <= b ; i++ )
    {

        int l;

        if( cout[i].b == 0) continue;
        if( cout[i].b == 1)
        {
            l = i;

        }

        if ( cout[i].b == 2 && cout[i].a == 6)
        {
            int te = cout[i+1].a;


            for(int h = 0; te > 0 ; h++)
                te/=10;

            for(int h=0; h>0 ; h--)
                cout[i+1].a /= 10;
            cout[l].a += cout[i+1].a;
            cout[i+1].b = 0;
            cout[i].b = 0;

        }
    }
     int l = -1;
    for(int i = a ; i <= b ; i++ )                 //Ans,Π
    {
        if( cout[i].b == 0) continue;

        if( cout[i].b == 1)
        {
            l = i;

        }


        if( cout[i].b > 1 && cout[i].b < 6)
            l = -1;

        if( cout[i].b == 6)
        {
            if( l != -1)
            {
                if( cout[i].a == 1) cout[l].a *= M_PI;
                if( cout[i].a == 2) cout[l].a *= exp(1);
                if( cout[i].a == 3) cout[l].a *= ans[acount];
                cout[i].b = 0;

            }
            if( l == -1 )
            {
                if( cout[i].a == 1)
                {
                    cout[i].b = 1;
                    cout[i].a = M_PI;
                }
                if( cout[i].a == 2)
                {
                    cout[i].b = 1;
                    cout[i].a = exp(1);
                }
                if( cout[i].a == 3)
                {
                    cout[i].b = 1;
                    cout[i].a = ans[acount];
                }

            }
        }
    }
    for(int i = a ; i <= b ; i++ )
    {
        double temp0 ;
        int l;

        if( cout[i].b == 0) continue;
        if( cout[i].b == 1)
        {
            l = i;
            temp0 = cout[i].a;
        }

        if( cout[i].b == 2 && cout[i].a == 5)
        {
            for(int k = 1 ; k < cout[i+1].a ; k++ )
                cout[l].a *= temp0;
            cout[i].b = 0;
            cout[i+1].b = 0;

        }
    }

    for(int i = b ; i >= a ; i-- )                 //
    {
        int l;


        if( cout[i].b == 0) continue;

        if( cout[i].b == 1)
        {
            l = i;

        }

        if( cout[i].b == 3)
        {
            if(cout[i].a == 1)                       //sqrt
            {
                cout[i].a = sqrt(cout[l].a);
                cout[i].b = 1;
                cout[l].b = 0;
                continue;
            }
            if(cout[i].a == 2)                       //sin
            {
                cout[i].a = sin(cout[l].a);
                cout[i].b = 1;
                cout[l].b = 0;
                continue;
            }
            if(cout[i].a == 3)                       //cos
            {
                cout[i].a = cos(cout[l].a);
                cout[i].b = 1;
                cout[l].b = 0;
                continue;
            }
            if(cout[i].a == 4)                       //tan
            {
                cout[i].a = tan(cout[l].a);
                cout[i].b = 1;
                cout[l].b = 0;
                continue;
            }
            if(cout[i].a == 5)                       //lg
            {
                cout[i].a = log10(cout[l].a);
                cout[i].b = 1;
                cout[l].b = 0;
                continue;
            }
            if(cout[i].a == 6)                       //ln
            {
                cout[i].a = log(cout[l].a);
                cout[i].b = 1;
                cout[l].b = 0;
                continue;
            }
            for( int k = i-1 ; k >= a ; k-- )
            {
                if(cout[k].b == 0) continue;

                if(cout[k].b > 1 ) break;

                if(cout[k].b == 1)
                {
                    cout[i].a *= cout[k].a;
                    cout[k].b = 0;
                }
            }

            i++;
        }


    }

    int ju = 0;
    for(int i = a ; i <= b ; i++ )                 //
    {

        if( cout[i].b == 0 ) continue;

        if(ju == 0 && !(cout[i].b == 2 && cout[i].a == 2)) break;

        if( cout[i].b == 2 && cout[i].a == 2 && ju == 0)
        {
            l = i;
            ju = 1;
            continue;
        }

        if( cout[i].b == 1 && ju == 1)
        {
            cout[i].a = 0 - cout[i].a;
            cout[l].b = 0;

            break;
        }

        if(ju == 1 && cout[i].b != 0)
        {

            break;
        }
    }

    for(int i = a ; i <= b ; i++ )
    {
        int l1, l2;

        if( cout[i].b == 0) continue;

        if( cout[i].b == 1) l1 = i;

        if( cout[i].b == 2)
        {
            if( cout[i].a == 3)
            {
                for( int k = i+1 ; k <= b ; k++ )
                {
                    if( cout[k].b == 1)
                    {
                        l2 = k;
                        break;
                    }
                }
                cout[i].a = cout[l2].a * cout[l1].a;
                cout[i].b = 1;
                cout[l1].b = 0;
                cout[l2].b = 0;
                i--;

            }

            else if( cout[i].a == 4)
            {
                for( int k = i+1 ; k <= b ; k++ )
                {
                    if( cout[k].b == 1)
                    {
                        l2 = k;
                        break;
                    }
                }
                cout[i].a = cout[l1].a / cout[l2].a;
                cout[i].b = 1;
                cout[l1].b = 0;
                cout[l2].b = 0;
                i--;

            }
        }

    }

    for(int i = a ; i <= b ; i++ )
    {
        int l1 , l2 ;

        if( cout[i].b == 0) continue;

        if( cout[i].b == 1) l1 = i;

        if( cout[i].b == 2)
        {
            if( cout[i].a == 1)
            {
                qDebug() << " " << cout[l1].a <<endl;
                for( int k = i+1 ; k <= b ; k++ )
                {
                    if( cout[k].b == 1)
                    {
                        l2 = k;
                        break;
                    }
                }
                cout[i].a = cout[l2].a + cout[l1].a;
                cout[i].b = 1;
                cout[l1].b = 0;
                cout[l2].b = 0;
                i--;

            }

            else if( cout[i].a == 2)
            {
                for( int k = i+1 ; k <= b ; k++ )
                {
                    if( cout[k].b == 1)
                    {
                        l2 = k;
                        break;
                    }
                }
                cout[i].a = cout[l1].a - cout[l2].a;
                cout[i].b = 1;
                cout[l1].b = 0;
                cout[l2].b = 0;
                i--;

            }

        }

    }



    for(int i = a; i <= b ; i++ )
        if( cout[i].b == 1) return cout[i].a ;

    return 0;
}

bool MainWindow::judge2()                       //
{
    return 1;
}

void MainWindow::trans()                             //字符串转换
{
    int t=0,gap=10;

    for( int i=0 ; i< j ;i++ ,gap=10 ,t=0 )
    {

        if(str [i] == '[' )                                   //
        {
            for(i++,gap=0 ; str[i] != ']' ; i++)
            {
                gap*=10;
                QChar Zero= str.QString::at(i);
                gap+=Zero.unicode()-'0';
            }

            i++ ;
        }
        if ( i<= str && ((str[i]>='0' && str[i] <= '9')||(str[i]>= 'A' && str[i] <= 'F' )) )
        {
        for( ; i<= str && ((str[i]>='0' && str[i] <= '9')||(str[i] >= 'A' && str[i] <= 'F' ));i++)
        {
            t*=gap;

            if(str[i]>='0' && str[i] <= '9')
            {

                QChar Zero = str.QString::at(i);
                t+=Zero.unicode() - '0';
            }
            if( str[i]>= 'A' && str[i] <= 'F')
            {

                QChar Zero = str.QString::at(i);
                t+=Zero.unicode() +10-'A';
            }
        }
        i--;
        cout[bcount].a = t;
        cout[bcount++].b = 1;

        }
        else
        {
            if( str[i] == '+'){
                    cout[bcount].a = 1;
                    cout[bcount++].b = 2; }
            if( str[i] == '-'){
                    cout[bcount].a = 2;
                    cout[bcount++].b = 2; }
            if( str[i] == '*'){
                    cout[bcount].a = 3;
                    cout[bcount++].b = 2; }
            if( str[i] == '/'){
                    cout[bcount].a = 4;
                    cout[bcount++].b = 2; }
            if( str[i] == '^'){
                    cout[bcount].a = 5;
                    cout[bcount++].b = 2; }
            if( str[i] == '.'){
                    cout[bcount].a = 6;
                    cout[bcount++].b = 2; }
            if( str[i] == 's' && str[i+1] == 'q'){
                    cout[bcount].a = 1;
                    cout[bcount++].b = 3;
                    i+=3; }
            if( str[i] == 's' && str[i+1] == 'i'){
                    cout[bcount].a = 2;
                    cout[bcount++].b = 3;
                    i+=2; }
            if( str[i] == 'c' && str[i+1] == 'o'){
                    cout[bcount].a = 3;
                    cout[bcount++].b = 3;
                    i+=2; }
            if( str[i] == 't' && str[i+1] == 'a'){
                    cout[bcount].a = 4;
                    cout[bcount++].b = 3;
                    i+=2; }
            if( str[i] == 'l' && str[i+1] == 'g'){
                    cout[bcount].a = 5;
                    cout[bcount++].b = 3;
                    i++;  }
            if( str[i] == 'l' && str[i+1] == 'n'){
                    cout[bcount].a = 6;
                    cout[bcount++].b = 3;
                    i++;  }
            if( str[i] == 'p' && str[i+1] == 'i'){
                    cout[bcount].a = 1;
                    cout[bcount++].b = 6;
                    i++;  }
            if( str[i] == 'e' ){                         //e
                    cout[bcount].a = 2;
                    cout[bcount++].b = 6;  }
            if( str[i] == 'a' && str[i+1] == 'n'){   //ans
                    cout[bcount].a = 3;
                    cout[bcount++].b = 6;
                    i+=2; }
            if( str[i] == '('){
                    cout[bcount++].b = 4;  }
            if( str[i] == ')'){
                    cout[bcount++].b = 5;  }
        }

    }

}

bool MainWindow::judge1()                       //
{
    int l1=0,l2=0,r1=0,r2=0;

    for(int i=0 ; i<j ;i++)                  //
    {
        if(str[i] == '(') l1++;
        if(str[i] == '[') l2++;
        if(str[i] == ')') r1++;
        if(str[i] == ']') r2++;
    }

    if(l1 != r1 || l2 != r2) return 0;

    for(int i=0 ; i<j ;i++)
    {
        if ( str[i] == '[')                      // 
        {
            if ( str[i+1] == ']') return 0;      //[]
            if ( i > 0 && str[i-1] == '.') return 0;      //[x]3.[x]3
            for(i++ ; str[i] != ']'; i++)        //[+-^]
            {
                if(str[i] < '0' || str[i] > '9') return 0;
            }
        }
    }
    return 1;
}

void MainWindow::yue (double a, double b)              //
{
    int x = a, y = b , z ;
    z = x>y?x/2:y/2;
    for(int i = 2 ; i<=z ; i++)
        if(x%i == 0 && y%i == 0) spe[c++] = i;
      p=spe[c-1];


}


void MainWindow::on_BT00_clicked()
{
    str[j++]='0';
    ui->INput->setText(str);
}

void MainWindow::on_BT01_clicked()
{
    str[j++]='1';
    ui->INput->setText(str);
}


void MainWindow::on_BT02_clicked()
{
    str[j++]='2';
   ui->INput->setText(str);
}


void MainWindow::on_BT03_clicked()
{
   str[j++]='3';
    ui->INput->setText(str);
}

void MainWindow::on_BT04_clicked()
{
    str[j++]='4';
    ui->INput->setText(str);
}

void MainWindow::on_BT05_clicked()
{
  str[j++]='5';
    ui->INput->setText(str);
}
void MainWindow::on_BT06_clicked()
{
    str[j++]='6';
   ui->INput->setText(str);
}

void MainWindow::on_BT07_clicked()
{
  str[j++]='7';
    ui->INput->setText(str);
}

void MainWindow::on_BT08_clicked()
{
   str[j++]='8';
    ui->INput->setText(str);
}

void MainWindow::on_BT09_clicked()
{
    str[j++]='9';
    ui->INput->setText(str);
}
void MainWindow::on_BTPOINT_clicked()
{
    str[j++]='.';
    ui->INput->setText(str);
}

void MainWindow::on_BTPLUS_clicked()
{
   str[j++]='+';
   ui->INput->setText(str);
}

void MainWindow::on_BTMINUS_clicked()
{
  str[j++]='-';
   ui->INput->setText(str);
}

void MainWindow::on_BTMULT_clicked()
{
   str[j++]='*';
   ui->INput->setText(str);
}

void MainWindow::on_BTDIV_clicked()
{
   str[j++]='/';
    ui->INput->setText(str);
}

void MainWindow::on_BTLEFT_clicked()
{
  str[j++]='(';
    ui->INput->setText(str);
}

void MainWindow::on_BTRIGHT_clicked()
{
  str[j++]=')';
   ui->INput->setText(str);
}

void MainWindow::on_BTDEL_clicked()
{
    if(j>0) {
    str[--j]=0;
    ui->INput->setText(str);
    }


}

void MainWindow::on_BTAC_clicked()
{

     str = "0";
     pre = "0";
     j = 0;
     count= 0;
     count0= 0;
     bcount = 0;
     ui->INput->setText(QString(str));
     ui->OUTput->setText(QString(str));
 }




void MainWindow::on_BTEQUAL_clicked()
{
    if(count == 0)
    {

        temp= MainWindow::start();

        ui->OUTput->setText(temp);
        str = "0";
        j = 0;
        bcount = 0;
    }
    if(count== 1)                                                        //CMP
    {
        temp = start();
        pre = pre + temp;
        if (count0== 0) pre = pre+ "second:";
        ui->INput->setText(QString(pre));
        spe[count0++] = outc;
        str = "0";
        j = 0;
        bcount = 0;
        if( count0 == 1) ui->OUTput->setText(QString(str));
        if( count0 == 2)
        {
            if(spe[0] > spe[1]) ui->OUTput->setText(QString(">"));
            if(spe[0] == spe[1]) ui->OUTput->setText(QString("="));
            if(spe[0] < spe[1]) ui->OUTput->setText(QString("<"));

            count = 0;
            pre = "0";
            count0 = 0;
        }
    }
    if(count == 2)
    {
        temp = start();
        pre= pre+ temp;
        if (count0 == 0) pre = pre + "second:";
        ui->INput->setText(QString(pre));
        spe[count0++] = outc;
        str = "0";
        j = 0;
        bcount = 0;
        if( count0 == 1) ui->OUTput->setText(QString(str));
        if( count0 == 2)
        {
           yue(spe[0] , spe[1]);

           ui->OUTput->setText(QString(p));
        }
    }


}


void MainWindow::on_BTTAN_clicked()
{
    str[j++]='t';
    str[j++]='a';
    str[j++]='n';
     ui->INput->setText(str);
}

void MainWindow::on_BTe_clicked()
{
    str[j++]='e';
     ui->INput->setText(str);
}

void MainWindow::on_BTpai_clicked()
{
    str[j++]='p';
    str[j++]='i';
     ui->INput->setText(str);
}

void MainWindow::on_BTA_clicked()
{
    str[j++]='A';
     ui->INput->setText(str);
}

void MainWindow::on_BTB_clicked()
{
    str[j++]='B';
     ui->INput->setText(str);
}

void MainWindow::on_BTC_clicked()
{
    str[j++]='C';
     ui->INput->setText(str);
}

void MainWindow::on_BTD_clicked()
{
    str[j++]='D';
     ui->INput->setText(str);
}

void MainWindow::on_BTE_clicked()
{
    str[j++]='E';
     ui->INput->setText(str);
}

void MainWindow::on_BTF_clicked()
{
    str[j++]='F';
     ui->INput->setText(str);
}

void MainWindow::on_BTG_clicked()
{
    str[j++]='G';
     ui->INput->setText(str);
}

void MainWindow::on_BTleft_clicked()
{
    str[j++]='[';
     ui->INput->setText(str);
}

void MainWindow::on_BTright_clicked()
{
    str[j++]=']';
     ui->INput->setText(str);
}

void MainWindow::on_BTlog_clicked()
{

}

void MainWindow::on_BTln_clicked()
{
    str[j++]='l';
    str[j++]='n';
     ui->INput->setText(str);
}

void MainWindow::on_BTSIN_clicked()
{
    str[j++]='s';
    str[j++]='i';
    str[j++]='n';
     ui->INput->setText(str);
}

void MainWindow::on_BTCOS_clicked()
{
    str[j++]='c';
    str[j++]='o';
    str[j++]='s';
     ui->INput->setText(str);
}

void MainWindow::on_BTCOMP_clicked()
{
    j = 0;
    count = 1;
    count0 = 0;
    bcount = 0;
    str = "0";
    pre = " first num:";
    ui->INput->setText(QString(pre));
    ui->OUTput->setText(QString(str));
}


void MainWindow::on_BTYUE_clicked()
{
    j = 0;
    count = 2;
    count0= 0;
    bcount = 0;
    str = "0";
    pre = "first:";
    ui->INput->setText(QString(pre));
    ui->OUTput->setText(QString(str));
}


void MainWindow::on_BTdaoshu_clicked()
{

}

void MainWindow::on_BTlg_clicked()
{
    str[j++]='l';
    str[j++]='g';
     ui->INput->setText(str);
}

void MainWindow::on_BTmi_clicked()
{
    str[j++]='^';
    ui->INput->setText(str);
}
