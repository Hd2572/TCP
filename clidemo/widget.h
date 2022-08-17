#ifndef WIDGET_H
#define WIDGET_H

/*
    客户端类
*/

#include <QTcpSocket>  //只需要套接字对象
#include <QWidget>

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
    int _iscon = 0;  //连接标志
  private slots:
    void Connect();                   //连接
    void Get();                       //接收
    void on_buttonconnect_clicked();  //连接按钮

    void on_buttonsend_clicked();  //发送按钮

    void on_buttonclose_clicked();  //断开按钮

  private:
    Ui::Widget* ui;
    QTcpSocket* socket = nullptr;  //套接字对象
};

#endif  // WIDGET_H
