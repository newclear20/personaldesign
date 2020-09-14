#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QLineEdit>
#include <QString>
#include <QPainter>
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
    this->setFixedSize(500,650);

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
double outc,wasd[100] = {0},wasd2[100]={0},fun[4]={0};
double ans[5] = {0};       //ans
QString str,pre;
int hanshu=0;

QString MainWindow::start()   //最初的判定
{
    bool i = MainWindow::judge1();
    if ( i == 0 ) {  return  QString("ERROR"); }

    transto();

    i = judge2();                                       //无数字
    if ( i == 0 ) {  return  QString("ERROR"); }
    i = judge3();                                       //两个连续符号
    if ( i == 0 ) {  return  QString("ERROR"); }
    i = judge4();                                       //开头
    if ( i == 0 ) {  return  QString("ERROR"); }
    i = judge5();                                       //小数点唯一
    if ( i == 0 ) {  return  QString("ERROR");}
    i = judge6();                                        //*和/前
    if ( i == 0 ) {  return  QString("ERROR"); }
    i = judge7();                                        //zuo(
    if ( i == 0 ) {  return  QString("ERROR"); }
    i = judge8();                                        //you)
    if ( i == 0 ) {  return  QString("ERROR"); }
    i = judge9();                                        //+ -前
    if ( i == 0 ) {  return  QString("ERROR");}

    outc = calcu(0 , bcount - 1);

    QString temp = QString::number(outc , 'g' , 10);
    anssave(outc);
     return temp;
}


