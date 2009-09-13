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
#include <sys/type.h>
#include <termios.h>


#DEFINE BAUD 9600
#DEFINE SERIALDEV "/dev/ttyUSB0"

int main(int argc, char *argv[])
{
   int fd = 0;
   int res = 0;
   struct termios ctl_port;
   char from_tv[20];
   char to_tv[20];

   /* Deamonize the Application */
   if ((pid= fork()) < 0 )
   {  perror(Form);
      exit(errno);
   }
   else if ( pid != 0)
      exit(0);
   
   if ( (fd=open(SERIALDEV, O_RDWR | O_NOCTTY )) < 0)
   {
      perror(SERIALDEV);
      exit -1;
   }

   bzero(&ctl_port, sizeof(ctl_port));
   ctl_port.c_flag = BAUD | CRTSCTS | CS8 | CLOCAL | CREAD;
   ctl_port.c_iflag = IGNPAR;
   ctl_port.c_oflag = 0;
   ctl_port.c_lflag = 0;
   ctl_port.c_cc[VTIME] = 0;
   ctl_port.c_cc[VMIN] = 5;
   tcflush(fd, TCIFLUH);
   tcsetattr(fd, TCSANOW,&ctl_port);

}
   


