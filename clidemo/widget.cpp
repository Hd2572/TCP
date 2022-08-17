#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);  //设置窗口
    setGeometry(950, 150, 622, 467);
    setWindowTitle("客户端");

    socket = new QTcpSocket(this);  //创建对象

    connect(socket, SIGNAL(connected()), this, SLOT(Connect()));  //连接槽
    connect(socket, SIGNAL(readyRead()), this, SLOT(Get()));
    connect(socket, &QTcpSocket::disconnected, [=]() { _iscon = 0; });
}

Widget::~Widget() { delete ui; }

//连接
void Widget::Connect()
{
    ui->textEditRead->setText("连接成功！");
    _iscon = 1;
}

//接收
void Widget::Get()
{
    QString str = socket->readAll();               //读取全部信息
    ui->textEditRead->append("服务器端：" + str);  //显示
}

//连接按钮
void Widget::on_buttonconnect_clicked() { socket->connectToHost("127.0.0.1", 6666); }  //链接服务器

//发送按钮
void Widget::on_buttonsend_clicked()
{
    if (nullptr == socket || !_iscon)  //检验指针非空和连接状态
        return;

    QString str = ui->textEditWrite->toPlainText();  //获取发送信息
    if (str == "")                                   //检验信息非空
    {
        return;
    }

    socket->write(str.toUtf8().data());  //信息发送

    ui->textEditRead->append("客户端：" + str);  //显示
    ui->textEditWrite->clear();                  //清空输入栏
}

void Widget::on_buttonclose_clicked()  //断开按钮
{
    if (socket == nullptr)  //检验指针非空
        return;

    QString str = "客户端断开连接！";  //发送提示语
    socket->write(str.toUtf8().data());
    ui->textEditRead->append(str);  //自己显示

    socket->disconnectFromHost();  //断开
    socket->close();
}
