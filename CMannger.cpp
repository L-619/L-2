#include "CMannger.h"
CMannger CMannger::m_man;
using namespace std;


int CMannger::Menu()
{
	system("cls");
	int nPrior = GetPrior();
	const char* p = nPrior ? "��ͨ" : "�߼�";
	cout << "\n\n\t\t��ǰ�˺ţ�" << GetUser() << "��" << p << "��" << endl;
	puts("\t\t********************************");
	puts("\t\t*\t1�����������Ϣ        *");
	puts("\t\t*\t2�������Ϣ            *");
	puts("\t\t*\t3��ɾ����Ϣ            *");
	puts("\t\t*\t4���޸���Ϣ            *");
	puts("\t\t*\t5��������Ϣ            *");
	if (nPrior)
		puts("\t\t*\t6�������޸�            *");
	else
		puts("\t\t*\t6���˺Ź���            *");
	puts("\t\t*\t0���˳�                *");
	puts("\t\t********************************");
	cout << "\t\t��ѡ��";
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
		cout << "�����˿�ʧ��" << m_sock.GetLastError() << endl;
		return -1;
	}
	if (!m_sock.Connect("192.168.18.1", SEVER_PORT))
	{
		cout << "���ӷ�����ʧ��" << m_sock.GetLastError() << endl;
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
