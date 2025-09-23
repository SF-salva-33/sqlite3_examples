#include <iostream>
#include "sqlite3.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//>> *
//<<
// Realizar una tabla de bolitas de colores con numero, permitir añadir y mostrar bolitas

/**
* 1- Manejo de errores
* 2- eliminacion-modificacion
* 3- menu
**/

//int (*callback)(void*,int,char**,char**)
int obtenerBolitas(void* param, int argc /*Argument counter*/, char** argv /*Argument value*/, char** col /*Argument counter*/){
	for (int i = 0; i < argc; i++){
		cout << col[i]	<< ":" << argv[i] << "\n";	
	}
	return 0;
}

char campo[20];
bool nuevo = false;

int main(int argc, char** argv) {
	sqlite3* messi;
	char loco[] = "amongas";
	//int (*f)(const char*, sqlite3**) = sqlite3_open;
	//auto f = sqlite3_open;
	//f(loco,&messi); ! alternativa para la apertura de la base de datos
	
	//Abrimos o creamos el archivo de base de datos "amongas"
	sqlite3_open(loco,&messi);
	
	//sqlite3_exec(db,sql,callback,param,errmsg); ! Creamos una tabla bolita con un numero y un color
	sqlite3_exec(messi,"CREATE TABLE IF NOT EXISTS bolitas(id INTEGER PRIMARY KEY,numero NUMBER, color TEXT);",NULL,NULL,NULL);	
	do {
	
	int opc = 0;
	cout << "\t----------------------------------\n";
	cout << "\t\t\tMen" << char(163) << "\n\n";
	cout << "\t\t1- Insertar bolitas\n";
	cout << "\t\t2- Listado de bolitas\n";
	cout << "\t\t3- Añadir nuevo campo a la tabla\n";
	cout << endl <<"\t\t4- Salir\n";
	cout << "\t----------------------------------\n";
	
	cout << "\n\t\t\tElija la opcion:";
	cin >> opc;
	switch(opc){
		case 1:{
			//INSERCION
	//Obtenemos los datos que necesitamos para ingresar un registro de bolita
	int numero;
	char color[25];
	char extra[25];
	cout << "Ingrese numero de bolita\n";
	cin >> numero;
	cout << "Ingrese color de bolita\n";
	cin >> color;
	//TODO:
	if (nuevo){
		cout << "Ingrese " << campo << " de bolita\n";
		cin >> extra;
	}
	
	//INSERT INTO bolitas VALUES (numero,color);
	sqlite3_stmt* insertar;
	sqlite3_prepare_v2(messi,"INSERT INTO bolitas(color, numero) VALUES(?,?);",-1,&insertar,NULL); 
	//! -1 es un parametro que define el tamaño del texto a insertar 
	//Bind es para ingresar los valores al query SQL
	sqlite3_bind_int(insertar,2,numero);
	sqlite3_bind_text(insertar,1,color,-1,SQLITE_STATIC); //! -1 es un parametro que define el tamaño del texto a insertar
	//El numero se refiere al orden de aparicion de signo de pregunta, el cual esta estructurado segun la tabla
	//(Numero, Color)
	
	//Ejecutar query
	sqlite3_step(insertar);
		
			break;
		}
	case 2: {
			//CONSULTA
			// int sqlite3_exec(db, sql, callback, param, errmsg) {
			// for (EJECUTAR(sql)){
			// 	callback(result);
			// 	}
			// }
			sqlite3_exec(messi,"SELECT * FROM bolitas;",obtenerBolitas,NULL,NULL);		
			break;
		}
	case 3: {
		char tipo[20];
		cout << "\nIngresar nombre de nuevo campo: ";
		cin >> campo;
		cout << "\nIngresar tipo de nuevo campo: ";
		cin >> tipo;
		
		string query = "CREATE TABLE NBolitas (id INTEGER PRIMARY KEY,numero NUMBER, color TEXT,";
		query += string(campo);
		//query += " ";
		//query += string(tipo);
		query += " TEXT);";
		//cout << query;
		sqlite3_exec(messi,query.c_str(),NULL,NULL,NULL);
		
		sqlite3_exec(messi,"INSERT INTO NBolitas(id,numero,color) SELECT * FROM bolitas;",NULL,NULL,NULL);
		//sqlite3_exec(messi,"SELECT * FROM NBolitas;",obtenerBolitas,NULL,NULL);
		//sqlite3_exec(messi,"DROP TABLE bolitas;",obtenerBolitas,NULL,NULL);	Para borrar tabla
		sqlite3_exec(messi,"ALTER TABLE bolitas RENAME TO bolitas1;",NULL,NULL,NULL);	
		sqlite3_exec(messi,"ALTER TABLE NBolitas RENAME TO bolitas;",NULL,NULL,NULL);
		string upd = "UPDATE bolitas SET ";
		upd += string(campo);
		upd += " = 'a';";
		sqlite3_exec(messi,upd.c_str(),NULL,NULL,NULL);
		sqlite3_exec(messi,"SELECT (id,numero,color) FROM bolitas;",obtenerBolitas,NULL,NULL);
		break;
	}
	case 4: {
			return 0;
			break;
		}
	default: {
			cout << "Ingrese una opción correcta\n";
			break;
		}	
	}
	
	}while(true);
	
	
	//Cerramos la base de datos
	sqlite3_close(messi);
	system("pause");
	return 0;
}