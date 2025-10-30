#include "clases.h"


Enrutador::Enrutador(){
    indice = -1;
    id = "";
    conexiones.push_back(0);conexiones.push_back(0);conexiones.push_back(0);conexiones.push_back(0);
    tabla.push_back(0);tabla.push_back(0);tabla.push_back(0);tabla.push_back(0);
}

Enrutador::Enrutador(int index, string identificador){
    //4 enrutadores inicialmente
    conexiones.push_back(0);conexiones.push_back(0);conexiones.push_back(0);conexiones.push_back(0);
    tabla.push_back(0);tabla.push_back(0);tabla.push_back(0);tabla.push_back(0);
    indice = index;
    id = identificador;
}

int Enrutador::getIndex(){
    return indice;
}

void Enrutador::setIndex(int index){
    indice = index;
}

string Enrutador::getId(){
    return id;
}

void Enrutador::setId(const string identificador){
    id = identificador;
}

void Enrutador::modificarRuta(int costo, int index){
    try {
        conexiones.at(index) = costo;
    } catch (const exception &) {
        cout<< "\nPreocupese si lee esto\n";
    }

}

void Enrutador::agregarRuta(int posicion, int costo){
    conexiones[posicion] = costo;
}

void Enrutador::eliminarRuta(int posicion){
    vect::iterator pos;
    pos = conexiones.begin() + posicion;
    conexiones.erase(pos);
}

vect * Enrutador::retornarConexionesVecinas(){
    return &conexiones;
}

void Enrutador::mostrarConexionesVecinas(vector<string> letras){
    for (const auto &letra:letras){
        cout << letra << " ";
    }
    cout << endl;
    for (const auto i: conexiones){
        cout << i << " ";
    }
    cout << "\n\n";
}

void Enrutador::mostrarTabla(vector<string> letras){
    for (const auto &letra:letras){
        cout << letra << " ";
    }
    cout << endl;
    for (const auto i: tabla){
        cout << i << " ";
    }
    cout << "\n\n";
}

void Enrutador::setTablaEnrutamiento(TablaEnrutamiento tab){
    tabla = (*tab.getCaminos())[indice];            //Get caminos cortos
}

void Enrutador::pushBackConexionesTabla(){
    conexiones.push_back(0);
    tabla.push_back(0);
}

vect Enrutador::getTabla(){
    return tabla;
}

TablaEnrutamiento::TablaEnrutamiento(){
    for (int j = 0; j < 4; j++){
        vect temporal(4);
        for (int i = 0; i< 4;i++){
            temporal[i] = 0;
        }
        conexionesOrg.push_back(temporal);
        caminosCortos.push_back(temporal);
    }
    cantEnrutadores = 4;
}

void TablaEnrutamiento::aggBackConexiones(){
    vect temporal(conexionesOrg.size());
    for (int i = 0 ; i < int (temporal.size()); i++){
        temporal[i] = 0;
    }
    conexionesOrg.push_back(temporal);
    caminosCortos.push_back(temporal);
    for (auto &vect : conexionesOrg){
        vect.push_back(0);
    }
    for (auto &vect : caminosCortos){
        vect.push_back(0);
    }

}

vector<vect> * TablaEnrutamiento::getEnrutadores(){
    return &conexionesOrg;
}

vector<vect> * TablaEnrutamiento::getCaminos(){
    return &caminosCortos;
}

int TablaEnrutamiento::getCantEnrutadores(){
    return cantEnrutadores;
}

void TablaEnrutamiento::aumentarCantEnrutadores(){
    cantEnrutadores++;
}

void TablaEnrutamiento::setEnrutador(vect &conexiones,const int pos){
    int len = conexiones.size();
    for (int i = 0; i < len; i++){
        conexionesOrg[pos][i] = conexiones[i];
    }

}

void TablaEnrutamiento::setConexion(vect &conexiones,const int pos){
    int len = conexiones.size();
    for (int i = 0; i < len; i++){
        conexionesOrg[i][pos] = conexiones[i];
    }
}

