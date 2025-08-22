#include <iostream>
#include "sqlite3.h"
using namespace std;

int callback(void* param, int argc, char** argv, char** col){
  cout << argv[0] << endl;
  cout << argv[1] << endl;
  return 0;
}

int main()
{
	sqlite3 *pepardo;

	if (sqlite3_open("base.db", &pepardo))
	{
		 cout  << "Error opening the database" <<  endl;
		return -1;
	}

	char *errmsg;
	if (sqlite3_exec(pepardo, "CREATE TABLE IF NOT EXISTS tabla (val TEXT, vol TEXT);", NULL, NULL, &errmsg) != 0)
	{
		 cout  << "Error creating a table: " <<  endl
				  << " " << errmsg <<  endl;
		return -1;
	}

    if (sqlite3_exec(pepardo, "INSERT INTO tabla (val,vol) VALUES ('ola','addios');", NULL, NULL, &errmsg) != 0){
         cout << errmsg << endl;
    }

    if (sqlite3_exec(pepardo, "SELECT * FROM tabla;", callback, NULL, &errmsg) != 0 ){
         cout << errmsg << endl;
    }

    sqlite3_close(pepardo);
return 0;
}