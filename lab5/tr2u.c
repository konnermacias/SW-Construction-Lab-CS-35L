#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]){
        // check number of arguments
        if (argc != 3){
                fprintf(stderr, "Must have 2 arguments");
                exit(1);
        }

        char* from = argv[1];
        char* to = argv[2];
        int  fromSize = strlen(from);
        int  toSize = strlen(to);

        // check equal lengths
        if (fromSize != toSize){
                fprintf(stderr, "Input and output must be same size");
                exit(1);
        }
        // check for duplicate bytes
        int i, j;
        for (i = 0; i < fromSize; i++){
                for (j = i+1; j < fromSize; j++){
                        if (from[i] == from[j]){
                                fprintf(stderr, "Duplicate bytes!");
                                exit(1);
                        }
                }
        }

        // Like tr2b.c, we will create a conversion array
        char asciiRep[256];
        for (i = 0; i < 256; i++)
                asciiRep[i] = i;
	
	// now we can replace the values in "from" to one in "to" 
        for (j = 0; j < fromSize; j++)
                asciiRep[from[j]] = to[j];

        //now we read and write instead of using putchar and getchar
        int curr;
        char src[2];
        int result = read(0, &curr, 1);

        if (result < 0){
                fprintf(stderr, "Read error");
                exit(1);
        }
        // reuslt == 0 means end of file
        while (result > 0){
                src[0] = asciiRep[curr];
                write(1, src, 1);
                result = read(0, &curr, 1);
        }

        return 0;
}