void TablaEnrutamiento::eliminarEnrutador(int pos, vector<string> &letras){
    vect *elim = &conexionesOrg[pos],*elimCamino = &caminosCortos[pos];
    vect:: iterator borrar = (*elim).begin(),borrarCamino = (*elimCamino).begin();
    vector<string>::iterator letra = letras.begin()+ pos;
    letras.erase(letra);
    for (int i = 0; i < cantEnrutadores ; i++){
        (*elim).erase(borrar);
        (*elimCamino).erase(borrarCamino);
    }

    cantEnrutadores--;
    auto Elim = (conexionesOrg.begin()) + pos, ElimCamino = (caminosCortos.begin()) + pos;
    conexionesOrg.erase(Elim);
    caminosCortos.erase(ElimCamino);

    for (int i = 0; i < cantEnrutadores ; i++){
        elim = &conexionesOrg[i];
        elimCamino = &caminosCortos[i];
        borrar = (*elim).begin()+pos;
        borrarCamino = (*elimCamino).begin()+pos;
        (*elim).erase(borrar);
        (*elimCamino).erase(borrarCamino);
    }
}

void TablaEnrutamiento::mostrarEnrutadores(vector<string> letras){
    for (auto &letra: letras ){
        cout << "   " << letra;
    }
    vector<string> ::iterator iterador= letras.begin();
    for (const auto &caminoCorto: caminosCortos){
        cout << endl << *iterador << " ";
        *iterador ++;
        for (const auto  objeto: caminoCorto){
            int lenObjt = ((objeto >= 10)|| (objeto < 0)) ? 2:1 ;
            if (lenObjt == 2){
                cout<< " "<< objeto << " ";
            }
            else cout<< "  "<< objeto << " ";
        }
    }
    cout << "\n\n";
}

void TablaEnrutamiento::minDist(){
    vaciarCaminosCortos();
    for (int i = 0; i < cantEnrutadores; i++){
        dijkstra(conexionesOrg,i, caminosCortos);
    }
}


void actualizarTablas(TablaEnrutamiento tabla, vector <Enrutador *> &enrutadores){
    for (auto enrutador : enrutadores){
        (*enrutador).setTablaEnrutamiento(tabla);
    }
}

void TablaEnrutamiento::vaciarCaminosCortos(){
    for (int camino = 0; camino < int (caminosCortos.size()); camino++){
        for (int posicion = 0; posicion < int (caminosCortos[camino].size()); posicion++){
            caminosCortos[camino][posicion] = 0;
        }
    }

}




