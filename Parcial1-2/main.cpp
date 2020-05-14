#include "cine.h"

int main()
{
    bool salir=true;
    while(salir==true){
      cinecito administrador,user;
      bool decision,exit=true;
      string usuario="users.txt";
      string admin="sudo.txt";
      string invent="productos.txt";
      string combo="combos.txt";

      cout<<"Ingresar como usuario presiona 1\nIngresar como administrador presiona 0\n";cin>>decision;

      if(decision){
          user.cargar_map_user(usuario);
          if(user.login_usuario()==true){
              cout<<endl;
              cout<<"BIENVENIDO!!!! "<<endl<<endl;
              //cout<<"AQUI ESTAN LOS COMBOS"<<endl;
              user.cargar_combo(combo);
              user.mostrar_combo();



          }
      }
      else{

              char eleccion;
              administrador.cargar_map_admin(admin);
              if (administrador.login_admin()==true){

                do{
                  cout<<endl<<endl;
                  cout<<"Que desea hacer administrador?"<<endl<<endl;
                  cout<<"A-Agregar usuarios de cine"<<endl;
                  cout<<"B-Ver inventario"<<endl;
                  cout<<"C-Agregar productos al inventario"<<endl;
                  cout<<"D-Crear combos"<<endl;
                  cout<<"E-Mirar reporte de ventas"<<endl;
                  cout<<"F-Para salir"<<endl;
                  cout<<"G-Para finalizar dia"<<endl;
                  cin>>eleccion;

                  if (eleccion==65 or eleccion==97){ //Opcion A
                      administrador.cargar_map_user(usuario);
                      administrador.agregar_users(usuario);
                  }
                  if (eleccion==66 or eleccion==98){ //Opcion B
                      administrador.cargar_inventario(invent);
                      administrador.mostrar_inventary();

                  }
                  if (eleccion==67 or eleccion==99){ //Opcion C
                      administrador.cargar_inventario(invent);
                      administrador.ingresar_productos(invent);
                  }
                  if (eleccion==68 or eleccion==100){   //Opcion D
                      administrador.cargar_inventario(invent);
                      administrador.crear_combos(combo);
                  }
                  if (eleccion==69 or eleccion==101){ //Opcion E


                  }
                  if (eleccion==70 or eleccion==102) exit=false;
                  if (eleccion==71 or eleccion==103) {
                      salir=false;
                      exit=false;
                  }
              }while (exit==true);

          }
      }



    }


}