void MainWindow::anssave(double a)              //save
{
    acount++;
    if(acount >= 5) acount -= 5;
    ans[acount] = a;
    apoint = acount;
}
double MainWindow::calcu ( int a , int b)
    {
        int x = 0, y = 0, kk = 0;
        bool jud = 0,ju = 0;

        while(!ju)
        {
            for( int i = a ; i <= b ; i++ )
            {
                if(cout[i].b == 4)
                {
                    if( jud == 0)
                    {
                        x=i+1;
                        jud = 1;
                    }
                    kk++;
                }
                if( cout[i].b == 5)
                {
                    kk--;
                    if(kk == 0 )
                    {
                        y = i - 1;
                        break;
                    }
                }
            }
            if( jud == 1 )
            {
               calcu( x , y );
                cout[x-1].b = 0;
                cout[y+1].b = 0;
            }
            ju = 1;
            jud = 0;
            for( int i = a ; i <= b ; i++ )
            {
                if(cout[i].b == 4)
                {
                    ju = 0;
                    break;
                }
            }
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
                int count1 = cout[i+1].a;

                int k;
                for(k = 0; count1 > 0 ; k++)
                    count1/=10;

                for( ; k>0 ; k--)
                    cout[i+1].a /= 10;
                cout[l].a += cout[i+1].a;
                cout[i+1].b = 0;
                cout[i].b = 0;

            }
        }


        int l = -1;
        for(int i = a ; i <= b ; i++ )                 //Ans,Pi
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

        for(int i = b ; i >= a ; i-- )
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

                   if(cout[i].a>=0&&cout[i].a < 0.000000001)
                       cout[i].a = 0;
                   if(cout[i].a<0&&cout[i].a>-0.00000001)
                       cout[i].a=0;
                    cout[i].b = 1;
                    cout[l].b = 0;
                    continue;
                }
                if(cout[i].a == 3)                       //cos
                {
                    cout[i].a = cos(cout[l].a);

                    cout[i].b = 1;
                    cout[l].b = 0;
                    if(cout[i].a>=0&&cout[i].a < 0.000000001)
                        cout[i].a = 0;
                    if(cout[i].a<0&&cout[i].a>-0.00000001)
                        cout[i].a=0;
                    continue;
                }
                if(cout[i].a == 4)                       //tan
                {
                    cout[i].a = tan(cout[l].a);
                    if(cout[i].a>=0&&cout[i].a < 0.000000001)
                        cout[i].a = 0;
                    if(cout[i].a<0&&cout[i].a>-0.00000001)
                        cout[i].a=0;
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
        int count2 = 0;
        for(int i = a ; i <= b ; i++ )
        {

            if( cout[i].b == 0 ) continue;

            if(count2== 0 && !(cout[i].b == 2 && cout[i].a == 2)) break;

            if( cout[i].b == 2 && cout[i].a == 2 && count2 == 0)
            {
                l = i;
                count2 = 1;
                continue;
            }

            if( cout[i].b == 1 && count2 == 1)
            {
                cout[i].a = 0 - cout[i].a;
                cout[l].b = 0;

                break;
            }

            if(count2 == 1 && cout[i].b != 0)
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
            if( cout[i].b == 1)
                return cout[i].a ;

        return 0;
    }
 bool MainWindow::judge1(){                       //括号

    int l1=0,l2=0,r1=0,r2=0;

    for(int i=0 ; i<j ;i++)                  //（）【】
    {
        if(str[i] == '(') l1++;
        if(str[i] == ')') r1++;
        if(str[i] == '[') l2++;
        if(str[i] == ']') r2++;
    }

    if(l1 != r1 || l2 != r2) return 0;

    for(int i=0 ; i<j ;i++)
    {
        if ( str[i] == '[')
        {
            if ( str[i+1] == ']') return 0;      //[]
            if ( i > 0 && str[i-1] == '.')
                return 0;                         //[x].[x]
            for(i++ ; str[i] != ']'; i++)      //
            {
                if(str[i] < '0' || str[i] > '9') return 0;
            }
        }
    }
    return 1;
}
 bool MainWindow::judge2(){                 //如果输入的只有符号无数字就进行报错
     if (hanshu==1)
         return 1;
    if(hanshu==0){
     int value=0;
     for( int i=0 ; i< j;i++){
         if ( i<= j && ((str[i]>='0' && str[i] <= '9')||(str[i]>= 'A' && str[i] <= 'F' )) )
         value++;

     }

     if(value){
         return 1;

        }
     return 0;}
}
 bool MainWindow::judge3(){                 //如果又两个来连续 的四则符号
     if (hanshu==1)
         return 1;
    if(hanshu==0){
     int value0=0;

      for( int i=0 ; i< j-1;i++){
          if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/')

              if(str[i+1]=='+'||str[i+1]=='-'||str[i+1]=='*'||str[i+1]=='/')

                  value0++;
       }
      if(value0){
              return 0;

             }
          return 1;}

  }
 bool MainWindow::judge4(){                     //如果开头输入的无效
     if (hanshu==1)
         return 1;
     if(hanshu==0){
     int value1=0;
        if(str[0]=='.'||str[0]==']'||str[0]=='*'||str[0]=='/'||str[0]==')')
       value1++;
        if(value1){
                return 0;

               }
            return 1;}
   }
 bool MainWindow::judge5(){                    //小数点在一个数中出现多个
     if (hanshu==1)
         return 1;
     if(hanshu==0){
         int value2=0;
         for( int i=0 ; i< j;i++){
             if(str[i]=='.'){
             for(int z=i;z<j;z++){
                 if(str[z]=='.'){
                     for(int x=i;x<=z;x++){
                         if(str[x]=='+'||str[x]=='-'||str[x]=='*'||str[x]=='/')
                             value2++;
                     }
                 }

             }



                 }}
             if(!value2){
                     return 1;

                    }
                 return 0;}

 }
 bool MainWindow::judge6(){                    //乘数运算符 前不能为左括号和.
     if (hanshu==1)
         return 1;
     if(hanshu==0){
     int value3=0;
     for( int i=1; i< j;i++){
         if(str[i]=='*'||str[i]=='/')
             if(str[i-1]=='('||str[i-1]=='.')
             value3++;
         }
     if(value3){
             return 0;

            }
         return 1;}
 }
 bool MainWindow::judge7(){                    //左括号前不能为右括号和.和数字字母
     if (hanshu==1)
         return 1;
     if(hanshu==0){
     int value4=0;
     for( int i=1; i< j;i++){
         if(str[i]=='(')
             if(str[i-1]==')'||str[i-1]=='.'||(str[i-1]>='0'&&str[i-1]<='9')||(str[i-1]>='A'&&str[i-1]<='G'))
             value4++;}
         if(value4){
                 return 0;

                }
             return 1;}

 }
 bool MainWindow::judge8(){                     //右括号前不能为左括号或运算符或.
     if (hanshu==1)
         return 1;
     if(hanshu==0){
     int value5=0;
     for( int i=1; i< j-1;i++){
         if(str[i]=='.')
             if(str[i-1]=='('||str[i-1]=='+'||str[i-1]=='-'||str[i-1]=='*'||str[i-1]=='/'||str[i-1]=='.')
             value5++;}
         if(value5){
                 return 0;

                }
             return 1;}
 }
 bool MainWindow::judge9(){                   //+与 -前面不能为小数点
     if (hanshu==1)
         return 1;
     if(hanshu==0){
     int value6=0;
     for( int i=1; i< j-1;i++){
         if(str[i]=='+'||str[i]=='-')
             if(str[i-1]=='.')
             value6++;}
         if(value6){
                 return 0;

                }
             return 1; }
}
 void MainWindow::transto()                         //字符串转换
    {
        int t=0,gap=10;

        for( int i=0 ; i< j;i++ ,gap =10 ,t=0 )
        {

            if( str[i] == '[' )
            {
                for(i++,gap=0 ; str[i] != ']' ; i++)
                {
                    gap*=10;
                    QChar ch = str.QString::at(i);
                    gap+=ch.unicode() - '0';
                }

                i++ ;
            }
            if ( i<= j && ((str[i]>='0' && str[i] <= '9')||(str[i]>= 'A' && str[i] <= 'F' )) )
            {
            for( ; i<= j && ((str[i]>='0' && str[i] <= '9')||(str[i] >= 'A' && str[i] <= 'F' ));i++)
            {

                if(str[i]>='0' && str[i] <= '9')
                {
                    t*=gap;
                    QChar ch = str.QString::at(i);
                    t+=ch.unicode() - '0';
                }
                if( str[i]>= 'A' && str[i] <= 'F')
                {
                    t*=gap;
                    QChar ch = str.QString::at(i);
                    t+=ch.unicode()+10 - 'A';
                }
            }
            i--;
            cout[bcount].a = t;
            cout[bcount++].b = 1;

            }
            else                                                 //对字符串当中进行判定
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
                if( str[i] == 's' && str[i+1] == 'q'){   //sqrt
                        cout[bcount].a = 1;
                        cout[bcount++].b = 3;
                        hanshu=1;
                        i+=3; }
                if( str[i] == 's' && str[i+1] == 'i'){   //sin
                        cout[bcount].a = 2;
                        cout[bcount++].b = 3;
                        hanshu=1;
                        i+=2; }
                if( str[i] == 'c' && str[i+1] == 'o'){   //cos
                        cout[bcount].a = 3;
                        cout[bcount++].b = 3;
                        hanshu=1;
                        i+=2; }
                if( str[i] == 't' && str[i+1] == 'a'){   //tan
                        cout[bcount].a = 4;
                        cout[bcount++].b = 3;
                        hanshu=1;
                        i+=2; }
                if( str[i] == 'l' && str[i+1] == 'g'){   //lg
                        cout[bcount].a = 5;
                        cout[bcount++].b = 3;
                        hanshu=1;
                        i++;  }
                if( str[i] == 'l' && str[i+1] == 'n'){   //ln
                        cout[bcount].a = 6;
                        cout[bcount++].b = 3;
                        hanshu=1;
                        i++;  }
                if( str[i] == 'p' && str[i+1] == 'i'){   //pi
                        cout[bcount].a = 1;
                        cout[bcount++].b = 6;
                        hanshu=1;
                        i++;  }
                if( str[i] == 'e' ){                         //e
                        cout[bcount].a = 2;
                        cout[bcount++].b = 6;
                        hanshu=1;
                }
                if( str[i] == 'a' && str[i+1] == 'n'){   //ans
                        cout[bcount].a = 3;
                        cout[bcount++].b = 6;
                        hanshu=1;
                        i+=2; }
                if( str[i] == '('){
                        cout[bcount++].b = 4;  }
                if( str[i] == ')'){
                        cout[bcount++].b = 5;  }
            }

        }

    }
