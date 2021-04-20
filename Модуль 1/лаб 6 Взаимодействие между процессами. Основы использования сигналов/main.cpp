#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

using namespace std;

void sig_handler(int sum){
    int fd=open("text.txt",O_WRONLY | O_APPEND,0640);
    if (fd==-1){
        cerr<<"Failed to open the file"<<endl;
    }
    char Data[]="The SIGILL was received.";
    write(fd,&Data,sizeof(Data));
    close(fd);
}

int main()
{
    struct sigaction act;
    sigset_t newset;
    sigemptyset(&newset);
    sigaddset(&newset, SIGTERM);
    sigprocmask(SIG_BLOCK, &newset, 0);
    act.sa_handler = &sig_handler;
    act.sa_flags = 0;

    if(sigaction(SIGILL, &act, NULL)==-1){
        cerr<<"Error sigaction()"<<endl;
        return 1;
    }
    cout<<"PID:"<<getpid()<<endl;
    for(;;){ }
    return 0;
}
