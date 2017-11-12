#include "myheader.h"
int sigcheck = -1;

void signal_handler(int signo)
{
    printf("SIGINT pressed\n");
    sigcheck = 1;
}

int main()
{
    char * token[30];
    buff = (char *)malloc(1024);
    oper = (char *)malloc(100);
    signal(SIGINT,signal_handler);			//sigint handling

    getcwd(buff,1024);
    char * tmp = getenv("PATH");
    strcat(tmp,":");
    strcat(tmp,buff);
    setenv("PATH",tmp,1);

    printf("my shell support : \nmyset\nmyenv\nmyps\nmycd\nmypwd\nmyls\nmycat\nmyhead\nmytail\nmysort\nmycp\nmymkdir\nmyrm\n");

    while(1)
    {
	sigcheck =0;
	int i =0;
	getcwd(buff,1024);
	token[0] = strtok(buff,"/");		//split current directory
	while(token[i]!=NULL)
	{
	    i++;
	    token[i] = strtok(NULL,"/");
	}

	printf("[20122366 %s]$",token[i-1]);

	if(fgets(oper,100,stdin)==NULL)
	{
	    printf("Shell exit\n");
	    return 1;
	}

	if(sigcheck==1)
	    continue;
	option();	//split string

	if(strncmp(oper,"exit",4)==0)
	{
	    printf("Shell exit\n");
	    return 1;
	}

	select_oper();	//select operation
	options[0] =NULL;
	options[1] =NULL;
	options[2] =NULL;

    }
    return 0;
}

void option()
{
    int i=0;
    oper = strtok(oper," \n");
    options[0] = strtok(NULL," \n");//enter handling

    while(options[i] != NULL)
    {
	i++;
	options[i] = strtok(NULL," \n");//enter handling
    }
    //printf("%s///%s///%s\n",oper,options[0],options[1]);
}

void select_oper()
{
    if(sigcheck == 1)
	return ;
    if(oper ==NULL)
	return ;

    int pid = fork();
    if(pid>0)
	wait();
    else if(pid<0)
    {
	printf("fork error!!\n");
	exit(0);
    }
    else
    {
    if(strcmp(oper,"mypwd")==0)
	mypwd();
    else if(strcmp(oper,"mymkdir")==0)
	mymkdir();
    else if(strcmp(oper,"mycp")==0)
	mycp();
    else if(strcmp(oper,"mycat")==0)
	mycat();
    else if(strcmp(oper,"myhead")==0)
	myhead();
    else if(strcmp(oper,"mytail")==0)
	mytail();
    else if(strcmp(oper,"mysort")==0)
	mysort();
    else if(strcmp(oper,"myset")==0)
	myset();
    else if(strcmp(oper,"myrm")==0)
	myrm();
    else if(strcmp(oper,"myps")==0)
	myps();
    else if(strcmp(oper,"myenv")==0)
	myenv();

    exit(0);
   }

    if(strcmp(oper,"mycd")==0)
	mycd();
    else if(strcmp(oper,"myset")==0)
	myset();
    else if(strcmp(oper,"myls")==0)
	myls();
}
