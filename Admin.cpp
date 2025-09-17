#include "Admin.h"
#include"CMannger.h"
using namespace std;

int Admin::Menu()
{
	system("cls");
	puts("\n\n\t\t********************************");
	puts("\t\t*\t1����������˺�        *");
	puts("\t\t*\t2������˺�            *");
	puts("\t\t*\t3��ɾ���˺�            *");
	puts("\t\t*\t4���޸�����            *");
	puts("\t\t*\t0���������˵�          *");
	puts("\t\t********************************");
	cout << "\t\t��ѡ��";
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
	cout << "����������룺";
	cin >> sOld;
	if (sOld != m_user.sPass)
	{
		cout << "���������" << endl;
		system("pause");
		return;
	}
	cout << "�����������룺";
	cin >> sNew;
	cout << "���ٴ����������룺";
	cin >> sConf;
	if (sNew != sConf)
	{
		cout << "������������벻һ��" << endl;
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
		cout << "�����жϣ�" << endl;
		system("pause");
		return false;
	}
	bool b = n > 0;
	if (b)
	{
		strcpy_s(m_user.sPass, sPass);
		cout << "�޸�����ɹ���" << endl;

		}
	else
	{
		cout << "�޸�����ʧ�ܣ�" << endl;
	}
	system("pause");
	return b;
}
void Admin::Delete()
{
	sAdmin a;
	cout << "��������Ҫɾ�����˺�:";
	cin >> a.sName;
	if (!Check(a))
	{
		cout << "δ�ҵ����˺ţ����˺Ų�����" << endl;
		system("pause");
		return;
	}
	Print(a);
	cout << "ȷ��Ҫɾ����?[y/n]";
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
	cout << "�������˺ţ�";
	cin >> a.sName;
	cout << "���������룺";
	cin >> a.sPass;
	int nCmd = AD_LOGIN;
	m_sock.Send(&nCmd, sizeof(nCmd));
	//�ȷ����ȣ�������
	//tcpճ��������+����

	int n = (int)strlen(a.sName);
	m_sock.Send(&n, sizeof(n));
	m_sock.Send(a.sName,n);
	n = (int)strlen(a.sPass);
	m_sock.Send(&n, sizeof(n));
	m_sock.Send(a.sPass, n);
	
	a.nPrior = -1;
	if (m_sock.Receive(&a.nPrior, sizeof(int )) < sizeof(int ))
	{
		cout << "�����жϣ�" << endl;
		return false;
	}
	if (a.nPrior< 0)
	{
		cout << "�˺Ż��������" << endl;
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
		cout<<"�����жϣ�"<<endl;
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
	cout << "�ܹ���" << i << "��" << "�˺���Ϣ" << endl;
	system("pause");
}
void Admin::Input()
{
	int nCmd = AD_INPUT;
	m_sock.Send(&nCmd, sizeof(nCmd));
	sAdmin a;
	cout << "��������Ҫ��ӵ��˺ź������Լ���ӦȨ��0:�߼�.1:��ͨ" << endl;
	cin >> a.sName >> a.sPass >> a.nPrior;
	m_sock.Send(&a, sizeof(a));
	Print();
}