int MainWindow::YUE(double a, double b)          //最大公约数
    {

        int x = a, y = b , z ;
        z = x>y?x/2:y/2;
        for(int i = z; i>=0; i--)
            if(x%i == 0 && y%i == 0)
                 return i;
   return 0;

    }

  int MainWindow::BEI(double a, double b)         //最小公倍数
    {
        int x = a , y = b ,z , w;
        z= x>y?x:y;
        w = x* y ;
        for(int i = z ; i <= w ; i++ )
            if(i%x == 0 && i%y == 0)
                return i;
        return 0;
    }


 //下面为UI界面




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
     hanshu=0;
     str = "0";
     pre = "0";
     j = 0;
     count= 0;
     count0= 0;
     bcount = 0;
     c = 0;
     p = 0;
     ui->INput->setText(QString(str));
     ui->OUTput->setText(QString(str));


 }




void MainWindow::on_BTEQUAL_clicked()
{

    if(count == 0)
    {
        hanshu=0;
        ui->INput->setText(QString(str));
        QString temp = MainWindow::start ();


        ui->OUTput->setText(temp);
        str = "0";
        j = 0;
        bcount = 0;


    }
    if(count== 1)                                                        //CMP
    {
        QString temp = start();
        pre = pre + temp;
        if (count0== 0) pre = pre+ "  second:";
        ui->INput->setText(QString(pre));
        wasd[count0++] = outc;
        str = "0";
        j = 0;
        bcount = 0;
        if( count0 == 1) ui->OUTput->setText(QString(str));
        if( count0 == 2)
        {
            if(wasd[0] > wasd[1]) ui->OUTput->setText(QString(">"));
            if(wasd[0] ==wasd[1]) ui->OUTput->setText(QString("="));
            if(wasd[0] < wasd[1]) ui->OUTput->setText(QString("<"));

            count = 0;
            pre = "0";
            count0 = 0;
            hanshu=0;
        }
    }
    if(count == 2)
    {
        QString temp= start();
        pre= pre+ temp;
        if (count0== 0) pre = pre + "  second:";
        ui->INput->setText(QString(pre));
        wasd[count0++] = outc;
        str = "0";
        j = 0;
        bcount = 0;
        if( count0 == 1) ui->OUTput->setText(QString(str));
        if( count0 == 2)
        {
            double temp = YUE( wasd[0] , wasd[1]);
            QString temp1 = QString::number(temp , 'g' , 10);
            ui->OUTput->setText(QString(temp1));

           count = 0;
            pre= "0";
           count0= 0;
           hanshu=0;
        }
    }
    if(count== 3)
    {
        QString temp= start();
        pre= pre+ temp;
        if (count0== 0) pre = pre + "  second:";
        ui->INput->setText(QString(pre));
        wasd[count0++] = outc;
        str = "0";
        j = 0;
        bcount = 0;
        if( count0 == 1) ui->OUTput->setText(QString(str));
        if( count0 == 2)
        {
            double temp = BEI( wasd[0] , wasd[1]);
            QString temp1 = QString::number(temp , 'g' , 10);
            ui->OUTput->setText(QString(temp1));

           count = 0;
            pre= "0";
           count0= 0;
            hanshu=0;
        }
    }
    if(count == 5)                                                        //a/x =
    {
        QString temp = start();
        if (count0== 0) pre = pre + temp;
        if (count0 == 0) pre= pre + "  x=";
        ui->INput->setText(QString(pre));
        fun[count0] = outc;
        str = "0";
        j = 0;
        bcount = 0;
        if( count0 == 0) ui->OUTput->setText(QString(str));
        if( count0 == 1)
        {
            double temp = fun[0]/fun[1];
            QString temp1  = QString::number(temp , 'g' , 10);
            ui->OUTput ->setText(QString(temp1));
        }
        if ( count0 == 0 ) count0++;

    }
    if(count == 4)                                                        //ax+b =
    {
        QString temp = start();
        if (count0 <= 1) pre = pre + temp;
        if (count0 == 0) pre = pre + " b=";
        if (count0 == 1) pre = pre + " x=";
        ui->INput->setText(QString(pre));
        fun[count0] = outc;
        str = "0";
        j = 0;
        bcount = 0;
        if( count0 <= 1) ui->OUTput->setText(QString(str));
        if( count0 == 2)
        {
            double temp = fun[0]*fun[2]+fun[1];
            QString temp1 = QString::number(temp, 'g' , 10);
            ui->OUTput->setText(QString(temp1));
        }
        if ( count0 <= 1 ) count0++;

    }
    if(count == 6)                                                        //ax^2+bx+c =
    {
         QString temp  = start();
        if (count0 <= 2) pre = pre + temp;
        if (count0 == 0) pre = pre + " b=";
        if (count0 == 1) pre = pre + " c=";
        if (count0 == 2) pre = pre + " x=";
        ui->INput->setText(QString(pre));
        fun[count0] = outc;
        str = "0";
        j = 0;
        bcount = 0;
        if( count0 <= 2) ui->OUTput->setText(QString(str));
        if( count0 == 3)
        {
            double temp = fun[0]*fun[3]*fun[3]+fun[1]*fun[3]+fun[2];
            QString temp1 = QString::number(temp , 'g' , 10);
            ui->OUTput->setText(QString(temp1));
        }
        if ( count0 <= 2 ) count0++;

    }
    if(count == 7)                                                        //a^x =
    {
        QString temp = start();
        if (count0 == 0) pre = pre + temp;
        if (count0 == 0) pre = pre + " x=";
        ui->INput->setText(QString(pre));
        fun[count0] = outc;
        str = "0";
        j = 0;
        bcount = 0;
        if( count0 == 0) ui->OUTput->setText(QString(str));
        if( count0 == 1)
        {
            double temp = 1;
            int z = fun[1];
            for(int i = 0 ; i < z ; i++ )
                temp*= fun[0];
            QString temp1 = QString::number(temp , 'g' , 10);
            ui->OUTput->setText(QString(temp1));
        }
        if ( count0 == 0 ) count0++;
    }
    if(count == 8)                                                        //loga x =
    {
        QString temp= start();
        if (count0 == 0) pre= pre +temp;
        if (count0 == 0) pre = pre+ " x=";
        ui->INput->setText(QString(pre));
        fun[count0] = outc;
        str = "0";
        j = 0;
        bcount = 0;
        if(count0 == 0) ui->OUTput->setText(QString(str));
        if(count0 == 1)
        {
            double temp = log(fun[1])/log(fun[0]);
            QString temp1 = QString::number(temp, 'g' , 10);
            ui->OUTput->setText(QString(temp1));
        }
        if ( count0 == 0 ) count0++;

    }

}


