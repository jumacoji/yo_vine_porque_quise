#ifndef PERFILES_H
#define PERFILES_H

#endif // PERFILES_H

#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

class cinecito{
    public:
    string leer_txt(string name);
    void cargar_map_user(string txt);
    void cargar_map_admin(string txt);
    bool login_usuario();
    bool login_admin();
    void agregar_users();
    void mostrar_inventary();
    void inventario_derecho(cinecito a);
    void ingresar_productos();
    void cargar_inventario(string inventario);
    void crear_combos();


    private:
    map<string,string>::iterator r;             //Iterador para recorrer los mapas de user y admin
    map<int,map<string,vector<int>>>::iterator Big;
    map<string,vector<int>>::iterator r21;      //Iterador para recorrer el map inventario
    map<string,string> user;                    //Contenedor para los usuarios
    map<string,string> admin;                   //Contenedor para los administradores
    vector<int> cantid_precio;                  //Vector para la cantidad de productos y su precio
    map<string,vector<int>> inventario;         //Contenedor para agregar el inventario
    map<int,map<string,vector<int>>> Inventary;
    long int reportes;

};
