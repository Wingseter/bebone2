
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
	DDX_Control(pDX, LIST_VISITORS, list_visitor);
	DDX_Control(pDX, RADIO_DATE, radio_date);
	DDX_Control(pDX, INPUT_DATE, input_date);
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
	// 전체 목록 지우기
	clear();

	// 전체 목록 불러오기
	db->execQuery("SELECT * FROM Visitors", 1);

	// 목록 업데이트
	update();
}

void Cbebone2Dlg::clear()
{
	// db 결과 버퍼 비우기
	db->clearResult();
	// 모든 리스트 아이템 지우기
	list_visitor.DeleteAllItems();
}

void Cbebone2Dlg::update()
{
	// 다음 column 으로 이동
	for (int i = 0; db->next(); i++) {
		// 결과 얻기
		dbresult = db->getResult();

		// 문자열 자르기
		char* context = NULL;
		char* cutPtr = strtok_s(dbresult, "|", &context);

		// 새로운 ROW 추가
		list_visitor.InsertItem(i, cutPtr);
		// 첫번째 column 패스
		cutPtr = strtok_s(NULL, "|", &context);

		// ROW에 아이템 추가
		for (int j = 0; cutPtr != NULL; j++) {
			list_visitor.SetItemText(i, j + 1, cutPtr);
			cutPtr = strtok_s(NULL, "|", &context);
		}
	}
}

BOOL Cbebone2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	SetWindowText("Covid-19 visitor List");

	// DB 초기화
	db = new dataBase();

	// 목록 초기화
	CRect listRect;
	list_visitor.GetClientRect(&listRect);
	list_visitor.InsertColumn(0, "id", LVCFMT_LEFT, 100);
	list_visitor.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	list_visitor.InsertColumn(2, "Location", LVCFMT_LEFT, 100);
	list_visitor.InsertColumn(3, "Phone", LVCFMT_LEFT, 100);
	list_visitor.InsertColumn(4, "Time", LVCFMT_LEFT, listRect.Width() - 400);

	// 전체 목록 불러오기
	refresh();

	// 기본으로 id 검색 체크
	radio_id.SetCheck(TRUE);

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

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서 이 함수를 호출합니다.
HCURSOR Cbebone2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 검색 기능 함수
void Cbebone2Dlg::OnBnClickedSearch()
{
	// 입력한 문자열 가져오기
	CString input;

	// Query 문자열
	char query[100];


	clear();
	// id로 검색
	if (radio_id.GetCheck()) {
		// 텍스트 상자로 부터 정보 가져오기
		input_search.GetWindowTextA(input);
		sprintf_s(query, sizeof(query), "EXEC dbo.find_visitor_by_id '%s'", LPSTR(LPCTSTR(input)));
	}
	// 이름으로 검색
	else if (radio_name.GetCheck()) {
		// 텍스트 상자로 부터 정보 가져오기
		input_search.GetWindowTextA(input);		
		sprintf_s(query, sizeof(query), "EXEC dbo.find_visitor_by_name '%s'", LPSTR(LPCTSTR(input)));
	}
	// 날짜로 검색
	else if (radio_date.GetCheck()) {
		// 날짜 입력 상자로 부터 정보 가져오기
		input_date.GetWindowTextA(input);
		sprintf_s(query, sizeof(query), "EXEC dbo.find_visitor_by_date '%s'", LPSTR(LPCTSTR(input)));
	}
	
	db->execQuery(query, 1);
	update();

	// 입력된 텍스트 지우기
	input_search.Clear();
}


void Cbebone2Dlg::OnBnClickedAdd()
{
	// 입력한 문자열 가져오기
	CString name, location, phone;

	// Query 문자열
	char query[100];

	// 텍스트 상자로 부터 정보 가져오기
	input_name.GetWindowTextA(name);
	input_addr.GetWindowTextA(location);
	input_phone.GetWindowTextA(phone);

	// 문자열 조합
	sprintf_s(query, sizeof(query), "EXEC dbo.input_new_user '%s','%s','%s'", LPSTR(LPCTSTR(name)), LPSTR(LPCTSTR(location)), LPSTR(LPCTSTR(phone)));

	// 사용자 입력 실행
	db->execQuery(query, 0);

	// 전체 목록 불러오기
	refresh();

	// 입력된 텍스트 지우기
	input_name.Clear();
	input_addr.Clear();
	input_phone.Clear();
}

// 새로고침 버튼 클릭시 호출
void Cbebone2Dlg::OnBnClickedRefresh()
{
	// 전체 목록 불러오기
	refresh();
}

// 종료시 호출
void Cbebone2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	// DB 종료
	delete db;
}


