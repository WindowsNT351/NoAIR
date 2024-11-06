#pragma once


// CDiaSet 对话框

extern int crackUseAPI;
extern int crackUseCMD;
extern int crackTime;

class CDiaSet : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaSet)

public:
	CDiaSet(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDiaSet();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIASET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit m_edit1;
	CButton m_check1;
	CButton m_check2;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
};
