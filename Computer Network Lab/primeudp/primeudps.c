#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<strings.h>
int isPrime(int n)
{
int i;
for(i=2;i<=n/2;i++)
{
if(n%i==0)
return 0;
}
return 1;
}
int main()
{
int numrecieved;
int serversocket,port; 
struct sockaddr_in serveraddr,clientaddr;
socklen_t len; 
char message[50];
serversocket=socket(AF_INET,SOCK_DGRAM,0);
bzero((char*)&serveraddr,sizeof(serveraddr));
serveraddr.sin_family=AF_INET;
printf("Enter the port number ");
scanf("%d",&port);
serveraddr.sin_port=htons(port);
serveraddr.sin_addr.s_addr=INADDR_ANY; 
bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
printf("\nWaiting for the client connection\n");
bzero((char*)&clientaddr,sizeof(clientaddr));
len=sizeof(clientaddr);
recvfrom(serversocket,&numrecieved,sizeof(numrecieved),0,(struct sockaddr*)&clientaddr,&len);
printf("\nThe client sent number:\t%d\n",numrecieved);
if(isPrime(numrecieved))
{
sendto(serversocket,"The number is prime.",sizeof("The number is prime."),0,( struct sockaddr*)&clientaddr,sizeof(clientaddr));
}
else
{
sendto(serversocket,"The number is not prime.",sizeof("The number is not prime."),0,( struct sockaddr*)&clientaddr,sizeof(clientaddr));
}
close(serversocket);
}