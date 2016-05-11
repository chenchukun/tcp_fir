#include "mainwindow.h"
#include "Board.h"
#include "type.h"
#include "ControlView.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow()
{
	// 初始化窗口
	this->resize(900, 642);
	this->setWindowTitle("五子棋");
	this->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background, QColor(244, 197, 123));
	this->setPalette(palette);

	// 初始化对象元素
	login = new Login(this);
	// 添加 棋盘 和 控制类
	board = new Board(this);
	// control 需要控制board
	control = new ControlView(this, board);

	// 初始化网络连接
	m_tcpsocket = new QTcpSocket();
	m_tcpsocket->abort();
	m_tcpsocket->connectToHost(QHostAddress::LocalHost, 16666);
//	m_tcpsocket->connectToHost("172.18.147.44", 16666);
	// 接收服务器消息
	connect(m_tcpsocket, SIGNAL(readyRead()), this, SLOT(readMsg()));
	// 转发信号
	connect(this, SIGNAL(sendToLogin(QByteArray)), login, SLOT(readMsg(QByteArray)));
		
	connect(this, SIGNAL(sendToControl(QByteArray)), control, SLOT(readMsg(QByteArray)));
	connect(this, SIGNAL(sendToBoard(QByteArray)), board, SLOT(readMsg(QByteArray)));
	start();
}

void MainWindow::start()
{
	login->show();

	int ret = login->exec();

	if(ret == 1)
	{
		delete login;


		QHBoxLayout *mainLayout = new QHBoxLayout;
		mainLayout->addWidget(board);
		mainLayout->addWidget(control);
		mainLayout->setStretchFactor(board, 5);
		mainLayout->setStretchFactor(control, 2);
		this->setLayout(mainLayout);
		this->show();
	}
	else
	{
		exit(0);
	}
}

// 接收服务器信息
void MainWindow::readMsg()
{
	// 临时保存
	QString text;
	QByteArray tempBlock;
	QDataStream out(&tempBlock, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_7);

	// 服务类型
	int state;
	int x, y;
	QByteArray block = m_tcpsocket->readAll();
	QDataStream in(&block, QIODevice::ReadWrite);
	in.setVersion(QDataStream::Qt_4_7);
	// 获取服务类型
	in >> state;

	switch(state)
	{
	case LOGIN_YES:      // 登录成功
		in << LOGIN_YES;
		emit sendToLogin(block);
		break;
	case LOGIN_NO:     // 登录失败
		in << LOGIN_NO;
		emit sendToLogin(block);
		break;
	case REGISTER_YES:    // 注册成功
		in << REGISTER_YES;
		emit sendToLogin(block);
		break;
	case REGISTER_NO:    // 注册失败
		in << REGISTER_NO;
		emit sendToLogin(block);
		break;
	case SEND_MSG:   // 发送消息
//		QMessageBox::information(this, "登录OK", "登录OK", QMessageBox::Ok);
		in >> text;
		out << SEND_MSG;
		out << text;
		emit sendToControl(tempBlock);
		break;
	case START:     // 开始
//		QMessageBox::information(this, "start", "start", QMessageBox::Ok);
		in << START;
		emit sendToControl(block);
		break;
	case DOWN:    // 落子
		out << DOWN;
		in >> x;
		in >> y;
		out << x;
		out << y;
		emit sendToBoard(tempBlock);
		break;
	case LOSE:   // 输了
		out << LOSE;
		emit sendToBoard(tempBlock);
		break;
	case DRAW:  // 认输
		out << DRAW;
		emit sendToBoard(tempBlock);  // 用于设置棋盘为不可用
		emit sendToControl(tempBlock);  // 设置按钮
		break;
	case UNDO:  // 悔棋
		out << UNDO;
		emit sendToBoard(tempBlock);
		break;
	case LEAVE:
		QMessageBox::information(this, "对方已下线", "对方已下线", QMessageBox::Ok);
		board->setEn();
		break;

	default:
		break;
	}
}

// 转发信息到服务器
void MainWindow::sendMsg(QByteArray block)
{
//	QMessageBox::information(this, "send", "send", QMessageBox::Ok);
	m_tcpsocket->write(block);
}

void MainWindow::sendLoseMsg(QByteArray block)  // 设计问题，只能先这样写了
{
	QMessageBox::information(this, "你赢了", "你赢了", QMessageBox::Ok);
	m_tcpsocket->write(block);
}

void MainWindow::sendLeaveMsg(QByteArray block)
{
	m_tcpsocket->write(block);
	QMessageBox::information(this, "游戏结束", "游戏结束", QMessageBox::Ok);
	exit(0);
}

