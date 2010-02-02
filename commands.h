/*
 * This will be the definations for the Commands to control the TV
 * There are 2 sets. One set is sent, the other is returned from the TV
 * to indicate the command status
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


#define ON 01
#define OFF 00
#define TV 10
#define AVI1 20
#define AVI2 21
#define COMP1 40
#define COMP2 41
#define RGB 60
#define HDMI1 90
#define HDMI2 91
#define HDMI3 92
#define VOLUP 100
#define VOLDN 110
#define MUTE  111


/* Commands set to the tv */

#define S_POWER(set,state) ka set state

/*
 * Input Selection data controls 
 * 10: TV
 * 20: AVI-1 21: AVI-2
 * 40: Componsent-1 41: Componsent-2
 * 60: RGB-PC
 * 90: HDMI-1 91: HDMI-2 92: HDMI-3 
 */
#define S_INPUT(set,source) "xb %.2d %.2d",set, source
#define S_SCREEN_MUTE(set) "kd %.2d %.2d", set, state
#define S_VOL_MUTE(set,state) "ke %.2d %2d", set, state
#define S_VOL_CTL(set,vol) "kf %.2d %.2d", set, vol
#define S_PWR_CTL(set,state) "ka %.2d %.2d", set, state

/*
 * Return data from the tv
 */

#define R_POWER_SUCCESS(set,state) a set OK state
#define R_POWER_FAILURE(set,state) a set NG state
#define R_INPUT_SUCCESS(set,source) b set OK source
#define R_INPUT_FAILURE(set,source) b set NG source
#define R_SCREEN_MUTE(set,state) d set OK state
#define R_SCREEN_MUTE_FAILURE(set,state) d set NG state
#define R_MUTE_SUCCESS(set,state) e set OK state
#define R_MUTE_FAILUTRE(set,state) e set NG state
#define R_VOL_SUCCESS(set,vol) f set set OK vol
#define R_VOL_FAILURE(set,vol) f set NG vol



