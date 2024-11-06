// CDiaSet.cpp: 实现文件
//

#include "pch.h"
#include "NoAIR.h"
#include "CDiaSet.h"
#include "afxdialogex.h"

int crackUseAPI = 1;
int crackUseCMD = 0;
int crackTime = 2;
// CDiaSet 对话框

IMPLEMENT_DYNAMIC(CDiaSet, CDialogEx)

CDiaSet::CDiaSet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIASET, pParent)
{

}

CDiaSet::~CDiaSet()
{
}

void CDiaSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_CHECK2, m_check2);
}


BEGIN_MESSAGE_MAP(CDiaSet, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaSet::OnBnClickedOk)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CDiaSet::OnDeltaposSpin1)
END_MESSAGE_MAP()


// CDiaSet 消息处理程序


void CDiaSet::OnBnClickedOk()
{
	CString edit1 = NULL;
	m_edit1.GetWindowText(edit1);
	int check1 = m_check1.GetCheck();
	int check2 = m_check2.GetCheck();
	int iedit1 = _ttoi(edit1);

	crackTime = iedit1;
	crackUseAPI = check2;
	crackUseCMD = check1;
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


BOOL CDiaSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	wchar_t ltime[255] = { 0 };
	wsprintf(ltime, L"%d", crackTime);
	m_edit1.SetWindowText(ltime);
	m_check1.SetCheck(crackUseCMD);
	m_check2.SetCheck(crackUseAPI);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDiaSet::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CString edit1 = NULL;
	m_edit1.GetWindowText(edit1);
	int iedit1 = _ttoi(edit1);
	if (pNMUpDown->iDelta == 1)//下
	{
		if (iedit1 <= 0)
			return;
		wchar_t ltime[255] = { 0 };
		wsprintf(ltime, L"%d", --iedit1);
		m_edit1.SetWindowText(ltime);
	}
	else
	{
		wchar_t ltime[255] = { 0 };
		wsprintf(ltime, L"%d", ++iedit1);
		m_edit1.SetWindowText(ltime);
	}
}
