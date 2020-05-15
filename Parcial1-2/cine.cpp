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
               r21=inventario.begin();
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
    if(!decision)escribir_txt(products,txt);
    else reescribir_inventario(txt);
}


void cinecito::mostrar_inventary(){ //Funcion para ver el inventario de forma ordenada
    //int big_tam,min_tam;
    int ID,cantidad,Precio;
    string product;
    string id,cantidadX,precioX;

    cout<<"\nINVENTARIO"<<endl<<endl;                         //Se utiliza printElement para poder
    printElement("ID|",5);                                    //imprimir una tabla de forma ordenada
    printElement("PRODUCTOS|",50);                            //Usando template
    printElement("CANTIDAD|",15);
    printElement("PRECIO|",20);
    cout<<endl;

    for(Big=Inventary.begin();Big!=Inventary.end();Big++){
        ID=Big->first;
        id=to_string(ID);
        inventario=Big->second;
        for(r21=inventario.begin();r21!=inventario.end();r21++){ //Simplemente es sacar cada elemento que se desa imprimir dentro
            product=r21->first;                                  //de los contenedores e implementarlos en printElement
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
    ofstream k2(txt, ios::out | ios::binary ); //Escribo en txt el contenido del string texto
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


void cinecito::cargar_combo(string txt){         //En esta funcion usa como base los anteriores cargar_map pero esta vez utilizandola
    map<string,map<int,vector<int>>> Grandito;   //para poder guardar los combos en una variable map y guardar
    map<int,vector<int>> precio_cantidad;        //el ID, el nombre del combo, su precio, el ID del inventario necesario
    vector<int> id_cantidad;                     //Y su respectiva cantidad
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
            precio_cantidad[dinero]=id_cantidad;    //En este punto se ingresan los elementos en el map
            Grandito[name]=precio_cantidad;         //combos
            comboS[id]=Grandito;

            Grandito.clear();
            precio_cantidad.clear();            //Luego se borra el resto para no tener problemas en la
            id_cantidad.clear();                //Proxima iteraci�n
            id++;
        }

        linea++;
        copia.clear();
    }
}

void cinecito::mostrar_combo(){      //Funcion muy similar a mostrar_inventario solo que para mostrarle el combo a los
    map<int,vector<int>> precio_cantidad; //usuarios
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
        printElement(mini_id,10);             //Se separa cada elemento en sus respectivas variables
        printElement(name,25);                //Para luego imprimirlas ordenadamente
        printElement(money,15);
        cout<<endl;

    }
    cout<<endl;


}

void cinecito::seleccionar_combo(string txt,string dia){ //De esta funcion se derivan muchas otras
    map<int,vector<int>> precio_cantidad;                //ya que esta es la encargada de quitarle las cantidades necesarias
    map<int,vector<int>>::iterator banano;               //a los productos del inventario para poder vender los combos
    vector<int> Copia_C;
    map<string,map<int,vector<int>>> Grandito;
    map<string,map<int,vector<int>>>::iterator grandi;
    bool ban=true;
    string name,nombre;
    int precio;
    int ID,other_id,other_cantidad,CantidadX,Cash;
    cout<<"Selecciona el combo que mas te gusta"<<endl;
    while (ban){

        cin>>ID;
        manzana=comboS.find(ID);                                   //Se busca el id del combo
        if(manzana==comboS.end()){
            cout<<"Ingrese un numero de combo existente"<<endl;
        }
        else ban=false;
    }
    Grandito=manzana->second;

    for(grandi=Grandito.begin();grandi!=Grandito.end();grandi++){           //Se empizan a separar las variables de los contenedores
        nombre=grandi->first;
        precio_cantidad=grandi->second;                                     //para poder accerder a los contenedores interiores

        for(banano=precio_cantidad.begin();banano!=precio_cantidad.end();banano++){
            cantid_precio=banano->second;
            precio=banano->first;
        }
    }
    for(unsigned int i=0,j=1;i<cantid_precio.size();i+=2,j+=2){
        if(cantid_precio[i]>0 && cantid_precio[j]>0){
            other_id=cantid_precio[i];
            other_cantidad=cantid_precio[j];
            Big=Inventary.find(other_id);
            inventario=Big->second;
            r21=inventario.begin();
            name=r21->first;
            CantidadX=r21->second[0];
            if(CantidadX-other_cantidad<=0){
                cout<<"Combo agotado, lo sentimos"<<endl;
            }
            else{
                CantidadX-=other_cantidad;
                Cash=r21->second[1];
                Copia_C.push_back(CantidadX);
                Copia_C.push_back(Cash);
                inventario[name]=Copia_C;
                Inventary[other_id]=inventario;          //Finalmente Se modifican los contenedores de inventary
                inventario.clear();
                Copia_C.clear();

            }


        }
    }
    reescribir_inventario(txt);
    pagar(precio);
    string Prc=to_string(precio);
    reportes_ventas(dia,nombre,Prc);
}

