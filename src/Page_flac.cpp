#include "StdAfx.h"
#include "mp3infp.h"

#include "Dlg_ogg_exttag.h"

static const int ids[] =
{
	-1,
	-1,
	CLP_NAM,
	CLP_TRACK,
	CLP_DISC,
	CLP_ART,
	CLP_PRD,
	CLP_AART,
	CLP_CRD,
	CLP_GNR,
	CLP_CMT,
	0
};

static const int staticWnd[] =
{
	IDC_STATIC_FORMAT_,
	IDC_STATIC_TIME_,
	IDC_STATIC_NAM,
	IDC_STATIC_TRK,
	IDC_STATIC_DISC,
	IDC_STATIC_ART,
	IDC_STATIC_PRD,
	IDC_STATIC_AART,
	IDC_STATIC_CRD,
	IDC_STATIC_GNR,
	IDC_STATIC_CMT,
	0
};

static const int editWnd[] =
{
	IDC_STATIC_FORMAT,
	IDC_STATIC_TIME,
	IDC_EDIT_SBJ,
	IDC_EDIT_TRK,
	IDC_EDIT_DISC,
	IDC_EDIT_ART,
	IDC_EDIT_PRD,
	IDC_EDIT_AART,
	IDC_EDIT_CRD,
	IDC_EDIT_GNR,
	IDC_EDIT_CMT,
	0
};

class CFlacExt
{
public:
	CFlacExt(LPCTSTR name,LPCTSTR value)
	{
		m_strName = name;
		m_strValue = value;
	};
	virtual ~CFlacExt()
	{
	};

	CString GetName(){return m_strName;};
	void SetName(LPCTSTR name){m_strName = name;};
	CString GetValue(){return m_strValue;};
	void SetValue(LPCTSTR value){m_strValue = value;};
	CString Get1LineDisp()
	{
		//���s������Ƃ���(...)�ɒu������
		CString strValue;
		int crlf = m_strValue.FindOneOf(_T("\r\n"));
		if(crlf != -1)
		{
			strValue = CString(m_strValue,crlf) + _T("(...)");
		}
		else
		{
			strValue = m_strValue;
		}
		return m_strName + _T("=") + strValue;
	}

private:
	CString m_strName;
	CString m_strValue;
};

UINT CALLBACK CShellExt::PageCallback_ogg(HWND hWnd,UINT uMessage,LPPROPSHEETPAGE ppsp)
{
	LPCSHELLEXT	lpcs = (CShellExt *)ppsp->lParam;
	switch(uMessage){
	case PSPCB_CREATE:	//�v���p�e�B�y�[�W���쐬�������
		return TRUE;
	case PSPCB_RELEASE:	//�v���p�e�B�y�[�W���j�󂳂����
		if(lpcs) 
		{
			lpcs->m_hwndPage = NULL;
			lpcs->Release();
		}
		return TRUE;
	}

	return TRUE;
}

