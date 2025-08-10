#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;

void menu(int &opc){
	//system("cls");
	cout << "\n|------------------------------------------------------------------------|";
	cout << "\n| \tOpciones:\t\t\t\t\t\t\t |\n| \t1: Agregar otro estudiante.\t\t\t\t\t |\n| \t2: Ver apellido y edad de los estudiantes.\t\t\t |\n| \t3: Ver listado completo de los estudiantes.\t\t\t |\n| \t4: Mostrar al estudiante de mayor edad.\t\t\t\t |\n| \t5: Recibir el promedio de edades\t\t\t\t |\n| \tIngrese cualquier otro numero para finalizar el programa:\t |";
	cout << "\n|------------------------------------------------------------------------|";
	cout << "\n\tIngrese Aqui: ";
	cin >> opc;
}

int callback(void* param, int argc, char** argv, char** col){
	cout << argv[0] << endl;
	cout << argv[1] << endl;
	return 0;
}

int select(sqlite3* &database, char* &errmsg){
	if (sqlite3_exec(database,"SELECT * FROM tabla;",callback,NULL,&errmsg) != 0){
		std::cerr << "Error creating a table: " << std::endl <<" "<<errmsg << std::endl;
		return -1;
	}
	return 0;
}

void datos(string &n, string &a, string &s, string &ec, int &e, int &m){
	//system("cls");
	cout << "\nIngrese el Nombre del estudiante: ";
	cin >> n;
	system("cls");
	cout << "\nIngrese el Apellido del estudiante: ";
	cin >> a;
	system("cls");
	cout << "\nIngrese la edad del estudiante: ";
	cin >> e;
	system("cls");
	cout << "\nIngrese el estado civil del estudiante: ";
	cin >> ec;
	system("cls");
	cout << "\nIngrese el sexo del estudiante: ";
	cin >> s;
	system("cls");
	cout << "\nIngrese la cantidad de materias aprobadas por el alumno: ";
	cin >> m;
}

int convertir(string &n, string &a, string &s, string &ec, int &e, int &m, sqlite3* &database){
	sqlite3_stmt* stmt;
	if(sqlite3_prepare_v2(database,"INSERT INTO tabla VALUES(?,?,?,?,?,?);",-1,&stmt,0) != SQLITE_OK){
		std::cerr << "Error creating a statement " << std::endl;
		return -1;
	}
	const char* nombrechar = n.c_str();
	if(sqlite3_bind_text(stmt, 1,nombrechar,20,SQLITE_STATIC) != SQLITE_OK){
		std::cerr << "Error binding nombre " <<std::endl;
		return -1;
	}
	const char* apellidochar = a.c_str();
	if(sqlite3_bind_text(stmt,2,apellidochar,20,SQLITE_STATIC) != SQLITE_OK){
		std::cerr << "Error binding apellido " <<std::endl;
		return -1;
	}
	
	if(sqlite3_bind_int(stmt,3,e) != SQLITE_OK){
		std::cerr << "Error binding edad" <<std::endl;
		return -1;
	}
	const char* eCchar = ec.c_str();
	if(sqlite3_bind_text(stmt,4,eCchar,20,SQLITE_STATIC) != SQLITE_OK){
		std::cerr << "Error binding Estado Civil" <<std::endl;
		return -1;
	}
	const char* sexochar = s.c_str();
	if(sqlite3_bind_text(stmt,5,sexochar,20,SQLITE_STATIC) != SQLITE_OK){
		std::cerr << "Error binding sexo" <<std::endl;
		return -1;
	}
	if(sqlite3_bind_int(stmt,6,m) != SQLITE_OK){
		std::cerr << "Error binding materias aprobadas" <<std::endl;
		return -1;
	}
	if(sqlite3_step(stmt) != SQLITE_DONE){
		std::cerr << "Error stteping " <<std::endl;
		return -1;
	}
	if(sqlite3_finalize(stmt) != SQLITE_OK){
		std::cerr << "Error finalizing " <<std::endl;
		return -1;
	}
	return 0;
}

int main(int argc, char** argv) {
	string nombre, apellido, sexo, estadoCivil;
	int edad, materias, opc=1;
	sqlite3* db;
	sqlite3_open("base.db", &db);
	char* errmsg;
	if (sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS tabla (nombre TEXT, apellido TEXT, edad INTEGER, estadocivil TEXT, sexo TEXT, materias INTEGER);",NULL,NULL,&errmsg) != 0){
		std::cerr << "Error creating a table: " << std::endl <<" "<<errmsg << std::endl;
		return -1;
	}
	while (opc>0 && opc<6){
		menu(opc);
		switch(opc){
			case 1:
				datos(nombre,apellido,sexo,estadoCivil,edad,materias);
				convertir(nombre,apellido,sexo,estadoCivil,edad,materias, db);
				break;
			case 2:
				select(db, errmsg);
				break;
			case 3:
				select(db, errmsg);
				break;
			case 4:
				//mas tarde :P
				break;
		}
	}
	sqlite3_close(db);
	return 0;
}