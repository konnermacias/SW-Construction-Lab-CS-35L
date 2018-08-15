#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int  frobcmp(char const* a, char const* b);
int  cmp_wrapFn(const void* a, const void* b);
void writeStr(const char * str);
void whatErr(const char* msg);

int main(void)
{
        int (* cmp) (const void*, const void*);
        char* i_1, * i_2, ** lnbuf, curr;
        size_t lnNum, lnSize, bufSize, i, fSize;
        int space, eof;
        bufSize = 0, lnNum = 0, lnSize = 0, eof = feof(stdin), fSize = 19;
        cmp = &cmp_wrapFn;
        i_1 = (char*) malloc(sizeof(char) * fSize);
        if (i_1 == NULL)
                whatErr("Memory Allocation Error");

        while (!eof)
        {
                curr = getchar();
                if (ferror(stdin))
                        whatErr("IO Error");

                space = curr == ' ';
                eof = feof(stdin);
                if (!lnSize && space)
                        continue;
                if (bufSize == fSize)
                {
                        fSize *= 2;
                        i_2 = (char*) realloc(i_1, sizeof(char) * fSize);
                        if (i_2 == NULL)
                                whatErr("Memory Allocation Error");

                        i_1 = i_2;
		}


                if (!eof)
                {
                        i_1[bufSize++] = curr;
                        lnSize++;
                        if (!space)
                                continue;
                }
                else
                {
                        if (!bufSize)
                        {
                                free(i_1);
                                return 0;
                        }

                        if (i_1[bufSize-1] != ' ')
                                i_1[bufSize++] = ' ';
                        if (!lnSize)
                                break;
                }

                lnNum++;
                lnSize = 0;
        }
        lnbuf = (char**) malloc(sizeof(char*) * lnNum);
        if (i_1 == NULL)
                whatErr("Memory Allocation Error");
        size_t count;
        char* line = i_1;
        for (i = 0, count = 0; i < bufSize; i++)
        {
                if (i_1[i] == ' ')
                {
                        lnbuf[count++] = line;
                        line = i_1 + i + 1;
                }
        }
	qsort(lnbuf, lnNum, sizeof(char*), cmp);

        for (i = 0; i < lnNum; i++)
                writeStr(lnbuf[i]);

        free(lnbuf);
        free(i_1);
        return 0;
}

inline
void whatErr(const char* msg)
{
        fprintf(stderr, "%s: %d\n", msg, errno);
        exit(1);
}

inline
int cmp_wrapFn(const void* a, const void* b)
{
        return frobcmp(*((const char**) a), *((const char**) b));
}

void writeStr(const char* str)
{
        for (;;)
        {
                putchar(*str);
                if (ferror(stdout))
                        whatErr("IO Error");
                if (*str++ == ' ')
                        return;
        }
}

int frobcmp(char const* a, char const* b)
{
        for ( ; *a == *b; a++, b++)
                if (*a == ' ')
                        return 0;
        return (((*a^42) < (*b^42)) ? -1 : 1);
}

