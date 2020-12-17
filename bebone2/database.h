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
	// 변수 정의
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
	bool checkError; // 에러 체크

	// 함수 정의
	bool connectDB();
	void exitDB();
	


};