void cinecito::reescribir_inventario(string txt){

    int precio,cantidad,tamano_map=Inventary.size(),tam=0;            //Funcion para poder modificar las cantidades de los productos de l
    string texto="",nombre,PrecioX,CantidadX;                         //Inventario
    for(Big=Inventary.begin();Big!=Inventary.end();Big++){
        inventario=Big->second;
        for(r21=inventario.begin();r21!=inventario.end();r21++){
            nombre=r21->first;
            cantidad=r21->second[0];
            precio=r21->second[1];
            PrecioX=to_string(precio);                             //Consta de utilizar el string texto para sobreescribir la informacion
            CantidadX=to_string(cantidad);                        //del inventario
            texto.append(nombre);
            texto.append(" (");
            texto.append(CantidadX);
            texto.append(") $");
            texto.append(PrecioX);
            tam++;
            if(tam!=tamano_map){
                texto.append("\n");
            }



        }
    }
    escribir_txt(texto,txt);
}


void cinecito::pagar(int precio){              //Funcion utilizada en la practica 2, es simple y funciona como una maquina dispensadora
    bool decision,ban=true,ban2=true;
    int dinero,copia;
    vector<int>Mon={50000,20000,10000,5000,2000,1000,500,200,100,50};
    short CinM=0,VentM=0,DieM=0,cinm=0,dosm=0,mil=0,qui=0,dos=0,cien=0,cinq=0;
    cout<<"Seleccionar metodo de pago\nPara efectivo presione 1, para tarjeta presione 0\n";
    cin>>decision;
    if(decision){
        while (ban){
            cout<<"Por favor ingrese su dinero para efectuar la compra"<<endl;
            cin>>dinero;
            if(dinero<precio){
                cout<<"Dinero insuficiente"<<endl;
            }
            else{
                copia=dinero;
                dinero-=precio;
                copia-=precio;
                while(ban2){                         //Consta de ir haciendo comparaciones

                    if(dinero>=Mon[0]){
                        dinero-=Mon[0];
                        CinM++;
                    }
                    if(dinero>=Mon[1]){
                        dinero-=Mon[1];
                        VentM++;
                    }
                    if(dinero>=Mon[2]){
                        dinero-=Mon[2];
                        DieM++;
                    }
                    if(dinero>=Mon[3]){
                        dinero-=Mon[3];
                        cinm++;
                    }
                    if(dinero>=Mon[4]){
                        dinero-=Mon[4];
                        dosm++;
                    }
                    if(dinero>=Mon[5]){
                        dinero-=Mon[5];
                        mil++;
                    }
                    if(dinero>=Mon[6]){
                        dinero-=Mon[6];
                        qui++;
                    }
                    if(dinero>=Mon[7]){
                        dinero-=Mon[7];
                        dos++;
                    }
                    if(dinero>=Mon[8]){
                        dinero-=Mon[8];
                        cien++;
                    }
                    if(dinero>=Mon[9]){
                        dinero-=Mon[9];
                        cinq++;
                    }
                    if(dinero==0) ban2=false;
                }
                cout<<"La maquina te devuelve"<<endl;
                cout<<Mon[0]<<" :"<<CinM<<endl;
                cout<<Mon[1]<<" :"<<VentM<<endl;
                cout<<Mon[2]<<" :"<<DieM<<endl;
                cout<<Mon[3]<<" :"<<cinm<<endl;
                cout<<Mon[4]<<" :"<<dosm<<endl;
                cout<<Mon[5]<<" :"<<mil<<endl;
                cout<<Mon[6]<<" :"<<qui<<endl;
                cout<<Mon[7]<<" :"<<dos<<endl;
                cout<<Mon[8]<<" :"<<cien<<endl;
                cout<<Mon[9]<<" :"<<cinq<<endl;
                cout<<"Sobrante: "<<dinero<<endl<<endl;
                cout<<"Tu devuelta total es: "<<copia<<endl<<endl;
                ban=false;
            }
        }
       //Al final se imprimen la devuelta con su respectivo billete (En caso de que haya pagado medio efectivo)

    }
    else{
        cout<<"Gracias, su compra ha sido un exito"<<endl;
    }


}

