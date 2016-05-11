#ifndef LOGIN_H
#define LOGIN_H
#include <QApplication>
#include <QDialog>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QtNetwork>
#include <QTcpSocket>
#include <QByteArray>

class Login : public QDialog
{
	Q_OBJECT
public:
	Login(QWidget *parent);

signals:
	void sendMsgToMain(QByteArray block);
private slots:
	void sendLoginMsg();
	void sendRegisterMsg();
public slots:
	void readMsg(QByteArray block);

private:
	QVBoxLayout *mainLayout;
	QHBoxLayout *firstLayout, *secondLayout, *thirdLayout;
	QLabel *lbuserName, *lbuserPasswd;
	QLineEdit *leuserName, *leuserPasswd;
	QPushButton *loginButton, *regButton;
	QWidget *m_parent;
};

#endif
