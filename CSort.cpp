#include "CSort.h"
#include"CWorker.h"

#include <iostream>
using namespace std;
int CSort::Menu()
{

	system("cls");
	puts("\n\n\t\t********************************");
	puts("\t\t*\t1������������        *");
	puts("\t\t*\t2������������        *");
	puts("\t\t*\t3������������        *");
	puts("\t\t*\t4������ְ��������    *");
	puts("\t\t*\t0���������˵�         *");
	puts("\t\t********************************");
	cout << "\t\t��ѡ��";
	int i = 0;
	cin >> i;
	if (i > 0 && i < 5)
		m_pWorker->Print(i-1);
	

	return i;
}

CSort::CSort(CWorker* pWorker) :m_sock(pWorker->m_sock), m_pWorker(pWorker)
{

}