void cinecito::elegir_silla(){                                      //Funcion para pedirle al usuario en que silla se le debe
    cout<<endl<<endl;                                               //enviar el combo
    cout<<"Elige el puesto al cual mandaras el combo"<<endl;
    int matriz[15][20],filas=15,columnas=10,ReservaF,ReservaC;      //Esta funcion fue utilizada de mi codigo de la practica 2
    char filA=65,reser_quit,FILIN;
    bool ban=true;

    cout<<" |1|2|3|4|5|6|7|8|9|10|"<<endl;
    //Agregar ceros a la matriz
    for (int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            matriz[i][j]=0;
        }
    }
    for(int k=0;k<2;k++){
        filA=65;
        for (int i=0;i<filas;i++){
            cout<<filA;
            cout<<"|";
            filA++;

            for (int j=0;j<columnas;j++){                      //Consta en llenar una matriz de ceros y hacer su estuctura para
                if (matriz[i][j]==0){                         //Simular los puestos de un cine
                cout<<"-";}
                else {cout<<"+";}
                cout<<"|";
            }
            cout<<endl;


        }
        if(k<1){
            while (ban) {
                reser_quit='+';
                bool ban2=true;
                if(reser_quit=='+'){
                    while(ban2){
                        cout<<"Digita fila y numero de asiento a para enviar: ";
                        cin>>FILIN>>ReservaC;
                        cout<<"Estas seguro de que es tu asiento?\nPresiona 0 para confirmar, 1 para corregir: ";cin>>ban2;
                    }
                    ReservaF=int(FILIN-64);
                    if(matriz[ReservaF-1][ReservaC-1]!=0){
                        cout<<"Asiento ya reservado"<<endl;
                    }
                    else
                        matriz[ReservaF-1][ReservaC-1]=1;
                    ban=false;
                }
                }
            }

        }
    cout<<"Tu combo sera enviado a dicho puesto"<<endl;
}

void cinecito::reportes_ventas(string dia,string nombre,string venta){ //Funcion para guardar las ventas en un txt
    string txt="reportes.txt";
    string texto;
    texto=leer_txt(txt);
    texto.append(dia);
    texto.append(" ");
    texto.append(nombre);
    texto.append(" $");
    texto.append(venta);
    texto.append("\n");
    escribir_txt(texto,txt); //Se almacena en texto
}

void cinecito::leer_reportes(){        //Funcion para imprimir los reportes
    cout<<"REPORTES DE VENTA"<<endl;   //muy basica
    string txt="reportes.txt";
    string Text=leer_txt(txt);
    cout<<Text<<endl;
}
