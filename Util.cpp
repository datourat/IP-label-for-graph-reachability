#ifndef UTIL_CPP_
#define UTIL_CPP_

#include "Util.h"

string extractFilename(const char* filename){
	string name(filename);
	int pos=name.find_last_of('.');

	return name.substr(0, pos);
}

void quit(){
	system("pause");
	exit(0);
}

#endif
