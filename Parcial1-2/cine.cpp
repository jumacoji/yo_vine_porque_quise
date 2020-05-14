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
    //cout<<text;                          //string provocado por la funcion push_back
    //cout<<endl;
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


void cinecito::agregar_users(string txt){                    //Esta funcion solo para administradores permite agregar más usuarios
    string nombre, clave, completo;                          //al servicio del cine
    string name, password;
    for(r=user.begin();r!=user.end();r++){
        name=r->first;                                      //Tambien se ingresan en una variable string para poder
        password=r->second;                                 //ingresarla a la base de datos (txt)
        completo.append(name);
        completo.append(" ");
        completo.append(password);
        completo.append("\n");
    }


    cout<<"Ingresa el ID del usuario(nombre)"<<endl;
    cout<<"Ten en cuenta que cada ID debe ser diferente"<<endl;
    cin>>nombre;
    r=user.find(nombre);                                       //Todos los ID son diferentes, funcionan como si fuera una cuenta
    if (r==user.end()){                                        //de videojuegos o como un correo electrónico personal para
        cout<<"Ingresa la clave: ";                            //cada persona
        cin>>clave;
        user[nombre]=clave;                                    //Una vez el programa revise que no existe, lo agregará
        completo.append(nombre);
        completo.append(" ");
        completo.append(clave);
        escribir_txt(completo,txt);
        cout<<"Usuario Ingresado con exito"<<endl;
    }
    else cout<<"El ID ya existe"<<endl;

}


void cinecito::ingresar_productos(string txt){ //Funcion para ingresar productos o cantidades para los productos
    //map<string,vector<int>> copia;
    string products=leer_txt(txt),cantid,cashing;
    string productosCopy;
    int cantidadX,cashX;
    int cantidadY;//cashY;
    int ID;
    bool decision;
    char exit;
    string name;
//    if(products.size()>0) products.append("\n");
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
                    //cashY=r21->second[1];
                    //cashY/=cantidadY;

                    cantidadY+=cantidadX;
                    //cashY*=cantidadX;
                    cashX=r21->second[1];
                    //cashX+=cashY;
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
            if(products.size()>0) products.append("\n");
            cout<<"Ingresa el nombre del producto"<<endl;    //En este punto es si el administrador quiere ingresar un nuevo producto
            cin.ignore();
            getline(cin,name);                               //se ingresa el nombre del producto, la cantidad de este y el costo del
            products.append(name);
            products.append(" (");
            cout<<"Ingresa la cantidad del producto"<<endl;  //monto
            cin>>cantidadY;
            cantid=to_string(cantidadY);
            products.append(cantid);
            products.append(") $");
            cout<<"Ingresa el costo del producto (individual)"<<endl;
            cin>>cashX;
            cashing=to_string(cashX);
            products.append(cashing);
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
    escribir_txt(products,txt);
}


void cinecito::mostrar_inventary(){ //Funcion para ver el inventario de forma ordenada
    //int big_tam,min_tam;
    int ID,cantidad,Precio;
    string product;
    string id,cantidadX,precioX;

    cout<<"\nINVENTARIO"<<endl<<endl;
    printElement("ID|",5);
    printElement("PRODUCTOS|",50);
    printElement("CANTIDAD|",15);
    printElement("PRECIO|",20);
    cout<<endl;

    for(Big=Inventary.begin();Big!=Inventary.end();Big++){
        ID=Big->first;
        id=to_string(ID);
        inventario=Big->second;
        for(r21=inventario.begin();r21!=inventario.end();r21++){
            product=r21->first;
            cantidad=r21->second[0];
            Precio=r21->second[1];
            cantidadX=to_string(cantidad);
            precioX=to_string(Precio);
        }
        printElement(id, 5);
        printElement(product, 50);
        printElement(cantidadX, 15);
        printElement(precioX, 20);
        cout<<endl;

    }
}




void cinecito::escribir_txt(string texto, string txt){ //Funcion para escribir un string en un txt
    ofstream k2(txt, ios::out | ios::binary );
    k2 << texto;
    k2.close();
}

