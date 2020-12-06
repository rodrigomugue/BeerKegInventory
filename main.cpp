/*
*Rodrigo Muñoz Guerrero
*A00572858
*29/11/2020
*/

//Librerias que se utilizarán en el main
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
//Archivo tipo header que se utilizara en el main
#include "Barrel.h"

using namespace std;

//Definimos una variable para los distintos casos del menú
string r;

int main()
{
// Creamos un apuntador a un objeto de tipo clase coldroom
coldroom *coldr = new coldroom();

// Creamos la lista de objetos y le damos atributos a cada uno
coldr->add();

// Se crea un ciclo while para poder utilizar el programa tantas veces se quiera
while (true){
    cout << "WHAT WOULD YOU LIKE TO DO WITH THE DATA?\n 1)SEE INVENTORY 2)SORT 3)SEARCH" << endl;
    cin >> r;
    if (r=="1" || r == "one" || r == "ONE" || r == "see" || r == "SEE" || r == "inventory" || r == "INVENTORY" || r == "see inventory"){
        // Se imprimen los atributos de todos los objetos
        coldr->print();
    }
    else if (r=="2" || r == "two" || r == "sort" || r == "SORT" || r == "TWO"){
        // Se usa la función de ordenamiento de la clase coldroom
        coldr->sort(coldr->add());
    }
    else if (r == "3" || r == "three" || r == "THREE" || r == "search" || r == "SEARCH"){
        // Se hace una busqueda y se imprimen todos los atributos del objeto encontrado
        coldr->get();
    }
    cout << "WOULD YOU LIKE TO DO ANYTHING ELSE WITH THE DATA?" << endl;
    cin >> r;
    if (r == "yes" || r == "YES" || r == "1")
        // Se repite el ciclo while
        continue;
    else{
        // Se interrumpe el ciclo while
        break;
    }
}

// Se borra el objeto tipo coldroom
coldr->clear();
delete coldr;
return 0;
}
