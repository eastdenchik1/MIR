
#include "MIR.h"

vector<string> split(const string &s, char delim);

int main(int argc, char ** argv){

    if (argc==2){
        if (strcmp(argv[1],"--help")==0){
            cout << "Раздел помощи. " << endl;
            const char fname[36] = "cat.file";
            string line;
            ifstream fin(fname, ios::in);
            
            while (getline(fin,line)){
               cout << line << endl;
            }
            fin.close();
        } else {
            MIR obj = MIR(argv[1]);
            obj.get_without_keys();
        }
    } else if (argc==3) {
        MIR obj = MIR(argv[2]);
        for(int i = 1; i < strlen(argv[1]); i++)
        {
            cout << endl << "Аргумент " << argv[1][i] <<endl;
            obj.get_with_keys(argv[1][i]);
        }
    } else {
        string str;
        while(1){
            cin >> str;
            cout << str << endl;            
        }
    }
}

