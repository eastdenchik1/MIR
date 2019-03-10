
#include "MIR.h"
using namespace std;


int main(int argc, char ** argv){

    if (argc==2){
        MIR obj = MIR(argv[1]);
        obj.get_without_keys();
        // Для начала проверить не каталог ли это и если да вывести что каталог
        // Вывод содержимого файла полностью без ключей 
        // Проверка на то каталог ли это
    } else if (argc==3) {
        // Для начала проверить не каталог ли это и если да вывести что каталог
        MIR obj = MIR(argv[2]);
        obj.get_with_keys(argv[1]);       
    } else {
        string str;
        while(1){
            cin >> str;
            cout << str << endl;            
        }
    }
}