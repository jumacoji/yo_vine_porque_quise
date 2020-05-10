#include "cine.h"

string cinecito::leer_txt(string name){   //Funcion para leer el txt
    string text;
    int i=0;
    char textin;
    ifstream tex(name, ios::in);
    while (!tex.eof()){
        tex.get(textin);
        text.push_back(textin);
        i++;
    }
    text.pop_back();
    cout<<text;
    cout<<endl;
    tex.close();
    return text;
}


void cinecito::cargar_map_user(string txt){
    string texto;                             //Donde se guardará el txt y donde se encuentra
    string nombre,contra,copia;               //Variable para guardar el nombre de usuario y la otra la contraseña
    int lineas=1,i=0;                         //Cuenta el numero de lineas
    texto=leer_txt(txt);
    for (unsigned int j=0;j<texto.size();j++){
        if(texto[j]=='\n')lineas++;              //variable para saber el numero de lineas
    }
    for (int j=0;j<lineas;j++){
        while (texto[i]!='\n' && texto[i]!='\0'){
            copia.append(1,texto[i]);
            i++;
        }
        i++;
        nombre=copia.substr(0,copia.find(" ")); //Se guarda el nombre de la linea correspondiente
        contra=copia.substr(copia.find(" ")+1); //Igualmente sse guarda la contraseña

        copia.clear();
        user[nombre]=contra;                   //Se guarda en el map el usuario y contraseña
    }


}

void cinecito::cargar_map_admin(string txt){ //Es exactamente igual que la funcion anterior
    string texto;                             //Solo que con el map de administradores
    string nombre,contra,copia;
    int lineas=1,i=0;
    texto=leer_txt(txt);
    for (unsigned int j=0;j<texto.size();j++){
        if(texto[j]=='\n')lineas++;
    }
    for (int j=0;j<lineas;j++){
        while (texto[i]!='\n' && texto[i]!='\0'){
            copia.append(1,texto[i]);
            i++;
        }
        i++;
        nombre=copia.substr(0,copia.find(" "));
        contra=copia.substr(copia.find(" ")+1);

        copia.clear();
        admin[nombre]=contra;
    }

}


bool cinecito::login_usuario(){                          //Funcion para loguearse y determinar si existe el usuario o no
    string name,password;
    cout<<"Ingresa tu nombre: ";cin>>name;
    r=user.find(name);                                    //Se utiliza el iterador para encontrar el nombre como clave en el map
    if(r!=user.end()){
        cout<<"\nIngresa tu contrasena: ";cin>>password;
        if(r->second==password){                         //Se compara si el valor del map es igual a la contraseña
            return  true;
        }                                               //Si ambos son correctos se retorna true para continuar con los siguentes procesos
        else{
            cout<<"Contrasena incorrecta"<<endl;
            return false;
        }
    }
    else {
        cout<<"Usuario no encontrado"<<endl; //Si uno de los dos no es correcto, se acaba el proceso
        return false;
    }
}

bool cinecito::login_admin(){ //Es igual que la funcion de login_usuario solo que con el administrador
    string name,password;
    cout<<"Ingresa tu nombre: ";cin>>name;
    r=admin.find(name);
    if(r!=admin.end()){
        cout<<"\nIngresa tu contrasena: ";cin>>password;
        if(r->second==password){
            return  true;
        }
        else{
            cout<<"Contrasena incorrecta"<<endl;
            return false;
        }
    }
    else {
        cout<<"Usuario no encontrado"<<endl;
        return false;
    }
}

void cinecito::ingresar_productos(){

}



