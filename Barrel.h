/*
*Rodrigo Muñoz Guerrero
*A00572858
*29/11/2020
*/

//Librerias que se utilizarán en el programa
#ifndef BARREL_H_INCLUDED
#define BARREL_H_INCLUDED
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Se crea la clase kegs que representa los vértices de la lista
class kegs{
private:
    string name, style, brewery;
    int price, lt, pint;
    kegs();
    kegs(string name, string style, string brewery, int price, int lt, int pint);
    kegs *next;
    kegs *prev;
    friend class coldroom;
};

// Constructor por default, se definen los apuntadores del nodo anterior y siguiente en 0
kegs::kegs() : prev(0), next(0) {}

// Constructor completo donde se le asignan valores a sus atributos
kegs::kegs(string name_, string style_, string brewery_, int price_, int lt_, int pint_){
    name_ = name;
    style_ = style;
    brewery_ = brewery;
    price_ = price;
    lt_ = lt;
    pint_ = pint;
}

// Se crea la clase coldroom que representa la lista de objetos
class coldroom{
private:
    kegs *head;
    kegs *tail;
    int size;
public:
    coldroom();
    ~coldroom();
    vector<vector<string>> read();
    vector<kegs> add();
    void get();
    void sort(const vector<kegs>&);
    void clear();
    void print();
    void printbeer(kegs *);
    void swap(vector<kegs>&, int, int);
};

// Constructor por default de la clase
coldroom::coldroom() : size(0), head(0), tail(0) {}

// Destructor por default del objeto tipo clase coldroom
coldroom::~coldroom() {
    clear();
}

/*
* Función que lee el archivo de texto donde se tienen los datos de los barriles de cerveza y
* crea una matriz de variables tipo string.
* O(n) ya que hace un ciclo por cada uno de los elementos de la lista de barriles o
* en otras palabras, de filas en la matriz.
*/
vector<vector<string>> coldroom::read() {
    string line, filein;
    vector<vector<string>> dl;
    filein = "sign.txt";
    ifstream myfile(filein);
    if (myfile.is_open()){
        while (getline(myfile,line)){
            vector<string> v;
            stringstream auxi;
            auxi << line;
            string a, b, c, d, e, f;
            auxi >> a >> b >> c >> d >> e >> f;
            v.push_back(a);
            v.push_back(b);
            v.push_back(c);
            v.push_back(d);
            v.push_back(e);
            v.push_back(f);
            dl.push_back(v);
        }
        myfile.close();
    }
    else{
        cout << "UNABLE" << endl;
    }
    return dl;
}

/*
* Esta funcion utiliza la matriz creada en la funcion read() para crear los objetos
* de tipo kegs ó, ingresa los datos de cada barril de cerveza. A la vez que crea
* los objetos, crea la lista doblemente dirigida con cada nodo siendo un objeto tipo kegs.
* Complejidad O(n) ya que hace un ciclo for del tamaño de la lista de objetos o en otras
* palabras, del número de filas en la matriz.
*/
vector<kegs> coldroom::add(){
    kegs *NewKeg;
    vector<kegs> Tap;
    vector<vector<string>> dl = read();
    int sze = dl.size();
    for (int i=1;i<(sze);i++){
            NewKeg = new kegs();
            NewKeg->name = dl[i][0];
            NewKeg->style = dl[i][1];
            NewKeg->brewery = dl[i][2];
            NewKeg->price = stoi(dl[i][3]);
            NewKeg->lt = stoi(dl[i][4]);
            NewKeg->pint = stoi(dl[i][5]);
            if (i == 1){
                head = NewKeg;
                tail = NewKeg;
            }
            else{
                tail->next = NewKeg;
                NewKeg->prev = tail;
                tail = NewKeg;
            }
            Tap.push_back(*NewKeg);
            size++;
    }
    return Tap;
}

/*
* Esta funcion borra todos los elementos de la lista con la operación "delete"
* porque son objetos creados en el heap con la operación "new"
* Complejidad O(n) ya que hace lo mismo para cada objeto de la lista.
*/
void coldroom::clear(){
    kegs *p, *q;
    p = head;
    while (p!=0){
        q = p-> next;
        delete p;
        p = q;
    }
    head = 0;
    size = 0;
}

/*
* Función que imprime la matriz creada con la funcion read()
* Complejidad O(n*a) siendo "a" los atributos de los objetos ya que sigue dos ciclos for anidados
* en los que uno pasa por cada fila y el ciclo interno, por cada columna y cada columna representa
* un atributo del objeto.
*/
void coldroom::print(){
    int i = 0;
    vector<vector<string>> dl = read();
    for (vector<string> v : dl){
        if (i == 0){
            cout << "NUM    ";
        }
        else{
        cout << i << "  ";
        }
        for (string data : v){
            cout << data << "   ";
        }
        cout << endl;
        i++;
    }
}

