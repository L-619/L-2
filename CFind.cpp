#include "CFind.h"
#include"CMannger.h"
using namespace std;
void CFind::FindByNumb()
{
	SInfo d;
	int nNumb;
	cout << "��������Ҫ���ҵĹ��ţ�";
	cin >> d.nNumb;
	if (FindNumb(d))
		CMannger::PrintWorker(d);
	else
		puts("������Ĺ��Ų����ڣ�");
	system("pause");

}

void CFind::FindByName()
{
	string sName;
	cout << "��������Ҫ���ҵ�����(���Բ���)��";
	cin >> sName;
	int nCmd = WK_FIND_NAME;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(sName.c_str(), sName.length());
	SInfo d;
	//�˴��ͻ��˲���recvive���������������ݷ���ʱ�ᵼ�¿ͻ�������������
	//����취���ڷ���������ǰ�ȷ���һ����������||�ڷ��������ݷ�����Ϻ���һ�������������ݣ��Ӷ�ʹ�ͻ��˽��ܵ�����������ֱ�ӽ�������
	int n = 0;
		while(m_sock.Receive(&d, sizeof(d)) == sizeof(d))
	CMannger::PrintWorker(d),++n;
		cout << "���������ļ�¼��" << n << "��" << endl;
	system("pause");
}

void CFind::FindBySalary()
{
	float fMin, fMax;
	cout << "��������Ҫ���ҵĹ��ʶ�(����������):";
	cin >> fMin >> fMax;
	int nCmd = WK_FIND_SALARY;
	m_sock.Send(&nCmd, sizeof(nCmd));

	m_sock.Send(&fMin, sizeof(fMin));
	m_sock.Send(&fMax, sizeof(fMax));
		SInfo d;
		int n = 0;
		while (m_sock.Receive(&d, sizeof(d)) == sizeof(d))
			CMannger::PrintWorker(d), ++n;
		cout << "���������ļ�¼��" << n << "��" << endl;
		system("pause");
}

void CFind::FindByDate()
{
	char sMin[20], sMax[20];
	cout << "��������Ҫ���ҵ����ڶΣ�2������:yyyy-mm-dd����";
	cin >> sMin >> sMax;
	int nCmd = WK_FIND_DATE;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&sMin, (int)strlen(sMin));
	int n=m_sock.Receive(&nCmd, sizeof(nCmd));
	if (n < sizeof(nCmd))
	{
		cout << "������ϣ�" << endl;
		system("pause");
		return;
	}
	m_sock.Send(&sMax,(int)strlen(sMax));
	SInfo d;
	 n = 0;
	while (m_sock.Receive(&d, sizeof(d)) == sizeof(d))
		CMannger::PrintWorker(d), ++n;
	cout << "���������ļ�¼��" << n << "��" << endl;
	system("pause");
	


}
int CFind::Menu()
{
	system("cls");
	puts("\n\n\t\t********************************");
	puts("\t\t*\t1�������Ų���        *");
	puts("\t\t*\t2������������        *");
	puts("\t\t*\t3�������ʶβ���      *");
	puts("\t\t*\t4�������ڶβ���      *");
	puts("\t\t*\t0���������˵�        *");
	puts("\t\t********************************");
	cout << "\t\t��ѡ��";
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
			cout << "�������!" << m_sock.GetLastError() << endl;
			system("pause");
			return false;
		}
		if (nRes <= 0)
			return false;
		if (m_sock.Receive(&d, sizeof(d)) < sizeof(d))
		{
			cout << "�������!" << m_sock.GetLastError() << endl;
			system("pause");
			return false;
		}
		return true;
	
}