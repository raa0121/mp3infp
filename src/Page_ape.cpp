#include "StdAfx.h"
#include "mp3infp.h"

static const int ids[] =
{
	-1,
	-1,
	CLP_NAM,
	CLP_TRACK,
	CLP_ART,
	CLP_PRD,
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
	IDC_STATIC_ART,
	IDC_STATIC_PRD,
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
	IDC_EDIT_ART,
	IDC_EDIT_PRD,
	IDC_EDIT_CRD,
	IDC_EDIT_GNR,
	IDC_EDIT_CMT,
	0
};

UINT CALLBACK CShellExt::PageCallback_ape(HWND hWnd,UINT uMessage,LPPROPSHEETPAGE ppsp)
{
	LPCSHELLEXT	lpcs = (CShellExt *)ppsp->lParam;
	switch(uMessage){
	case PSPCB_CREATE:	//プロパティページが作成されつつある
		return TRUE;
	case PSPCB_RELEASE:	//プロパティページが破壊されつつある
		if(lpcs) 
		{
			lpcs->m_hwndPage = NULL;
			lpcs->Release();
		}
		return TRUE;
	}

	return TRUE;
}

static void EnableEdit(HWND hDlg,CShellExt *lpcs,BOOL bEnable)
{
	SetWindowText(GetDlgItem(hDlg,IDC_EDIT_SBJ),_T(""));
	EnableWindow(GetDlgItem(hDlg,IDC_EDIT_SBJ),bEnable);
	EnableWindow(GetDlgItem(hDlg,IDC_STATIC_NAM),bEnable);
	SetWindowText(GetDlgItem(hDlg,IDC_EDIT_TRK),_T(""));
	EnableWindow(GetDlgItem(hDlg,IDC_EDIT_TRK),bEnable);
	EnableWindow(GetDlgItem(hDlg,IDC_STATIC_TRK),bEnable);
	SetWindowText(GetDlgItem(hDlg,IDC_EDIT_ART),_T(""));
	EnableWindow(GetDlgItem(hDlg,IDC_EDIT_ART),bEnable);
	EnableWindow(GetDlgItem(hDlg,IDC_STATIC_ART),bEnable);
	SetWindowText(GetDlgItem(hDlg,IDC_EDIT_PRD),_T(""));
	EnableWindow(GetDlgItem(hDlg,IDC_EDIT_PRD),bEnable);
	EnableWindow(GetDlgItem(hDlg,IDC_STATIC_PRD),bEnable);
	SetWindowText(GetDlgItem(hDlg,IDC_EDIT_CRD),_T(""));
	EnableWindow(GetDlgItem(hDlg,IDC_EDIT_CRD),bEnable);
	EnableWindow(GetDlgItem(hDlg,IDC_STATIC_CRD),bEnable);
	SetWindowText(GetDlgItem(hDlg,IDC_EDIT_GNR),_T(""));
	EnableWindow(GetDlgItem(hDlg,IDC_EDIT_GNR),bEnable);
	EnableWindow(GetDlgItem(hDlg,IDC_STATIC_GNR),bEnable);
	SetWindowText(GetDlgItem(hDlg,IDC_EDIT_CMT),_T(""));
	EnableWindow(GetDlgItem(hDlg,IDC_EDIT_CMT),bEnable);
	EnableWindow(GetDlgItem(hDlg,IDC_STATIC_CMT),bEnable);
	if(bEnable)
	{
		EnableWindow(GetDlgItem(hDlg,IDC_BUTTON_DEL_TAG),TRUE);	//Make Id3Tag
		EnableWindow(GetDlgItem(hDlg,IDC_BUTTON_MAKE_TAG),FALSE);	//Make Id3Tag
	}
	else
	{
		EnableWindow(GetDlgItem(hDlg,IDC_BUTTON_DEL_TAG),FALSE);	//Del Id3Tag
		EnableWindow(GetDlgItem(hDlg,IDC_BUTTON_MAKE_TAG),TRUE);	//Make Id3Tag
	}
}