/*
* Funcion auxiliar para la funcion sort, intercambia un objeto por otro dados sus índices
* en el vector.
* Complejidad O(1) porque solo se definen variables directas, no se tienen ciclos.
*/
void coldroom::swap(vector<kegs> &v,int i, int j){
    kegs aux;
    aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

/*
* Funcion que utiliza el método de ordenamiento de burbuja dependiendo el atributo
* que el usuario ingresa ya sea el precio o el tamaño del vaso en que se sirve.
* La funcion tambien crea un archivo llamado "sort.txt" donde imprime el nuevo
* orden de los objetos con sus atributos después de ser ordenado.
* Complejidad O(n^2) por el proceso de ordenamiento de burbuja.
*/
void coldroom::sort(const vector<kegs> &source){
    vector<kegs> v(source);
    int pos;
    string re;
    cout << "ON WHAT DATA TYPE WOULD YOU LIKE TO SORT THE DATA?\n 1)PRICE 2)PINT SIZE" << endl;
	cin >> re;
	if (re == "1" || re == "one" || re == "ONE"){
        for (int i = v.size()-1; i>0 ; i--){
            pos = 0;
            for (int j=1 ; j<=i; j++){
                if (v[j].price >= v[pos].price){
                    pos = j;
                }
            }
            if (pos!=i){
                swap(v, i, pos);
            }
        }
	}
	else if (re == "2" || re == "two" || re == "TWO"){
	    for (int i = v.size()-1; i>0 ; i--){
            pos = 0;
            for (int j=1 ; j<=i; j++){
                if (v[j].pint >= v[pos].pint){
                    pos = j;
                }
            }
            if (pos!=i){
                swap(v, i, pos);
            }
        }
	}
	ofstream myfileout("sort.txt");
	if (myfileout.is_open()){
    cout << "NUM    BEER    STYLE    BREWERY     PRICE     KEG LT    PINT/ML\n";
    myfileout << "NUM    BEER    STYLE    BREWERY     PRICE     KEG LT    PINT/ML\n";
    for (int i = 0; i<= v.size()-1; i++){
        cout << i << "  ";
        myfileout << i << "  ";
        cout << v[i].name << "   " << v[i].style << "   " << v[i].brewery << "   ";
        cout << v[i].price << "   " << v[i].lt << "   " << v[i].pint << endl;
        myfileout << v[i].name << "   " << v[i].style << "   " << v[i].brewery << "   ";
        myfileout << v[i].price << "   " << v[i].lt << "   " << v[i].pint << endl;
    }
	myfileout.close();
	}
	else {
        cout << "FILE NOT FOUND" << endl;
	}
}

// Esta funcion imprime los atributos de un objeto ingresado. Auxiliar de get().
// Complejidad O(1) ya que solo son impresiones y no hay ciclos.
void coldroom::printbeer(kegs *p){
    cout << "NAME: " << p->name << endl;
    cout << "STYLE: " << p->style << endl;
    cout << "BREWERY: " << p->brewery << endl;
    cout << "PRICE: " << p->price << endl;
    cout << "KEG LT: " << p->lt << endl;
    cout << "PINT ML: " << p->pint << endl;
}

/*
* Funcion que busca un atributo en específico entre los objetos de la lista.
* Se define el tipo de atributo que se quiere y se ingresa el valor del atributo
* y el programa recorre la lista hasta encontrar al objeto con ese valor de atributo.
* Complejidad O(n) ya que en el peor caso, recorre toda la lista si es que el atributo
* lo tiene el último objeto o si no existe un objeto con ese valor de atributo.
*/
void coldroom::get(){
    int pos, resp, f = 0;
    kegs *p;
    print();
    cout << "WHAT ATTRIBUTE WOULD YOU LIKE TO SEARCH?\n 1)NAME 2)STYLE 3)BREWERY 4)PRICE" << endl;
    cin >> resp;
    p = head;
    if (resp == 1){
        string a;
        cout << "WHAT IS THE BEER'S NAME?" << endl;
        cin >> a;
        while (p!=0){
            if (p->name == a){
                printbeer(p);
                f = 1;
                break;
            }
            p = p->next;
        }
        if (f == 0){
            cout << "BEER NOT FOUND" << endl;
        }
    }
    else if (resp == 2){
        string a;
        cout << "WHAT IS THE BEER'S STYLE?" << endl;
        cin >> a;
        while (p!=0){
            if (p->style == a){
                printbeer(p);
                f = 1;
                break;
            }
            p = p->next;
        }
        if (f == 0){
            cout << "BEER NOT FOUND" << endl;
        }
    }
    else if (resp == 3){
        string a;
        cout << "WHAT IS THE BEER'S BREWERY?" << endl;
        cin >> a;
        while (p!=0){
            if (p->brewery == a){
                printbeer(p);
                f = 1;
                break;
            }
            p = p->next;
        }
        if (f == 0){
            cout << "BEER NOT FOUND" << endl;
        }
    }
    else if (resp == 4){
        int a;
        cout << "WHAT IS THE BEER'S PRICE?" << endl;
        cin >> a;
        while (p!=0){
            if (p->price == a){
                printbeer(p);
                f = 1;
                break;
            }
            p = p->next;
        }
        if (f == 0){
            cout << "BEER NOT FOUND" << endl;
        }
    }
}

#endif // BARREL_H_INCLUDED
