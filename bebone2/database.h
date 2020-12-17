#pragma once
#include "static.h"
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>

#pragma comment(lib, "odbc32.lib")

#define SQL_RESULT_LEN 240 // 
#define SQL_RETURN_CODE_LEN 1024// length of the query result

class dataBase {
public:
	dataBase();
	~dataBase();
private:
	// ���� ����
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
	bool checkError; // ���� üũ

	// �Լ� ����
	bool connectDB();
	void exitDB();
	


};