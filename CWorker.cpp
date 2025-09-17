#include "CWorker.h"
#include"CMannger.h"
using namespace std;



void CWorker::Input()
{
	int nCmd = WK_INPUT;
	cout << "��¼��һ������:";
	SInfo d;
	cin >> d.nNumb;
	bool b =m_find.FindNumb(d);
	if (b)
	{
		cout << "������Ĺ����Ѵ���" << endl;
		cout << d.nNumb << '\t' << d.sDate << "\t" << d.fsala << "\t" << d.sDate << endl;
		system("pause");
		return;
	}
	cout << "�����¼�����������ʺ���ְ����[1999-9-1]��";
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
	//�˴��ͻ��˲���recvive���������������ݷ���ʱ�ᵼ�¿ͻ�������������
	//����취���ڷ���������ǰ�ȷ���һ����������||�ڷ��������ݷ�����Ϻ���һ�������������ݣ��Ӷ�ʹ�ͻ��˽��ܵ�����������ֱ�ӽ�������
		while(m_sock.Receive(&d, sizeof(d)) == sizeof(d))
		CMannger::PrintWorker(d);
	system("pause");
}

void CWorker::Delete()
{
	SInfo d;
	cout << "������Ҫɾ����Ա���Ĺ��ţ�";
	cin >> d.nNumb;
	
	if (!m_find.FindNumb(d))
	{
		puts("������Ĺ��Ų����ڣ�");
		system("pause");
		return;
	}
	CMannger::PrintWorker(d);
	cout << "��ȷ��Ҫɾ��������¼��?[y/n]";
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
		cout << "�����ж�" << endl;
		system("pause");
		return;
	}
	cout << "�ɹ�դ����" << n << "����¼" << endl;
	system("pause");
		Print();

}

void CWorker::Modify()
{
	SInfo d;
	cout << "������Ҫ�޸ĵ�Ա���Ĺ��ţ�";
	cin >> d.nNumb;

	if (!m_find.FindNumb(d))
	{
		puts("������Ĺ��Ų����ڣ�");
		system("pause");
		return;
	}
	CMannger::PrintWorker(d);
	cout << "��ȷ��Ҫ�޸�������¼��?[y/n]";
	char c;
	cin >> c;
	if (c != 'Y' && c != 'y')
		return;

	cout << "��¼���µ����������ʺ���ְ���ڣ�";
	cin >> d.sName >> d.fsala >> d.sDate;
	int nCmd = WK_MODIFY;
	m_sock.Send(&nCmd, sizeof(nCmd));
	m_sock.Send(&d, sizeof(d));
	Print();
}
