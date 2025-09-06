#include <iostream>;
#include "sqlite3.h":
using namespace std;

/**
 * @breif Una guarderia que contiene niños con nombre, apellido y edad 
 *
 * Se debe permitir el ingreso, salida, obtencion y modificacion de datos de los pibes
 *
 */
int prepare_database(sqlite3* database){
    char* error;
    if (sqlite3_exec(db,"CREATE TABLE IF NOT EXISTS pibes (nombre TEXT, apellido TEXT, edad NUMBER);", NULL,NULL,&error) != SQLITE_OK){
      cout << "Error creando la tabla de pibes: " << error << endl;
      return -1;
    }
    return 0;
}

int query_pibes(sqlite3* db, sqlite3_stmt* stmt, const char* sql){
  sqlite3_finalize(stmt);
  if (sqlite3_prepare_v2(db,sql,stmt) != SQLITE_OK){
    cout << "Error preparando query: " << sqlite3_errmsg(db) << endl;
    return -1;
  }
  while (sqlite3_step(stmt) == SQLITE_ROW){
    const char* nombre = sqlite3_column_text(stmt, 1);
    const char* apellido = sqlite3_column_text(stmt, 2);
    int edad = sqlite3_column_int(stmt, 3);
    cout << "Nombre: " << nombre << "  Apellido: " << apellido << " Edad: "<< edad << endl;
  }
}

int main(){
  sqlite3* db;
  if (sqlite3_open("datos.db",&db) != SQLITE_OK){
    cout << "Error abriendo base de datos\n"; 
    return -1;
  }

  prepare_database(db);

  int opcion = 0;
  while (opcion < 5 && opcion > 0){
    cout << 
      "Guarderia\
      \n-Ingrese 1 para obtener una lista de pibes\
      \n-Ingrese 2 para añadir a un pibe\
      \n-Ingrese 3 para modificar los datos de un pibe\
      \n-Ingrese 4 para eliminar a un pibe\
      \n-Ingrese 5 para salir\n";
    cin >> opcion;

    sqlite3_stmt* statement*
    switch (opcion) {
    case 1:


      default:
        
        break;
    }
  }
}
