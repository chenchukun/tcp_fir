#include "login.h"
#include <QMessageBox>
#include <QByteArray>
#include <QDataStream>
#include <QMessageBox>
#include "type.h"

Login::Login(QWidget *parent):m_parent(parent)
{
	mainLayout = new QVBoxLayout;

	firstLayout = new QHBoxLayout;
	lbuserName = new QLabel("用户名:");
	leuserName = new QLineEdit;
	firstLayout->addWidget(lbuserName);
	firstLayout->addWidget(leuserName);

	secondLayout = new QHBoxLayout;
	lbuserPasswd = new QLabel("密  码:");
	leuserPasswd = new QLineEdit;
	leuserPasswd->setEchoMode(QLineEdit::Password);
	secondLayout->addWidget(lbuserPasswd);
	secondLayout->addWidget(leuserPasswd);

	thirdLayout = new QHBoxLayout;
	loginButton = new QPushButton("登录");
	regButton = new QPushButton("注册");
	thirdLayout->addWidget(loginButton);
	thirdLayout->addWidget(regButton);

//	connect(regButton, SIGNAL(clicked()), this, SLOT(sendRegister()));
//	connect(m_tcpsocket, SIGNAL(readyRead()), this, SLOT(readMsg()));
	// 登录 信号
	connect(loginButton, SIGNAL(clicked()), this, SLOT(sendLoginMsg()));
	connect(this, SIGNAL(sendMsgToMain(QByteArray)), m_parent, SLOT(sendMsg(QByteArray)));

	// 注册 信号
	connect(regButton, SIGNAL(clicked()), this, SLOT(sendRegisterMsg()));
	connect(this, SIGNAL(sendMsgToMain(QByteArray)), m_parent, SLOT(sendMsg(QByteArray)));

	mainLayout->addLayout(firstLayout);
	mainLayout->addLayout(secondLayout);
	mainLayout->addLayout(thirdLayout);

	setLayout(mainLayout);

}

void Login::sendLoginMsg()
{
	TYPE type = LOGIN;
	QString username = leuserName->text();
	QString passwd = leuserPasswd->text();
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out << type;
	out << username;
	out << passwd;
	emit sendMsgToMain(block);
}

void Login::sendRegisterMsg()
{
	TYPE type = REGISTER;
	QString username = leuserName->text();
	QString passwd = leuserPasswd->text();
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out << type;
	out << username;
	out << passwd;
	emit sendMsgToMain(block);
}

void Login::readMsg(QByteArray block)
{
	int state;
	QDataStream in(&block, QIODevice::ReadOnly);
	in >> state;
	if(state == LOGIN_YES)
	{
		done(1);
	}
	else if(state == LOGIN_NO)
	{
		QMessageBox::information(this, "登录失败", "登录失败", QMessageBox::Ok);
	}
	else if(state == REGISTER_YES)
	{
		QMessageBox::information(this, "注册成功", "注册成功", QMessageBox::Ok);
	}
	else if(state == REGISTER_NO)
	{
		QMessageBox::information(this, "注册失败", "注册失败", QMessageBox::Ok);
	}
}


