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

int main(int argc, char *argv[]){
    int opcion;
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

    seleccionarOpciones(valor,usuario,mapeo1,ubicacion,anadir,numeros);

    return 0;
    }
