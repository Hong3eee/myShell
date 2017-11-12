#include "myheader.h"

void myhead()
{
    FILE * fp;
    char ch;
    int enter=0;

    if(options[0] == NULL)
    {
	printf("usage error! : usage -> myhead [filename] [positive integer]\n");
	return ;
    }

    if(strcmp(options[0],"--help")==0)
    {
	printf("usage -> myhead [filename] (number)\n");
	printf("print FILENAME's data until 5 line\n");
	printf("if there is number, print data until number line\n");
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
	    printf("usage error! : usage -> myhead [filename] [positive integer]\n");
	    return;
	}
	int i=0;

	while((ch=fgetc(fp))!=EOF)
	{
	    putchar(ch);
	    if(ch=='\n')		//enter count and compare
		enter++;
	    if(enter==count)
		break;

	}
    }
    else
    {
	while((ch=fgetc(fp))!=EOF)
	{
	    putchar(ch);
	    if(ch=='\n')
		enter++;
	    if(enter==5)		//default enter = 5
		break;
	}
    }
    fclose(fp);
}
