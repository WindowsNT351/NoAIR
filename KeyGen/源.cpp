#pragma comment(lib,"iphlpapi.lib")
#include <stdlib.h>
#include <stdio.h>
//#include <Windows.h>
#include <iostream>
#include <ctime>
#include <cstring>
//#include <shlwapi.h>
#include <WinSock2.h>
#include <Iphlpapi.h>
#include <random>
using namespace std;

int getIPLast()
{
	//PIP_ADAPTER_INFO结构体指针存储本机网卡信息
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	//得到结构体大小,用于GetAdaptersInfo参数
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量;其中stSize参数既是一个输入量也是一个输出量
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	//记录网卡数量
	DWORD netCardNum = 0;
	GetNumberOfInterfaces(&netCardNum);
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//如果函数返回的是ERROR_BUFFER_OVERFLOW
		//则说明GetAdaptersInfo参数传递的内存空间不够,同时其传出stSize,表示需要的空间大小
		//这也是说明为什么stSize既是一个输入量也是一个输出量
		//释放原来的内存空间
		delete pIpAdapterInfo;
		//重新申请内存空间用来存储所有网卡信息
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//再次调用GetAdaptersInfo函数,填充pIpAdapterInfo指针变量
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}
	if (ERROR_SUCCESS == nRel)
	{
		//输出网卡信息
		//可能有多网卡,因此通过循环去判断
		while (pIpAdapterInfo)
		{
			//可能网卡有多IP,因此通过循环去判断
			IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);
			do
			{
				if (strcmp(pIpAdapterInfo->GatewayList.IpAddress.String, "0.0.0.0") != 0)
				{
					//cout << "IP 地址：" << pIpAddrString->IpAddress.String << endl;
					//cout << "--------------------------------------------------------------------" << endl;
					//strcpy(iptemp, pIpAddrString->IpAddress.String);
					char buffer[255] = { 0 };
					int count = 0;
					for (int i = 0;; i++)
					{
						if (pIpAddrString->IpAddress.String[i] == '.')
							count++;
						if (count == 3)
						{
							for (int j = 1;; j++)
							{
								buffer[j - 1] = pIpAddrString->IpAddress.String[i + j];
								if (pIpAddrString->IpAddress.String[i + j] == 0)
									break;
							}
							break;
						}
					}
					return atoi(buffer);
				}
				pIpAddrString = pIpAddrString->Next;
			} while (pIpAddrString);
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}

	}
	//释放内存空间
	if (pIpAdapterInfo)
	{
		delete pIpAdapterInfo;
	}
	return 0;
}

int checkKey(int iKey)
{
	if (iKey == 8351)
	{
		return 2;
	}
}

string keyGen(int date1,int date2,int ip)
{
	string sKey;
	sKey += "001";
	char buffer[255] = { 0 };
	sprintf_s(buffer, "%06d", date1);
	//_itoa_s(date1, buffer, 10);
	sKey += buffer;
	sprintf_s(buffer, "%06d", date2);
	//_itoa_s(date2, buffer, 10);
	sKey += buffer;
	sprintf_s(buffer, "%03d", ip);
	//_itoa_s(ip, buffer, 10);
	sKey += buffer;
	srand(351 + 1 + date1 + date2 + ip);
	int iCheckS = 1 + (int)(9999999.0 * rand() / (RAND_MAX + 1.0));
	sprintf_s(buffer, "%07d", iCheckS);
	//_itoa_s(iCheckS, buffer, 10);
	sKey += buffer;

	for (int i = 0; i < 25; i++)
	{
		char cbuffer;
		cbuffer = sKey[i];
		switch (cbuffer)
		{
		case '1':
			cbuffer = '2';
			break;
		case '2':
			cbuffer = '6';
			break;
		case '3':
			cbuffer = '1';
			break;
		case '4':
			cbuffer = '8';
			break;
		case '5':
			cbuffer = '9';
			break;
		case '6':
			cbuffer = '4';
			break;
		case '7':
			cbuffer = '3';
			break;
		case '8':
			cbuffer = '7';
			break;
		case '9':
			cbuffer = '5';
			break;
		case '0':
			cbuffer = '0';
			break;
		}
		sKey[i] = cbuffer;
	}
	return sKey;
}

int main()
{
	printf("\n  NoAIR - KeyGen\n ==================================================\n\n");
	printf(" Your key for KeyGen: ");
	int iKey = 0;
	cin >> iKey;

	int iFunc = checkKey(iKey);


	//cout << "\033[2J\033[H";
	system("cls");
	printf("\n  NoAIR - KeyGen\n ==================================================\n\n");
	if (iFunc == 2)
	{
		printf(" [1] 快速生成本机密钥\n");
		printf(" [2] 指定生成密钥\n");
	}
	else if (iFunc == 1)
	{
		printf(" [N/A] 快速生成本机密钥\n");
		printf(" [N/A] 指定生成密钥\n");
	}
	printf(" [N/A] 随机数生成器\n");
	printf("\n [0] 退出\n");
	printf(" 键入您的选择:");
	int iChoice = 0;
	cin >> iChoice;

	if (iChoice == 1 && iFunc == 2)
	{
		int date1 = 000000;
		int date2 = 999999;
		int ip = getIPLast();
		system("cls");
		//cout << "\033[2J\033[H";
		printf("\n  NoAIR - KeyGen\n ==================================================\n\n");
		printf(" Date1: ");
		cout << date1;
		printf("\n Date2: ");
		cout << date2;
		printf("\n Ip: ");
		cout << ip;
		string sKey = keyGen(date1, date2, ip);
		printf("\n\n Key: ");

		for (int j = 0; j < 25; j++)
		{
			if (j % 5 == 0 && j != 0)
			{
				cout << '-' << sKey.at(j);
			}
			else
			{
				cout << sKey.at(j);
			}
		}
		printf("\n ");
		system("pause");
		system("cls");
		main();
	}
	else if (iChoice == 2 && iFunc == 2)
	{
		int date1 = 0;
		int date2 = 0;
		int ip = 0;
		system("cls");
		//cout << "\033[2J\033[H";
		printf("\n  NoAIR - KeyGen\n ==================================================\n\n");
		printf(" Date1: ");
		cin >> date1;
		printf("\n Date2: ");
		cin >> date2;		
		printf("\n Ip: ");
		cin >> ip;
		string sKey = keyGen(date1, date2, ip);
		printf("\n Key: ");
	
		for (int j = 0;j < 25;j++)
		{
			if (j % 5 == 0 && j != 0)
			{
				cout << '-' << sKey.at(j);
			}
			else
			{
				cout << sKey.at(j);
			}
		}
		printf("\n ");
		system("pause");
		system("cls");
		main();
	}
	else if (iChoice == 3)
	{
		
	}
	
	return 0;
}