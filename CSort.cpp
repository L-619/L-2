#include "CSort.h"
#include"CWorker.h"

#include <iostream>
using namespace std;
int CSort::Menu()
{

	system("cls");
	puts("\n\n\t\t********************************");
	puts("\t\t*\t1、按工号排序        *");
	puts("\t\t*\t2、按姓名排序        *");
	puts("\t\t*\t3、按工资排序        *");
	puts("\t\t*\t4、按入职日期排序    *");
	puts("\t\t*\t0、返回主菜单         *");
	puts("\t\t********************************");
	cout << "\t\t请选择：";
	int i = 0;
	cin >> i;
	if (i > 0 && i < 5)
		m_pWorker->Print(i-1);
	

	return i;
}

CSort::CSort(CWorker* pWorker) :m_sock(pWorker->m_sock), m_pWorker(pWorker)
{

}
