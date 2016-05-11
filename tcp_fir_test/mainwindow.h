#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtNetwork>
#include <QTcpSocket>
#include <QWidget>
#include <QByteArray>
#include <QDataStream>
#include "login.h"
#include "ControlView.h"
#include "Board.h"

class MainWindow : public QWidget
{
Q_OBJECT
	friend class ControlView;
public:
	MainWindow();

private slots:
	// 接收服务器信息
	void readMsg();
public slots:
	// 转发其它类的信息到服务器
	void sendMsg(QByteArray block);
	void sendLoseMsg(QByteArray block);
	void sendLeaveMsg(QByteArray block);
signals:
	void sendToLogin(QByteArray block);
	void sendToControl(QByteArray block);
	void sendToBoard(QByteArray block);

private:
	QTcpSocket *m_tcpsocket;
	void start();
	ControlView *control;
	Board *board;
	Login *login;
};

#endif