void menu(){
    vector <string> letras = {"A","B","C","D"};
    Enrutador A(0,"A"),B(1,"B"),C(2,"C"),D(3,"D"),A2, A3,A4,A5;
    vector  <Enrutador * > Enrutadores= {&A,&B,&C,&D}, restantes = {&A2,&A3,&A4,&A5}, total = {&A,&B,&C,&D,&A2,&A3,&A4,&A5};
    Enrutador *& punteroEnrut = restantes.back();

    TablaEnrutamiento rut;
    //Anexo rutas por defecto
    A.agregarRuta(B.getIndex(),4); A.agregarRuta(C.getIndex(),10);
    B.agregarRuta(A.getIndex(),4); B.agregarRuta(D.getIndex(),1);
    C.agregarRuta(A.getIndex(),10); C.agregarRuta(D.getIndex(),2);
    D.agregarRuta(C.getIndex(),2); D.agregarRuta(B.getIndex(),1);
    //Anexo de rutas conocidas a la tabla
    rut.setEnrutador(*A.retornarConexionesVecinas(),A.getIndex());
    rut.setEnrutador(*B.retornarConexionesVecinas(),B.getIndex());
    rut.setEnrutador(*C.retornarConexionesVecinas(),C.getIndex());
    rut.setEnrutador(*D.retornarConexionesVecinas(),D.getIndex());
    //Mostrar enrutadores en la tabla de enrutamiento
    //rut.mostrarEnrutadores(letras);
    //Establecer tablas de enrutamiento para cada enrutador
    rut.minDist();
    actualizarTablas(rut,Enrutadores);

    int opcion = 0;
    while (opcion != 5){
        cout << "\nIngrese una opción."
                "\n1. Agregar enrutador."
                "\n2. Eliminar enrutador."
                "\n3. Mostrar conexiones más cortas de toda la red."
                "\n4. Mostrar costo entre par de enrutadores."
                "\n5. Salir."
                "\nOpcion: ";
        cin >> opcion;
        switch(opcion){
        case 1:
            for(auto enrut : Enrutadores){
                enrut->pushBackConexionesTabla();
            }
            for(auto enrut : restantes){
                enrut->pushBackConexionesTabla();
            }
            punteroEnrut = restantes.back();
            agregar(&letras, &Enrutadores, *punteroEnrut);
            rut.aggBackConexiones();
            rut.setEnrutador(*punteroEnrut->retornarConexionesVecinas(),punteroEnrut->getIndex());
            rut.setConexion(*punteroEnrut->retornarConexionesVecinas(),punteroEnrut->getIndex());
            Enrutadores.push_back(punteroEnrut);
            restantes.pop_back();
            rut.aumentarCantEnrutadores();
            rut.minDist();
            actualizarTablas(rut,Enrutadores);
            setTablas(&Enrutadores, rut);
            break;
        case 2:
            eliminar(&Enrutadores, &letras, &rut, &restantes);
            rut.minDist();
            actualizarTablas(rut,Enrutadores);
            setTablas(&Enrutadores, rut);
            break;
        case 3:
            rut.mostrarEnrutadores(letras);
            break;
        case 4:
            mostrarCosto(&Enrutadores);
            break;
        case 5:
            system("cls");
            cout << "\nHasta pronto";
            break;
        default:
            cout << "\nOpción inválida.";
            break;
        }
    }


}

void eliminar(vector<Enrutador *> *Enrutadores, vector<string> *letras, TablaEnrutamiento *rut,vector<Enrutador *> *restantes){
    vector <Enrutador *>:: iterator iteradorEnrut = (*Enrutadores).begin();
    bool validacion = false ;
    string ingresado;
    while (validacion != true){
        cout << "\nIngrese el nombre del enrutador que desea eliminar: ";
        cin >> ingresado;
        for (auto enrutador : (*Enrutadores)){
            if ((*enrutador).getId() == ingresado){
                validacion = true;
                (*rut).eliminarEnrutador((*enrutador).getIndex(),*letras);
                (*Enrutadores).erase(iteradorEnrut+(*enrutador).getIndex());
                (*rut).minDist();
                for (auto router : (*Enrutadores)){
                    if(router->getIndex()>=(*enrutador).getIndex()){
                        router->setIndex(router->getIndex()-1);
                        (*router).setTablaEnrutamiento(*rut);
                    }
                    else
                        (*router).setTablaEnrutamiento(*rut);
                    router->eliminarRuta((*enrutador).getIndex());
                }
                for (auto restante : *restantes){
                    restante->eliminarRuta((*enrutador).getIndex());
                }
                enrutador->eliminarRuta(0);
                restantes->push_back(enrutador);
                break;
            }
            if (validacion == false) system("cls");
        }
        if (validacion != true)
            cout << "\nEnrutador no encontrado";
    }
}

void agregar(vector<string> *letras, vector<Enrutador *> *Enrutadores, Enrutador &punteroEnrut){
    string id;
    vector <Enrutador *>:: iterator iteradorEnrut = (*Enrutadores).begin();
    Enrutador * punteroDestino;
    cout <<"\nIngrese el nombre del enrutador: ";
    cin >> id;
    punteroEnrut.setIndex(Enrutadores->size());
    punteroEnrut.setId(id);
    for(const auto &letra:*letras){
        int costo;
        cout <<"\nIngrese el costo al enrutador " << letra << "\nEn "
                                                               "caso de que no tenga conexión directa ingrese 0 \nCosto: ";
        cin >> costo;
        punteroEnrut.agregarRuta((*iteradorEnrut)->getIndex(),costo);      //Agregar el costo de la ruta directa para ese enrutador
        if(costo > 0){
            try {
                punteroDestino = Enrutadores->at((*iteradorEnrut)->getIndex());
                punteroDestino->agregarRuta(punteroEnrut.getIndex(),costo);
            } catch (const exception &) {
                cout << "\nSigue";
            }
        }
        iteradorEnrut++;
    }
    punteroEnrut.agregarRuta((punteroEnrut.getIndex()),0);
    (letras)->push_back(id);
}

