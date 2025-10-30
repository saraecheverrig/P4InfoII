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
    vector<string> letras = {"A","B","C","D"};
    Enrutador A(0,"A"), B(1,"B"), C(2,"C"), D(3,"D"), A2, A3, A4, A5;
    vector<Enrutador*> Enrutadores = {&A,&B,&C,&D};
    vector<Enrutador*> restantes  = {&A2,&A3,&A4,&A5};
    vector<Enrutador*> total      = {&A,&B,&C,&D,&A2,&A3,&A4,&A5};
    Enrutador *& punteroEnrut = restantes.back();

    TablaEnrutamiento rut;

    // Cargar topología desde archivo en lugar de definir manualmente
    // redDesdeTexto llenará Enrutadores, letras y restantes usando "total"
    generarRedAleatoria(4);

    redDesdeTexto(&Enrutadores, &letras, &restantes, &total);
    // Reconstruir 'letras' a partir de Enrutadores para que coincida con la matriz
    letras.clear();
    for (auto e : Enrutadores) {
        letras.push_back(e->getId());
    }

    // Reconstruir la TablaEnrutamiento con la información actual y recalcular
    // (el resto del código ya hace rut.setEnrutador / rut.minDist / actualizarTablas)
    rut = TablaEnrutamiento();
    for (auto enrut : Enrutadores) {
        rut.setEnrutador(*enrut->retornarConexionesVecinas(), enrut->getIndex());
    }
    rut.minDist();
    actualizarTablas(rut, Enrutadores);
    setTablas(&Enrutadores, rut);

    if (Enrutadores.empty()){
        cout << "No se cargó ninguna topología desde Conexiones.txt o el archivo está vacío.\n";
        // La red queda vacía; el menú seguirá permitiendo agregar enrutadores manualmente.
    } else {
        // Rellenar la TablaEnrutamiento con las conexiones leídas
        for (auto enrut : Enrutadores){
            rut.setEnrutador(*enrut->retornarConexionesVecinas(), enrut->getIndex());
        }
        // Calcular caminos y actualizar tablas locales
        rut.minDist();
        actualizarTablas(rut, Enrutadores);
        setTablas(&Enrutadores, rut);
    }

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
            // Actualizar puntero al siguiente disponible y usarlo para agregar
            if (!restantes.empty()){
                punteroEnrut = restantes.back();
                agregar(&letras, &Enrutadores, *punteroEnrut);
                rut.aggBackConexiones();
                rut.setEnrutador(*punteroEnrut->retornarConexionesVecinas(), punteroEnrut->getIndex());
                rut.setConexion(*punteroEnrut->retornarConexionesVecinas(), punteroEnrut->getIndex());
                Enrutadores.push_back(punteroEnrut);
                restantes.pop_back();
                rut.aumentarCantEnrutadores();
                rut.minDist();
                actualizarTablas(rut, Enrutadores);
                setTablas(&Enrutadores, rut);
            } else {
                cout << "No hay enrutadores disponibles para agregar (restantes vacío).\n";
            }
            break;
        case 2:
            eliminar(&Enrutadores, &letras, &rut, &restantes);
            // después de eliminar, recalcular y actualizar
            rut.minDist();
            actualizarTablas(rut, Enrutadores);
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
    Enrutadores->clear();
    letras->clear();
    restantes->clear();
    vector<Enrutador *> temporales;
    vector<string> lineas;

    try {
        archivo.open("ConexionesAle.txt", ios::in);
        if (!archivo.is_open()) {
            cout << "\nNo ha sido posible abrir el archivo Conexiones.txt\n";
            return;
        }
    } catch (...) {
        cout << "\nNo ha sido posible abrir el archivo\n";
        return;
    }

    string temp;
    while (std::getline(archivo, temp)) {
        // quitar '\r' si existe (Windows)
        if (!temp.empty() && temp.back() == '\r') temp.pop_back();
        // trim simple
        size_t start = temp.find_first_not_of(" \t");
        if (start == string::npos) continue;
        size_t end = temp.find_last_not_of(" \t");
        string line = temp.substr(start, end - start + 1);
        if (!line.empty()) lineas.push_back(line);
    }
    archivo.close();

    // Crear enrutadores temporales (sacando objetos de 'total')
    int indice = 0;
    for (const auto &line : lineas) {
        if (total->empty()) {
            cout << "Error: no hay suficientes objetos Enrutador en 'total' para cubrir las líneas del archivo\n";
            // limpiar temporales ya usados: devolverlos a `total` podría ser una mejora, pero aquí abortamos.
            return;
        }
        Enrutador *punteroEnrut = total->back();
        total->pop_back();
        // establecer id e índice
        size_t colon = line.find(':');
        if (colon == string::npos || colon == 0) {
            cout << "Línea con formato inválido (se esperaba 'ID:lista'): " << line << "\n";
            return;
        }
        string id = line.substr(0, colon);
        // trim id
        size_t idStart = id.find_first_not_of(" \t");
        size_t idEnd = id.find_last_not_of(" \t");
        string idTrim = (idStart == string::npos) ? id : id.substr(idStart, idEnd - idStart + 1);

        punteroEnrut->setId(idTrim);
        punteroEnrut->setIndex(indice);
        letras->push_back(idTrim);

        temporales.push_back(punteroEnrut);
        indice++;
    }

    // Para cada línea (mismo orden), procesar su parte de conexiones
    for (size_t idx = 0; idx < lineas.size(); ++idx) {
        Enrutador *origen = temporales[idx];
        const string &line = lineas[idx];
        size_t colon = line.find(':');
        if (colon == string::npos) continue;
        string connections = (colon + 1 < line.size()) ? line.substr(colon + 1) : string();
        // separar por comas
        size_t pos = 0;
        while (pos < connections.size()) {
            size_t comma = connections.find(',', pos);
            string token = (comma == string::npos) ? connections.substr(pos) : connections.substr(pos, comma - pos);
            pos = (comma == string::npos) ? connections.size() : comma + 1;

            // trim token
            size_t tstart = token.find_first_not_of(" \t");
            if (tstart == string::npos) continue;
            size_t tend = token.find_last_not_of(" \t");
            token = token.substr(tstart, tend - tstart + 1);
            if (token.empty()) continue;

            // separar nombre y número
            string nombre; string numero;
            for (char ch : token) {
                if (isalpha((unsigned char)ch)) nombre.push_back(ch);
                else if (isdigit((unsigned char)ch) || ch == '-') numero.push_back(ch);
            }
            if (nombre.empty() || numero.empty()) continue;

            // buscar el enrutador destino en temporales (NO eliminarlo)
            Enrutador *dest = nullptr;
            for (auto cand : temporales) {
                if (cand->getId() == nombre) { dest = cand; break; }
            }
            if (!dest) {
                cout << "Advertencia: destino '" << nombre << "' no encontrado entre los routers leídos.\n";
                continue;
            }

            int costo = 0;
            try { costo = stoi(numero); } catch (...) {
                cout << "Costo inválido en token: " << token << "\n";
                continue;
            }
            origen->agregarRuta(dest->getIndex(), costo);
        }
    }

    // Agregar todos los temporales al vector final Enrutadores (manteniendo orden)
    for (auto p : temporales) Enrutadores->push_back(p);

    // Mover lo que quede en total a restantes
    while (!total->empty()) {
        restantes->push_back(total->back());
        total->pop_back();
    }
}

