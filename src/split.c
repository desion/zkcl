#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void split(char *src, const char *separator, char **dest, int *num)
{
    char *pNext;
    int count = 0;
    
    if (src == NULL || strlen(src) == 0) return;
    if (separator == NULL || strlen(separator) == 0) return; 

    pNext = strtok(src,separator);
    
    while(pNext != NULL)
    {
        *dest++ = pNext;
        ++count;
        pNext = strtok(NULL,separator);
    }

    *num = count;
}

int main()
{
    char src[] = "Accsvr:tcp  -h    127.0.0.1      -p/n    20018";
    char *dest[128];
    char *dest2[128];
    int num = 0, num2 = 0;
    int i, j;

    split(src,":",dest,&num);

    for (i=0;i<num;++i)
    {
        printf("|%s|/n",dest[i]);
        split(dest[i]," /t/n",dest2,&num2);
        for (j=0;j<num2;++j)
        {
            printf("|%s|/n",dest2[j]);
        }
    }

    return 0;
}
