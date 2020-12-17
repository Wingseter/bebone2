#pragma once
#include "static.h"
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <wchar.h>

#pragma comment(lib, "odbc32.lib")

#define SQL_RESULT_LEN 240 // 
#define SQL_RETURN_CODE_LEN 1024// length of the query result

class dataBase {
public:
	dataBase();
	~dataBase();
	// option 0 = ����, option 1 = ��ȸ
	bool execQuery(TCHAR* query, INT option);
	TCHAR (*getResult(void))[200];

private:
	// ���� ����
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
	TCHAR result[200][200];
	bool checkError; // ���� üũ

	// �Լ� ����
	bool connectDB();
	void exitDB();
	

};