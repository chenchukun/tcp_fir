#include "server.h"
#include "type.h"
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QTextCodec>
#include <string>
#include <fstream>
#include <iostream>
using std::string;
using std::fstream;
using std::ios;
using std::ofstream;
Server::Server(QWidget *parent) :
QWidget(parent)
{
	textEdit = new QTextEdit;
	textEdit->setReadOnly(true);
	lineEdit = new QLineEdit;
	startBtn = new QPushButton("start");
	connect(startBtn,SIGNAL(clicked()),this,SLOT(startTcpServer()));
	sendBtn = new QPushButton("send");
	connect(sendBtn,SIGNAL(clicked()),this,SLOT(sendMessage()));
	QHBoxLayout *bottomlayout = new QHBoxLayout;
	bottomlayout->addWidget(startBtn);
	bottomlayout->addWidget(sendBtn);
	QVBoxLayout *mainlayout = new QVBoxLayout;
	mainlayout->addWidget(textEdit);
	mainlayout->addWidget(lineEdit);
	mainlayout->addLayout(bottomlayout);
	setLayout(mainlayout);
}
void Server::startTcpServer()
{
	startBtn->setEnabled(false);
	m_tcpserver = new QTcpServer;
	m_tcpserver->listen(QHostAddress::Any,16666);
	connect(m_tcpserver,SIGNAL(newConnection()),this,SLOT(newConnect()));
}
void Server::newConnect()
{
	textEdit->append(tr("有用户链接...")+'\n');
//	m_tcpsocket = m_tcpserver->nextPendingConnection();
//	connect(m_tcpsocket,SIGNAL(readyRead()),this,SLOT(readMessage()));
	QTcpSocket *tmpSocket = m_tcpserver->nextPendingConnection();
	pair<QString, QTcpSocket*> tmpPair;
	tmpPair.second = tmpSocket;
	m_tcpsocket.push_back(tmpPair);
	connect(tmpSocket, SIGNAL(readyRead()), this, SLOT(readMessage()));
}
void Server::readMessage()
{
	QString username;
	QString passwd;
	int type;
//	QByteArray block = m_tcpsocket->readAll();
	for(int i=0; i<m_tcpsocket.size(); ++i)
	{
		QByteArray block = (m_tcpsocket[i].second)->readAll();
		if(block.size() != 0)
		{
			QDataStream in(block);
			in.setVersion(QDataStream::Qt_4_7);
			in>> type;
			if(type == LOGIN)  // 登录
			{
				in >> username;
				in >> passwd;
				textEdit->append("login:" + username + "    " + passwd + '\n');
				// 将用户名与tcpsocket绑定
				m_tcpsocket[i].first = username;

				// 判断用户名和密码合法性
				bool success = false;
				// 打开文件
				fstream fcin("/Users/chenchukun/coding/qt/tcp_fir_server/data.txt");
				string sname, spasswd;
				while(fcin >> sname)
				{
//					textEdit->append("while\n");
					fcin >> spasswd;
					QString u(sname.c_str());
					QString p(spasswd.c_str());
					textEdit->append("read:" + u +" " + p + '\n');
					if(u==username && p==passwd)
					{
						fcin.close();
						success = true;
						break;
					}
				}

				QByteArray retBlock;
				QDataStream retOut(&retBlock,QIODevice::WriteOnly);
				retOut.setVersion(QDataStream::Qt_4_7);
				if(success)  // 验证成功
				{
					retOut << LOGIN_YES;
				}
				else        // 验证失败
				{
					retOut << LOGIN_NO;
				}
				// 发送验证结果给客户端
				(m_tcpsocket[i].second)->write(retBlock);
			}// 登录结束
			else if(type == REGISTER)  //注册
			{
				in >> username;
				in >> passwd;
				// 判断用户名合法性
				bool success = true;
				// 打开文件
				fstream fcin("/Users/chenchukun/coding/qt/tcp_fir_server/data.txt");
				string sname, spasswd;
				while(fcin >> sname)
				{
//					textEdit->append("while\n");
					fcin >> spasswd;
					QString u(sname.c_str());
					QString p(spasswd.c_str());
					textEdit->append("read:" + u +" " + p + '\n');
					if(u==username)
					{
						success = false; 
						fcin.close();
						break;
					}
				}
				QByteArray retBlock;
				QDataStream retOut(&retBlock,QIODevice::WriteOnly);
				retOut.setVersion(QDataStream::Qt_4_7);
				if(success)  // 注册成功
				{
					retOut << REGISTER_YES;
					ofstream fout("/Users/chenchukun/coding/qt/tcp_fir_server/data.txt", ios::app);
					fout << username.toStdString();
					fout << "\t";
					fout << passwd.toStdString();
					fout << "\n";
					fout.close();
					fout.close();
				}
				else        // 注册失败
				{
					retOut << REGISTER_NO;
				}
				// 发送验证结果给客户端
				(m_tcpsocket[i].second)->write(retBlock);
				
			}// 注册结束
			else if(type == SEND_MSG) // 聊天
			{
				QString text;
				// 获取聊天信息
				in >> text;
//				textEdit->append("send to client:" + text + '\n');
				QByteArray block;
				QDataStream out(&block,QIODevice::WriteOnly);
				out.setVersion(QDataStream::Qt_4_7);
				QString sendText = m_tcpsocket[i].first + ":" + text;
				textEdit->append(sendText + '\n');
				out << SEND_MSG;
				out << sendText;
				for(int index=0; index<m_tcpsocket.size(); ++index)
				{
					(m_tcpsocket[index].second)->write(block);
				}
			}
			else if(type == START)  // 有一方点击开始游戏
			{
				QByteArray block;
				QDataStream out(&block,QIODevice::WriteOnly);
				out.setVersion(QDataStream::Qt_4_7);
				out << START;
				for(int index=0; index<m_tcpsocket.size(); ++index)
				{
					if(index != i)
					{
						(m_tcpsocket[index].second)->write(block);
					}
				}
				textEdit->append("start\n");
			}
			else if(type == DOWN)  // 落子
			{
				QByteArray block;
				QDataStream out(&block,QIODevice::WriteOnly);
				out.setVersion(QDataStream::Qt_4_7);
				int x, y;
				in >> x;
				in >> y;
				out << DOWN;
				out << x;
				out << y;
				for(int index=0; index<m_tcpsocket.size(); ++index)
				{
					if(index != i)
					{
						(m_tcpsocket[index].second)->write(block);
					}
				}
				textEdit->append("down:" + QString::number(x, 10) + QString::number(y, 10) + '\n');
			}
			else if(type == LOSE) // 输了
			{
				QByteArray block;
				QDataStream out(&block,QIODevice::WriteOnly);
				out.setVersion(QDataStream::Qt_4_7);
				out << LOSE;
				for(int index=0; index<m_tcpsocket.size(); ++index)
				{
					if(index != i)
					{
						(m_tcpsocket[index].second)->write(block);
					}
				}
				textEdit->append("lose\n");
			}
			else if(type == DRAW) // 认输
			{
				QByteArray block;
				QDataStream out(&block,QIODevice::WriteOnly);
				out.setVersion(QDataStream::Qt_4_7);
				out << DRAW;
				for(int index=0; index<m_tcpsocket.size(); ++index)
				{
					if(index != i)
					{
						(m_tcpsocket[index].second)->write(block);
					}
				}
				textEdit->append("draw\n");
				
			}
			else if(type == UNDO)  //悔棋
			{
				QByteArray block;
				QDataStream out(&block,QIODevice::WriteOnly);
				out.setVersion(QDataStream::Qt_4_7);
				out << UNDO;
				for(int index=0; index<m_tcpsocket.size(); ++index)
				{
					if(index != i)
					{
						(m_tcpsocket[index].second)->write(block);
					}
				}
				textEdit->append("undo\n");
				
			}
			else if(type == LEAVE) // 离开游戏
			{
				textEdit->append("leave\n");
				QByteArray block;
				QDataStream out(&block,QIODevice::WriteOnly);
				out.setVersion(QDataStream::Qt_4_7);
				out << LEAVE;
				for(int index=0; index<m_tcpsocket.size(); ++index)
				{
					if(index != i)
					{
						(m_tcpsocket[index].second)->write(block);
					}
				}
				
			}
			else
			{
				textEdit->append("default\n");
			}

		}
	}
//	QMessageBox::information(this, "OK", "OK", QMessageBox::Ok);
}
void Server::sendMessage()
{
	QString text = lineEdit->text();
	QByteArray block;
	QDataStream out(&block,QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_7);
	out << text;
//	m_tcpsocket->write(block);
	for(int i=0; i<m_tcpsocket.size(); ++i)
	{
		(m_tcpsocket[i].second)->write(block);
	}
	lineEdit->clear();
}
