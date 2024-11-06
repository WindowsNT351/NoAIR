#pragma once


// CDiaAct 对话框

class CDiaAct : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaAct)

public:
	CDiaAct(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDiaAct();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit4;
	CEdit m_edit5;
	virtual BOOL OnInitDialog();
};
