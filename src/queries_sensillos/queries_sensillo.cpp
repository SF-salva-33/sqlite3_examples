#include<iostream>
#include"sqlite3.h"
#include<string>
using namespace std;

int callback(void* param, int argc, char** argv, char** col){
  cout << argv[0] << endl;
  cout << argv[1] << endl;
  return 0;
}

int main(){
sqlite3* db;

if (sqlite3_open("base.db",&db)){
	cout << "Error opening database" << endl;
	return -1;
}

char* errmsg;
if (sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS tabla (nombre TEXT, apellido TEXT);",NULL,NULL,&errmsg) != 0){
    	cout << "Error creating a table: " << errmsg << endl;
      return -1;
	}
string nombre = "amongas";
string apellido = "SD";
string query = "INSERT INTO tabla VALUES('" + nombre + "','" + apellido + "');";

if (sqlite3_exec(db,query.c_str(),NULL,NULL,&errmsg) != 0){
    	cout << "Error inserting into table: " << errmsg << endl;
    	return -1;
	}

if (sqlite3_exec(db,"SELECT * FROM tabla;",callback,NULL,&errmsg) != 0){
    	cout << "Error selecting from table: " << errmsg << endl;
    	return -1;
	}

sqlite3_close(db);
return 0;
}