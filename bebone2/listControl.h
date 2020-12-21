#pragma once

class listControl {
public:
	listControl();
	listControl(CDC * dc);
	~listControl();

	// 리스트 컨트롤 그리기
	void draw();

	// 열 추가
	void insertColumn(const char* colName, int width);

	// 행 추가
	void insertItem();

	// 클라이언트의 가로 세로 길이 가져오기
	void GetClientRect(CRect* rect);

private:
	int xPos, yPos;		// x, y 위치
	int width, height;	// 가로 세로 길이
	CDC * c_dc;		// 그리기 위한 dc
};