
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
#include <sys/stat.h>
#include <sys/socket.h>
#include "commands.h"

/* At some point I need to set this to be set via CLI or VIA a config file */
#define SERIALDEV "/dev/ttyS0"
#define CMD_FIFO  "/tmp/lg_cmd"
void signal_handler_IO (int status);

int read_status = 0;

int main(int argc, char *argv[])
{
   int serial_fd = 0;
   int res = 0;
   int CMD = 0;
   pid_t pid;
   int cmd;
   int fifo_fd;
   struct termios ctl_port;
   struct sigaction saio;
   char from_tv[20];
   char to_tv[20];
   char action[10];
/* This needs to be set 
   int tv_id=00; 
   */
   
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
   
  
   /* install the signal handler before making the device asynchronous */
   /*  saio.sa_handler = signal_handler_IO;
   saio.sa_flags = 0;
   saio.sa_restorer = NULL;
   sigaction(SIGIO,&saio,NULL); 
   fcntl(serial_fd, F_SETOWN, getpid());
   fcntl(serial_fd, F_SETFL, FASYNC);
   */
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
   
   /* make a fifo to read the comannds from */
   if ( ( mkfifo(CMD_FIFO,(S_IWUSR|S_IRUSR|S_IWGRP)) ) && (errno != EEXIST )) 
   {
      perror("mkfifo");
      exit(1);
   }
    
   if ((fifo_fd = open(CMD_FIFO, O_RDONLY )) < 0 )
   {
      perror("open");
      exit(1);
   }
   
   for(;;)
   {
      fputs("\nIn For loop\n", stderr); 
      /*if (( read(fifo_fd,action,10) < 0)) */
      if ( read(fifo_fd, action, 10) == -1)
      {
	 perror("read()");
	 exit(1);
      }
      
      fputs("After Read\n", stderr); 
      /* Read input from the outside and sent the proper command to the TV and verify that the tv gets the command properly */
      switch (CMD)
      {
      case ON:
	 break;
      case OFF:
	 break;
      case TV:
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
   }

   /* We should never Reach this point */
   close(serial_fd);
   close(fifo_fd);
   exit(0);
}
   

void signal_handler_IO (int status)
{

}

