#pragma once

class listControl {
public:
	listControl();
	listControl(CDC * dc);
	~listControl();

	// ����Ʈ ��Ʈ�� �׸���
	void draw();

	// �� �߰�
	void insertColumn(const char* colName, int width);

	// �� �߰�
	void insertItem();

	// Ŭ���̾�Ʈ�� ���� ���� ���� ��������
	void GetClientRect(CRect* rect);

private:
	int xPos, yPos;		// x, y ��ġ
	int width, height;	// ���� ���� ����
	CDC * c_dc;		// �׸��� ���� dc
};