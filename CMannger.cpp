#include "CMannger.h"
CMannger CMannger::m_man;
using namespace std;


int CMannger::Menu()
{
	system("cls");
	int nPrior = GetPrior();
	const char* p = nPrior ? "普通" : "高级";
	cout << "\n\n\t\t当前账号：" << GetUser() << "【" << p << "】" << endl;
	puts("\t\t********************************");
	puts("\t\t*\t1、浏览所有信息        *");
	puts("\t\t*\t2、添加信息            *");
	puts("\t\t*\t3、删除信息            *");
	puts("\t\t*\t4、修改信息            *");
	puts("\t\t*\t5、查找信息            *");
	if (nPrior)
		puts("\t\t*\t6、密码修改            *");
	else
		puts("\t\t*\t6、账号管理            *");
	puts("\t\t*\t0、退出                *");
	puts("\t\t********************************");
	cout << "\t\t请选择：";
	int i = 0;
	cin >> i;
	switch (i)
	{
	case 1:
		while (m_sort.Menu())
			;
		//CWorker::Print();
		break;
	case 2:
		CWorker::Input();
		break;
	case 3:
		CWorker::Delete();
		break;
	case 4:
		CWorker::Modify();
		break;
	case 5:
		while (m_find.Menu())
			;
		break;
	case 6:
		Admin::Main();
		break;

	}
	return i;

}


int CMannger::Main()
{
	if (!m_sock.Create())
	{
		cout << "创建端口失败" << m_sock.GetLastError() << endl;
		return -1;
	}
	if (!m_sock.Connect("192.168.18.1", SEVER_PORT))
	{
		cout << "连接服务器失败" << m_sock.GetLastError() << endl;
		return -1;
	}
	if (!Login())
	{
		return -1;
	}
	while (Menu())
		;
	return 0;
}
