#ifndef WIDGET_H
#define WIDGET_H

#include <QTcpServer>  //tcp服务器
#include <QTcpSocket>  //tcp套接字类，实现网络通信数据收发
#include <QWidget>
/*
    服务端类
*/

namespace Ui
{
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

  public:
    explicit Widget(QWidget* parent = nullptr);
    ~Widget();

  private:
    Ui::Widget* ui;
    QTcpServer* server = nullptr;  //服务器指针
    QTcpSocket* socket = nullptr;  //套接字指针
  private slots:
    void on_buttonsend_clicked();   //发送按钮
    void on_buttonclose_clicked();  //断开按钮
    void Connect();                 //连接客户端
    void Get();                     //接收客户端信息
};

#endif  // WIDGET_H
