#ifndef SERVER_H
 
#define SERVER_H
#include <QWidget>
#include <QtGui>
#include <QtNetwork>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QTcpSocket>
#include <QTcpServer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include <map>
using std::vector;
using std::pair;
class Server : public QWidget
{
Q_OBJECT
public:
	explicit Server(QWidget *parent = 0);
private:
	QTextEdit *textEdit;
	QLineEdit *lineEdit;
	QPushButton *sendBtn;
	QPushButton *startBtn;
//	QTcpSocket *m_tcpsocket;
	QTcpServer *m_tcpserver;
	vector< pair<QString, QTcpSocket*> > m_tcpsocket;
private slots:
	void startTcpServer();
	void sendMessage();
	void newConnect();
	void readMessage();
};
#endif // SERVER_H
