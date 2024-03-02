#include "stdio.h"
#include <unistd.h>

int main(int argc, char *argv[]){
	const char *path;
	path = NULL;
	printf ("%i\n", execv(path, argv));
}
