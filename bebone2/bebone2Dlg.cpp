
// bebone2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "bebone2.h"
#include "bebone2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cbebone2Dlg 대화 상자



Cbebone2Dlg::Cbebone2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BEBONE2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cbebone2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, EDIT_SEARCH, input_search);
	DDX_Control(pDX, EDIT_NAME, input_name);
	DDX_Control(pDX, EDIT_ADDR, input_addr);
	DDX_Control(pDX, EDIT_PHONE, input_phone);
	DDX_Control(pDX, RADIO_ID, radio_id);
	DDX_Control(pDX, RADIO_NAME, radio_name);
	DDX_Control(pDX, LIST_VISITOR, list_visit);
}

BEGIN_MESSAGE_MAP(Cbebone2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(BUTTON_SEARCH, &Cbebone2Dlg::OnBnClickedSearch)
	ON_BN_CLICKED(BUTTON_ADD, &Cbebone2Dlg::OnBnClickedAdd)
	ON_BN_CLICKED(BUTTON_REFRESH, &Cbebone2Dlg::OnBnClickedRefresh)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// Cbebone2Dlg 메시지 처리기

void Cbebone2Dlg::refresh()
{
	// 전체 목록 새로 고침
	db->execQuery("SELECT * FROM Visitors", 1);

	// 다음 column 으로 이동
	while (db->next()) {
		// 결과 얻기
		dbresult = db->getResult();
		list_visit.InsertString(-1, dbresult);
	}
}

BOOL Cbebone2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	db = new dataBase();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void Cbebone2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR Cbebone2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cbebone2Dlg::OnBnClickedSearch()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Cbebone2Dlg::OnBnClickedAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void Cbebone2Dlg::OnBnClickedRefresh()
{
	refresh();
}


void Cbebone2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	delete db;
}
