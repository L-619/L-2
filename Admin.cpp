#include "Admin.h"
#include"CMannger.h"
using namespace std;

int Admin::Menu()
{
	system("cls");
	puts("\n\n\t\t********************************");
	puts("\t\t*\t1、浏览所有账号        *");
	puts("\t\t*\t2、添加账号            *");
	puts("\t\t*\t3、删除账号            *");
	puts("\t\t*\t4、修改密码            *");
	puts("\t\t*\t0、返回主菜单          *");
	puts("\t\t********************************");
	cout << "\t\t请选择：";
	int i = 0;
	cin >> i;
	switch (i)
	{
	case 1:
		Print();
		break;
	case 2:
		Input();
		break;
	case 3:
		Delete();
		break;
	case 4:
		CPass();

	}
	return i;

}
void Admin::Main()
{
	if (m_user.nPrior)
		CPass();
	else
		while (Menu())
			;

}
void Admin::CPass()
{
	string sOld, sNew, sConf;
	cout << "请输入旧密码：";
	cin >> sOld;
	if (sOld != m_user.sPass)
	{
		cout << "旧密码错误" << endl;
		system("pause");
		return;
	}
	cout << "请输入新密码：";
	cin >> sNew;
	cout << "请再次输入新密码：";
	cin >> sConf;
	if (sNew != sConf)
	{
		cout << "两次输入的密码不一致" << endl;
		system("pause");
		return;
	}
	ChangePass(sNew.c_str());


}
bool Admin::ChangePass(const char* sPass)
{
	sAdmin a = m_user;
	strcpy_s(a.sPass, sPass);
	int nCmd = AD_CHHPASS;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&a, sizeof(a));

	int n = 0;
	if (m_sock.Receive(&n, sizeof(n)) != sizeof(n))
	{
		cout << "网络中断！" << endl;
		system("pause");
		return false;
	}
	bool b = n > 0;
	if (b)
	{
		strcpy_s(m_user.sPass, sPass);
		cout << "修改密码成功！" << endl;

		}
	else
	{
		cout << "修改密码失败！" << endl;
	}
	system("pause");
	return b;
}
void Admin::Delete()
{
	sAdmin a;
	cout << "请输入你要删除的账号:";
	cin >> a.sName;
	if (!Check(a))
	{
		cout << "未找到该账号，该账号不存在" << endl;
		system("pause");
		return;
	}
	Print(a);
	cout << "确定要删除吗?[y/n]";
	char c;
	cin >> c;
	if (c != 'y' && c != 'Y')
		return;
	int nCmd = AD_DELETE;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(a.sName, strlen(a.sName));
	Print();
}
bool Admin::Login()
{
	sAdmin a;
	cout << "请输入账号：";
	cin >> a.sName;
	cout << "请输入密码：";
	cin >> a.sPass;
	int nCmd = AD_LOGIN;
	m_sock.Send(&nCmd, sizeof(nCmd));
	//先发长度，后发内容
	//tcp粘包，长度+内容

	int n = (int)strlen(a.sName);
	m_sock.Send(&n, sizeof(n));
	m_sock.Send(a.sName,n);
	n = (int)strlen(a.sPass);
	m_sock.Send(&n, sizeof(n));
	m_sock.Send(a.sPass, n);
	
	a.nPrior = -1;
	if (m_sock.Receive(&a.nPrior, sizeof(int )) < sizeof(int ))
	{
		cout << "网络中断！" << endl;
		return false;
	}
	if (a.nPrior< 0)
	{
		cout << "账号或密码错误" << endl;
		return false;
	}
	m_user = a;
	return true;
}
bool Admin::Check(sAdmin& a)
{
	int nCmd = AD_CHECK;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(a.sName, (int)strlen(a.sName));
	int nCount = 0;
	if (m_sock.Receive(&nCount, sizeof(nCount)) < sizeof(nCount))
	{
		cout<<"网络中断！"<<endl;
		system("pasue");
		return false;
	}
	if (nCount <= 0)
	{
		return false;
	}
	return m_sock.Receive(&a, sizeof(sAdmin)) == sizeof(sAdmin);
}

void Admin::Print()
{
	int nCmd = AD_PRINT;
	m_sock.Send(&nCmd, sizeof(nCmd));
	int nCount = 0,i=-1;
	m_sock.Receive(&nCount, sizeof(nCount));
	sAdmin a;
	while (++i < nCount)
	{
		if (m_sock.Receive(&a, sizeof(a)) < sizeof(a))\
			break;
		Print(a);
	}
	cout << "总共有" << i << "条" << "账号信息" << endl;
	system("pause");
}
void Admin::Input()
{
	int nCmd = AD_INPUT;
	m_sock.Send(&nCmd, sizeof(nCmd));
	sAdmin a;
	cout << "请输入你要添加的账号和密码以及对应权限0:高级.1:普通" << endl;
	cin >> a.sName >> a.sPass >> a.nPrior;
	m_sock.Send(&a, sizeof(a));
	Print();
}