void MainWindow::on_BTTAN_clicked()
{
    str[j++]='t';
    str[j++]='a';
    str[j++]='n';
    hanshu=1;
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
    hanshu=1;
    j = 0;
    count= 8;
    count0 = 0;
    bcount = 0;
    str = "0";
    pre = "dishu=";
    ui->INput->setText(QString(pre));
    ui->OUTput->setText(QString(str));
}

void MainWindow::on_BTln_clicked()
{
    hanshu=1;
    str[j++]='l';
    str[j++]='n';
     ui->INput->setText(str);
}

void MainWindow::on_BTSIN_clicked()
{
    str[j++]='s';
    str[j++]='i';
    str[j++]='n';
    hanshu=1;
    ui->INput->setText(str);
}

void MainWindow::on_BTCOS_clicked()
{
    str[j++]='c';
    str[j++]='o';
    str[j++]='s';
    hanshu=1;
    ui->INput->setText(str);
}

void MainWindow::on_BTCOMP_clicked()
{

    hanshu=1;
    j = 0;
    count = 1;
    count0 = 0;
    bcount = 0;
    str = "0";
    pre = "first:";
    ui->INput->setText(QString(pre));
    ui->OUTput->setText(QString(str));

}


void MainWindow::on_BTYUE_clicked()
{
    hanshu=1;
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
    hanshu=1;
    j = 0;
    count = 5;
    count0 = 0;
    bcount = 0;
    str = "0";
    pre = "a=";
    ui->INput->setText(QString(pre));
    ui->OUTput->setText(QString(str));
}

