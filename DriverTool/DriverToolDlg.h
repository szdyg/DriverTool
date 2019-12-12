
// DriverToolDlg.h: 头文件
//

#pragma once


// CDriverToolDlg 对话框
class CDriverToolDlg : public CDialogEx
{
// 构造
public:
	CDriverToolDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRIVERTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CEdit _ComError;
    CString _Driverlog;
    CString _DriverPath;
    CEdit _Win32Error;
    CEdit _NtstatusError;
};
