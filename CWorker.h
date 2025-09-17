#pragma once
#include "CFind.h"
#include"CSort.h"
class CWorker:virtual public CBase
{
	friend class CMannger;
	CFind m_find{ m_sock };
	CSort m_sort{ this};
	void Input();
	void Delete();
	void Modify();
public:
	void Print(int nOrder = -1);
	CWorker()
	{

	}
};

