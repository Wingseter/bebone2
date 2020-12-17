#include "pch.h"
#include "database.h"

dataBase::dataBase()
{
	// 초기화
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;

	// ODBC 핸들 설정 및 초기화
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
		exitDB();
	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		exitDB();
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
		exitDB();

	connectDB();
}

dataBase::~dataBase()
{
	exitDB();
}

bool dataBase::connectDB()
{
	TCHAR connectSQL[150];

	wsprintf(connectSQL, TEXT("DRIVER={SQL Server};SERVER=%s, 1433;DATABASE=%s;UID=%s;PWD=%s;"), SQL_SERVER, SQL_DB, SQL_ID, SQL_PW);
	// 연결 시도
	switch (SQLDriverConnect(sqlConnHandle,
		NULL,
		(SQLWCHAR*)connectSQL,
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {
	case SQL_SUCCESS: // 성공
	case SQL_SUCCESS_WITH_INFO: 
		checkError = TRUE;
		break;
	case SQL_INVALID_HANDLE: // 실패
	case SQL_ERROR: 
		checkError = FALSE;
		exitDB();
		break;
	default: // 실패
		checkError = FALSE;
		exitDB();
		break;
	}
	// 만약 연결에 문제가 있다면
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		// 종료
		exitDB();
    return checkError;
}

void dataBase::exitDB()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;

    return;
}