static void DispInfo(HWND hDlg,CShellExt *lpcs)
{
	SetDlgItemText(hDlg,IDC_STATIC_FORMAT,lpcs->m_Monkeys.GetAudioFormatString());
	SetDlgItemText(hDlg,IDC_STATIC_TIME,lpcs->m_Monkeys.GetTimeString());
	
	//その他の情報
	CString strFormat;
	strFormat = lpcs->m_Monkeys.GetFormatInfoString();
	if(lpcs->m_Ape.IsEnable())
	{
		strFormat.Format(_T("%sTag: APE Tag v%.0f"),lpcs->m_Monkeys.GetFormatInfoString(),double(lpcs->m_Ape.GetApeVersion())/1000);
	}
	else
	{
		strFormat.Format(_T("%sTag: n/a"),lpcs->m_Monkeys.GetFormatInfoString());
	}
	SetDlgItemText(hDlg,IDC_STATIC_FORMAT_INFO,strFormat);
	SetDlgItemText(hDlg,IDC_STATIC_AUDIO_INFO,lpcs->m_Monkeys.GetAudioInfoString());
	SetDlgItemText(hDlg,IDC_STATIC_SIZE_INFO,lpcs->m_Monkeys.GetSizeInfoString());
	
	if(lpcs->m_Ape.IsEnable())
	{
		EnableEdit(hDlg,lpcs,TRUE);

		CString tmp;
		lpcs->m_Ape.GetComment(CTag_Ape::APE_TAG_FIELD_TITLE,tmp);
		SetDlgItemText(hDlg,IDC_EDIT_SBJ,tmp);

		lpcs->m_Ape.GetComment(CTag_Ape::APE_TAG_FIELD_TRACK,tmp);
		SetDlgItemText(hDlg,IDC_EDIT_TRK,tmp);
		
		lpcs->m_Ape.GetComment(CTag_Ape::APE_TAG_FIELD_ARTIST,tmp);
		SetDlgItemText(hDlg,IDC_EDIT_ART,tmp);
		
		lpcs->m_Ape.GetComment(CTag_Ape::APE_TAG_FIELD_ALBUM,tmp);
		SetDlgItemText(hDlg,IDC_EDIT_PRD,tmp);
		
		lpcs->m_Ape.GetComment(CTag_Ape::APE_TAG_FIELD_YEAR,tmp);
		SetDlgItemText(hDlg,IDC_EDIT_CRD,tmp);
		
		lpcs->m_Ape.GetComment(CTag_Ape::APE_TAG_FIELD_GENRE,tmp);
		SetDlgItemText(hDlg,IDC_EDIT_GNR,tmp);
		
		lpcs->m_Ape.GetComment(CTag_Ape::APE_TAG_FIELD_COMMENT,tmp);
		SetDlgItemText(hDlg,IDC_EDIT_CMT,tmp);

		lpcs->m_bApply = FALSE;
	}
	else
	{
		EnableEdit(hDlg,lpcs,FALSE);
	}
	
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

BOOL CALLBACK CShellExt::PageDlgProc_ape(HWND hDlg,UINT uMessage,WPARAM wParam,LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LPCSHELLEXT	lpcs = (CShellExt *)GetWindowLongPtr(hDlg,DWLP_USER);
	CString strTmp;

	switch(uMessage){
	case WM_INITDIALOG:
		{
			lpcs = (LPCSHELLEXT )((LPPROPSHEETPAGE )lParam)->lParam;
			lpcs->m_hwndPage = hDlg;
			SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)lpcs);
			lpcs->m_bApply = FALSE;

			//Ver情報
			SetDlgItemText(hDlg,IDC_STATIC_VER_INFO,SOFT_NAME);
			//タイトル
			SetDlgItemText(hDlg,IDC_EDIT_FILENAME,getFileName(lpcs->m_strSelectFile));
			//アイコンを表示
			SHFILEINFO sfi;
			if(SHGetFileInfo(lpcs->m_strSelectFile,0,&sfi,sizeof(sfi),SHGFI_ICON))
			{
				Static_SetImage_Icon(GetDlgItem(hDlg,IDC_ICON1),sfi.hIcon);
			}

			//コンボボックスの初期化
			ComboBox_AddString(GetDlgItem(hDlg,IDC_EDIT_GNR), _T(""));
			for(int i=0; i<256; i++)
			{
				if(lpcs->m_Id3tagv1.GenreNum2String((unsigned char)i).GetLength())
					ComboBox_AddString(GetDlgItem(hDlg,IDC_EDIT_GNR),
							lpcs->m_Id3tagv1.GenreNum2String((unsigned char)i));
			}
			//オーナードローボタンの初期化
/*			RECT rect;
			SetRect(&rect,145,208,145,75);//ボタン位置の基準
			MapDialogRect(hDlg,&rect);
			SetWindowPos(GetDlgItem(hDlg,IDC_BUTTON_REW),NULL,rect.left+25*0,rect.top,23,23,SWP_NOZORDER | SWP_SHOWWINDOW);
			SetWindowPos(GetDlgItem(hDlg,IDC_BUTTON_PLAY),NULL,rect.left+25*1,rect.top,23,23,SWP_NOZORDER | SWP_SHOWWINDOW);
			SetWindowPos(GetDlgItem(hDlg,IDC_BUTTON_PAUSE),NULL,rect.left+25*2,rect.top,23,23,SWP_NOZORDER | SWP_SHOWWINDOW);
			SetWindowPos(GetDlgItem(hDlg,IDC_BUTTON_STOP),NULL,rect.left+25*3,rect.top,23,23,SWP_NOZORDER | SWP_SHOWWINDOW);
			SetWindowPos(GetDlgItem(hDlg,IDC_BUTTON_FFW),NULL,rect.left+25*4,rect.top,23,23,SWP_NOZORDER | SWP_SHOWWINDOW);
*/			
			//情報を表示
			DispInfo(hDlg,lpcs);
			
			lpcs->m_bApply = FALSE;
			
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
	// オーナー描画コントロール
	case WM_DRAWITEM:
		DrawControl(hDlg,(LPDRAWITEMSTRUCT )lParam);
		break;
	case WM_COMMAND:
	switch(LOWORD(wParam)){
		case IDC_EDIT_SBJ:
		case IDC_EDIT_TRK:
		case IDC_EDIT_ART:
		case IDC_EDIT_PRD:
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
		case IDC_BUTTON_DEL_TAG:
			//「APE Tagを削除します。よろしいですか？」
			strTmp.Format(IDS_PAGE_MP3APE_DEL_APE);
			if(MessageBox(hDlg,strTmp,APP_NAME,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
			{
				//ファイルが書き込み可能か調べる
				if(GetFileAttributes(lpcs->m_strSelectFile) & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY))
				{
					//「このファイルは「読み込み専用」です」
					AfxMessageBox(IDS_PAGE_THIS_READONLY,MB_ICONINFORMATION);
					break;
				}
				//タイムスタンプを保存
				lpcs->PushTimeStamp(lpcs->m_strSelectFile);
				// APE Tagを消去
				{
					DWORD dwRet = lpcs->m_Ape.DelTag(lpcs->m_strSelectFile);
					if(dwRet == -1)
					{
						//「ファイルを正しく更新できませんでした。」
						AfxMessageBox(IDS_PAGE_BROKEN,MB_ICONINFORMATION);
						break;
					}
					else if(dwRet != ERROR_SUCCESS)
					{
						//システムエラーを表示
						errMessageBox(hDlg,dwRet);
						break;
					}
				}
				//タイムスタンプを復元
				if(lpcs->m_bSaveTimeStamp)
				{
					lpcs->PopTimeStamp(lpcs->m_strSelectFile);
				}
				//情報を表示
				lpcs->m_Ape.Load(lpcs->m_strSelectFile);
				DispInfo(hDlg,lpcs);

				lpcs->m_bApply = FALSE;
				
				//シェルに変更を通知
				SHChangeNotify(SHCNE_UPDATEITEM,SHCNF_FLUSH|SHCNF_PATH,lpcs->m_strSelectFile,NULL);
			}
			break;
		case IDC_BUTTON_MAKE_TAG:
			//「APE Tagを作成します。よろしいですか？」
			strTmp.Format(IDS_PAGE_MP3APE_MAKE_APE);
			if(MessageBox(hDlg,strTmp,APP_NAME,MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES)
			{
				//ファイルが書き込み可能か調べる
				if(GetFileAttributes(lpcs->m_strSelectFile) & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY))
				{
					//「このファイルは「読み込み専用」です」
					AfxMessageBox(IDS_PAGE_THIS_READONLY,MB_ICONINFORMATION);
					break;
				}
				//タイムスタンプを保存
				lpcs->PushTimeStamp(lpcs->m_strSelectFile);
				// APE Tagを作成
				{
					DWORD dwRet = lpcs->m_Ape.MakeTag(lpcs->m_strSelectFile);
					if(dwRet == -1)
					{
						//「ファイルを正しく更新できませんでした。」
						AfxMessageBox(IDS_PAGE_BROKEN,MB_ICONINFORMATION);
						break;
					}
					else if(dwRet != ERROR_SUCCESS)
					{
						//システムエラーを表示
						errMessageBox(hDlg,dwRet);
						break;
					}
				}
				//タイムスタンプを復元
				if(lpcs->m_bSaveTimeStamp)
				{
					lpcs->PopTimeStamp(lpcs->m_strSelectFile);
				}
				//情報を表示
				lpcs->m_Ape.Load(lpcs->m_strSelectFile);
				DispInfo(hDlg,lpcs);

				lpcs->m_bApply = FALSE;
				
				//シェルに変更を通知
				SHChangeNotify(SHCNE_UPDATEITEM,SHCNF_FLUSH|SHCNF_PATH,lpcs->m_strSelectFile,NULL);
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
			OpenConfigPage(hDlg,9);
			break;
		case IDC_HELPVIEW:
			lpcs->OpenHtmlHelp(hDlg,_T("extension.htm"));
			break;
		DLG_CLIPBOARD_MACRO(lpcs->m_strSelectFile);
		}
		break;
	// コンテキストメニュー
	case WM_CONTEXTMENU:
		DlgContextMenu(hDlg,lParam,lpcs->m_Ape.IsEnable());
		break;
	//状況依存ヘルプ
	case WM_HELP:
		OpenAboutDlg(hDlg);
		break;

	case WM_NOTIFY:
		switch(((NMHDR FAR *)lParam)->code){
//		case PSN_SETACTIVE:
//			break;
		case PSN_APPLY:
			//保存
			if(lpcs->m_bApply)
			{
				TRACE(_T("WM_NOTIFY(PSN_APPLY) - 保存\n"));
				//ファイルが書き込み可能か調べる
				if(GetFileAttributes(lpcs->m_strSelectFile) & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY))
				{
					//「このファイルは「読み込み専用」です」
					AfxMessageBox(IDS_PAGE_THIS_READONLY,MB_ICONINFORMATION);
					//適用ボタンは引き続き有効
					SetWindowLongPtr(hDlg,DWLP_MSGRESULT,PSNRET_INVALID);
					break;
				}

				CString strTmp;
				CWnd wnd;

				wnd.Attach(hDlg);

				wnd.GetDlgItemText(IDC_EDIT_SBJ,strTmp);
				lpcs->m_Ape.SetComment(CTag_Ape::APE_TAG_FIELD_TITLE,strTmp);

				wnd.GetDlgItemText(IDC_EDIT_TRK,strTmp);
				lpcs->m_Ape.SetComment(CTag_Ape::APE_TAG_FIELD_TRACK,strTmp);

				wnd.GetDlgItemText(IDC_EDIT_ART,strTmp);
				lpcs->m_Ape.SetComment(CTag_Ape::APE_TAG_FIELD_ARTIST,strTmp);

				wnd.GetDlgItemText(IDC_EDIT_PRD,strTmp);
				lpcs->m_Ape.SetComment(CTag_Ape::APE_TAG_FIELD_ALBUM,strTmp);

				wnd.GetDlgItemText(IDC_EDIT_CRD,strTmp);
				lpcs->m_Ape.SetComment(CTag_Ape::APE_TAG_FIELD_YEAR,strTmp);

				wnd.GetDlgItemText(IDC_EDIT_GNR,strTmp);
				lpcs->m_Ape.SetComment(CTag_Ape::APE_TAG_FIELD_GENRE,strTmp);

				wnd.GetDlgItemText(IDC_EDIT_CMT,strTmp);
				lpcs->m_Ape.SetComment(CTag_Ape::APE_TAG_FIELD_COMMENT,strTmp);

				wnd.Detach();

				//タイムスタンプを保存
				lpcs->PushTimeStamp(lpcs->m_strSelectFile);

				DWORD dwRet = lpcs->m_Ape.Save(lpcs->m_strSelectFile);
				if(dwRet != ERROR_SUCCESS)
				{
					lpcs->m_bApply = TRUE;
					if(dwRet == -1)
						//「ファイルを正しく更新できませんでした。」
						AfxMessageBox(IDS_PAGE_BROKEN,MB_ICONINFORMATION);
					else
						//システムエラーを表示
						errMessageBox(hDlg,dwRet);
					//適用ボタンは引き続き有効
					SetWindowLongPtr(hDlg,DWLP_MSGRESULT,PSNRET_INVALID);
					break;
				}

				//タイムスタンプを復元
				if(lpcs->m_bSaveTimeStamp)
				{
					lpcs->PopTimeStamp(lpcs->m_strSelectFile);
				}

				//情報を表示
				lpcs->m_Ape.Load(lpcs->m_strSelectFile);
				DispInfo(hDlg,lpcs);

				lpcs->m_bApply = FALSE;
				SetWindowLongPtr(hDlg,DWLP_MSGRESULT,PSNRET_NOERROR);

				//シェルに変更を通知
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
