#include <iostream>
#include "Barrel.h"

using namespace std;

string r;

int main()
{
coldroom *coldr = new coldroom();
coldr->add();
while (true){
    cout << "WHAT WOULD YOU LIKE TO DO WITH THE DATA?\n 1)SEE INVENTORY 2)SORT 3)SEARCH" << endl;
    cin >> r;
    if (r=="1" || r == "one" || r == "ONE" || r == "see" || r == "SEE" || r == "inventory" || r == "INVENTORY" || r == "see inventory"){
        coldr->print();
    }
    else if (r=="2" || r == "two" || r == "sort" || r == "SORT" || r == "TWO"){
        coldr->sort(coldr->add());
    }
    else if (r == "3" || r == "three" || r == "THREE" || r == "search" || r == "SEARCH"){
        coldr->get();
    }
    cout << "WOULD YOU LIKE TO DO ANYTHING ELSE WITH THE DATA?" << endl;
    cin >> r;
    if (r == "yes" || r == "YES" || r == "1")
        continue;
    else{
        break;
    }
}
delete coldr;
return 0;
}
