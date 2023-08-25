#include "funciones.h"
#include <iostream> 
#include <unistd.h>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void sumatoriaVector(const char* valor) {

    const char* valor2 = valor;

    if(strlen(valor2) == 0){
        cout << "No ingreso correctamente el vector" << endl;
        return;
    }

    while (*valor2) {
        if (*valor2 == ',') {
            ++valor2;
        }
        if (!isdigit(*valor2)) {
            cout << "No ingreso correctamente el vector" << endl;
            return;
        }
        ++valor2;
    }


    int suma = 0;

    char* copiaValor = strdup(valor);
    char* token = strtok(copiaValor, ",");
    
    while (token != nullptr) {
        suma += atoi(token);
        token = strtok(nullptr, ",");
    }

    free(copiaValor);

    cout << "La sumatoria es: " << suma << endl;
}

void promedioVector(const char* valor){

    const char* valor2 = valor;

    if(strlen(valor2) == 0){
        cout << "No ingreso correctamente el vector" << endl;
        return;
    }

    while (*valor2) {
        if (*valor2 == ',') {
            ++valor2;
        }
        if (!isdigit(*valor2)) {
            cout << "No ingreso correctamente el vector" << endl;
            return;
        }
        ++valor2;
    }

    
    int sum = 0;
    int count = 0;

    int numInicio = 0;
    for (int i = 0; valor[i] != '\0'; ++i) {
        if (valor[i] == ',') {
            int num = stoi(string(valor + numInicio, i - numInicio));
            sum += num;
            numInicio = i + 1;
            count++;
        }
    }
    
    int num = stoi(string(valor + numInicio));
    sum += num;
    count++;

    if (count > 0) {
        float promedio = static_cast<float>(sum) / count;
        cout << "El promedio es: " << promedio << endl;
    } else {
        cout << "No se encontraron números en la cadena." << endl;
    }
}


void modaVector(const char* valor ){

    const char* valor2 = valor;

    if(strlen(valor2) == 0){
        cout << "No ingreso correctamente el vector" << endl;
        return;
    }

    while (*valor2) {
        if (*valor2 == ',') {
            ++valor2;
        }
        if (!isdigit(*valor2)) {
            cout << "No ingreso correctamente el vector" << endl;
            return;
        }
        ++valor2;
    }
    
    map<int, int> frecuencia; 

    int numInicio = 0;
    for (int i = 0; valor[i] != '\0'; ++i) {
        if (valor[i] == ',') {
            int num = stoi(string(valor + numInicio, i - numInicio));
            frecuencia[num]++;
            numInicio = i + 1;
        }
    }
    
    int num = stoi(string(valor + numInicio));
    frecuencia[num]++;

    int moda = 0;  
    int maxfrecuencia = 0;

    for (const auto& pair : frecuencia) {
        if (pair.second > maxfrecuencia) {
            maxfrecuencia = pair.second;
            moda = pair.first;
        }
    }

    if (maxfrecuencia > 1) {
        cout << "La moda es: " << moda << endl;
    } else {
        cout << "No hay moda en los números." << endl;
    }


}

void contarElem(const char* valor){
    
    const char* valor2 = valor;

    if(strlen(valor2) == 0){
        cout << "No ingreso correctamente el vector" << endl;
        return;
    }

    while (*valor2) {
        if (*valor2 == ',') {
            ++valor2;
        }
        if (!isdigit(*valor2)) {
            cout << "No ingreso correctamente el vector" << endl;
            return;
        }
        ++valor2;
    }

    int cont = 1;
    for(size_t i = 0; i < strlen(valor);i++){
        if(valor[i] == ',')
            cont++;
    }

    cout << "Se ingresaron " << cont << " elementos" << endl;
}


