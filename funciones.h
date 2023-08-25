#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include <vector>

void sumatoriaVector(const char* valor);
void promedioVector(const char* valor);
void modaVector(const char* valor);
void contarElem(const char* valor);
void crearArchivo(const std::string &ubicacion);
void agregarTexto(const std::string &ubicacion, const std::string &texto);
bool textoExisteEnArchivo(const std::string &ubicacion, const std::string &texto);
std::vector<int> mostrarop(std::vector<int> user);
void seleccionarOpciones(const char* valor, std::string usuario, std::vector<int> mapeo1, std::string ubicacion, std::string anadir, std::vector<int> user);

#endif
