#include <QtGui>
#include <QMessageBox>
#include "Board.h"
#include "type.h"

Board::Board(QWidget *parent):m_parent(parent),isStart(false)
{
	resize(602, 602);
	memset(a, 0, 15*15*sizeof(int));
	player = 0;
	setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background, QColor(244,197,123));
	setPalette(palette);
	connect(this, SIGNAL(down(QByteArray)), m_parent, SLOT(sendMsg(QByteArray)));	
	connect(this, SIGNAL(lose(QByteArray)), m_parent, SLOT(sendLoseMsg(QByteArray)));	
}

Board::~Board()
{

}

void clearStack(stack<Node> &s)
{
	while(!s.empty())
	{
		s.pop();
	}
}

void Board::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing, true);
	
	int i, j;
	for(i=0; i<16; ++i)
	{
		p.drawLine(1, 1+ i*40, 601, 1+ i*40);
		p.drawLine(1 + i*40, 1, 1+ i*40, 601);
	}

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	
	for(i=0; i<15; ++i)
	{
		for(j=0; j<15; ++j)
		{
			if(1 == a[i][j])
			{
				brush.setColor(Qt::black);
				p.setBrush(brush);
				p.drawEllipse(QPoint((i+0)*40+20, (j+0)*40+20), 15, 15);
			}
			else if(2 == a[i][j])
			{
				brush.setColor(Qt::white);
				p.setBrush(brush);
				p.drawEllipse(QPoint((i+0)*40+20, (j+0)*40+20), 15, 15);
			}
		}
	}
}

void Board::mouseReleaseEvent(QMouseEvent *e)
{
	int x, y;
	// 判断是否已开始
	if(isStart)
	{
		if( e->x()>=1 && e->x()<601 && e->y()>=1 && e->y()<601)
		{
			x = (e->x()-1) / 40;
			y = (e->y()-1) / 40;
			if(!a[x][y])
			{
				Node node(x, y, 0);
				m_downStack.push(node);  // 记录下棋步骤
				a[x][y] = player;        // 设置棋子类型
				isStart = false;         // 设置为无法落子，等待对方落子 
				// 发送信号
				QByteArray block;
				QDataStream out(&block, QIODevice::WriteOnly);
				out.setVersion(QDataStream::Qt_4_7);
				out << DOWN;
				out << x;
				out << y;
				emit down(block);
			}
			if(isWin(x, y))
			{
				update();
				QByteArray block;
				QDataStream out(&block, QIODevice::WriteOnly);
				out.setVersion(QDataStream::Qt_4_7);
				out << LOSE;
				emit lose(block);
		//		QMessageBox::information(this, "你赢了", "你赢了", QMessageBox::Ok);
				setEnabled(false);
			}
		}
		update();
	}
}

int Board::isWin(int x, int y)
{
	return f1(x, y) || f2(x, y) || f3(x, y) || f4(x, y);
}

int Board::f1(int x, int y)
{
	int i;
	for(i=0; i<5; ++i)
	{
		if(y-i >= 0 && y+4-i <= 15 &&
				a[x][y-i] == a[x][y+1-i] &&
				a[x][y-i] == a[x][y+2-i] &&
				a[x][y-i] == a[x][y+3-i] &&
				a[x][y-i] == a[x][y+4-i])
		{
			return 1;
		}
	}
	return 0;
}

int Board::f2(int x, int y)
{
	int i;
	for(i=0; i<5; ++i)
	{
		if(x-i >= 0 && x+4-i <= 15 &&
				a[x-i][y] == a[x+1-i][y] &&
				a[x-i][y] == a[x+2-i][y] &&
				a[x-i][y] == a[x+3-i][y] &&
				a[x-i][y] == a[x+4-i][y])
		{
			return 1;
		}
	}
	return 0;
}

int Board::f3(int x, int y)
{
	int i;
	for(i=0; i<5; ++i)
	{
		if(x-i >= 0 && y-i >= 0 &&
				y+4-i <= 15 && y+4-i <= 15 &&
				a[x-i][y-i] == a[x+1-i][y+1-i] &&
				a[x-i][y-i] == a[x+2-i][y+2-i] &&
				a[x-i][y-i] == a[x+3-i][y+3-i] &&
				a[x-i][y-i] == a[x+4-i][y+4-i])
		{
			return 1;
		}
	}
	return 0;
}

int Board::f4(int x, int y)
{
	int i;
	for(i=0; i<5; ++i)
	{
		if(x+i <= 15 && y-i >= 0 &&
				x-4+i >= 0 && y+4-i <= 15 &&
				a[x+i][y-i] == a[x-1+i][y+1-i] &&
				a[x+i][y-i] == a[x-2+i][y+2-i] &&
				a[x+i][y-i] == a[x-3+i][y+3-i] &&
				a[x+i][y-i] == a[x-4+i][y+4-i])
		{
			return 1;
		}
	}
	return 0;
}

void Board::start()
{
	isStart = true;
	player = 1;
}

void Board::readMsg(QByteArray block)
{
	QDataStream in(&block, QIODevice::ReadOnly);
	in.setVersion(QDataStream::Qt_4_7);
	int state;
	in >> state;
	if(state == DOWN)  // 对方落子了
	{
		int x, y;
		in >> x;
		in >> y;
		Node node(x, y, 1);
		m_downStack.push(node);
		a[x][y] = player==1?2:1;
		isStart = true;
		update();
	}
	else if(state == LOSE)  // 对方赢了
	{
		update();
		setEn();
		QMessageBox::information(this, "你输了", "你输了", QMessageBox::Ok);
	}
	else if(state == DRAW)  // 对方认输
	{
		update();
		isStart = false;
		setEnabled(false);
		QMessageBox::information(this, "对方已认输", "对方已认输", QMessageBox::Ok);
	}
	else if(state == UNDO)  // 对方悔棋
	{
		isStart = false;
		Node node = m_downStack.top();
		m_downStack.pop();
		a[node.x][node.y] = 0;
		update();
		QMessageBox::information(this, "对方悔棋了", "对方悔棋了", QMessageBox::Ok);
	}
}