static void DispInfo(HWND hDlg,CShellExt *lpcs)
{
	SetDlgItemText(hDlg,IDC_STATIC_FORMAT,lpcs->m_Flac.GetAudioFormatString());
	SetDlgItemText(hDlg,IDC_STATIC_TIME,lpcs->m_Flac.GetTimeString());
	
	//���̑��̏��
	CString strAvg;
	if(lpcs->m_Flac.GetBitrateAvg() != -1)
		strAvg.Format(_T(" %ld(avg)"),lpcs->m_Flac.GetBitrateAvg());
	CString strUpper;
	if(lpcs->m_Flac.GetBitrateUpper() != -1)
		strUpper.Format(_T(" %ld(upper)"),lpcs->m_Flac.GetBitrateUpper());
	CString strNominal;
	if(lpcs->m_Flac.GetBitrateNominal() != -1)
		strNominal.Format(_T(" %ld(nominal)"),lpcs->m_Flac.GetBitrateNominal());
	CString strLower;
	if(lpcs->m_Flac.GetBitrateLower() != -1)
		strLower.Format(_T(" %ld(lower)"),lpcs->m_Flac.GetBitrateLower());
	CString strWindow;
	if(lpcs->m_Flac.GetBitrateWindow() != 0)
		strWindow.Format(_T(" %ld(window)"),lpcs->m_Flac.GetBitrateWindow());

	CString tmp;
	tmp.Format( _T("Version = %ld ,Serial=%ld\n")
				_T("Bitrate = %s%s%s%s%s\n")
				_T("Vendor = %s\n"),
				lpcs->m_Flac.GetVersion(),
				lpcs->m_Flac.GetSerial(),
				strAvg,
				strUpper,
				strNominal,
				strLower,
				strWindow,
				lpcs->m_Flac.GetVendor()
				);
	SetDlgItemText(hDlg,IDC_STATIC_ETC_INFO,tmp);

	lpcs->m_Flac.GetComment(_T("TITLE"),0,tmp);
	SetDlgItemText(hDlg,IDC_EDIT_SBJ,tmp);

	lpcs->m_Flac.GetComment(_T("TRACKNUMBER"),0,tmp);
	SetDlgItemText(hDlg,IDC_EDIT_TRK,tmp);
	
	lpcs->m_Flac.GetComment(_T("ARTIST"),0,tmp);
	SetDlgItemText(hDlg,IDC_EDIT_ART,tmp);
	
	lpcs->m_Flac.GetComment(_T("ALBUM"),0,tmp);
	SetDlgItemText(hDlg,IDC_EDIT_PRD,tmp);
	
	lpcs->m_Flac.GetComment(_T("ALBUMARTIST"),0,tmp);
	SetDlgItemText(hDlg,IDC_EDIT_AART,tmp);

	lpcs->m_Flac.GetComment(_T("DISCNUMBER"),0,tmp);
	SetDlgItemText(hDlg,IDC_EDIT_DISC,tmp);

	lpcs->m_Flac.GetComment(_T("DATE"),0,tmp);
	SetDlgItemText(hDlg,IDC_EDIT_CRD,tmp);
	
	lpcs->m_Flac.GetComment(_T("GENRE"),0,tmp);
	SetDlgItemText(hDlg,IDC_EDIT_GNR,tmp);
	
	lpcs->m_Flac.GetComment(_T("COMMENT"),0,tmp);
	SetDlgItemText(hDlg,IDC_EDIT_CMT,tmp);

	lpcs->m_bApply = FALSE;
	
	if(lpcs->m_bPropAOT)
	{
		CheckDlgButton(hDlg,IDC_CHECK_AOT,BST_CHECKED);
		SetWindowPos(GetParent(hDlg),HWND_TOPMOST,0,0,0,0,
			SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOSIZE);
	}
	else
	{
		CheckDlgButton(hDlg,IDC_CHECK_AOT,BST_UNCHECKED);
		SetWindowPos(GetParent(hDlg),HWND_NOTOPMOST,0,0,0,0,
			SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOSIZE);
	}
}

