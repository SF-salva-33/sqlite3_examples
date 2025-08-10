#include<iostream>
#include"../lib/sqlite3.h"

int callback(void* param, int argc, char** argv, char** col){
	int i = std::stoi("54");
	float b = std::stof("3.14");
	std::cout << i << " " << b << std::endl;
	for (int i = 0; i < argc; i++){
		std::cout << col[i] << " : " << argv[i] << std::endl;
	}
	return 0;
}

int main(){
	sqlite3* db;


	if (sqlite3_open("amongas.db",&db)){
		std::cerr << "Error opening the database" << std::endl;
		return -1;
	}

	char* errmsg;
	if (sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS tabla (nombre TEXT, apellido TEXT);",NULL,NULL,&errmsg) != 0){
		std::cerr << "Error creating a table: " << std::endl <<" "<<errmsg << std::endl;
		return -1;
	}


	sqlite3_stmt* stmt;
	if(sqlite3_prepare_v2(db,"INSERT INTO tabla VALUES(?,?);",-1,&stmt,0) != SQLITE_OK){
		std::cerr << "Error creating a statement " << std::endl;
		return -1;
	}

	if(sqlite3_bind_text(stmt,1,"Amongas",7,SQLITE_STATIC) != SQLITE_OK){
		std::cerr << "Error binding amongas " <<std::endl;
		return -1;
	}


	if(sqlite3_bind_text(stmt,2,"SD",2,SQLITE_STATIC) != SQLITE_OK){
		std::cerr << "Error binding SD " <<std::endl;
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


		if(sqlite3_prepare_v2(db,"SELECT * FROM tabla WHERE nombre = ? AND apellido = ?;",-1,&stmt,0) != SQLITE_OK){
		std::cerr << "Error creating a statement " << std::endl;
		return -1;
	}

//Ahora hacemos binding, que seria añadirle a la declaracion lo siguiente (https://sqlite.org/c3ref/bind_blob.html)
	if(sqlite3_bind_text(stmt, /*El index de los signos de pregunta que añadimos, como esto va en el primero, ponemos 1*/ 1,"Amongas",/*Tamaño del texto*/7,SQLITE_STATIC) != SQLITE_OK){
		std::cerr << "Error binding amongas " <<std::endl;
		return -1;
	}

//Añadimos el segundo
	if(sqlite3_bind_text(stmt,2,"SD",2,SQLITE_STATIC) != SQLITE_OK){
		std::cerr << "Error binding SD " <<std::endl;
		return -1;
	}


//Y ahora hacemos un paso (ejecucion), Ahora, como necesitamos obtener valores de esto, necesitamos iterar por todos las columnas hasta que ya deje de devolver columnas:
	while(sqlite3_step(stmt) == SQLITE_ROW){
//https://sqlite.org/c3ref/column_blob.html
	const unsigned char* nombre = sqlite3_column_text(stmt, /*Index de la columna, en este caso, 0 es Nombre*/0);
const unsigned char* apellido = sqlite3_column_text(stmt, /*Index de la columna, en este caso, 1 es Apellido*/1);
		std::cout << "Nombre: "<< nombre<< " Apellido: "<< apellido<< std::endl;
	}

	
	sqlite3_close(db);

	return 0;
	
	
}
