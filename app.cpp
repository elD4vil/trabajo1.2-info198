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

int opciones(vector<int> user);
bool numeroEstaEnVector(const vector<string>& vectorNumeros, const string& numero);
void sumatoriaVector(const char* valor);
void promedioVector(const char* valor);
void modaVector(const char* valor); 
void contarElem(const char* valor);
void crearArchivo(const string &ubicacion);
void agregarTexto(const string &ubicacion, const string &texto);
bool textoExisteEnArchivo(const string &ubicacion, const string &texto);

vector<int> mostrarop(vector<int> user);

int main(int argc, char *argv[]){
    int opcion;
    int seleccionada;
    string usuario,ubicacion,anadir;
    const char* valor;
    while ((opcion = getopt(argc, argv, "u:v:f:t:")) != -1) {
        switch (opcion) {
            case 'u':
                usuario = optarg;
                break;
            case 'v':
                valor = optarg;
                break;
             case 'f':
                ubicacion = optarg;
                break;
            case 't':
                anadir = optarg;
                break;
            default:
                cerr << "Uso: " << argv[0] << " -u usuario -v valor -f ubicacion -t añadir" << endl;
                return 1;
        }
    }
    

    ifstream file("basededatos.txt");
    if (!file.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }

    bool encontrarUsuario = false;
    string line;
    vector<int> numeros;
    while (getline(file, line)) {
        size_t pos = line.find(usuario);
        if (pos != string::npos) {
                string numerosStr = line.substr(pos + usuario.length() + 1); 
                istringstream numerosStream(numerosStr);
                int numero;

                while (numerosStream >> numero) {
                    numeros.push_back(numero);
                    char coma;
                    numerosStream >> coma; 
                }

                encontrarUsuario = true;
                break; 
            }
        }

    file.close();


    if (encontrarUsuario) {
        cout << "Usuario encontrado en el archivo." << endl;
    } else {
        cout << "Usuario no registrado en la base de datos." << endl;
        return 1;
    }

     if(numeros.empty()){
        cout << "El usuario no tiene permisos" << endl;
        exit(0);
    }

    cout << "========== Menu de Opciones ==========" << endl;

    vector<int> mapeo1 = mostrarop(numeros);

    cout << "=======================================" << endl;

    bool verdad = true;
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
        }
        else if(seleccionar == 2){
            promedioVector(valor);
        }
        else if(seleccionar == 3){
            modaVector(valor);
        }
        else if(seleccionar == 4){
            contarElem(valor);
        }
        else if(seleccionar == 5){
            crearArchivo(ubicacion);
        }
        else if(seleccionar == 6){
            agregarTexto(ubicacion,anadir);
        }
        else if(seleccionar == 7){
            cout << "La opcion " << seleccionar << " aún no ha sido implementada." << endl;
        }

        cout << "Ingrese otra opcion:";
        cin >> seleccionar;
    }
    cout << "Muchas gracias por usar este programa! Adios!" << endl;


    return 0;
    }

void sumatoriaVector(const char* valor){

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
    int cont = 1;
    for(int i = 0; i < strlen(valor);i++){
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
            return true; // El texto ya existe en el archivo
        }
    }

    return false; // El texto no se encontró en el archivo
}


vector<int> mostrarop(vector<int> user){
     
    ifstream archivo("MenuOpciones.txt");  // Abrir el archivo en modo lectura

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        
    }

    string linea;
    vector<string> palabras;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string palabra;

        getline(ss, palabra, ','); // Leer la primera palabra antes de la coma

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