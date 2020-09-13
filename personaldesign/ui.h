#ifndef UI_H
#define UI_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QString>


class UI : public QWidget
{
    Q_OBJECT

private:

    QLineEdit  *mline;              //显示行
    QPushButton *mbuton[20];        //按钮成员
    UI();
    bool construct();

private slots:
    void handler_clicked();         //处理按键消息

public:
    int  MatchingBoth(QString &str1,const char *str2);          //匹配str1和str2,判断str1是否有str2的字符
    int  LastMatchingBoth(QString &str1,const char *str2);      //反向匹配str1和str2
    static UI* NewIntance();    //成员需要资源申请,所以使用二阶构造
    void show();
};
#endif // QCALCULATORUI_H
