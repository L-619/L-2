#pragma once
#include"define.h"
class Admin :virtual public CBase
{
	sAdmin m_user;
	bool Check(sAdmin& a);
	void Print();
	void Input();
	void Delete();
	int Menu();
	void CPass();//�޸�����
	bool ChangePass(const char * sPass);
	static void  Print(const sAdmin& a)
	{
		std::cout << a.sName << "\t" << a.sPass << "\t" << (a.nPrior ? "��ͨ" : "�߼�" )<< std::endl;
	}
public:
	bool Login();
	void Main();
	int GetPrior()const
	{
		return m_user.nPrior;
	}
	const char* GetUser()const
	{
		return m_user.sName;
	}
};