static void DispInfoExt(HWND hDlg,CShellExt *lpcs)
{
	//�N���A
	long items = ListBox_GetCount(GetDlgItem(hDlg,IDC_LIST_VALUE));
	if(items != LB_ERR)
	{
		for(int i=0; i<items; i++)
		{
			CFlacExt *oggExt = (CFlacExt *)ListBox_GetItemData(GetDlgItem(hDlg,IDC_LIST_VALUE),0);
			if(oggExt)
			{
				delete oggExt;
			}
			ListBox_DeleteString(GetDlgItem(hDlg,IDC_LIST_VALUE),0);
		}
	}

	CString strDisp;
	CStringArray strArray;
	lpcs->m_Flac.GetCommentNames(strArray);
	items = 0;
	for(int i=0; i<strArray.GetSize(); i++)
	{
		CString strName = strArray.GetAt(i);
		CString strValue;
		CString _strValue;
		int j = 0;
		while(1)
		{
			if(!lpcs->m_Flac.GetComment(strName,j++,strValue))
			{
				break;
			}

			//�W�����͏��O
			if((j == 1) &&
				(
				!strName.Compare(_T("TITLE")) ||
				!strName.Compare(_T("TRACKNUMBER")) ||
				!strName.Compare(_T("ARTIST")) ||
				!strName.Compare(_T("ALBUM")) ||
				!strName.Compare(_T("ALBUMARTIST")) ||
				!strName.Compare(_T("DISCNUMBER")) ||
				!strName.Compare(_T("DATE")) ||
				!strName.Compare(_T("GENRE")) ||
				!strName.Compare(_T("COMMENT")))
				)
			{
				continue;
			}
//			TRACE(_T("OGG %s %s\n"),strName,strValue);
			CFlacExt *oggExt = new CFlacExt(strName,strValue);
			ListBox_AddString(GetDlgItem(hDlg,IDC_LIST_VALUE),oggExt->Get1LineDisp());
			ListBox_SetItemData(GetDlgItem(hDlg,IDC_LIST_VALUE),items,oggExt);
			items++;
		}
	}
}

