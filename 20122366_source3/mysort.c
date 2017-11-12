#include "myheader.h"

void mysort()
{
    FILE * fp,*fp2;
    char * temp = (char *)malloc(1024);
    int enter=0;
    int x=0,y=0,z=0;
    char change[200];
    int i=0,i2=0;

    if(options[0] == NULL)
    {
	printf("usage error! : usage -> mysort [filename] (option)\n");
	return ;
    }

    if(strcmp(options[0],"--help")==0)
    {
	printf("usage -> mysort [filename] (option)\n");
	printf("sort FILENAME's data and print data by line\n");
	printf("-b option : ignore blank\n");
	printf("-r option : sort inverse order\n");
	return ;
    }

    if((fp = fopen(options[0],"r"))==NULL)
    {
	printf("file doesn't exist\n");
	return ;
    }
    else
    {

	while(fgets(temp,1024,fp)!=NULL)
	    enter++;
	fclose(fp);
    }
    char line[enter][1024];
    char line2[enter][1024];
    fp = fopen(options[0],"r");
    fp2 = fopen(options[0],"r");

    if(options[1] != NULL)
    {
	if(strcmp(options[1],"-r")==0)
	{
	    while(fgets(line[i],1024,fp)!=NULL)
		i++;

	    for(x=0;x<enter-1;x++)
		for(y=0;y<enter-1-x;y++)
		    if(strcmp(line[y],line[y+1])<0)
		    {
			strcpy(change,line[y]);
			strcpy(line[y],line[y+1]);
			strcpy(line[y+1],change);
		    }

	}
	else if(strcmp(options[1],"-b")==0)
	{
	    while(fgets(line[i],1024,fp)!=NULL)
		i++;

	    while(fgets(line2[i2],1024,fp2)!=NULL)
		i2++;


	    for(x=0;x<enter;x++)
		for(y=0;y<strlen(line2[x]);y++)
		{
		    if(line2[x][y] == ' ')			//deleting blank 
		    {
			for(z=y;z<strlen(line2[x]);z++)
			    line2[x][z] = line2[x][z+1];

			y--;
		    }

		}

	    for(x=0;x<enter-1;x++)
		for(y=0;y<enter-1-x;y++)
		    if(strcmp(line2[y],line2[y+1])>0)		//compare line2 but change line's order
		    {
			strcpy(change,line[y]);
			strcpy(line[y],line[y+1]);
			strcpy(line[y+1],change);
		    }

	}

    }
    else
    {
	while(fgets(line[i],1024,fp)!=NULL)
	    i++;

	for(x=0;x<enter-1;x++)
	    for(y=0;y<enter-1-x;y++)
		if(strcmp(line[y],line[y+1])>0)
		{
		    strcpy(change,line[y]);
		    strcpy(line[y],line[y+1]);
		    strcpy(line[y+1],change);
		}

    }
    for(x=0;x<enter;x++)
	printf("%s",line[x]);
}