void MainWindow::on_BTlg_clicked()
{
    hanshu=1;
    str[j++]='l';
    str[j++]='g';
     ui->INput->setText(str);
}

void MainWindow::on_BTmi_clicked()
{
    str[j++]='^';
    ui->INput->setText(str);
}

void MainWindow::on_BTsqrt_clicked()
{
    hanshu=1;
    str[j++]='s';
    str[j++]='q';
    str[j++]='r';
    str[j++]='t';

     ui->INput->setText(str);
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap("../tupain/0000"));
}

void MainWindow::on_BTbei_clicked()
{
   hanshu=1;
    j = 0;
   count = 3;
   count0= 0;
    bcount = 0;
    str = "0";
    pre = "first:";
    ui->INput->setText(QString(pre));
    ui->OUTput->setText(QString(str));
}

void MainWindow::on_BTX_clicked()
{
    hanshu=1;
    j = 0;
    count= 4;
    count0 = 0;
    bcount = 0;
    str = "0";
    pre = "a=";
    hanshu=1;
    ui->INput->setText(QString(pre));
    ui->OUTput->setText(QString(str));
}

void MainWindow::on_BTXX_clicked()
{
    hanshu=1;
    j = 0;
    count = 6;
    count0 = 0;
    bcount = 0;
    str = "0";
    pre= "a=";
    ui->INput->setText(QString(pre));
    ui->OUTput->setText(QString(str));
}

void MainWindow::on_BTAX_clicked()
{
    hanshu=1;
    j = 0;
    count = 7;
    count0 = 0;
    bcount = 0;
    str = "0";
    pre = "a=";
    ui->INput->setText(QString(pre));
    ui->OUTput->setText(QString(str));
}

void MainWindow::on_BTANS_clicked()
{
    str [ j++ ] = 'a';
    str [ j++ ] = 'n';
    str [ j++ ] = 's';
    hanshu=1;
    ui->INput->setText(QString(str));
}
