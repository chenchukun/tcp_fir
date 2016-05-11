#ifndef CONTROLVIEW_H
#define CONTROLVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QtNetwork>
#include <QTcpSocket>
#include <QByteArray>
#include "Board.h"
class Board;

class ControlView : public QWidget
{
Q_OBJECT
public:
	ControlView(QWidget *parent, Board *board);
	~ControlView();
	void paintEvent(QPaintEvent *);

public slots:
	void sendMsg();
	// 读取聊天信息
	void readMsg(QByteArray block);
	// 开始游戏
	void start();
	void draw();
	void undo();
	void leave();
signals:
	void sendMsgToMain(QByteArray);
	void sendStartToBoard();
	void sendStartToMain(QByteArray);
	void sendDrawToMain(QByteArray);
	void sendUndoToMain(QByteArray);
	void sendLeaveToMain(QByteArray);
	

private:
	QWidget *user1Photo;
	QWidget *user2Photo;
	QWidget *user1Score;
	QWidget *user2Score;
	QLabel *user1Name;
	QLabel *user2Name;
	QPushButton *startButton;
	QPushButton *exitButton;
	QPushButton *undoButton;
	QPushButton *drawButton;
	QTextEdit *talkView;
	QLineEdit *inputText;
	QPushButton *sendButton;
//	QTcpSocket *m_tcpsocket;
	QWidget *m_parent;
	Board *m_board;
};
#endif