void setTablas(vector<Enrutador *> *Enrutadores, TablaEnrutamiento rut){
    for (auto enrut : *Enrutadores){
        enrut->setTablaEnrutamiento(rut);
    }
}

void mostrarCosto(vector<Enrutador *> *Enrutadores){
    string idOrg, idDest;
    bool validacion = false;
    while (validacion != true){
        cout << "\nIngrese el nombre del enrutador origen: ";
        cin >> idOrg;
        for (auto enrut : *Enrutadores){
            if(enrut->getId() == idOrg){
                while (validacion != true) {
                    cout << "\nIngrese el nombre del enrutador destino: ";
                    cin >> idDest;
                    for (auto enrutDest : *Enrutadores){
                        if (enrutDest->getId() == idDest){
                            try {
                                cout << "\nEl costo de " <<enrut->getId()<< " a "<<
                                    enrutDest->getId() << " es: "<<
                                    (enrut->getTabla()).at(enrutDest->getIndex())<< endl;
                                validacion = true;
                            } catch (const exception &) {
                                cout << "\nValor fuera de rango, no se cuenta con la información";
                            }
                            break;
                        }
                    }
                    if (validacion != true){
                        system("cls");
                        cout << "\nNo se ha encontrado un enrutador con ese identificador";
                    }
                }
                break;
            }
        }
        if (validacion != true){
            system("cls");
            cout << "\nNo se ha encontrado un enrutador con ese identificador";
        }

    }
}











void redDesdeTexto(vector<Enrutador *> *Enrutadores, vector<string> *letras,
                   vector<Enrutador *> *restantes, vector<Enrutador *> *total) {
    ifstream archivo;
    vector<Enrutador *> temporales;
    Enrutadores->clear(), letras->clear(),restantes->clear();
    int indice = 0;
    vector <string> lineas;
    Enrutador *& punteroEnrut = total->back();
    try {
        archivo.open("Conexiones.txt", ios::in);
    } catch (const exception &) {
        cout << "\nNo ha sido posible abrir el archivo\n";
        return ;
    }
    while(!archivo.eof()){
        string temp, substring;
        getline(archivo,temp,'\n');
        punteroEnrut = total->back();
        total->pop_back();
        temporales.push_back(punteroEnrut);
        substring = temp[0];
        punteroEnrut->setId(substring), letras->push_back(substring), punteroEnrut->setIndex(indice);
        indice++;
        substring = temp.substr(3,temp.size()-3);
        lineas.push_back( substring);
    }
    for (auto &linea: lineas){
        punteroEnrut = *temporales.begin();
        string substring2, substring, nombre;
        for (int  j = 0; j < ceil(linea.size()/4 ); j++){    //Cant de bloques
            substring2 = linea.substr(4*j,4);
            for (auto caracter : substring2){
                if(isdigit(caracter)) substring += caracter;       //substr asume el costo en string
                else if(isalpha(caracter)) nombre += caracter;
            }
            for (auto &enrut : temporales){
                if (enrut->getId() == nombre){
                    punteroEnrut->agregarRuta(enrut->getIndex(),stoi(substring));
                    vector <Enrutador *>:: iterator iteradorEnrut = (temporales).begin() + enrut->getIndex() ;
                    temporales.erase(iteradorEnrut);
                    Enrutadores->push_back(punteroEnrut);
                }
            }
        }
    }
    for (auto enrut : *total){
        restantes->push_back(enrut), total->pop_back();
    }
}

/*
redDesdeTexto(&Enrutadores,&letras, &restantes, &total);
for (auto enrut : Enrutadores){
    rut.setEnrutador(*enrut->retornarConexionesVecinas(),enrut->getIndex());
}
rut.minDist();
actualizarTablas(rut,Enrutadores);
*/
