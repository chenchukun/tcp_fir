#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QDialog>
#include <QByteArray>
#include <QDataStream>
#include <stack>
#include "type.h"
using std::stack;


class Board : public QWidget
{
	Q_OBJECT

public:
	stack<Node> m_downStack;  // 这里先定义为public类型，便于ControlView类调用，架构问题，重构时改正
	Board(QWidget *parent);
	~Board();
	void mouseReleaseEvent(QMouseEvent *);
	void paintEvent(QPaintEvent *);
	void setPlayer(int x)  // 设置棋子类型，由ControlView类调用
	{
		player = x;
	}

	void setEn()  // 由ControlView类调用，设计有问题，现在只能先这样写了
	{
		setEnabled(false);
		isStart = false;
	}

	// 重新开始的时候初始化用
	void setNEn()
	{
		memset(a, 0, sizeof(a));
		setEnabled(true);
		clearStack(m_downStack); // 清空栈
	}
	
	void setA(int x, int y)  // 由ControlView类调用，设计有问题，现在只能先这样写了
	{
		a[x][y] = 0;
		isStart = true;
		update();
	}


public slots:
	void start(); 
	void readMsg(QByteArray block);

signals:
	void down(QByteArray block);  // 落子
	void lose(QByteArray block);  // 对方输

private:
	int a[15][15];
	int isWin(int, int);
	int f1(int, int);
	int f2(int, int);
	int f3(int, int);
	int f4(int, int);
	int player;  // 棋子类型 1为黑 2为白
	bool isStart;  // 是否开始游戏
	QWidget *m_parent;
	void clearStack(stack<Node> &s);
};

#endif
