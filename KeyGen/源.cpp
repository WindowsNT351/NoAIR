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
	//PIP_ADAPTER_INFO�ṹ��ָ��洢����������Ϣ
	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
	//�õ��ṹ���С,����GetAdaptersInfo����
	unsigned long stSize = sizeof(IP_ADAPTER_INFO);
	//����GetAdaptersInfo����,���pIpAdapterInfoָ�����;����stSize��������һ��������Ҳ��һ�������
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	//��¼��������
	DWORD netCardNum = 0;
	GetNumberOfInterfaces(&netCardNum);
	if (ERROR_BUFFER_OVERFLOW == nRel)
	{
		//����������ص���ERROR_BUFFER_OVERFLOW
		//��˵��GetAdaptersInfo�������ݵ��ڴ�ռ䲻��,ͬʱ�䴫��stSize,��ʾ��Ҫ�Ŀռ��С
		//��Ҳ��˵��ΪʲôstSize����һ��������Ҳ��һ�������
		//�ͷ�ԭ�����ڴ�ռ�
		delete pIpAdapterInfo;
		//���������ڴ�ռ������洢����������Ϣ
		pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
		//�ٴε���GetAdaptersInfo����,���pIpAdapterInfoָ�����
		nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	}
	if (ERROR_SUCCESS == nRel)
	{
		//���������Ϣ
		//�����ж�����,���ͨ��ѭ��ȥ�ж�
		while (pIpAdapterInfo)
		{
			//���������ж�IP,���ͨ��ѭ��ȥ�ж�
			IP_ADDR_STRING *pIpAddrString = &(pIpAdapterInfo->IpAddressList);
			do
			{
				if (strcmp(pIpAdapterInfo->GatewayList.IpAddress.String, "0.0.0.0") != 0)
				{
					//cout << "IP ��ַ��" << pIpAddrString->IpAddress.String << endl;
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
	//�ͷ��ڴ�ռ�
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
		printf(" [1] �������ɱ�����Կ\n");
		printf(" [2] ָ��������Կ\n");
	}
	else if (iFunc == 1)
	{
		printf(" [N/A] �������ɱ�����Կ\n");
		printf(" [N/A] ָ��������Կ\n");
	}
	printf(" [N/A] �����������\n");
	printf("\n [0] �˳�\n");
	printf(" ��������ѡ��:");
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