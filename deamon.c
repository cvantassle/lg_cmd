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
#include "commands.h"

/* At some point I need to set this to be set via CLI or VIA a config file */
#define SERIALDEV "/dev/ttyS0"
void signal_handler_IO (int status);

int read_status = 0;

int main(int argc, char *argv[])
{
   int fd = 0;
   int res = 0;
   int CMD = 0;
   int pid;	
   struct termios ctl_port;
   struct sigaction saio;
   char from_tv[20];
   char to_tv[20];
   /* This needs to be set 
   int tv_id=00;
   
   /* Deamonize the Application */
   if ((pid= fork()) < 0 )
   {  perror("Fork");
      exit(errno);
   }
   else if ( pid != 0)
   {
      fputs("Exiting Parent\n", stderr);
      exit(0);
   }
   /*fputs("In Child/Deamon\n",stderr);*/
   
   /* install the signal handler before making the device asynchronous */
   saio.sa_handler = signal_handler_IO;
   /*saio.sa_mask = 0; Comile Error? */
   saio.sa_flags = 0;
   saio.sa_restorer = NULL;
   sigaction(SIGIO,&saio,NULL);
   /* allow the process to receive SIGIO */
   fcntl(fd, F_SETOWN, getpid());
   /* Make the file descriptor asynchronous (the manual page says only
      O_APPEND and O_NONBLOCK, will work with F_SETFL...) */
   fcntl(fd, F_SETFL, FASYNC);



   if ( (fd=open(SERIALDEV, O_RDWR | O_NOCTTY | O_NONBLOCK )) < 0)
   {
      perror(SERIALDEV);
      exit -1;
   }
   /* Set the Serial port Connection Paramaters  */

   tcgetattr(fd, &ctl_port);
   cfsetispeed(&ctl_port, B9600);                 /* Set the baud rates to 9600 */
   cfsetospeed(&ctl_port, B9600);
   ctl_port.c_cflag |= (CLOCAL | CREAD);
   ctl_port.c_cflag &= ~PARENB; /* Mask the character size to 8 bits, no parity */
   ctl_port.c_cflag &= ~CSTOPB;
   ctl_port.c_cflag &= ~CSIZE;
   ctl_port.c_cflag |=  CS8;                              /* Select 8 data bits */
   ctl_port.c_cflag &= ~CRTSCTS;         
   tcflush(fd, TCIFLUSH);
   tcsetattr(fd, TCSANOW,&ctl_port);
   
 

   while(1)
   {
      /* Read input from the outside and sent the proper command to the TV and verify that the tv gets the command properly */

   }

   /* We should never Reach this point */
   close(fd);
   exit(0);
}
   

void signal_handler_IO (int status)
{

}

