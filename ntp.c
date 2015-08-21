#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "ntp.h"

int gethostIPbyname(char *name)
{
    struct hostent *host=NULL;
    struct in_addr *addr=NULL;

    host = gethostbyname (name);
    if(host->h_addr == NULL)
        return -1;
    addr = (struct in_addr*)host->h_addr;
    
    return addr->s_addr;
}

int GetNTPTime(STNP_Header *H_SNTP)
{
    int sockfd=0;
    struct sockaddr_in server;
    
    bzero((void*)H_SNTP, sizeof(STNP_Header));
    H_SNTP->LiVnMode = 0x1b;
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = gethostIPbyname(NTP_SERVER_NAME);
    server.sin_port = htons(NTP_PORT);
    if(-1 == (int)server.sin_addr.s_addr)
        return -1;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd<0)
    {
        perror("sockfd");
        return -1;
    }
    if(sendto(sockfd, (void*)H_SNTP, sizeof(STNP_Header), 0, (struct sockaddr*)&server, sizeof(server))<0)
    {
        perror("sendto");
        return -1;
    }
    
    fd_set r;
    FD_ZERO(&r);
    FD_SET(sockfd, &r);
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    
    if(1 != select(sockfd+1, &r, NULL, NULL, &timeout))
        return -1;
    if(recv(sockfd, (void*)H_SNTP, sizeof(STNP_Header), 0)<0)
        return -1;
    
    close(sockfd);
    return 0;
}

int SYNC_Time(void)
{
    STNP_Header HeaderSNTP;
    time_t t1,t2,t3,t4,dis;
    
    time(&t1);
    t1+=JAN_1970;
    
    printf("sync time from %s\n", NTP_SERVER_NAME);
    if(GetNTPTime(&HeaderSNTP)<0)
        return -1;
        
    time(&t4);
    t4+=JAN_1970;
    
    t2 = ntohl(HeaderSNTP.RecvTimeInt);
    t3 = ntohl(HeaderSNTP.TranTimeInt);
    
    dis = ( (t2-t1)+(t3-t4) )/2;
    if(dis<=0)
        printf("local time is faster then server %d seconds\n", (int)-dis);
    else
        printf("local time is slower then server %d seconds\n", (int)dis);
    
    struct timeval tv;
    gettimeofday (&tv, 0);
    tv.tv_sec+=dis;
    printf("%s", ctime(&tv.tv_sec));
    
    settimeofday (&tv, NULL);
    
    return 0;
}
