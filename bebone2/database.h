#pragma once
#include "static.h"
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <wchar.h>

#pragma comment(lib, "odbc32.lib")

#define SQL_RESULT_LEN 240 // ��� ��ȯ ����
#define SQL_COLUMN_LEN 50 // ������ Column ����
#define MAX_COLUMN 10 // �ִ� Column ����
#define SQL_RETURN_CODE_LEN 1024 // Query ��� ����

class dataBase {
public:
	dataBase();
	~dataBase();
	// Query ���� 
	// option 0 = ����, option 1 = ��ȸ
	bool execQuery(TCHAR* query, INT option);
	// ���� ���
	bool next();
	// ��� ��������
	char * getResult();

private:
	// SQL Query�� ���� ���� ����
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLCHAR retconstring[SQL_RETURN_CODE_LEN];
	SQLRETURN retval;

	char result[SQL_RESULT_LEN]; // ��� ���� ����
	bool checkError; // ���� üũ

	// ��� ��ȯ�� ����
	SQLINTEGER ids[MAX_COLUMN];
	SQLCHAR values[MAX_COLUMN][SQL_COLUMN_LEN];

	// �Լ� ����
	bool connectDB();
	void exitDB();
	

};