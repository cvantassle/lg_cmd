/* this is the Client part of the lg_cmd deamon.
   This is intended to be called from lirc and it will send commands to the control deamon
   Options are u for volume,d for volume down,  m for mute, h1-3 for HDMI inputs, r for rgb, o for on, f for off
   a# for avi input, c# for composit
*/

#include "commands.h"
#include <string.h>
int main(int argc, char *argv[])
{
   int sock;
   struct sockaddr_in cmd_srv;
   char cmd[20];

   if(argc > 2)
   {
      fputs("Not enough arguments\n",stderr);
      return 1;
   }
   if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
      perror("socket:");
   }
   memset(&cmd_srv, 0, sizeof(cmd_srv));       
   cmd_srv.sin_family = AF_INET;                
   cmd_srv.sin_addr.s_addr = inet_addr("127.0.0.1");  
   cmd_srv.sin_port = htons(6100);
   
   switch(getopt(argc, argv, "mduh:rofa:c:"))
   {
   case 'u':
      strcpy(cmd,"VOLUP");
      if (sendto(sock, cmd, strlen(cmd), 0,(struct sockaddr *) &cmd_srv,sizeof(cmd_srv)) != strlen(cmd))
      {
	 perror("VOLUP sending error");
      }
      break;
   case 'd':
      strcpy(cmd,"VOLDN");
      if (sendto(sock, cmd, strlen(cmd), 0,(struct sockaddr *) &cmd_srv,sizeof(cmd_srv)) != strlen(cmd))
      {
	 perror("VOLDM sending error");
      }
      break;
   case 'r':
      strcpy(cmd,"RGB");
      if (sendto(sock, cmd, strlen(cmd), 0,(struct sockaddr *) &cmd_srv,sizeof(cmd_srv)) != strlen(cmd))
      {
	 perror("RGB sending error");
      }
      break;
   case 'o':
      strcpy(cmd,"ON");
      if (sendto(sock, cmd, strlen(cmd), 0,(struct sockaddr *) &cmd_srv,sizeof(cmd_srv)) != strlen(cmd))
      {
	 perror("ON sending error");
      }
      break;
   case 'f':
      strcpy(cmd,"OFF");
      if (sendto(sock, cmd, strlen(cmd), 0,(struct sockaddr *) &cmd_srv,sizeof(cmd_srv)) != strlen(cmd))
      {
	 perror("OFF sending error");
      }
      break;
   case 'a':
      strcpy(cmd,"AVI");
      strcat(cmd,optarg);
      if (atoi(optarg) <= 2)
      {
	 if(sendto(sock, cmd, strlen(cmd), 0,(struct sockaddr *) &cmd_srv,sizeof(cmd_srv)) != strlen(cmd))
	 {
	    perror("OFF sending error");
	 }
      }
      break;
   case 'c':
      strcpy(cmd,"COMP");
      strcat(cmd,optarg);
      if (atoi(optarg) <= 2)
      {
	 if(sendto(sock, cmd, strlen(cmd), 0,(struct sockaddr *) &cmd_srv,sizeof(cmd_srv)) != strlen(cmd))
	 {
	    perror("OFF sending error");
	 }	
      }
      break;
   case 'h':
      strcpy(cmd,"HDMI");
      strcat(cmd,optarg);
      if (atoi(optarg) <= 3)
      {
	 if(sendto(sock, cmd, strlen(cmd), 0,(struct sockaddr *) &cmd_srv,sizeof(cmd_srv)) != strlen(cmd))
	 {
	    perror("OFF sending error");
	 }	
      }      
      break;
   case 'm':
      strcpy(cmd,"MUTE");
      if (sendto(sock, cmd, strlen(cmd), 0,(struct sockaddr *) &cmd_srv,sizeof(cmd_srv)) != strlen(cmd))
      {
	 perror("ON sending error");
      }
   default:
      return 0;
      break;
   }
   /*we Should not Get here */
   printf("Clean up goes here\n");
   return 0;
}
