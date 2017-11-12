#include "myheader.h"

void mytail()
{
    FILE * fp;
    char ch;
    int enter=0,total_enter=0,dif=0;

    if(options[0] == NULL)
    {
	printf("usage error! : usage -> mytail [filename] [positive integer]\n");
	return ;
    }

    if(strcmp(options[0],"--help")==0)
    {
	printf("usage -> mytail [filename] (number)\n");
	printf("print FILENAME's data until 5 line from bottom\n");
	printf("if there is number, print data until number line from bottom\n");
	return ;
    }

    if((fp = fopen(options[0],"r"))==NULL)
    {
	printf("file doesn't exist\n");
	return ;
    }
    else
    {

	while((ch=fgetc(fp))!=EOF)
	    if(ch=='\n')			//first, count total enter
		total_enter++;
	fclose(fp);
    }
    fp = fopen(options[0],"r");

    if(options[1] != NULL)
    {
	int count = atoi(options[1]);
	if(count <= 0)
	{
	    printf("usage error! : usage -> mytail [filename] [positive integer]\n");
	    return;
	}

	while((ch=fgetc(fp))!=EOF)
	{
	    dif = total_enter - enter;		//for inverse counting
	    if(dif <= count)
	    putchar(ch);
	    if(ch=='\n')
		enter++;

	}
    }
    else
    {
	while((ch=fgetc(fp))!=EOF)
	{
	    dif = total_enter - enter;
	    if(dif <= 5)
	    putchar(ch);
	    if(ch=='\n')
		enter++;

	}
    }
}
