#include "CFG/cfg.h"

#include <fstream>

using namespace std;

int main(int argc, char *argv[]){
	
	if(argc!=3)
		return 0;
      
    Cfg cfg;
                
    ifstream file_1(argv[1]); file_1 >> cfg;
    if(cfg.is_empty())
        cout << "ERROR EN EL FICHERO INTRODUCIDO" << endl;
    else
        cfg.Simplify(0);
    ofstream file_2; file_2.open(argv[2]); file_2 << cfg;

	file_1.close();	file_2.close();
}