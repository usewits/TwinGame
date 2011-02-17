#include "System.h"

System system;

int main (int argc, char* argv[]){
	if( system.initialize() ){
		system.gameLoop();
	}
	system.cleanup();
    return 0;
} 

