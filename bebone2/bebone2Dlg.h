﻿
// bebone2Dlg.h: 헤더 파일
//

#pragma once
#include "database.h"

// Cbebone2Dlg 대화 상자
class Cbebone2Dlg : public CDialogEx
{
// 생성입니다.
public:
	Cbebone2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BEBONE2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 목록 전체 새로고침
	void refresh();

	// 목록 비우기
	void clear();

	// 목록 업데이트
	void update();

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	dataBase* db;
	char *dbresult;
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedRefresh();
	// 검색어 입력
	CEdit input_search;
	// 이름 입력
	CEdit input_name;
	// 주소 입력
	CEdit input_addr;
	// 연락처 입력
	CEdit input_phone;
	// id로 검색
	CButton radio_id;
	// 이름으로 검색
	CButton radio_name;
	afx_msg void OnDestroy();
	// 방문자 목록
	CListCtrl list_visitor;
	// 날짜로 검색
	CButton radio_date;
	// 날짜 입력
	CDateTimeCtrl input_date;
};
