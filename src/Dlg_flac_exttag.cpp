// Dlg_flac_exttag.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "mp3infp.h"
#include "Dlg_flac_exttag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlg_flac_exttag �_�C�A���O


CDlg_flac_exttag::CDlg_flac_exttag(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_flac_exttag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_flac_exttag)
	m_strName = _T("");
	m_strValue = _T("");
	//}}AFX_DATA_INIT
}


void CDlg_flac_exttag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_flac_exttag)
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_strValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg_flac_exttag, CDialog)
	//{{AFX_MSG_MAP(CDlg_flac_exttag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg_flac_exttag ���b�Z�[�W �n���h��

BOOL CDlg_flac_exttag::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_strName.GetLength())
	{
		::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT_VALUE));
	}

	return FALSE;
//	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CDlg_flac_exttag::OnOK()
{
	CString strName;
	CString strValue;

	GetDlgItem(IDC_EDIT_NAME)->GetWindowText(strName);
	GetDlgItem(IDC_EDIT_VALUE)->GetWindowText(strValue);
	//�t�B�[���h�������`�F�b�N
	if(strName.IsEmpty())
	{
		AfxMessageBox(IDS_PLEASE_TAG_NAME);
		::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT_NAME));
		Edit_SetSel(::GetDlgItem(m_hWnd,IDC_EDIT_NAME),0,-1);
		return;
	}
	//�t�B�[���h���`�F�b�N
	for(int i=0; i<strName.GetLength(); i++)
	{
		int c = strName[i];
		if(
			!((c >= ' ') && ('}' >= c))	//0x20 - 0x7d
			||
			(c == '=')	//0x3d
			)
		{
			//�֎~�����𔭌�
			AfxMessageBox(IDS_OGG_BAD_CHAR);
			::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT_NAME));
			Edit_SetSel(::GetDlgItem(m_hWnd,IDC_EDIT_NAME),0,-1);
			return;
		}

	}
	
	CDialog::OnOK();
}