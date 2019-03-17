

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;
    
class MIR {
    private: 
        __mode_t _FileMode;
        const char * _FileName;

    public:
        MIR(char * fileName);
        void get_without_keys();
        void get_with_keys(char mode);
};
