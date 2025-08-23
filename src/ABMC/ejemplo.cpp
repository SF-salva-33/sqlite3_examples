#include <iostream> //cout, cin, etc
#include "sqlite3.h" //En la carpeta del proyecto
using namespace std;

int procesar_usuarios(void * param, int argc, char** argv, char** col){
    for (int i = 0; i < argc; i++) {
        cout << col[i] << ":" << argv[i] << endl;
    }
    return 0;
}
/**
 * @brief Menu que contenga inicio de sesion, creacion de usuario y obtencion de usuarios
 * 
 * @return int 
 */

int main(){
    //Crear una variable que nos permita interactuar con el motor de base de datos
    //Y decirle al motor de base de datos que busque el archivo (o lo cree) y que nos de la conexion

    char* error;
    sqlite3* db;
    if (sqlite3_open("base.db",&db) != SQLITE_OK){
        cout << "Failed to open database" << endl;
        return -1;
    }

    //Creamos una tabla llamada usuarios con nombre, apellido y edad
    if (sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS usuarios (nombre TEXT, apellido TEXT, edad NUMBER);",NULL,NULL,&error) != SQLITE_OK){
        cout << "Failed to create table usuarios " << error << endl;
        return -1;
    }

    int opc = 0;
    cout << "Ingresar 1 para iniciar sesion\n Ingresar 2 para registrarse\n";
    cin >> opc;

    switch (opc) {
        case 1:
            {
                //Crear declaracion de query
                sqlite3_stmt* qr;
                sqlite3_prepare_v2(db,"SELECT * FROM usuarios WHERE nombre = ? AND apellido = ?;",-1,&qr,0);

                char nombre[25];
                char apellido[25];

                cout << "Ingresar nombre\n";
                cin >> nombre;
                cout << "Ingresar apellido\n";
                cin >> apellido;

                //Añadir nombre y apellido recien obtenidos
                sqlite3_bind_text(qr,1,nombre,-1,SQLITE_STATIC);
                sqlite3_bind_text(qr,2,apellido,-1,SQLITE_STATIC);
                
                //Ejecutando
                if (sqlite3_step(qr) == SQLITE_ROW){
                    //Obtener los datos de todos los usuarios
                    if (sqlite3_exec(db, "SELECT * FROM usuarios;",procesar_usuarios,NULL,&error) != SQLITE_OK){
                        cout << "Error selecting " << error << endl;
                        return -1;
                    }

                    const unsigned char* nom = sqlite3_column_text(qr,0);
                    const unsigned char* ape = sqlite3_column_text(qr,1);
                    int ed = sqlite3_column_int(qr, 2);

                    cout << "Ingresado con exito:\n Nombre: "<< nom << "\nApellido: " << ape << "\nEdad: " << ed << endl;
                }

                sqlite3_finalize(qr);

                break;      
            }
        case 2:
        {
                //Crear declaracion de query
                sqlite3_stmt* qr;
                sqlite3_prepare_v2(db,"INSERT INTO usuarios VALUES(?,?,?);",-1,&qr,0);

                char nombre[25];
                char apellido[25];
                int edad;

                cout << "Ingresar nombre\n";
                cin >> nombre;
                cout << "Ingresar apellido\n";
                cin >> apellido;
                cout << "Ingresar edad\n";
                cin >> edad;

                //Añadir nombre y apellido recien obtenidos
                sqlite3_bind_text(qr,1,nombre,-1,SQLITE_STATIC);
                sqlite3_bind_text(qr,2,apellido,-1,SQLITE_STATIC);
                sqlite3_bind_int(qr, 3, edad);

                //Ejecutar
                if (sqlite3_step(qr) != SQLITE_DONE){
                    cout << "Failed to insert values" << sqlite3_errmsg(db) << endl;
                    return -1;
                }

                sqlite3_finalize(qr);
                break;

        }
        default:
            cout << "Valor invalido" << endl;
            break;
    }



    sqlite3_close(db);
    return 0;
}