BOOL CALLBACK CShellExt::PageDlgProc_ogg(HWND hDlg,UINT uMessage,WPARAM wParam,LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LPCSHELLEXT	lpcs = (CShellExt *)GetWindowLongPtr(hDlg,DWLP_USER);

	switch(uMessage){
	case WM_INITDIALOG:
		{
			lpcs = (LPCSHELLEXT )((LPPROPSHEETPAGE )lParam)->lParam;
			lpcs->m_hwndPage = hDlg;
			SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)lpcs);
			lpcs->m_bApply = FALSE;

			//Ver���
			SetDlgItemText(hDlg,IDC_STATIC_VER_INFO,SOFT_NAME);
			//�^�C�g��
			SetDlgItemText(hDlg,IDC_EDIT_FILENAME,getFileName(lpcs->m_strSelectFile));
			//�A�C�R����\��
			SHFILEINFO sfi;
			if(SHGetFileInfo(lpcs->m_strSelectFile,0,&sfi,sizeof(sfi),SHGFI_ICON))
			{
				Static_SetImage_Icon(GetDlgItem(hDlg,IDC_ICON1),sfi.hIcon);
			}

			//�R���{�{�b�N�X�̏�����
			ComboBox_AddString(GetDlgItem(hDlg,IDC_EDIT_GNR), _T(""));
			for(int i=0; i<256; i++)
			{
				if(lpcs->m_Id3tagv1.GenreNum2String((unsigned char)i).GetLength())
					ComboBox_AddString(GetDlgItem(hDlg,IDC_EDIT_GNR),
							lpcs->m_Id3tagv1.GenreNum2String((unsigned char)i));
			}
			//�I�[�i�[�h���[�{�^���̏�����
/*			RECT rect;
			SetRect(&rect,145,208,145,75);//�{�^���ʒu�̊
			MapDialogRect(hDlg,&rect);
			SetWindowPos(GetDlgItem(hDlg,IDC_BUTTON_REW),NULL,rect.left+25*0,rect.top,23,23,SWP_NOZORDER | SWP_SHOWWINDOW);
			SetWindowPos(GetDlgItem(hDlg,IDC_BUTTON_PLAY),NULL,rect.left+25*1,rect.top,23,23,SWP_NOZORDER | SWP_SHOWWINDOW);
			SetWindowPos(GetDlgItem(hDlg,IDC_BUTTON_PAUSE),NULL,rect.left+25*2,rect.top,23,23,SWP_NOZORDER | SWP_SHOWWINDOW);
			SetWindowPos(GetDlgItem(hDlg,IDC_BUTTON_STOP),NULL,rect.left+25*3,rect.top,23,23,SWP_NOZORDER | SWP_SHOWWINDOW);
			SetWindowPos(GetDlgItem(hDlg,IDC_BUTTON_FFW),NULL,rect.left+25*4,rect.top,23,23,SWP_NOZORDER | SWP_SHOWWINDOW);
*/			
			//����\��
			DispInfo(hDlg,lpcs);
			DispInfoExt(hDlg,lpcs);
			
			return FALSE;
		}
		break;

	case WM_TIMER:
		switch(wParam){
		case REW_TIMER:
			SendMessage(hDlg,WM_COMMAND,
				MAKEWPARAM((UINT )IDC_BUTTON_REW,(UINT )BN_CLICKED),
				0);
			break;
		case FFW_TIMER:
			SendMessage(hDlg,WM_COMMAND,
				MAKEWPARAM((UINT )IDC_BUTTON_FFW,(UINT )BN_CLICKED),
				0);
			break;
		}
		break;
	// �I�[�i�[�`��R���g���[��
	case WM_DRAWITEM:
		DrawControl(hDlg,(LPDRAWITEMSTRUCT )lParam);
		break;
	case WM_COMMAND:
	switch(LOWORD(wParam)){
		case IDC_BUTTON_ADD_VALUE:
			//�l�ǉ�
			{
				CDlg_ogg_exttag dlg;
				if(dlg.DoModal() == IDOK)
				{
					CFlacExt *oggExt = new CFlacExt(dlg.m_strName,dlg.m_strValue);
					long index = ListBox_AddString(GetDlgItem(hDlg,IDC_LIST_VALUE),oggExt->Get1LineDisp());
					if(index == LB_ERR)
					{
						delete oggExt;
					}
					else
					{
						ListBox_SetItemData(GetDlgItem(hDlg,IDC_LIST_VALUE),index,oggExt);
					}
				
					PropSheet_Changed(GetParent(hDlg),hDlg);
					lpcs->m_bApply = TRUE;
				}
			}
			break;
		case IDC_BUTTON_DEL_VALUE:
			//�l�폜
			{
				long item = ListBox_GetCurSel(GetDlgItem(hDlg,IDC_LIST_VALUE));
				if(item == LB_ERR)
					break;
				
				CFlacExt *oggExt = (CFlacExt *)ListBox_GetItemData(GetDlgItem(hDlg,IDC_LIST_VALUE),item);
				if(oggExt)
				{
					delete oggExt;
				}
				ListBox_DeleteString(GetDlgItem(hDlg,IDC_LIST_VALUE),item);
				
				PropSheet_Changed(GetParent(hDlg),hDlg);
				lpcs->m_bApply = TRUE;
			}
			break;
		case IDC_LIST_VALUE:
			if(HIWORD(wParam) == LBN_DBLCLK)
			{
				//�_�u���N���b�N - �ҏW
				long item = ListBox_GetCurSel(GetDlgItem(hDlg,IDC_LIST_VALUE));
				if(item == LB_ERR)
					break;
				
				CFlacExt *oggExt = (CFlacExt *)ListBox_GetItemData(GetDlgItem(hDlg,IDC_LIST_VALUE),item);
				if(oggExt == NULL)
					break;
				
				CDlg_ogg_exttag dlg;

				dlg.m_strName = oggExt->GetName();
				dlg.m_strValue = oggExt->GetValue();
				if(dlg.DoModal() == IDOK)
				{
					oggExt->SetName(dlg.m_strName);
					oggExt->SetValue(dlg.m_strValue);
					ListBox_DeleteString(GetDlgItem(hDlg,IDC_LIST_VALUE),item);
					ListBox_InsertString(GetDlgItem(hDlg,IDC_LIST_VALUE),item,oggExt->Get1LineDisp());
					ListBox_SetItemData(GetDlgItem(hDlg,IDC_LIST_VALUE),item,oggExt);
					
					PropSheet_Changed(GetParent(hDlg),hDlg);
					lpcs->m_bApply = TRUE;
				}
			}
			break;
		case IDC_EDIT_SBJ:
		case IDC_EDIT_TRK:
		case IDC_EDIT_ART:
		case IDC_EDIT_PRD:
		case IDC_EDIT_AART:
		case IDC_EDIT_DISC:
		case IDC_EDIT_CRD:
		case IDC_EDIT_CMT:
			if((HIWORD(wParam) == EN_CHANGE) &&
				(IsWindowEnabled((HWND )lParam)) )
			{
				PropSheet_Changed(GetParent(hDlg),hDlg);
				lpcs->m_bApply = TRUE;
			}
			break;
		case IDC_EDIT_GNR:
			if( ((HIWORD(wParam) == CBN_SELENDOK) || (HIWORD(wParam) == CBN_EDITCHANGE)) &&
				(IsWindowEnabled((HWND )lParam)) )
			{
				PropSheet_Changed(GetParent(hDlg),hDlg);
				lpcs->m_bApply = TRUE;
			}
			break;
		case IDC_BUTTON_PLAY:
			{
				PlayWinamp(hDlg,lpcs->m_strSelectFile);
				break;
			}
		case IDC_BUTTON_PAUSE:
			{
				PauseWinamp();
				break;
			}
		case IDC_BUTTON_STOP:
			{
				StopWinamp();
				break;
			}
		case IDC_BUTTON_REW:
			{
				Rew5Winamp();
				break;
			}
		case IDC_BUTTON_FFW:
			{
				Ffw5Winamp();
				break;
			}
		case IDC_CHECK_AOT:
			if(IsDlgButtonChecked(hDlg,IDC_CHECK_AOT) == BST_CHECKED)
			{
				lpcs->m_bPropAOT = TRUE;
				SetWindowPos(GetParent(hDlg),HWND_TOPMOST,0,0,0,0,
					SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOSIZE);
			}
			else
			{
				lpcs->m_bPropAOT = FALSE;
				SetWindowPos(GetParent(hDlg),HWND_NOTOPMOST,0,0,0,0,
					SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOSIZE);
			}
			regSetDword(HKEY_CURRENT_USER,MP3INFP_REG_ENTRY,_T("PropAOT"),(DWORD )lpcs->m_bPropAOT);
			break;
		case IDC_SETUP:
			OpenConfigPage(hDlg,8);
			break;
		case IDC_HELPVIEW:
			lpcs->OpenHtmlHelp(hDlg,_T("extension.htm"));
			break;
		DLG_CLIPBOARD_MACRO(lpcs->m_strSelectFile);
		}
		break;
	case WM_DESTROY:
		{
			//��n��
			long items = ListBox_GetCount(GetDlgItem(hDlg,IDC_LIST_VALUE));
			if(items != LB_ERR)
			{
				for(int i=0; i<items; i++)
				{
					CFlacExt *oggExt = (CFlacExt *)ListBox_GetItemData(GetDlgItem(hDlg,IDC_LIST_VALUE),i);
					if(oggExt)
					{
						delete oggExt;
					}
				}
			}
		}
		return TRUE;
	// �R���e�L�X�g���j���[
	case WM_CONTEXTMENU:
		DlgContextMenu(hDlg,lParam,lpcs->m_Flac.IsEnable());
		break;
	//�󋵈ˑ��w���v
	case WM_HELP:
		OpenAboutDlg(hDlg);
		break;

	case WM_NOTIFY:
		switch(((NMHDR FAR *)lParam)->code){
//		case PSN_SETACTIVE:
//			break;
		case PSN_APPLY:
			//�ۑ�
			if(lpcs->m_bApply)
			{
				TRACE(_T("WM_NOTIFY(PSN_APPLY) - �ۑ�\n"));
				//�t�@�C�����������݉\�����ׂ�
				if(GetFileAttributes(lpcs->m_strSelectFile) & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY))
				{
					//�u���̃t�@�C���́u�ǂݍ��ݐ�p�v�ł��v
					AfxMessageBox(IDS_PAGE_THIS_READONLY,MB_ICONINFORMATION);
					//�K�p�{�^���͈��������L��
					SetWindowLongPtr(hDlg,DWLP_MSGRESULT,PSNRET_INVALID);
					break;
				}
				lpcs->m_bApply = FALSE;

				CString strTmp;
				CWnd wnd;
				//�������񃊃Z�b�g
				lpcs->m_Flac.Release();

				wnd.Attach(hDlg);

				wnd.GetDlgItemText(IDC_EDIT_SBJ,strTmp);
				lpcs->m_Flac.AddComment(_T("TITLE"),strTmp);

				wnd.GetDlgItemText(IDC_EDIT_TRK,strTmp);
				lpcs->m_Flac.AddComment(_T("TRACKNUMBER"),strTmp);

				wnd.GetDlgItemText(IDC_EDIT_ART,strTmp);
				lpcs->m_Flac.AddComment(_T("ARTIST"),strTmp);

				wnd.GetDlgItemText(IDC_EDIT_PRD,strTmp);
				lpcs->m_Flac.AddComment(_T("ALBUM"),strTmp);

				wnd.GetDlgItemText(IDC_EDIT_AART,strTmp);
				lpcs->m_Flac.AddComment(_T("ALBUMARTIST"),strTmp);

				wnd.GetDlgItemText(IDC_EDIT_DISC,strTmp);
				lpcs->m_Flac.AddComment(_T("DISCNUMBER"),strTmp);

				wnd.GetDlgItemText(IDC_EDIT_CRD,strTmp);
				lpcs->m_Flac.AddComment(_T("DATE"),strTmp);

				wnd.GetDlgItemText(IDC_EDIT_GNR,strTmp);
				lpcs->m_Flac.AddComment(_T("GENRE"),strTmp);

				wnd.GetDlgItemText(IDC_EDIT_CMT,strTmp);
				lpcs->m_Flac.AddComment(_T("COMMENT"),strTmp);

				wnd.Detach();

				//���̑�����ۑ�
				long items = ListBox_GetCount(GetDlgItem(hDlg,IDC_LIST_VALUE));
				if(items != LB_ERR)
				{
					for(int i=0; i<items; i++)
					{
						CFlacExt *oggExt = (CFlacExt *)ListBox_GetItemData(GetDlgItem(hDlg,IDC_LIST_VALUE),i);
						if(oggExt)
						{
							lpcs->m_Flac.AddComment(oggExt->GetName(),oggExt->GetValue());
						}
					}
				}

				//�^�C���X�^���v��ۑ�
				lpcs->PushTimeStamp(lpcs->m_strSelectFile);

				DWORD dwRet = lpcs->m_Flac.Save(lpcs->m_strSelectFile);
				if(dwRet != ERROR_SUCCESS)
				{
					lpcs->m_bApply = TRUE;
					if(dwRet == -1)
						//�u�t�@�C���𐳂����X�V�ł��܂���ł����B�v
						AfxMessageBox(IDS_PAGE_BROKEN,MB_ICONINFORMATION);
					else
						//�V�X�e���G���[��\��
						errMessageBox(hDlg,dwRet);
					//�K�p�{�^���͈��������L��
					SetWindowLongPtr(hDlg,DWLP_MSGRESULT,PSNRET_INVALID);
					break;
				}

				//�^�C���X�^���v�𕜌�
				if(lpcs->m_bSaveTimeStamp)
				{
					lpcs->PopTimeStamp(lpcs->m_strSelectFile);
				}

				//����\��
				lpcs->m_Flac.Load(lpcs->m_strSelectFile);
				DispInfo(hDlg,lpcs);
				DispInfoExt(hDlg,lpcs);

				SetWindowLongPtr(hDlg,DWLP_MSGRESULT,PSNRET_NOERROR);

				//�V�F���ɕύX��ʒm
				SHChangeNotify(SHCNE_UPDATEITEM,SHCNF_PATH,lpcs->m_strSelectFile,NULL);
			}
			break;
		default:
			break;
		}
		break;

	default:
		return FALSE;
	
	}

	return TRUE;
}