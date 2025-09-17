#include "CFind.h"
#include"CMannger.h"
using namespace std;
void CFind::FindByNumb()
{
	SInfo d;
	int nNumb;
	cout << "请输入你要查找的工号：";
	cin >> d.nNumb;
	if (FindNumb(d))
		CMannger::PrintWorker(d);
	else
		puts("你输入的工号不存在！");
	system("pause");

}

void CFind::FindByName()
{
	string sName;
	cout << "请输入你要查找的姓名(可以部分)：";
	cin >> sName;
	int nCmd = WK_FIND_NAME;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(sName.c_str(), sName.length());
	SInfo d;
	//此处客户端不断recvive，当服务器无数据发送时会导致客户端阻塞在这里
	//解决办法：在服务器发送前先发送一个数组总量||在服务器数据发送完毕后发送一个不完整的数据，从而使客户端接受到不完整数据直接结束接收
	int n = 0;
		while(m_sock.Receive(&d, sizeof(d)) == sizeof(d))
	CMannger::PrintWorker(d),++n;
		cout << "符合条件的记录有" << n << "条" << endl;
	system("pause");
}

void CFind::FindBySalary()
{
	float fMin, fMax;
	cout << "请输入你要查找的工资段(两个浮点数):";
	cin >> fMin >> fMax;
	int nCmd = WK_FIND_SALARY;
	m_sock.Send(&nCmd, sizeof(nCmd));

	m_sock.Send(&fMin, sizeof(fMin));
	m_sock.Send(&fMax, sizeof(fMax));
		SInfo d;
		int n = 0;
		while (m_sock.Receive(&d, sizeof(d)) == sizeof(d))
			CMannger::PrintWorker(d), ++n;
		cout << "符合条件的记录有" << n << "条" << endl;
		system("pause");
}

void CFind::FindByDate()
{
	char sMin[20], sMax[20];
	cout << "请输入你要查找的日期段（2个日期:yyyy-mm-dd）：";
	cin >> sMin >> sMax;
	int nCmd = WK_FIND_DATE;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&sMin, (int)strlen(sMin));
	int n=m_sock.Receive(&nCmd, sizeof(nCmd));
	if (n < sizeof(nCmd))
	{
		cout << "网络故障！" << endl;
		system("pause");
		return;
	}
	m_sock.Send(&sMax,(int)strlen(sMax));
	SInfo d;
	 n = 0;
	while (m_sock.Receive(&d, sizeof(d)) == sizeof(d))
		CMannger::PrintWorker(d), ++n;
	cout << "符合条件的记录有" << n << "条" << endl;
	system("pause");
	


}
int CFind::Menu()
{
	system("cls");
	puts("\n\n\t\t********************************");
	puts("\t\t*\t1、按工号查找        *");
	puts("\t\t*\t2、按姓名查找        *");
	puts("\t\t*\t3、按工资段查找      *");
	puts("\t\t*\t4、按日期段查找      *");
	puts("\t\t*\t0、返回主菜单        *");
	puts("\t\t********************************");
	cout << "\t\t请选择：";
	int i = 0;
	cin >> i;
	switch (i)
	{
	case 1:
		FindByNumb();
		break;
	case 2:
		FindByName();
		break;
	case 3:
		FindBySalary();
		break;
	case 4:
		FindByDate();
	}
	return i;

}
bool CFind::FindNumb(SInfo& d)
{
	
		int nCmd = WK_FIND_NUMB;
		m_sock.Send(&nCmd, sizeof(nCmd));
		m_sock.Send(&d.nNumb, sizeof(d.nNumb));
		int nRes = 0;
		if (m_sock.Receive(&nRes, sizeof(nRes)) < sizeof(nRes))
		{
			cout << "网络故障!" << m_sock.GetLastError() << endl;
			system("pause");
			return false;
		}
		if (nRes <= 0)
			return false;
		if (m_sock.Receive(&d, sizeof(d)) < sizeof(d))
		{
			cout << "网络故障!" << m_sock.GetLastError() << endl;
			system("pause");
			return false;
		}
		return true;
	
}