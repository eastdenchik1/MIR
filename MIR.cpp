

#include "MIR.h"

char* str_replace(char* str, size_t size, const char* old, const char* ns);

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

void MIR::get_with_keys(char mode){

    if ((_FileMode & S_IFMT)!=S_IFDIR){
        if (mode == 'b') {
                /*
                Вывод файла полностью, только с нумерацией не пустых строк
                */
                int count = 1;
                string line;
                ifstream fin(_FileName, ios::in);
                while (getline(fin,line)){
                    if (line[0]){
                        cout << count << "   " << line << endl;
                        count ++;
                    } else {
                        cout  << "   " << "   " << line << endl;
                    }
                }
                fin.close();
        } else if (mode == 'E') {
                /*
                В конец каждой строки при выводе дописывать $
                */
                string line;
                ifstream fin(_FileName, ios::in);
                while (getline(fin,line)){
                        cout << line << "$" << endl;
                    } 
                fin.close();
            /* code */
        } else if (mode == 'n') {
                /*
                Вывод файла полностью, только с нумерацией всех строк
                */
                string line;
                ifstream fin(_FileName, ios::in);
                int count = 1;
                while (getline(fin,line)){
                        cout << setw(6) << count << "   " << line << endl;
                        count ++;
                    } 
                fin.close();
            /* code */
        } else if (mode == 'T') {
                /*
                Если есть сиволы табуляции показывать как ^I
                */
                string line;
                ifstream fin(_FileName, ios::in);
                char old[]    = "\t";
	            char ns[]     = "^I";
                while (getline(fin,line)){     
                        int n = line.length();
                        char cline[n+1];
                        strcpy(cline, line.c_str());
                        str_replace(cline, sizeof(line)-1, old, ns);
                        cout << cline << endl;                   
                    } 
                fin.close();
            /* code */
        }
    } else {
        cout << "Это каталог. Пвторите попытку с файлом." << endl;
    }
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
