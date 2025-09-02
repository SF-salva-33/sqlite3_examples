#include <iostream>
#include "sqlite3.h"
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//>> *
//<<
// Realizar una tabla de bolitas de colores con numero, permitir añadir y mostrar bolitas

int main(int argc, char** argv) {
	sqlite3* messi;
	char loco[] = "amongas";
	//int (*f)(const char*, sqlite3**) = sqlite3_open;
	//auto f = sqlite3_open;
	//f(loco,&messi); ! alternativa para la apertura de la base de datos
	
	//Abrimos o creamos el archivo de base de datos "amongas"
	sqlite3_open(loco,&messi);
	
	//sqlite3_exec(db,sql,callback,param,errmsg); ! Creamos una tabla bolita con un numero y un color
	sqlite3_exec(messi,"CREATE TABLE IF NOT EXISTS bolitas(numero NUMBER, color TEXT);",NULL,NULL,NULL);	
	
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
	sqlite3_prepare_v2(messi,"INSERT INTO bolitas VALUES(?,?);",-1,&insertar,NULL); 
	//! -1 es un parametro que define el tamaño del texto a insertar 
	
	//Bind es para ingresar los valores al query SQL
	sqlite3_bind_int(insertar,1,numero);
	sqlite3_bind_text(insertar,2,color,-1,SQLITE_STATIC); //! -1 es un parametro que define el tamaño del texto a insertar
	//El numero se refiere al orden de aparicion de signo de pregunta, el cual esta estructurado segun la tabla
	//(Numero, Color)
	
	//Ejecutar query
	sqlite3_step(insertar);

	//Cerramos la base de datos
	sqlite3_close(messi);
	return 0;
}
