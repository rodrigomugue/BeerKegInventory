#ifndef BARREL_H_INCLUDED
#define BARREL_H_INCLUDED
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

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

kegs::kegs() : prev(0), next(0) {}

kegs::kegs(string name_, string style_, string brewery_, int price_, int lt_, int pint_){
    name_ = name;
    style_ = style;
    brewery_ = brewery;
    price_ = price;
    lt_ = lt;
    pint_ = pint;
}

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
    vector<string> explode(string const &, char);
    void swap(vector<kegs>&, int, int);
};

coldroom::coldroom() : size(0), head(0) {}

coldroom::~coldroom() {
    clear();
}

vector<string> coldroom::explode(string const &s, char delim){
    vector<string> result;
    istringstream iss(s);
    for (string token; getline(iss,token,delim);){
        result.push_back(move(token));
    }
    return result;
}

vector<vector<string>> coldroom::read() {
    string line = "", filein;
    vector<vector<string>> dl;
    vector<string> v;
    filein = "sign.csv";
    ifstream myfile (filein);
    if (myfile.is_open()){
        while (getline(myfile,line)){
            auto v = explode(line,',');
            dl.push_back(v);
        }
        myfile.close();
    }
    else{
        cout << "UNABLE" << endl;
    }
    return dl;
}

vector<kegs> coldroom::add(){
    kegs *NewKeg, *p;
    int i=1;
    vector<kegs> Tap;
    vector<vector<string>> dl = read();
    for (i;i<dl.size()-1;i++){
            NewKeg = new kegs();
            NewKeg->name = dl[i][0];
            NewKeg->style = dl[i][1];
            NewKeg->brewery = dl[i][2];
            NewKeg->price = stoi(dl[i][3]);
            NewKeg->lt = stoi(dl[i][4]);
            NewKeg->pint = stoi(dl[i][5]);
            if (i = 1){
                NewKeg->next = head;
                head->prev = NewKeg;
                head = NewKeg;
            }
            else{
                tail->next = NewKeg;
                NewKeg->prev = tail;
                tail = NewKeg;
            }
            Tap.push_back(*NewKeg);
            size++;
            i++;
    }
    return Tap;
}

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

void coldroom::swap(vector<kegs> &v,int i, int j){
    kegs aux;
    aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

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
    cout << "NUM    BEER    STYLE    BREWERY     PRICE     KEG LT    PINT/ML";
    myfileout << "NUM    BEER    STYLE    BREWERY     PRICE     KEG LT    PINT/ML";
    for (int i = 0; i<= v.size(); i++){
        cout << i << "  ";
        myfileout << i << "  ";
        cout << v[i].name << "   " << v[i].style << "   " << v[i].brewery << "   ";
        cout << v[i].price << "   " << v[i].lt << "   " << v[i].pint << endl;
        myfileout << v[i].name << "   " << v[i].style << "   " << v[i].brewery << "   ";
        myfileout << v[i].price << "   " << v[i].lt << "   " << v[i].pint << endl;
        i++;
    }
	myfileout.close();
	}
	else {
        cout << "FILE NOT FOUND" << endl;
	}
}

void coldroom::printbeer(kegs *p){
    cout << "NAME: " << p->name << endl;
    cout << "STYLE: " << p->style << endl;
    cout << "BREWERY: " << p->brewery << endl;
    cout << "PRICE: " << p->price << endl;
    cout << "KEG LT: " << p->lt << endl;
    cout << "PINT ML: " << p->pint << endl;
}

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
