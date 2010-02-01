
/*
 * This is the Deamon part of the application.
 * This part will mantain the Setting that can not be changed
 * like what the next configured input will be, and what the current
 * volume is at so it can change the volume properly.
 * It will also write out the config file
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <termios.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "commands.h"

/* At some point I need to set this to be set via CLI or VIA a config file */
#define SERIALDEV "/dev/ttyS0"
#define CMD_FIFO  "/tmp/lg_cmd"
#define MAX_FD	  3


int main(int argc, char *argv[])
{
   int serial_fd, fifo_fd;
   int res = 0;
   pid_t pid;
   char from_tv[20];
   char to_tv[20];
   char cmd[10];
   int vol;
   struct termios ctl_port;
   struct sockaddr_in lg_cmd;
/* This needs to be set  */
   int tv_id=00; 
  
   
   /* Deamonize the Application */
   if ((pid = fork()) == -1  )
   {
      perror("Fork");
      exit(errno);
   }
   else if ( pid != 0 )
   {  
      fputs("Exiting Parent\n", stderr);
      exit(0);
   }
   
   if ( (serial_fd=open(SERIALDEV, O_RDWR | O_NOCTTY | O_NONBLOCK )) < 0)
   {
      perror(SERIALDEV);
      exit(1);
   }
   tcgetattr(serial_fd, &ctl_port);
   cfsetospeed(&ctl_port, B9600);
   ctl_port.c_cflag |= (CLOCAL | CREAD);
   ctl_port.c_cflag &= ~PARENB; 
   ctl_port.c_cflag &= ~CSTOPB;
   ctl_port.c_cflag &= ~CSIZE;
   ctl_port.c_cflag |=  CS8;                              
   ctl_port.c_cflag &= ~CRTSCTS;         
   tcflush(serial_fd, TCIFLUSH);
   tcsetattr(serial_fd, TCSANOW,&ctl_port);
  

   if ((fifo_fd = socket(PF_INET,SOCK_DGRAM, IPPROTO_UDP)) < 0)
   {
      perror("bind");
      exit(1);
   }

   memset(&lg_cmd, 0, sizeof(lg_cmd));       		/* Clear struct */
   lg_cmd.sin_family = AF_INET;                  	/* Internet/IP */
   lg_cmd.sin_addr.s_addr = htonl(INADDR_ANY);  	/* Incoming addr */
   lg_cmd.sin_port = htons(6100);     		/* server port */
   if (bind(fifo_fd, (struct sockaddr *) &lg_cmd, sizeof(lg_cmd)) < 0)
   {
      perror("bind");
      exit(1);
   }
   res=sizeof(lg_cmd);
      

   while(1)
   {
      bzero(cmd,sizeof(cmd));
      if (( recvfrom(fifo_fd, cmd, 10, 0,(struct sockaddr *) &lg_cmd ,&res)) < 0)
      {
	 perror("recvfrom");
	 exit(1);
      }
      switch( get_cmd(cmd))
	 {
	 case VOLUP:
	    
	    break;
	    /* vol up*/
	 case VOLDN:
	    
	    break;
	    /* vol down*/
	 case MUTE:
	    
	    break;
	    /* Mute */
	 case ON:
	    
	    break;
	 case OFF:
	    
	    break;
	 case AVI1:
	    
	    break;
	 case AVI2:
	    
	    break;
	 case COMP1:
	    
	    break;
	 case COMP2:
	    
	    break;
	 case RGB:
	    
	    break;
	 case HDMI1:
	    
	    break;
	 case HDMI2:
	    
	    break;
	 case HDMI3:
	    
	    break;
	 default:
	    break;
	 };
   };

   /* We should never Reach this point */
   close(serial_fd);
   close(fifo_fd);
   exit(0);
}



