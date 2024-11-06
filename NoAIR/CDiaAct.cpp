// CDiaAct.cpp: 实现文件
//

#include "pch.h"
#include "NoAIR.h"
#include "CDiaAct.h"
#include "afxdialogex.h"
#include <shlwapi.h>


// CDiaAct 对话框

IMPLEMENT_DYNAMIC(CDiaAct, CDialogEx)

CDiaAct::CDiaAct(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ACTBOX, pParent)
{

}

CDiaAct::~CDiaAct()
{
}

void CDiaAct::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
	DDX_Control(pDX, IDC_EDIT4, m_edit4);
	DDX_Control(pDX, IDC_EDIT5, m_edit5);
}


BEGIN_MESSAGE_MAP(CDiaAct, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaAct::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDiaAct::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDiaAct 消息处理程序

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
void CDiaAct::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csEdit1;
	CString csEdit2;
	CString csEdit3;
	CString csEdit4;
	CString csEdit5;
	m_edit1.GetWindowText(csEdit1);
	m_edit2.GetWindowText(csEdit2);
	m_edit3.GetWindowText(csEdit3);
	m_edit4.GetWindowText(csEdit4);
	m_edit5.GetWindowText(csEdit5);
	CString csKey = csEdit1 + csEdit2 + csEdit3 + csEdit4 + csEdit5;

	if (csKey.GetLength() != 25)
	{
		MessageBox(L"请正确输入密钥！");
		return;
	}

	//CString csKey;
	//csKey.ReleaseBufferSetLength(25);
	for (int i = 0; i < 25; i++)
	{
		TCHAR buffer;
		buffer = csKey.GetAt(i);
		switch (buffer)
		{
			case '1':
				buffer = '3';
				break;
			case '2':
				buffer = '1';
				break;
			case '3':
				buffer = '7';
				break;
			case '4':
				buffer = '6';
				break;
			case '5':
				buffer = '9';
				break;
			case '6':
				buffer = '2';
				break;
			case '7':
				buffer = '8';
				break;
			case '8':
				buffer = '4';
				break;
			case '9':
				buffer = '5';
				break;
			case '0':
				buffer = '0';
				break;
		}
		csKey.SetAt(i, buffer);
	}

	CString csType = csKey.Left(3);
	CString csDate1 = csKey.Mid(3, 6);
	CString csDate2 = csKey.Mid(9, 6);
	CString csIp = csKey.Mid(15, 3);
	CString csCheck = csKey.Mid(18, 7);
	


	int flag = 10000;
	int iType = _wtoi(csType);
	if (!(iType == 1))
		flag += 1;

	CTime time = CTime::GetCurrentTime();
	int iDate1 = _wtoi(csDate1);
	int iDate2 = _wtoi(csDate2);
	int iDate = time.GetYear() %100 * 10000 + time.GetMonth() * 100 + time.GetDay();
	if (!(iDate >= iDate1 && iDate <= iDate2))
		flag += 10;

	int iIp = _wtoi(csIp);
	if (!(iIp == getIPLast()))
		flag += 100;

	srand(351 + iType + iDate1 + iDate2 + iIp);
	int iCheckS = 1 + (int)(9999999.0 * rand() / (RAND_MAX + 1.0));
	int iCheck = _wtoi(csCheck);
	if (!(iCheckS == iCheck))
		flag += 1000;

	if (flag != 10000)
	{
		TCHAR buffer[255] = {0};
		wsprintf(buffer, L"WK,%d", flag);
		MessageBox(buffer);
		exit(0);
	}
	CDialogEx::OnOK();
}


void CDiaAct::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
	CDialogEx::OnCancel();
}


BOOL CDiaAct::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_edit1.SetLimitText(5);
	m_edit2.SetLimitText(5);
	m_edit3.SetLimitText(5);
	m_edit4.SetLimitText(5);
	m_edit5.SetLimitText(5);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
