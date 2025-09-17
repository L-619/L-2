#pragma once
#include"define.h"
class CFind
{
	CSockLx& m_sock;
	void FindByNumb();
	void FindByName();
	void FindBySalary();
	void FindByDate();

public:
	bool FindNumb(SInfo& d);
	int Menu();
	CFind(CSockLx& sock) :m_sock(sock)
	{

	}
};