void crearArchivo(const string &ubicacion) {
    ifstream archivoExistente(ubicacion);
    if (archivoExistente) {
        cout << "El archivo ya existe en la ubicación proporcionada." << endl;
    } else {
        ofstream nuevoArchivo(ubicacion);
        if (nuevoArchivo) {
            cout << "Archivo creado exitosamente en la ubicación: " << ubicacion << endl;
        } else {
            cerr << "No se pudo crear el archivo en la ubicación: " << ubicacion << endl;
        }
    }
}

void agregarTexto(const string &ubicacion, const string &texto) {
    ifstream archivoExistente(ubicacion);
    if (!archivoExistente) {
        cout << "El archivo no existe en la ubicación proporcionada." << endl;
    }

    ofstream archivoAgregar(ubicacion, ios::app);
    if (textoExisteEnArchivo(ubicacion, texto)) {
        cout << "El texto ya existe en el archivo." << endl;
        archivoAgregar << texto << endl;
    } else {
        if (archivoAgregar) {
            archivoAgregar << texto << endl;
            cout << "Texto agregado exitosamente al archivo: " << texto << endl;
        } else {
            cerr << "No se pudo agregar el texto al archivo." << endl;
        }
    }
}

bool textoExisteEnArchivo(const string &ubicacion, const string &texto) {
    ifstream archivo(ubicacion);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return false;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea == texto) {
            return true; 
        }
    }

    return false;
}


vector<int> mostrarop(vector<int> user){
     
    ifstream archivo("MenuOpciones.txt"); 

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        
    }

    string linea;
    vector<string> palabras;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string palabra;

        getline(ss, palabra, ',');
        while (getline(ss, palabra, ',')) {
            palabras.push_back(palabra);
        }
    }

    archivo.close();

    int j = 0;
    vector<int> mapeo;
    
    cout << "0) " << palabras[0] << endl;
    for (size_t i = 0; i < palabras.size(); i=i+2) {
        if(find(user.begin(), user.end(), i/2) != user.end()){
            cout << j << ") " << palabras[i] << endl;
            mapeo.push_back(stoi(palabras[i+1]));
        }
        j++;
    }
    return mapeo;
}

void seleccionarOpciones(const char* valor, string usuario, vector<int> mapeo1, string ubicacion, string anadir, vector<int> user){
    bool verdad = true;
    int acc = 0;
    int seleccionar;
    cout << "Ingrese el número de una de las opciónes: ";
    cin >> seleccionar;
    while(seleccionar != 0){
        while(verdad){
            if(seleccionar == 0){
                cout << "Muchas gracias por usar este programa! Adios!" << endl;
                exit(0);
            }
            if(find(mapeo1.begin(), mapeo1.end(), seleccionar) != mapeo1.end()){
                verdad = false;
            }
            else { 
                cout << "Opcion no disponible, seleccione otra opcion: ";
                cin >>seleccionar;
            }
        }
        if(seleccionar == 1){
            sumatoriaVector(valor);
            acc++;
        }
        else if(seleccionar == 2){
            promedioVector(valor);
            acc++;
        }
        else if(seleccionar == 3){
            modaVector(valor);
            acc++;
        }
        else if(seleccionar == 4){
            contarElem(valor);
            acc++;
        }
        else if(seleccionar == 5){
            crearArchivo(ubicacion);
            acc++;
        }
        else if(seleccionar == 6){
            agregarTexto(ubicacion,anadir);
            acc++;
        }
        else if(seleccionar >= 7){
            cout << "La opcion " << seleccionar << " aún no ha sido implementada." << endl;
            acc++;
        }

        if (acc == 5){
            cout << "Presiona Enter para limpiar la pantalla y mostrar el menú nuevamente..." << endl;
            cin.ignore();
            system("clear");
            cout << "========== Menu de Opciones ==========" << endl;
            mapeo1 = mostrarop(user);
            cout << "=======================================" << endl;
            acc = 0;
        }
        cout << "Ingrese otra opcion:";
        cin >> seleccionar;
    }
    cout << "Muchas gracias por usar este programa! Adios!" << endl;

}