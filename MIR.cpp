

#include "MIR.h"

MIR::MIR(char * file_name){
    struct stat buf;
    stat(file_name, &buf);
    _FileName = file_name;
    _FileMode = buf.st_mode;
}


void MIR::get_without_keys(){
    if ((_FileMode & S_IFMT)!=S_IFDIR){
            string line;
            ifstream fin(_FileName, ios::in); 
            while (getline(fin,line)){
               cout << line << endl;
            }
            fin.close(); // закрываем файл
    } else {
        cout << "Это каталог. Пвторите попытку с файлом." << endl;
    }
}

void MIR::get_with_keys(char * mode){

    // Проверка на файл
    if ((_FileMode & S_IFMT)!=S_IFDIR){

        string TMP_File = ".TMP_File", STD_File = _FileName, line;

        ifstream fin(STD_File); 
        ofstream fout(TMP_File); 

        while (getline(fin,line)){
               fout << line << endl;
        }

        fin.close();
        fout.close();  

        // Проверка на наличие ключей b и n. Если в строке одновременно оба этих ключа, то оставляем только ключ b.
        if (find_str(mode)) {
            string tmp="";
            for(auto j = 1; j <= strlen(mode); j++) {
                if (mode[j]!='n') {
                    tmp += mode[j];
                }
            }

            for(int i = 0; i < tmp.length(); i++)
            {
                _params(tmp[i], TMP_File);
            }
            

        } else {
            string tmp="";
            for(auto j = 1; j <= strlen(mode); j++) {
                tmp += mode[j];
            }
            
            for(int i = 0; i < tmp.length(); i++)
            {
                _params(tmp[i], TMP_File);
            }

        }

        ifstream tmp(TMP_File); 
        while (getline(tmp,line)){
               cout << line << endl;
        }
        tmp.close();
        remove(TMP_File.c_str());
               
    } else {
        cout << "Это каталог. Пвторите попытку с файлом." << endl;
    }
}

bool find_str(char * str){
    bool tmp = false;
    for(auto i = 1; i <= strlen(str); i++) {
        if (str[i]=='b') {
            for(auto j = 1; j <= strlen(str); j++) {
                if (str[j]=='n') {
                    tmp = true;
                }
            }
        }
    }
    return tmp;
}

char* str_replace(char* str, size_t size, const char* old, const char* ns){
	size_t len, num;
	char*  tmp  = str;
	size_t len1 = strlen(old);
	size_t len2 = strlen(ns);
 
	if(len2 > len1){
		len = strlen(str);
		num = len2 - len1;
	}
 
	while((str = strstr(str, old)) != NULL){
		if(len1 > len2){
			strncpy(str, ns, len2);
			strcpy(str + len2, str + len1);
		} else if(len1 < len2){
 
			if((len + num + 1) >= size)
				break;
 
			memmove(str + num, str, (len - (size_t)(str - tmp)) * sizeof(char));
			strncpy(str, ns, len2);
			len += num;
		} else
			strncpy(str, ns, len2);
		str += len2;
	}
	return tmp;
}



void _params(char mode, string file){
    if (mode == 'b') {
                /*
                Вывод файла полностью, только с нумерацией не пустых строк
                */
                int count = 1;
                string line;
                ifstream fin(file);
                ofstream fout(".TMP");
                while (getline(fin,line)){
                    if (line[0]){
                        fout << setw(6) << count << "   " << line << endl;
                        count ++;
                    } else {
                        fout << line << endl;
                    }
                }
                fin.close();
                fout.close();
                remove(file.c_str());
                rename(".TMP",file.c_str());
        } else if (mode == 'E') {
                /*
                В конец каждой строки при выводе дописывать $
                */
                string line;
                ifstream fin(file);
                ofstream fout(".TMP");
                while (getline(fin,line)){
                        fout << line << "$\n";
                    } 
                fin.close();
                fout.close();
                remove(file.c_str());
                rename(".TMP",file.c_str());
        } else if (mode == 'n') {
                /*
                Вывод файла полностью, только с нумерацией всех строк
                */
                string line;
                ifstream fin(file);
                ofstream fout(".TMP");
                int count = 1;
                while (getline(fin,line)){
                        fout << setw(6) << count << "   " << line << endl;
                        count ++;
                    } 
                fin.close();
                fout.close();
                remove(file.c_str());
                rename(".TMP",file.c_str());
        } else if (mode == 'T') {
                /*
                Если есть сиволы табуляции показывать как ^I
                */
                string line;
                ifstream fin(file);
                ofstream fout(".TMP");
                char old[]    = "\t";
	            char ns[]     = "^I";
                while (getline(fin,line)){     
                        int n = line.length();
                        char cline[n+1];
                        strcpy(cline, line.c_str());
                        str_replace(cline, sizeof(line)-1, old, ns);
                        fout << cline << endl;                   
                    } 
                fin.close();
                fout.close();
                remove(file.c_str());
                rename(".TMP",file.c_str());
        }
}


