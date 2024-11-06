
// NoAIRDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "NoAIR.h"
#include "NoAIRDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <tlhelp32.h>
#include <winsvc.h>
#include <cctype>
#include "CDiaSet.h"
#include "CDiaAct.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNoAIRDlg 对话框



CNoAIRDlg::CNoAIRDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOAIR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNoAIRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNoAIRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CNoAIRDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTABOUT, &CNoAIRDlg::OnBnClickedButabout)
	ON_BN_CLICKED(IDC_BUTSET, &CNoAIRDlg::OnBnClickedButset)
	ON_BN_CLICKED(IDC_BUTTON3, &CNoAIRDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CNoAIRDlg 消息处理程序

BOOL CNoAIRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CDiaAct dlg;
	dlg.DoModal();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNoAIRDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CNoAIRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CNoAIRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

std::string UnicodeToAscii(const std::wstring& in_str)
{
	int nNeedChars = WideCharToMultiByte(CP_ACP, 0, in_str.c_str(), -1, 0, 0, 0, 0);
	if (nNeedChars > 0)//再次判断一下
	{
		std::vector<char> temp(nNeedChars);
		::WideCharToMultiByte(CP_ACP, 0, in_str.c_str(), -1, &temp[0], nNeedChars, 0, 0);
		return std::string(&temp[0]);
	}

	return std::string();
}
bool icompare_pred(unsigned char a, unsigned char b)
{
	return std::tolower(a) == std::tolower(b);
}

bool icasecompare(std::string const& a, std::string const& b)
{
	if (a.length() == b.length()) {
		return std::equal(b.begin(), b.end(),
			a.begin(), icompare_pred);
	}
	else {
		return false;
	}
}
void doCommand(TCHAR *cmd, TCHAR *para)
{
	ShellExecute(NULL, L"open", cmd, para, NULL, SW_SHOWNORMAL);
}
bool KillProcessEx(vector<string> &processNameVec,int useAPI,int useCMD)
{
	if (useAPI == 1)
	{
		HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);

		if (!Process32First(hSnapShot, &pe))
		{
			goto checkCMD;
		}

		while (Process32Next(hSnapShot, &pe))
		{
			wstring strTemp = pe.szExeFile;
			string strProcessTemp = UnicodeToAscii(strTemp);

			bool bIn = false;
			for (int i = 0; i < processNameVec.size(); i++)
			{
				if (icasecompare(processNameVec[i], strProcessTemp))
					//if (processNameVec[i] == strProcessTemp)
				{
					bIn = true;
				}
			}

			if (bIn)
			{
				DWORD dwProcessID = pe.th32ProcessID;
				HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessID);
				::TerminateProcess(hProcess, 0);
				CloseHandle(hProcess);
			}
		}
		goto checkCMD;
	}
checkCMD:
	if (useCMD == 1)
	{
		TCHAR cmdBuffer[255] = { 0 };
		for (int i = 0; i < processNameVec.size(); i++)
		{

			wsprintf(cmdBuffer, L"/F /IM \"%s\"", processNameVec[i]);
			//system(cmdBuffer);
			doCommand(L"taskkill", cmdBuffer);
		}
		return 1;
	}
	return 3;
}

