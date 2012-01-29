#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
//Karson Miller
//ece 4112
//simple port scanner
 
int main(int argc, char **argv)
   {
   int scket,port,start_port,end_port,cnect; 
   //socket,port,start port ,end port ,conection
   struct hostent *hostaddr; //Struct for IP Layer
   struct sockaddr_in servaddr; //Struct for TCP Socket
   if (argc<4)
      {printf("[IP] [Start Port] [end Port]\n");
      return 1;}
      
   start_port=atoi(argv[2]); //get start
   end_port=atoi(argv[3]); //get end
   for (port=start_port; port<=end_port; port++)
      { 
      scket=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP); // set socket type
      if (scket==-1) {printf("bad socket\n");  return 1;}     
      memset(&servaddr,0,sizeof(servaddr));    //copy it
      servaddr.sin_family = AF_INET; // set ip type
      servaddr.sin_port = htons(port);  // set port
      hostaddr = gethostbyname(argv[1]); //parse ip
      memcpy(&servaddr.sin_addr,hostaddr->h_addr,hostaddr->h_length); //copy ip header
      cnect=connect(scket,(struct sockaddr *) &servaddr,sizeof(servaddr)); //open connetion 
      if (cnect!=-1) printf("Tcp port %d is open\n",port);      
      close(scket); 
      }   
    return 0;
   }