#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char* argv[]){
        // check for correct number of args
        if (argc != 3){
                fprintf(stderr, "Please make sure to input only 2 arguments");
                exit(1);
        }

        char* from = argv[1];
        char* to = argv[2];

        int fromSize = strlen(from);
        int toSize = strlen(to);

        // check for unequal lengths
        if (fromSize != toSize){
                fprintf(stderr, "Unequal lengths!");
                exit(1);
        }
        // checkc for duplicate bytes
        int i,j;
        for (i = 0; i < fromSize; i++){
                for (j = i+1; j < fromSize; j++){
                        if (from[i] == from[j]){
                                fprintf(stderr, "Duplicate bytes");
                                exit(1);
                        }
                }
        }
	// Now we are going to replace values
        // We create this array to help 
        char asciiRep[256];
        for (i = 0; i < 256; i++)
                asciiRep[i] = i;

        // replace "from" values with corresponding value in "to"
        for (j = 0; j < fromSize; j++)
                asciiRep[from[j]] = to[j];

        // now we can putchar
        int curr = getchar();
        while(curr != EOF){
                putchar(asciiRep[curr]);
                curr = getchar();
        }
        return 0;
}

