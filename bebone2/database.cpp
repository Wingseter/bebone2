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

	sprintf_s(connectSQL, 120, "DRIVER={SQL Server};SERVER=%s, 1433;DATABASE=%s;UID=%s;PWD=%s;", SQL_SERVER, SQL_DB, SQL_ID, SQL_PW);
	// ���� �õ�
	switch (SQLDriverConnect(sqlConnHandle,
		NULL,
		(SQLCHAR*)connectSQL,
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
		break;
	default: // ����
		checkError = FALSE;
		break;
	}
	// ���� ���ῡ ������ �ִٸ�
	// ���� �Ѵ�.

	if (checkError) {
		MessageBox(NULL, "DB���� ����!", "Regular Warning", 0);
	}
	else {
		MessageBox(NULL, "���� �߻�!", "Regular Warning", 0);
		exitDB();
	}
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
	// ��� �޸� �ʱ�ȭ
	memset(values, 0, sizeof(values));
	memset(ids, -1, sizeof(ids));

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		checkError = FALSE;

	// Query ���� ���ν��� ���
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLCHAR*)query, SQL_NTS)) {
		// ���� �߻��� ����	
		return false;
	}
	if (option == 1) {
		// ���� ���� ��
		for (int i = 0; i < MAX_COLUMN; i++) {
			SQLBindCol(sqlStmtHandle, i + 1, SQL_CHAR, &values[i], sizeof(values[i]), &ids[i]);
		}

		return true;
	}
}

bool dataBase::next()
{
	if (SQLFetch(sqlStmtHandle) != SQL_NO_DATA) {
		clearResult();
		for (int i = 0; i < MAX_COLUMN; i++) {
			if (ids[i] < 0) {
				break;
			}
			sprintf_s(result, SQL_RESULT_LEN, "%s|%s",  result, values[i]);
		}
	}
	else {
		return false;
	}
}

char* dataBase::getResult()
{
	return result;
}

void dataBase::clearResult()
{
	memset(result, 0, sizeof(result));
}
