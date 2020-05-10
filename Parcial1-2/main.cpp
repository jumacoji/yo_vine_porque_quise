#include "cine.h"

int main()
{

    cinecito objeto;
    bool decision;
    string usuario="users.txt";
    string admin="sudo.txt";
    //objeto.leer_txt(usuario);
    cout<<"Ingresar como usuario presiona 1\nIngresar como administrador presiona 0: ";cin>>decision;
    if(decision){
        objeto.cargar_map_user(usuario);
        objeto.login_usuario();
    }
    else{
        objeto.cargar_map_admin(admin);
        objeto.login_admin();
    }
    return 0;
}
