#include "cine.h"

string cinecito::leer_txt(string name){   //Funcion para leer el txt
    string text;
    int i=0;
    char textin;                          //Se crea una variable char para leer el txt caracter por caracter
    ifstream tex(name, ios::in);
    while (!tex.eof()){
        tex.get(textin);
        text.push_back(textin);           //Posteriormente se incluye cada char dentro del string
        i++;
    }
    text.pop_back();                     //Esta funcion es necesaria para eliminar un caracter sobrante al final del
    cout<<text;                          //string provocado por la funcion push_back
    cout<<endl;
    tex.close();                        //Se cierra el txt para poder continuar y por ultimo se retorna el string con
    return text;                        //la informacion del txt
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
        cout<<"Usuario no encontrado"<<endl;            //Si uno de los dos no es correcto, se acaba el proceso
        return false;
    }
}

bool cinecito::login_admin(){                   //Es igual que la funcion de login_usuario solo que con el administrador
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


void cinecito::cargar_inventario(string inventarioX){ //Esta funcion es muy similar a cargar_map_user o cargar_map_admin
    string texto;                                     //solo que se ingresa el inventario en un map-vector
    string producto,copia;
    string cantidadX,precioX;
    int lineas=1,i=0;
    int cantidades, precio, id=1;
    texto=leer_txt(inventarioX);
    for (unsigned int j=0;j<texto.size();j++){
        if(texto[j]=='\n')lineas++;
    }
    for (int j=0;j<lineas;j++){
        while (texto[i]!='\n' && texto[i]!='\0'){
            copia.append(1,texto[i]);
            i++;
        }
        i++;
        producto=copia.substr(0,copia.find('(')-1);           //Se extrae cada elemento del string donde esta el txt completo
        for(unsigned int i=copia.find('(')+1;i<=copia.find(')')-1;i++){  //For necesario para extraer el elemento donde se
            cantidadX+=copia[i];                                         //encuentra la cantidad del producto
        }
        precioX=copia.substr(copia.find('$')+1);
        cantidades=stoi(cantidadX);                                 //Se convierte a enteros la cantidad y el precio
        precio=stoi(precioX);

        cantid_precio.push_back(cantidades);
        cantid_precio.push_back(precio);                          //Se agregan a el vector la cantidad y el precio
        inventario[producto]=cantid_precio;                       //Para luego ser guardados en el map
        Inventary[id]=inventario;
        id++;

        cantidadX.clear();
        copia.clear();
        inventario.clear();
        cantid_precio.clear();                                  //Es necesario borrar los elementos del vector para que no se
                                                                //repitan en la siguiente iteracion
    }

}


void cinecito::agregar_users(){                                //Esta funcion solo para administradores permite agregar más usuarios
    string nombre, clave;                                      //al servicio del cine
    cout<<"Ingresa el ID del usuario"<<endl;
    cout<<"Ten en cuenta que cada ID debe ser diferente"<<endl;
    cin>>nombre;
    r=user.find(nombre);                                       //Todos los ID son diferentes, funcionan como si fuera una cuenta
    if (r==user.end()){                                        //de videojuegos o como un correo electrónico personal para
        cout<<"Ingresa la clave: ";                            //cada persona
        cin>>clave;
        user[nombre]=clave;                                    //Una vez el programa revise que no existe, lo agregará
    }
    else cout<<"El ID ya existe"<<endl;

}


void cinecito::ingresar_productos(){ //Funcion para ingresar productos o cantidades para los productos
    //map<string,vector<int>> copia;
    int cantidadX,cashX;
    int cantidadY,cashY;
    int ID;
    bool decision;
    char exit;
    string name;
    cout<<"Ingresa los productos necesarios"<<endl<<endl;

    do{
        cout<<"Si el producto que vas a ingresar existe presiona 1\nSi no, presiona 0"<<endl;cin>>decision;
        if(decision){

           cout<<"Ingresa el ID del producto: ";          //En el caso de que solo se quiera ingresar la cantidad
           cin>>ID;                                       //El programa pedirá el ID del producto
           Big=Inventary.find(ID);
           if(Big==Inventary.end()){
               cout<<"ID no registrada"<<endl;
           }
           else{
               inventario=Big->second;
               cout<<"Ingrese la cantidad del producto: ";
               cin>>cantidadX;                                  //Luego pedirá la cantidad de ese producto que quiera anexar
               for(r21=inventario.begin();r21!=inventario.end();r21++){
                    cantidadY=r21->second[0];
                    cashY=r21->second[1];
                    cashY/=cantidadY;
                    cantidadY+=cantidadX;
                    cashY*=cantidadX;
                    cashX=r21->second[1];
                    cashX+=cashY;
                    cantid_precio.push_back(cantidadY);
                    cantid_precio.push_back(cashX);
                    name=r21->first;
                    inventario[name]=cantid_precio;
                    Inventary[ID]=inventario;                 //Una vez se realice el proceso se agrega el map la nueva cantidad
                    inventario.clear();                       //y su respectivo precio
                    cantid_precio.clear();
                    cout<<endl<<"Quieres seguir agregando?\nSi no quieres continuar presiona 'f' de lo contrario presiona otra letra"<<endl;
                    cin>>exit;
               }

           }


        }
        else{
            cout<<"Ingresa el nombre del producto"<<endl;    //En este punto es si el administrador quiere ingresar un nuevo producto
            cin.ignore();
            getline(cin,name);                               //se ingresa el nombre del producto, la cantidad de este y el costo del
            cout<<"Ingresa la cantidad del producto"<<endl;  //monto
            cin>>cantidadY;
            cout<<"Ingresa el costo del producto"<<endl;
            cin>>cashX;
            cantid_precio.push_back(cantidadY);
            cantid_precio.push_back(cashX);
            inventario[name]=cantid_precio;
            ID=Inventary.size()+1;
            Inventary[ID]=inventario;                        //Luego se agrega al map donde está el inventario
            cantid_precio.clear();
            inventario.clear();
            cout<<endl<<"Quieres seguir agregando?\nSi no quieres continuar presiona 'f' de lo contrario presiona otra letra"<<endl;
            cin>>exit;
        }
    }while (exit!='f');

}


void cinecito::mostrar_inventary(){ //Funcion para ver el inventario de forma ordenada
   cout<<"INVENTARIO"<<endl<<endl;
   cout<<"|ID|         Producto               Cantidad     Precio"<<endl;
   for(Big=Inventary.begin();Big!=Inventary.end();Big++){
       cout<<Big->first<<"   ";
       inventario=Big->second;
       for(r21=inventario.begin();r21!=inventario.end();r21++){
           cout<<r21->first<<"     ";
           cout<<r21->second[0]<<"    ";
           cout<<r21->second[1]<<endl;
       }
   }
}


void cinecito::inventario_derecho(cinecito a){

}


void cinecito::crear_combos(){

}
