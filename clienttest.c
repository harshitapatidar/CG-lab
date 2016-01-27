#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<sys/types.h>
#include<stdlib.h>
#include<netdb.h>

void main()
{
   int sockfd,n;
   sockfd=socket(AF_INET,SOCK_STREAM,0);

   struct in_addr ipv4;
   struct hostent *he;
   
   inet_pton(AF_INET, "127.0.0.1", &ipv4);
he = gethostbyaddr(&ipv4, sizeof ipv4, AF_INET);
printf("Host name: %s\n", he->h_name);


   if(sockfd<0)
    {
     printf("socket crration failed");
     exit(0);
    }
     struct sockaddr_in servaddr;
     bzero((&servaddr),sizeof(servaddr));
     servaddr.sin_family=AF_INET;
     servaddr.sin_port=htons(7000);
     servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    
     n=connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
     
     if(n<0)
      printf("connection failed");

     struct sockaddr_in client;
     int len;
     len=sizeof(client);
     getsockname(sockfd,&client,&len);
      printf("Local IP address is: %s\n", inet_ntoa(client.sin_addr));
   printf("Local port is: %d\n", (int) ntohs(client.sin_port));
     char line[300];
     printf("enter masg to send\n");
     gets(line);
     n=send(sockfd,line,300,0);
     if(n>0)
      printf("Message sent successfully\n");
     n=recv(sockfd,line,300,0);
      if(n>0){
    printf("Message recieved successfully\n");
     puts(line);
     }
}
