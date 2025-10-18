#include <iostream>
#include "sqlite3.h"
using namespace std;

int main(){
  sqlite3* db;
  sqlite3_open("datos.db",&db);

  sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS tickets (id INTEGER PRIMARY KEY, evento TEXT, precio REAL, cantidad INTEGER);",NULL,NULL,NULL);

cout << "\n\n INSERT \n\n";

  sqlite3_exec(db, "INSERT INTO tickets (evento, precio, cantidad) VALUES('Ozuna',1000,3);",NULL,NULL,NULL);

  sqlite3_stmt* insertar;
  sqlite3_prepare_v2(db,"INSERT INTO tickets(evento, precio, cantidad) VALUES(?,?,?);",-1,&insertar,NULL); 
 
  char evento[25];
float precio;
int cantidad;
cout << "Ingresa nombre del evento \n";
cin >> evento;
cout << "Ingresa precio del ticket\n";
cin >> precio;
cout << "Ingresa cantidad de tickets vendidos\n";
cin >> cantidad;


sqlite3_bind_text(insertar,1,evento,-1,SQLITE_STATIC);
sqlite3_bind_double(insertar,2,precio);
sqlite3_bind_int(insertar,3,cantidad);

sqlite3_step(insertar);

sqlite3_finalize(insertar);

cout << "\n\n UPDATE \n\n";
  sqlite3_stmt* actualizar;
  sqlite3_prepare_v2(db,"UPDATE tickets SET evento = ?, precio = ?, cantidad = ? WHERE id = ?;",-1,&actualizar,NULL); 
 
int id;
cout << "Ingresa ID del registro \n";
cin >> id;
cout << "Ingresa nombre del evento \n";
cin >> evento;
cout << "Ingresa precio del ticket\n";
cin >> precio;
cout << "Ingresa cantidad de tickets vendidos\n";
cin >> cantidad;


sqlite3_bind_text(actualizar,1,evento,-1,SQLITE_STATIC);
sqlite3_bind_double(actualizar,2,precio);
sqlite3_bind_int(actualizar,3,cantidad);
sqlite3_bind_int(actualizar,4,id);

sqlite3_step(actualizar);

sqlite3_finalize(actualizar);

cout << "\n\n DELETE \n\n";

  sqlite3_stmt* eliminar;
  sqlite3_prepare_v2(db,"DELETE FROM tickets WHERE id = ?;",-1,&eliminar,NULL); 
 
cout << "Ingresa ID del registro \n";
cin >> id;


sqlite3_bind_int(eliminar,1,id);

sqlite3_step(eliminar);

sqlite3_finalize(eliminar);

cout << "\n\n SELECT \n\n";

sqlite3_stmt* select;
    sqlite3_prepare_v2(db,"SELECT evento,precio,cantidad FROM tickets",-1,&select,NULL); 


while (sqlite3_step(select) == SQLITE_ROW){

cout << "Evento: " << sqlite3_column_text(select,0) << " Precio: " << sqlite3_column_double(select,1) << " Cantidad: " << sqlite3_column_int(select,2) << endl;
}


sqlite3_finalize(select);


return 0;

}
