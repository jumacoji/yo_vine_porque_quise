#include "cine.h"

int main()
{

    cinecito administrador,user;
    bool decision;
    string usuario="users.txt";
    string admin="sudo.txt";
    string invent="productos.txt";
    string combo="combos.txt";

    cout<<"Ingresar como usuario presiona 1\nIngresar como administrador presiona 0\n";cin>>decision;
    if(decision){
        user.cargar_map_user(usuario);
        if(user.login_usuario()==true){

        }
    }
    else{
        char eleccion;
        administrador.cargar_map_admin(admin);
        if (administrador.login_admin()==true){
            cout<<endl;
            cout<<"Que desea hacer administrador?"<<endl<<endl;
            cout<<"A-Agregar usuarios de cine"<<endl;
            cout<<"B-Ver inventario"<<endl;
            cout<<"C-Agregar productos al inventario"<<endl;
            cout<<"D-Crear combos"<<endl;
            cout<<"E-Mirar reporte de ventas"<<endl;
            cin>>eleccion;

            if (eleccion==65 or eleccion==97){

            }
            if (eleccion==66 or eleccion==98){
                administrador.cargar_inventario(invent);
                administrador.mostrar_inventary();

            }
            if (eleccion==67 or eleccion==99){
                administrador.cargar_inventario(invent);
                administrador.ingresar_productos();
            }
            if (eleccion==68 or eleccion==100){

            }
        }



    }
    return 0;
}
