#include <QtGui>
#include "ControlView.h"
#include "type.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

ControlView::ControlView(QWidget *parent, Board *board):m_parent(parent),m_board(board)
{

	resize(240, 602);


	// 创建图片控件
	user1Photo = new QWidget(this);
	user1Photo->setGeometry(10, 10, 100, 100);
	user1Photo->setAutoFillBackground(true);
	QPalette palette = user1Photo->palette();
	palette.setBrush(QPalette::Window, QBrush(QPixmap("/Users/chenchukun/"
		"coding/qt/qt5Project/fir/user.jpg")\
		.scaled(user1Photo->size(), Qt::IgnoreAspectRatio, 
		Qt::SmoothTransformation)));
	user1Photo->setPalette(palette);

	user1Name = new QLabel("用户名：cck", this);
	user2Name = new QLabel("用户名：chenchukun", this);
	user1Name->setGeometry(120, 10, 100, 20);
	user2Name->setGeometry(120, 120, 100, 20);

	user1Score = new QLabel("积分：1000", this);
	user2Score = new QLabel("积分：2000", this);
	user1Score->setGeometry(120, 40, 100, 20);
	user2Score->setGeometry(120, 150, 100, 20);

	


	// 创建图片2控件
	user2Photo = new QWidget(this);
	user2Photo->setGeometry(10, 120, 100, 100);
	user2Photo->setAutoFillBackground(true);
	QPalette palette2 = user2Photo->palette();
	palette2.setBrush(QPalette::Window, QBrush(QPixmap("/Users/chenchukun/"
		"coding/qt/qt5Project/fir/user.jpg")\
		.scaled(user2Photo->size(), Qt::IgnoreAspectRatio, 
		Qt::SmoothTransformation)));
	user2Photo->setPalette(palette2);


	// 聊天窗口
	talkView = new QTextEdit(this);
	talkView->setReadOnly(true);
	talkView->setGeometry(10, 230, 220, 240);

	inputText = new QLineEdit(this);
	inputText->setGeometry(25, 485, 155, 24);

	sendButton = new QPushButton("发送", this);
	sendButton->setGeometry(185,  487, 35, 20);


	// 创建按钮
	startButton = new QPushButton("开始游戏", this);
	startButton->setGeometry(25, 530, 80, 20);

	drawButton = new QPushButton("认输", this);
	drawButton->setGeometry(135, 530, 80, 20);
	drawButton->setEnabled(false);

	undoButton = new QPushButton("悔棋", this);
	undoButton->setGeometry(25, 570, 80, 20);
	undoButton->setEnabled(false);

	exitButton = new QPushButton("离开游戏", this);
	exitButton->setGeometry(135, 570, 80, 20);

	connect(this, SIGNAL(sendMsgToMain(QByteArray)), m_parent, SLOT(sendMsg(QByteArray)));
	connect(this, SIGNAL(sendStartToMain(QByteArray)), m_parent, SLOT(sendMsg(QByteArray)));
	connect(this, SIGNAL(sendDrawToMain(QByteArray)), m_parent, SLOT(sendMsg(QByteArray)));
	connect(this, SIGNAL(sendUndoToMain(QByteArray)), m_parent, SLOT(sendMsg(QByteArray)));
	connect(this, SIGNAL(sendLeaveToMain(QByteArray)), m_parent, SLOT(sendLeaveMsg(QByteArray)));
	connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMsg()));
	connect(drawButton, SIGNAL(clicked()), this, SLOT(draw()));
	connect(undoButton, SIGNAL(clicked()), this, SLOT(undo()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(leave()));
	connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
	connect(this, SIGNAL(sendStartToBoard()), m_board, SLOT(start()));
}

ControlView::~ControlView()
{

}

void ControlView::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	p.drawLine(0, 0, 240, 0);
	p.drawLine(0, 0, 0, 602);
	p.drawLine(0, 602, 240, 602);
	p.drawLine(240, 0, 240, 602);
}

void ControlView::readMsg(QByteArray block)
{
//	QMessageBox::information(this, "OK", "OK", QMessageBox::Ok);
	QDataStream in(&block, QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_4_7);
	// 服务类型
	int state;
	QString text;

	in >> state;
	switch(state)
	{
	case SEND_MSG:
		in >> text;
		talkView->append(text + '\n');
		break;
	case START:
	//	startButton->setEnabled(false);
		undoButton->setEnabled(true);
		drawButton->setEnabled(true);
		startButton->setEnabled(false);
		QMessageBox::information(this, "游戏开始", "游戏开始", QMessageBox::Ok);
		m_board->setPlayer(2);
		break;
	case DRAW:
		undoButton->setEnabled(false);
		drawButton->setEnabled(false);
		startButton->setEnabled(true);
		break;

	default:
		break;
	}
}

void ControlView::sendMsg()
{
	QString text = inputText->text();
	int type = SEND_MSG;
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_7);
	out << type;
	out << text;
	inputText->clear();
	emit sendMsgToMain(block);
}

void ControlView::start()
{
	emit sendStartToBoard();	

	// 设置按钮状态
	startButton->setEnabled(false);
	undoButton->setEnabled(true);
	drawButton->setEnabled(true);

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_7);
	out << START;
	emit sendStartToMain(block);
}

void ControlView::leave()
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_7);
	out << LEAVE;
	emit sendLeaveToMain(block);
}

void ControlView::draw()
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_7);
	out << DRAW;
	emit sendDrawToMain(block);
	m_board->setEn();
	// 设置按钮状态
	undoButton->setEnabled(false);
	drawButton->setEnabled(false);
	startButton->setEnabled(true);

	QMessageBox::information(this, "你已认输", "你已认输", QMessageBox::Ok);
//	ClearStack(m_board->m_downStack);  // 清空下棋过程栈
}

void ControlView::undo()
{
	if(m_board->m_downStack.empty())
	{
		QMessageBox::information(this, "当前无法悔棋", "当前无法悔棋", QMessageBox::Ok);
		return;
	}
	Node node = m_board->m_downStack.top();
	if(node.who != 0)  // 最近一次落子不是自己
	{
		QMessageBox::information(this, "当前无法悔棋", "当前无法悔棋", QMessageBox::Ok);
	}
	else
	{
		m_board->setA(node.x, node.y);
		m_board->m_downStack.pop();
		QByteArray block;
		QDataStream out(&block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_7);
		out << UNDO; 
		emit sendDrawToMain(block);
		QMessageBox::information(this, "你已悔棋", "你已悔棋", QMessageBox::Ok);
	}
}
