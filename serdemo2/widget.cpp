#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);  //设置窗口
    setWindowTitle("服务器端");
    setGeometry(350, 150, 622, 467);

    server = new QTcpServer(this);            //创建服务器
    server->listen(QHostAddress::Any, 6666);  //设置ip和端口

    //槽函数连接
    connect(server, SIGNAL(newConnection()), this, SLOT(Connect()));
}

Widget::~Widget() { delete ui; }
//连接
void Widget::Connect()
{
    socket = server->nextPendingConnection();  //返回连接好的套接字

    QString str = QString("连接成功！");  //显示成功
    ui->textEditRead->setText(str);

    //接收信息槽函数
    connect(socket, SIGNAL(readyRead()), this, SLOT(Get()));
    //断开槽函数
    connect(socket, &QTcpSocket::disconnected, [=]() { socket = nullptr; });
}
//接收
void Widget::Get()
{
    QString str2 = socket->readAll();             //读取全部内容
    ui->textEditRead->append("客户端：" + str2);  //显示
}

//发送按钮
void Widget::on_buttonsend_clicked()
{
    if (socket == nullptr)  //判断指针非空
    {
        return;
    }

    QString str = ui->textEditWrite->toPlainText();  //获取发送内容
    if (str == "")                                   //判断内容非空
    {
        return;
    }

    socket->write(str.toUtf8().data());  //转为utf8发送

    ui->textEditRead->append("服务器端：" + str);  //显示
    ui->textEditWrite->clear();                    //清空输入框
}
//断开按钮
void Widget::on_buttonclose_clicked()
{
    if (socket == nullptr)  //判断指针非空
        return;

    QString str = "服务器端断开连接！";  //发送断开信息
    socket->write(str.toUtf8().data());

    ui->textEditRead->append(str);  //显示断开

    socket->disconnectFromHost();  //断开连接
    socket->close();
    socket = nullptr;  //指针置空
}
