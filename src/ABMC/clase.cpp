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
	if (col[3][0] == 'V'){
		return 0;
	}
	for (int i = 0; i < argc; i++){
		if (i == 3){
		continue;
		}
		cout << col[i]	<< ":" << argv[i] << "\t";	
	}
	cout << endl;
	return 0;
}


int main(int argc, char** argv) {
	sqlite3* messi;
	char loco[] = "amongas";
	//int (*f)(const char*, sqlite3**) = sqlite3_open;
	//auto f = sqlite3_open;
	//f(loco,&messi); ! alternativa para la apertura de la base de datos
	
	//Abrimos o creamos el archivo de base de datos "amongas"
		sqlite3_open(loco,&messi);
	
	//sqlite3_exec(db,sql,callback,param,errmsg); ! Creamos una tabla bolita con un numero y un color
	sqlite3_exec(messi,"CREATE TABLE IF NOT EXISTS bolitas(id INTEGER PRIMARY KEY,numero NUMBER, color TEXT, eliminado TEXT);",NULL,NULL,NULL);	
	do {
	
	int opc = 0;
	cout << "\t----------------------------------\n";
	cout << "\t\t\tMen" << char(163) << "\n\n";
	cout << "\t\t1- Insertar bolitas\n";
	cout << "\t\t2- Listado de bolitas\n";
	cout << "\t\t3- Actualizar bolita\n";
	cout << "\t\t4- Eliminar bolitas de forma fisica\n";
	cout << "\t\t5- Eliminar bolitas de forma logica\n";
	cout << endl <<"\t\t6- Salir\n";
	cout << "\t----------------------------------\n";
	
	cout << "\n\t\t\tElija la opcion:";
	cin >> opc;
	switch(opc){
		case 1:{
			//INSERCION
	//Obtenemos los datos que necesitamos para ingresar un registro de bolita
	int numero;
	char color[25];
	cout << "Ingrese numero de bolita\n";
	cin >> numero;
	cout << "Ingrese color de bolita\n";
	cin >> color;
	
	//INSERT INTO bolitas VALUES (numero,color);
	//Este puntero va a almacenar el query que vallamos creando
	sqlite3_stmt* insertar;
	//sqlite3_prepare_v2(db,sql,size,&sqlite3_stmt,sql_extra);
	//el parametro "sql_extra" es opcional y solo en los casos en donde haya multiples queryes
	//el parametro "sql" contiene comodines definidos con el caracter ?
	//que especifica el lugar en donde luego se van a añadir los datos
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
	// int sqlite3_exec(d b, sql, callback, param, errmsg) {
	// for (EJECUTAR(sql)){
	// 	callback(result);
	// 	}
	// }
	sqlite3_exec(messi,"SELECT * FROM bolitas;",obtenerBolitas,NULL,NULL);		
		break;
	}
	case 3: {
		//ACTUALIZACION
		//Pedir algun dato identificador al usuario
		system("cls");
		sqlite3_exec(messi,"SELECT * FROM bolitas;",obtenerBolitas,NULL,NULL);
		system("pause");
		
		int id;
		cout << "Ingrese id\n";
		cin >> id;
		
		
		//Pedimos los nuevos datos
		int numero;
		cout << "Ingrese numero\n";
		cin >> numero;
		char color[25];
		cout << "Ingrese color\n";
		cin >> color;
		
		sqlite3_stmt* stmt;
		sqlite3_prepare_v2(messi,"UPDATE bolitas SET numero = ?, color = ? WHERE id = ?;",-1,&stmt,0);
		sqlite3_bind_int(stmt,1,numero);
		sqlite3_bind_text(stmt,2,color,-1,SQLITE_STATIC);
		sqlite3_bind_int(stmt,3,id);
		
		sqlite3_step(stmt);
		sqlite3_exec(messi,"SELECT * FROM bolitas;",obtenerBolitas,NULL,NULL);
		break;
	}
	case 4: {
		
		//ELIMINACION
		//Pedir algun dato identificador al usuario
		system("cls");
		sqlite3_exec(messi,"SELECT * FROM bolitas;",obtenerBolitas,NULL,NULL);
		system("pause");
		
		int id;
		cout << "Ingrese id\n";
		cin >> id;
		
		
		sqlite3_stmt* stmt;
		sqlite3_prepare_v2(messi,"DELETE FROM bolitas WHERE id = ?;",-1,&stmt,0);
		sqlite3_bind_int(stmt,1,id);
		
		sqlite3_step(stmt);
		sqlite3_exec(messi,"SELECT * FROM bolitas;",obtenerBolitas,NULL,NULL);
		break;
	} 
	case 5: {
		
		//ELIMINACION LOGICA
		//Pedir algun dato identificador al usuario
		system("cls");
		sqlite3_exec(messi,"SELECT * FROM bolitas;",obtenerBolitas,NULL,NULL);
		system("pause");
		
		int id;
		cout << "Ingrese id\n";
		cin >> id;
		
		
		sqlite3_stmt* stmt;
		sqlite3_prepare_v2(messi,"UPDATE bolitas SET eliminado = 'V' WHERE id = ?;",-1,&stmt,0);
		sqlite3_bind_int(stmt,1,id);
		
		sqlite3_step(stmt);
		sqlite3_exec(messi,"SELECT * FROM bolitas;",obtenerBolitas,NULL,NULL);
		break;
	}
	case 6: {
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
	return 0;
}