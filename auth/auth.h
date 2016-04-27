
#include "auth.h"
#include "inc/common.h"

MYSQL *connection;
MYSQL_RES *result;
MYSQL_ROW row;

void connectSQL(MYSQL **connect);
INT8 authentication(const INT8 userName,const INT8 *password);

