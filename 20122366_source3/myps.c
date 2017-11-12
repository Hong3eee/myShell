#include "myheader.h"

DIR *dp;
struct dirent *dirp;
struct stat info;
struct passwd *uid;
char cmd[1000];
char tty[1000];
char cmd2[1000];
char cmdline[1000];
FILE * fp;

char * token[100];
char * token2[100];

void myps()
{
    int shellpid = getpid();
    int pid=-1;
    int i =0;

    sprintf(tty,"/proc/%d/stat",shellpid);
    fp = fopen(tty,"r");
    fgets(tty,1000,fp);
    fclose(fp);
    token2[0] = strtok(tty," \t\n");
    while(token2[i]!=NULL)
    {
	i++;
	token2[i] = strtok(NULL," \t\n");
    }
    int shelltty = atoi(token2[6]);

    if(options[0]==NULL)
    {
	dp = opendir("/proc");
	printf("<UID>\t<PID>\t <PPID>\t <PGID>\t <SID>\t <STIME> <TIME>\t <CMD>\n");
	while(dirp = readdir(dp))//implementation
	{
	    int count =0;
	    lstat(dirp->d_name,&info);
	    if(S_ISDIR(info.st_mode))
	    {
		i = 0 ;

		pid = atoi(dirp->d_name);

		if(pid<=0)	//if not process, do not open stat
		    continue;
		sprintf(cmd,"/proc/%d/status",pid);
		fp = fopen(cmd,"r");
		for(count =0; count <7;count++)
		    fgets(cmd,1000,fp);

		fclose(fp);
		token[0] = strtok(cmd," \t\n");
		while(token[i]!=NULL)
		{
		    i++;
		    token[i] = strtok(NULL," \t\n");
		}

		uid = getpwuid(atoi(token[1]));

		//sprintf(cmd,"/proc/stat");
		fp = fopen("/proc/stat","r");
		for(count =0;count<7;count++)
		    fgets(cmd,1000,fp);
		fclose(fp);
		token[0] = strtok(cmd," ");
		token[1] = strtok(NULL," \n");

		int btime = atoi(token[1]);

		sprintf(cmd,"/proc/%d/cmdline",pid);
		fp = fopen(cmd,"r");
		fgets(cmdline,1000,fp);
		fclose(fp);

		sprintf(cmd,"/proc/%d/stat",pid);
		fp = fopen(cmd,"r");
		fgets(cmd,1000,fp);
		fclose(fp);

		i=0;

		token[0] = strtok(cmd," \n");
		while(token[i]!=NULL)
		{
		    i++;
		    token[i] = strtok(NULL," \n");
		}
		int p_tty = atoi(token[6]);

		if(shelltty != p_tty)
		    continue;

		unsigned long starttime = atoi(token[21]);
		unsigned long  p_utime = atoi(token[13]);
		unsigned long  p_stime = atoi(token[14]);

		unsigned long stime = btime + starttime/100; 	//boot time + process starttime from boot time ,100 =  my cpu's HZ from usr/src/linux/include/asm-generic/param.h
		struct tm * stimeinfo = localtime(&stime);

		fp = fopen("/proc/uptime","r");
		fgets(cmd2,1000,fp);
		fclose(fp);

		token2[0] = strtok(cmd2," ");
		token2[1] = strtok(NULL," \n");
		int uptime = (int)atof(token2[0]);
		int cputime = 0;

		uptime = uptime - starttime/100.;	//time from process start
		if(uptime)
		    cputime = (int)((p_utime+p_stime)*1000ULL/100.)/uptime;


		printf("%5s\t%3s\t %3s\t %3s\t %3s\t %02d:%02d\t %02d:%02d\t %s\n",uid->pw_name,token[0],token[3],token[4],token[5],stimeinfo->tm_hour,stimeinfo->tm_min,cputime/10,cputime%10,cmdline);


	    }

	}

    }
    else
    {

	if(strcmp(options[0],"--help")==0)
	{
	    printf("usage -> myps\n");
	    printf("print my process info\n");
	}
	else
	    printf("usage error! : usage -> myps\n");

    }

}