void cinecito::crear_combos(string txt){ //Funcion para ingresar un combo en un txt

    string nombre,combitoX,precio,cantidadXx,Id;
    char sal;
    int ID,cantidad,k=0;
    combitoX=leer_txt(txt);
    cout<<"Ingresa el nombre del combo el cual quieres crear"<<endl;  //Se ingresa lo en una variable string los combos ya creados
    cin.ignore();                                                     //Para agregarle los que el admin cree de mas
    getline(cin,nombre);
    if(combitoX.length()>0) combitoX.append("\n");
    for(unsigned int i=0;i<nombre.size();i++){
        sal=nombre[i];
        combitoX.push_back(sal);
    }

    combitoX.append(" ");
    cout<<"Ingrese el precio del combo"<<endl;
    cout<<"Ten en cuenta el precio de los materiales"<<endl;
    cin>>precio;
    combitoX.append("$");
    combitoX.append(precio);
    combitoX.append("\n");
    do{
        cout<<"Una vez termines presiona 0 como ID"<<endl<<endl;
        cout<<"Ingresa el ID del material que requieres: ";cin>>ID;
        Big=Inventary.find(ID);
        if(Big!=Inventary.end()){
            cout<<"cuanta cantidad requieres?: ";cin>>cantidad;
            inventario=Big->second;
            for(r21=inventario.begin();r21!=inventario.end();r21++){
                if(r21->second[0]>=cantidad){
                    Id=to_string(ID);
                    cantidadXx=to_string(cantidad);
                    if(k!=0) combitoX.append("/");
                    combitoX.append(Id);
                    combitoX.append(",");
                    combitoX.append(cantidadXx);
                    k++;                                      //Todo se ingresa dentro de la misma variable para luego escribirla
                                                          //en el txt

                }

                else cout<<"No hay el material requerido para el combo"<<endl;
            }
        }

    }while(ID!=0);
    cout<<"Combo creado con exito!!"<<endl;
    //cout<<combitoX<<endl;

    escribir_txt(combitoX,txt);
}


void cinecito::cargar_combo(string txt){
    map<string,map<int,vector<int>>> Grandito;
    map<int,vector<int>> precio_cantidad;
    vector<int> id_cantidad;
    string texto,QUsa,copia,name,Monney,iDD,acd;
    int dinero,lineas=1,i=0,id=1,IDD,QUSA,linea=1;
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
        if(linea%2!=0){
            name=copia.substr(0,copia.find("$")-1);
            Monney=copia.substr(copia.find("$")+1);
            dinero=stoi(Monney);
        }
        else{
            for(size_t p=0,q=0;p!=copia.npos;p=q){

                acd=copia.substr(p+(p!=0),(q=copia.find('/', p+1))-p-(p!=0));
                iDD=acd.substr(0,acd.find(','));
                QUsa=acd.substr(acd.find(',')+1);
                IDD=stoi(iDD);
                QUSA=stoi(QUsa);
                id_cantidad.push_back(IDD);
                id_cantidad.push_back(QUSA);

            }    
        }
        if(linea%2==0){
            precio_cantidad[dinero]=id_cantidad;
            Grandito[name]=precio_cantidad;
            comboS[id]=Grandito;

            Grandito.clear();
            precio_cantidad.clear();
            id_cantidad.clear();
            id++;
        }

        linea++;
        copia.clear();



    }


}


void cinecito::mostrar_combo(){
    map<int,vector<int>> precio_cantidad;
    map<int,vector<int>>::iterator banano;
    map<string,map<int,vector<int>>> Grandito;
    map<string,map<int,vector<int>>>::iterator grandi;
    int ID, precio;
    string name,mini_id,money;
    cout<<"COMBOS"<<endl<<endl;
    printElement("Combo",10);
    printElement("Nombre",25);
    printElement("Precio",15);
    cout<<endl;
    for(manzana=comboS.begin();manzana!=comboS.end();manzana++){
        ID=manzana->first;
        mini_id=to_string(ID);
        Grandito=manzana->second;
        for (grandi=Grandito.begin();grandi!=Grandito.end();grandi++) {
            name=grandi->first;
            precio_cantidad=grandi->second;
            for(banano=precio_cantidad.begin();banano!=precio_cantidad.end();banano++){
                precio=banano->first;
                money=to_string(precio);
            }
        }
        printElement(mini_id,10);
        printElement(name,25);
        printElement(money,15);
        cout<<endl;

    }
    cout<<endl;


}


