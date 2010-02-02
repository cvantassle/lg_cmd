
/*
 * This is the Deamon part of the application.
 * This part will mantain the Setting that can not be changed
 * like what the next configured input will be, and what the current
 * volume is at so it can change the volume properly.
 * It will also write out the config file
 */


#include "commands.h"

/* At some point I need to set this to be set via CLI or VIA a config file */
#define SERIALDEV "/dev/ttyS0"
#define CMD_FIFO  "/tmp/lg_cmd"
#define MAX_FD	  3

int get_cmd( char *cmd, int len)
{
   char *newline;
   /* Check and remove newlines */
   if ( (newline = strrchr( cmd, '\n')))
   {
      newline = '\0';
      len--;
   }
   if( !strncmp(cmd,"VOLUP",len)) return VOLUP;
   if( !strncmp(cmd,"VOLDN",len)) return VOLDN;
   if( !strncmp(cmd,"MUTE",len)) return MUTE;
   if( !strncmp(cmd,"ON",len)) return ON;
   if( !strncmp(cmd,"OFF",len)) return OFF;
   if( !strncmp(cmd,"AVI1",len)) return AVI1;
   if( !strncmp(cmd,"AVI2",len)) return AVI2;
   if( !strncmp(cmd,"COMP1",len)) return COMP1;
   if( !strncmp(cmd,"COMP2",len)) return COMP2;
   if( !strncmp(cmd,"RGB",len)) return RGB;
   if( !strncmp(cmd,"HDMI1",len)) return HDMI1;
   if( !strncmp(cmd,"HDMI2",len)) return HDMI2;
   if( !strncmp(cmd,"HDMI3",len)) return HDMI3;

}



int main(int argc, char *argv[])
{
   int serial_fd, fifo_fd, cmd_len, vol = 0, unmute;
   int res = 0;
   pid_t pid;
   char from_tv[20];
   char to_tv[20];
   char cmd[10];
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
      if (( cmd_len = recvfrom(fifo_fd, cmd, 10, 0,(struct sockaddr *) &lg_cmd ,&res)) < 0)
      {
	 perror("recvfrom");
	 exit(1);
      }
      switch( get_cmd(cmd, cmd_len))
	 {
	 case VOLUP:
	    sprintf(to_tv,S_VOL_CTL(tv_id,vol++));
	    printf("VOLUP\n");
	    break;
	    /* vol up*/
	 case VOLDN:
	    sprintf(to_tv,S_VOL_CTL(tv_id,vol--));
	    printf("VOLDN\n");
	    break;
	    /* vol down*/
	 case MUTE:
	    unmute = vol;
	    //strcpy(to_tv,S_VOL_CTL(tv_id,00));
	    sprintf(to_tv,S_VOL_CTL(tv_id,00));
	    break;
	    /* Mute */
	 case ON:
	    sprintf(to_tv,S_PWR_CTL(tv_id,ON));
	    printf("ON\n");
	    break;
	 case OFF:
	    sprintf(to_tv,S_PWR_CTL(tv_id,OFF));
	    printf("OFF\n");
	    break;
	 case AVI1:
	    sprintf(to_tv,S_INPUT(tv_id,AVI1));
	    printf("AVI1\n");
	    break;
	 case AVI2:
	    sprintf(to_tv,S_INPUT(tv_id,AVI2));
	    printf("AVI2\n");
	    break;
	 case COMP1:
	    sprintf(to_tv,S_INPUT(tv_id,COMP1));
	    printf("COMP1\n");
	    break;
	 case COMP2:
	    sprintf(to_tv,S_INPUT(tv_id,COMP2));
	    printf("COMP2\n");
	    break;
	 case RGB:
	    sprintf(to_tv,S_INPUT(tv_id,RGB));
	    printf("RGB\n");
	    break;
	 case HDMI1:
	    sprintf(to_tv,S_INPUT(tv_id,HDMI1));
	    printf("HDMI1\n");
	    break;
	 case HDMI2:
	    sprintf(to_tv,S_INPUT(tv_id,HDMI2));
	    printf("HDMI2\n");
	    break;
	 case HDMI3:
	    sprintf(to_tv,S_INPUT(tv_id,HDMI3));
	    printf("HDMI3\n");
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



