#pragma once
#include"define.h"
class CWorker;
class CSort
{
	CSockLx& m_sock;
	CWorker* m_pWorker;
public:
	int Menu();
	CSort(CWorker* pWorker);

};

