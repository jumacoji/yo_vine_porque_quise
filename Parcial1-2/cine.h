#ifndef PERFILES_H
#define PERFILES_H

#endif // PERFILES_H

#include <iostream>
#include <map>
#include <fstream>

using namespace std;

class cinecito{
    public:
    string leer_txt(string name);
    void cargar_map_user(string txt);
    void cargar_map_admin(string txt);
    bool login_usuario();
    bool login_admin();
    void ingresar_productos();


    private:
    map<string,string>::iterator r; //Iterador para recorrer los mapas
    map<string,string> user;  //Contenedor para los usuarios
    map<string,string> admin; //Contenedor para los administradores

};
