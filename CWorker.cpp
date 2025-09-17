#include "CWorker.h"
#include"CMannger.h"
using namespace std;



void CWorker::Input()
{
	int nCmd = WK_INPUT;
	cout << "请录入一个工号:";
	SInfo d;
	cin >> d.nNumb;
	bool b =m_find.FindNumb(d);
	if (b)
	{
		cout << "你输入的工号已存在" << endl;
		cout << d.nNumb << '\t' << d.sDate << "\t" << d.fsala << "\t" << d.sDate << endl;
		system("pause");
		return;
	}
	cout << "请继续录入姓名、工资和入职日期[1999-9-1]：";
	cin >> d.sName >> d.fsala >> d.sDate;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&d, sizeof(d));

	Print();
}


void CWorker::Print(int nOrder)
{
	int nCmd = WK_PRINT;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&nOrder, sizeof(nOrder));
	SInfo d;
	//此处客户端不断recvive，当服务器无数据发送时会导致客户端阻塞在这里
	//解决办法：在服务器发送前先发送一个数组总量||在服务器数据发送完毕后发送一个不完整的数据，从而使客户端接受到不完整数据直接结束接收
		while(m_sock.Receive(&d, sizeof(d)) == sizeof(d))
		CMannger::PrintWorker(d);
	system("pause");
}

void CWorker::Delete()
{
	SInfo d;
	cout << "请输入要删除的员工的工号：";
	cin >> d.nNumb;
	
	if (!m_find.FindNumb(d))
	{
		puts("你输入的工号不存在！");
		system("pause");
		return;
	}
	CMannger::PrintWorker(d);
	cout << "你确定要删除这条记录吗?[y/n]";
	char c;
	cin >> c;
	if (c != 'Y' && c != 'y')
		return;
	int n = 0;
	int nNumb = WK_DELETE;
	m_sock.Send(&nNumb, sizeof(nNumb));
	m_sock.Send(&d.nNumb, sizeof(d.nNumb));
	if (m_sock.Receive(&n, sizeof(n)) != sizeof(n))
	{
		cout << "网络中断" << endl;
		system("pause");
		return;
	}
	cout << "成功栅除了" << n << "条记录" << endl;
	system("pause");
		Print();

}

void CWorker::Modify()
{
	SInfo d;
	cout << "请输入要修改的员工的工号：";
	cin >> d.nNumb;

	if (!m_find.FindNumb(d))
	{
		puts("你输入的工号不存在！");
		system("pause");
		return;
	}
	CMannger::PrintWorker(d);
	cout << "你确定要修改这条记录吗?[y/n]";
	char c;
	cin >> c;
	if (c != 'Y' && c != 'y')
		return;

	cout << "请录入新的姓名、工资和入职日期：";
	cin >> d.sName >> d.fsala >> d.sDate;
	int nCmd = WK_MODIFY;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&d, sizeof(d));
	Print();
}
