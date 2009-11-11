/*
 * This will be the definations for the Commands to control the TV
 * There are 2 sets. One set is sent, the other is returned from the TV
 * to indicate the command status
 */


#DEFINE ON 01
#DEFINE OFF 00
#DEFINE TV 10
#DEFINE AVI1 20
#DEFINE AVI2 21
#DEFINE COMP1 40
#DEFINE COMP2 41
#DEFINE RGB 60
#DEFINE HDMI1 90
#DEFINE HDMI2 91
#DEFINE HDMI3 92

/* Commands set to the tv */

#DEFINE S_POWER(set,state) ka set state

/*
 * Input Selection data controls 
 * 10: TV
 * 20: AVI-1 21: AVI-2
 * 40: Componsent-1 41: Componsent-2
 * 60: RGB-PC
 * 90: HDMI-1 91: HDMI-2 92: HDMI-3 
 */
#DEFINE S_INPUT(set,source) xb state source
#DEFINE S_SCREEN_MUTE(set) kd set state
#DEFINE S_VOL_MUTE(set,state) ke set state
#DEFINE S_VOL_CTL(set,vol) kf set vol

/*
 * Return data from the tv
 */

#DEFINE R_POWER_SUCCESS(set)
#DEFINE R_POWER_FAILURE(set)
#DEFINE R_INPUT
#DEFINE R_SCREEN_MUTE
#DEFINE R_VOL_MUTE
#DEFINE R_VOL_UP
#DEFINE R_VOL_DN




 