bool KillService(LPCWSTR ServiceName, int useAPI, int useCMD)
{
	if (useAPI == 1)
	{
		SC_HANDLE hSC = ::OpenSCManager(NULL,
			NULL, GENERIC_EXECUTE);
		if (hSC == NULL)
		{
			//TRACE("open SCManager error");
			goto checkCMD;
		}
		// 打开服务。
		SC_HANDLE hSvc = ::OpenService(hSC, ServiceName,
			SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
		if (hSvc == NULL)
		{
			//TRACE("Open www erron。");
			::CloseServiceHandle(hSC);
			goto checkCMD;
		}
		// 获得服务的状态
		SERVICE_STATUS status;
		if (::QueryServiceStatus(hSvc, &status) == FALSE)
		{
			//TRACE("Get Service state error。");
			::CloseServiceHandle(hSvc);
			::CloseServiceHandle(hSC);
			goto checkCMD;
		}
		//停止服务。
		if (status.dwCurrentState == SERVICE_RUNNING)
		{
			// 停止服务
			if (::ControlService(hSvc,
				SERVICE_CONTROL_STOP, &status) == FALSE)
			{
				//TRACE("stop service error。");
				::CloseServiceHandle(hSvc);
				::CloseServiceHandle(hSC);
				goto checkCMD;
			}
			// 等待服务停止
			while (::QueryServiceStatus(hSvc, &status) == TRUE)
			{
				::Sleep(status.dwWaitHint);
				if (status.dwCurrentState == SERVICE_STOPPED)
				{
					//MessageBox(L"stop success");
					::CloseServiceHandle(hSvc);
					::CloseServiceHandle(hSC);
					goto checkCMD;
				}
			}
		}
	}
checkCMD:
	if (useCMD == 1)
	{
		TCHAR cmdBuffer[255] = { 0 };
		
		wsprintf(cmdBuffer, L"stop \"%s\"", ServiceName);
		//system(cmdBuffer);
		doCommand(L"sc", cmdBuffer);
	}
	return 3;
}


void CNoAIRDlg::OnBnClickedOk()
{	

	/*单进程部分*/
	vector<string> killedPrssName;
	/*单进程*/
	killedPrssName.push_back("AsusAppService.exe");
	killedPrssName.push_back("AsusDetectDVD.exe");
	killedPrssName.push_back("AsusOSD.exe");
	killedPrssName.push_back("AsusSoftwareManager.exe");
	killedPrssName.push_back("AsusSoftwareManagerAgent.exe");
	killedPrssName.push_back("AsusSwitch.exe");
	killedPrssName.push_back("AsusSystemDiagnosis.exe");
	killedPrssName.push_back("rClient.exe");
	killedPrssName.push_back("rConsoleApp.exe");
	killedPrssName.push_back("rConsole.exe");
	killedPrssName.push_back("rService.exe");
	killedPrssName.push_back("rConsoleSec.exe");
	killedPrssName.push_back("capclient_c.exe");
	killedPrssName.push_back("SU10Guard.exe");
	killedPrssName.push_back("cceventapp.exe");
	/*杀不掉系列*/
	//killedPrssName.push_back("AbmSvcHost.exe");
	//killedPrssName.push_back("DevHookSvc.exe");
	/*KILL Processes*/
	for (int i = 0; i < crackTime; i++)
	{
		/*服务部分*/
		//KillService(L"AsusLinkNear", crackUseAPI, crackUseCMD);
		//KillService(L"AsusLinkRemote", crackUseAPI, crackUseCMD);
		//KillService(L"AsusLinkOptimization", crackUseAPI, crackUseCMD);
		//KillService(L"AsusLinkOptimizationStartupTask", crackUseAPI, crackUseCMD);
		//KillService(L"AsusSAIO", crackUseAPI, crackUseCMD);
		//KillService(L"AsusSystemAnalysis", crackUseAPI, crackUseCMD);
		/*忘了大小写了*/

		KillService(L"ASUSLinkNear", crackUseAPI, crackUseCMD);
		KillService(L"ASUSLinkRemote", crackUseAPI, crackUseCMD);
		KillService(L"ASUSLinkOptimization", crackUseAPI, crackUseCMD);
		KillService(L"ASUSLinkOptimizationStartupTask", crackUseAPI, crackUseCMD);
		KillService(L"ASUSSAIO", crackUseAPI, crackUseCMD);
		KillService(L"ASUSSystemAnalysis", crackUseAPI, crackUseCMD);

		KillService(L"ASUSOptimization", crackUseAPI, crackUseCMD);
		KillService(L"ASUSSoftwareManager", crackUseAPI, crackUseCMD);
		KillService(L"ASUSSwitch", crackUseAPI, crackUseCMD);
		KillService(L"ASUSBusinessUtility", crackUseAPI, crackUseCMD);
		KillService(L"tvnserver", crackUseAPI, crackUseCMD);

		KillProcessEx(killedPrssName, crackUseAPI, crackUseCMD);



		TCHAR cmdBuffer[255] = { 0 };
		wsprintf(cmdBuffer, L"failure AbmSvc reset= 0 actions= none/3000/none/3000/none/3000");
		doCommand(L"sc", cmdBuffer);
		wsprintf(cmdBuffer, L"/F /IM AbmSvcHost.exe");
		doCommand(L"taskkill", cmdBuffer);
	}

	MessageBox(L"完成！");



	//CDialogEx::OnOK();
}


void CNoAIRDlg::OnBnClickedButabout()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CNoAIRDlg::OnBnClickedButset()
{
	// TODO: 在此添加控件通知处理程序代码
	CDiaSet dlgSet;
	dlgSet.DoModal();
}


void CNoAIRDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
}
