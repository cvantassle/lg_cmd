/* this is the Client part of the lg_cmd deamon.
   This is intended to be called from lirc and it will send commands to the control deamon
   Options are v for volume, m for mute, h1-3 for HDMI inputs, r for rgb, o for on, f for off
   a# for avi input, c# for composit
*/

#include "commands.h"

int main(int argc, char *argv[])
{
   if(argc != 2)
   {
      fputs("Not enough arguments or to many arguments\n",stderr);
      exit 1;
   }

   switch(getopt(argc, argv, "v:h:rofa:c:"))
   {
   case 'v':
      break;
   case 'h':
      break;
   case 'r':
      break;
   case 'o':
      break;
   case 'f':
      break;
   case 'a':
      break;
   case 'c':
      break;
   default:
      break;
   }
   
}
