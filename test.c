#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{		
    int fd;
    int k;
    fd = open("deneme.txt",O_RDWR|O_CREAT);
    static char * buff;

    buff = (char *)malloc(51);
    if(buff == NULL)
        return 0;
    k = read(fd,buff,50);
    buff[k] = '\0';
    printf("%s",buff);
    k = read(fd,buff,50);
    buff[k] = '\0';
    printf("%s",buff);
    k = read(fd,buff,50);
    buff[k] = '\0';
    printf("%s",buff);
    close(fd);
    return 0;
}  
