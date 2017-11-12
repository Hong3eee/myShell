#include "myheader.h"

void mycat()
{
    FILE * fp;
    char ch;

    if(options[0] == NULL)
    {
	printf("usage error! : usage -> mycat [FILENAME] (number)\n");
	return ;
    }

    if(strcmp(options[0],"--help")==0)
    {
	printf("usage -> mycat [FILENAME] (number)\n");
	printf("print FILENAME's data\n");
	printf("if there is number, print data until number byte\n");
	return ;
    }

    if((fp = fopen(options[0],"r"))==NULL)
    {
	printf("file doesn't exist\n");
	return ;
    }


    if(options[1] != NULL)
    {
	int count = atoi(options[1]);
	if(count <= 0)
	{
	    printf("usage error! : usage -> mycat [filename] [positive integer]\n");
	    return;
	}
	int i=0;

	while((ch=fgetc(fp))!=EOF && i<count)	//print each byte and until count
	{
	    putchar(ch);
	    i++;
	}
    }
    else
    {
	while((ch=fgetc(fp))!=EOF)
	    putchar(ch);

    }
    printf("\n");
    fclose(fp);
}
