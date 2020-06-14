#if !defined(AFX_PAGEFLAC_H__288F90B1_11C1_4526_83BF_077A38DD7DB3__INCLUDED_)
#define AFX_PAGEFLAC_H__288F90B1_11C1_4526_83BF_077A38DD7DB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageFlac.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CPageFlac �_�C�A���O

class CPageFlac : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageFlac)

// �R���X�g���N�V����
public:
	CPageFlac();
	~CPageFlac();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CPageFlac)
	enum { IDD = IDD_SETUP_FLAC };
	CButton	m_wndPropEnable;
	CEdit	m_wndInfotipInfo;
	CEdit	m_wndInfotipFormat;
	CButton	m_wndInfotipEnable;
	CStatic	m_staticInfotipFormat;
	BOOL	m_bInfotipEnable;
	BOOL	m_bColumnEnable;
	BOOL	m_bPropEnable;
	CString	m_strInfotipFormat;
	CString	m_strInfotipInfo;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CPageFlac)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CPageFlac)
	afx_msg void OnDefault();
	afx_msg void OnSetCheck();
	virtual BOOL OnInitDialog();
	afx_msg void OnHelpview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void SetCheck();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PAGEFLAC_H__288F90B1_11C1_4526_83BF_077A38DD7DB3__INCLUDED_)
