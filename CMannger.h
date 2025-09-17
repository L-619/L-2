#pragma once
#include"define.h"
#include"CWorker.h"
#include"Admin.h"
class CMannger :public Admin,public CWorker
{

	int Menu();
public:

	static CMannger m_man;
	static void PrintWorker(const SInfo d)
	{
		std::cout << d.nNumb << '\t' << d.sName << "\t" << d.fsala << "\t" << d.sDate <<std:: endl;

	}

	int Main();
};

