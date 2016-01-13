#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
pid_t pid = fork();
if (pid)
{
int i = getpid();
char filename[20];

sprintf(filename,"file_%d.txt",i);
FILE *file = fopen(filename, "w");

fprintf(file, "Pid: %d\n",i);
fprintf(file, "child Pid: %d",pid);

fclose (file);
printf("file parent: %s, created\n",filename);
sleep (20);
}
else
{
int i = getpid();
char filename[15];

sprintf(filename,"file_%d.txt",i);
FILE *file = fopen(filename, "w");

fprintf(file, "Pid: %d\n",i);
fprintf(file, "parent Pid: %d",getppid());

printf("file child: %s, created\n",filename);

fclose(file);

}
}