void generarRedAleatoria(int N, double p, int minCost, int maxCost, const string &filename) {
    if (N <= 0) return;
    if (minCost > maxCost) swap(minCost, maxCost);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> prob(0.0, 1.0);
    uniform_int_distribution<> cost(minCost, maxCost);

    vector<string> names;
    for (int i = 0; i < N; ++i) {
        if (i < 26) names.push_back(string(1, char('A' + i)));
        else names.push_back("A" + to_string(i - 26));
    }

    vector<vector<int>> adj(N, vector<int>(N, -1));
    for (int i = 0; i < N; ++i) adj[i][i] = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            if (prob(gen) <= p) {
                int c = cost(gen);
                adj[i][j] = c;
                adj[j][i] = c;
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        bool tieneVecino = false;
        for (int j = 0; j < N; ++j) if (j != i && adj[i][j] >= 0) { tieneVecino = true; break; }
        if (!tieneVecino) {
            int j = i;
            while (j == i) j = gen() % N;
            int c = cost(gen);
            adj[i][j] = c;
            adj[j][i] = c;
        }
    }

    for (int i = 0; i + 1 < N; ++i) {
        if (adj[i][i+1] < 0) {
            int c = cost(gen);
            adj[i][i+1] = c;
            adj[i+1][i] = c;
        }
    }

    ofstream ofs(filename, ios::out);
    if (!ofs.is_open()) return;

    for (int i = 0; i < N; ++i) {
        ofs << names[i] << ":";
        bool first = true;
        for (int j = 0; j < N; ++j) {
            if (i == j) continue;
            if (adj[i][j] >= 0) {
                if (!first) ofs << ",";
                ofs << names[j] << adj[i][j];
                first = false;
            }
        }
        ofs << "\n";
    }
    ofs.close();
}
