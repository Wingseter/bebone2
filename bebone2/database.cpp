#include "pch.h"
#include "database.h"

dataBase::dataBase()
{
	// �ʱ�ȭ
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;

	// ODBC �ڵ� ���� �� �ʱ�ȭ
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
	// ���� �õ�
	switch (SQLDriverConnect(sqlConnHandle,
		NULL,
		(SQLWCHAR*)connectSQL,
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {
	case SQL_SUCCESS: // ����
	case SQL_SUCCESS_WITH_INFO: 
		checkError = TRUE;
		break;
	case SQL_INVALID_HANDLE: // ����
	case SQL_ERROR: 
		checkError = FALSE;
		exitDB();
		break;
	default: // ����
		checkError = FALSE;
		exitDB();
		break;
	}
	// ���� ���ῡ ������ �ִٸ�
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		// ����
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

bool dataBase::execQuery(TCHAR* query, INT option)
{
	// Query ���� ���ν��� ���
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)query, SQL_NTS)) {
		// ���� �߻��� ����
		return false;
	}

	if (option == 1) {
		// ���� ���� ��
		SQLINTEGER iId, iFirst, iSecond, iThird;
		SQLINTEGER id;
		SQLCHAR firstVal[50], secondVal[50], thirdVal[50];

		SQLBindCol(sqlStmtHandle, 1, SQL_INTEGER, &id, sizeof(id), &iId);
		SQLBindCol(sqlStmtHandle, 2, SQL_CHAR, &firstVal, sizeof(firstVal), &iFirst);
		SQLBindCol(sqlStmtHandle, 3, SQL_CHAR, &secondVal, sizeof(secondVal), &iSecond);
		SQLBindCol(sqlStmtHandle, 4, SQL_CHAR, &thirdVal, sizeof(thirdVal), &iThird);

		INT counter = 1;
		while (SQLFetch(sqlStmtHandle) != SQL_NO_DATA) {
			wsprintf(result[counter], TEXT("%ld %s %s %s"), id, firstVal, secondVal, thirdVal);
			counter++;
		}
		wsprintf(result[0], TEXT("%d"), counter-1);
		return true;
	}
}

TCHAR(*dataBase::getResult(void))[200]
{
	return result;
}
