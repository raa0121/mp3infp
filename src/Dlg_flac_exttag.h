#if !defined(AFX_DLG_FLAC_EXTTAG_H__C42A8D30_5A92_4310_859E_81A32C7A461A__INCLUDED_)
#define AFX_DLG_FLAC_EXTTAG_H__C42A8D30_5A92_4310_859E_81A32C7A461A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_flac_exttag.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_flac_exttag ダイアログ

class CDlg_flac_exttag : public CDialog
{
// コンストラクション
public:
	CDlg_flac_exttag(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlg_flac_exttag)
	enum { IDD = IDD_DIALOG_FLAC_EXTTAG };
	CString	m_strName;
	CString	m_strValue;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlg_flac_exttag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlg_flac_exttag)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLG_FLAC_EXTTAG_H__C42A8D30_5A92_4310_859E_81A32C7A461A__INCLUDED_)
