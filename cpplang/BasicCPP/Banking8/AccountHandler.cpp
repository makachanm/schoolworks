/*
 * ???????: AccountHandler.cpp
 * ?????: ??????
 * ??????? ????: [2010, 01, 01] ??????? 0.7 
 */

#include "BankingCommonDecl.h"
#include "AccountHandler.h"
#include "Account.h"
#include "NormalAccount.h"
#include "HighCreditAccount.h"

void AccountHandler::ShowMenu(void) const
{
	cout<<"-----Menu------"<<endl;
	cout<<"1. ???¡Æ???"<<endl;
	cout<<"2. ??    ??"<<endl;
	cout<<"3. ??    ??"<<endl;
	cout<<"4. ???????? ??? ???"<<endl;
	cout<<"5. ???¥á?? ????"<<endl;
}

void AccountHandler::MakeAccount(void)
{
	int sel;
	cout<<"[????????????]"<<endl;
	cout<<"1.???—¹????? ";
	cout<<"2.???????? "<<endl;
	cout<<"????: ";
	cin>>sel;
	
	if(sel==NORMAL)
		MakeNormalAccount();
	else
		MakeCreditAccount();
}

void AccountHandler::MakeNormalAccount(void)
{
	int id;
	char name[NAME_LEN];
	int balance;
	int interRate;

	cout<<"[???—¹????? ????]"<<endl;
	cout<<"????ID: ";	cin>>id;
	cout<<"??  ??: ";	cin>>name;
	cout<<"????: ";	cin>>balance;
	cout<<"??????: ";	cin>>interRate;
	cout<<endl;

	accArr[accNum++]=new NormalAccount(id, balance, name, interRate);
}

void AccountHandler::MakeCreditAccount(void)
{
	int id;
	char name[NAME_LEN];
	int balance;
	int interRate;
	int creditLevel;

	cout<<"[???????? ????]"<<endl;
	cout<<"????ID: ";	cin>>id;
	cout<<"??  ??: ";	cin>>name;
	cout<<"????: ";	cin>>balance;
	cout<<"??????: ";	cin>>interRate;
	cout<<"?????(1toA, 2toB, 3toC): ";	cin>>creditLevel;
	cout<<endl;

	switch(creditLevel)
	{
	case 1:
		accArr[accNum++]=new HighCreditAccount(id, balance, name, interRate, LEVEL_A);
		break;
	case 2:
		accArr[accNum++]=new HighCreditAccount(id, balance, name, interRate, LEVEL_B);
		break;
	case 3:
		accArr[accNum++]=new HighCreditAccount(id, balance, name, interRate, LEVEL_C);
	}
}

void AccountHandler::DepositMoney(void)
{
	int money;
	int id;
	cout<<"[??    ??]"<<endl;
	cout<<"????ID: ";	cin>>id;
	cout<<"????: ";	cin>>money;
	
	for(int i=0; i<accNum; i++)
	{
		if(accArr[i]->GetAccID()==id)
		{
			accArr[i]->Deposit(money);
			cout<<"?????"<<endl<<endl;
			return;
		}
	}
	cout<<"??????? ???? ID ????."<<endl<<endl;
}

void AccountHandler::WithdrawMoney(void)
{
	int money;
	int id;
	cout<<"[??    ??]"<<endl;
	cout<<"????ID: ";	cin>>id;
	cout<<"????: ";	cin>>money;
	
	for(int i=0; i<accNum; i++)
	{
		if(accArr[i]->GetAccID()==id)
		{
			if(accArr[i]->Withdraw(money)==0)
			{
				cout<<"??????"<<endl<<endl;
				return;
			}

			cout<<"?????"<<endl<<endl;
			return;
		}
	}
	cout<<"??????? ???? ID ????."<<endl<<endl;
}

AccountHandler::AccountHandler() : accNum(0)
{  }

void AccountHandler::ShowAllAccInfo(void) const
{
	for(int i=0; i<accNum; i++)
	{
		accArr[i]->ShowAccInfo();
		cout<<endl;
	}
}

AccountHandler::~AccountHandler()
{
	for(int i=0; i<accNum; i++)
		delete accArr[i];
}