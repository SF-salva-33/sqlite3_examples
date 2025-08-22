#include <iostream>
#include "sqlite3.h"
using namespace std;

int main()
{
	sqlite3 *db;

	if (sqlite3_open("base.db", &db))
	{
		 cout  << "Error opening the database" <<  endl;
		return -1;
	}

	char *errmsg;
	if (sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS tabla (nombre TEXT, apellido TEXT);", NULL, NULL, &errmsg) != 0)
	{
		 cout  << "Error creating a table: " <<  endl
				  << " " << errmsg <<  endl;
		return -1;
	}

	sqlite3_stmt *stmt;
	if (sqlite3_prepare_v2(db, "INSERT INTO tabla VALUES(?,?);", -1, &stmt, 0) != SQLITE_OK)
	{
		 cout  << "Error creating a statement " <<  endl;
		return -1;
	}

	if (sqlite3_bind_text(stmt, 1, "Amongas", -1, SQLITE_STATIC) != SQLITE_OK)
	{
		 cout  << "Error binding amongas " << sqlite3_errmsg(db) <<  endl;
		return -1;
	}

	if (sqlite3_bind_text(stmt, 2, "SD", -1, NULL) != SQLITE_OK)
	{
		 cout  << "Error binding SD " << sqlite3_errmsg(db) <<  endl;
		return -1;
	}

	if (sqlite3_step(stmt) != SQLITE_DONE)
	{
		 cout  << "Error stteping " <<  endl;
		return -1;
	}

	if (sqlite3_finalize(stmt) != SQLITE_OK)
	{
		 cout  << "Error finalizing " <<  endl;
		return -1;
	}

	if (sqlite3_prepare_v2(db, "SELECT * FROM tabla WHERE nombre = ? AND apellido = ?;", -1, &stmt, 0) != SQLITE_OK)
	{
		 cout  << "Error creating a statement " <<  endl;
		return -1;
	}

	// Ahora hacemos binding, que seria añadirle a la declaracion lo siguiente (https://sqlite.org/c3ref/bind_blob.html)
	if (sqlite3_bind_text(stmt, /*El index de los signos de pregunta que añadimos, como esto va en el primero, ponemos 1*/ 1, "Amongas", /*Tamaño del texto*/ -1, SQLITE_STATIC) != SQLITE_OK)
	{
		 cout  << "Error binding amongas " <<  endl;
		return -1;
	}

	// Añadimos el segundo
	if (sqlite3_bind_text(stmt, 2, "SD", -1, SQLITE_STATIC) != SQLITE_OK)
	{
		 cout  << "Error binding SD " <<  endl;
		return -1;
	}

	// Y ahora hacemos un paso (ejecucion), Ahora, como necesitamos obtener valores de esto, necesitamos iterar por todos las columnas hasta que ya deje de devolver columnas:
	while (sqlite3_step(stmt) == SQLITE_ROW)
	{
		// https://sqlite.org/c3ref/column_blob.html
		const unsigned char *nombre = sqlite3_column_text(stmt, /*Index de la columna, en este caso, 0 es Nombre*/ 0);
		const unsigned char *apellido = sqlite3_column_text(stmt, /*Index de la columna, en este caso, 1 es Apellido*/ 1);
		 cout << "Nombre: " << nombre << " Apellido: " << apellido <<  endl;
	}

	sqlite3_close(db);

	return 0;
}
