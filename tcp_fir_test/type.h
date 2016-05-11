#ifndef TYPE_H
#define TYPE_H
enum TYPE{LOGIN, REGISTER, LOGIN_YES, LOGIN_NO, REGISTER_YES, REGISTER_NO, SEND_MSG, START, END, DOWN, LOSE, DRAW, UNDO, LEAVE};

// 用于记录下棋过程的数据结构
struct Node
{
	Node(int a, int b, int c):x(a), y(b), who(c){}
	int x, y;  // 落子坐标
	int who;       // 谁下的？0为自己，1为对方
};
#endif
