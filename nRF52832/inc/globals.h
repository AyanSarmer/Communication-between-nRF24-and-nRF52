#ifndef GLOBALS_H_
#define GLOBALS_H_

#define BUTTON                                              28  
#define BUTTON_0_BIT                                        0
/* encoder rotor parameters */
#define ENCODER_ROTOR_TURN_COUNTER_INIT_VALUE			    7
#define ENCODER_ROTOR_TURN_COUNTER_DIF  				    4
#define ENCODER_ROTOR_TURN_COUNTER_MAX_VALUE			    ENCODER_ROTOR_TURN_COUNTER_INIT_VALUE + ENCODER_ROTOR_TURN_COUNTER_DIF
#define ENCODER_ROTOR_TURN_COUNTER_MIN_VALUE			    ENCODER_ROTOR_TURN_COUNTER_INIT_VALUE - ENCODER_ROTOR_TURN_COUNTER_DIF 
/* encoderRotorFlag states */
#define ENCODER_ROTOR_STOPPED                               0
#define ENCODER_ROTOR_TURNED_CLOCK_WISE                     1
#define ENCODER_ROTOR_TURNED_COUNTER_CLOCK_WISE             2
/* motor states */
#define MOTOR_IS_OFF                                        0
#define MOTOR_IS_ON                                         1

typedef struct Device
{
    volatile unsigned char buttonFlag;
    volatile unsigned char buttonsState;  
    volatile unsigned char timerCounter;  
    unsigned char timeSetEncoderRotorSate                   :2;    
    unsigned char motorState                                :1; 
    volatile unsigned int milliSecondsCounter;     
    volatile unsigned char oneSecondFlag                    :1;  
    unsigned char currentTime;        
} Device;
extern struct Device device;

#endif /* GLOBALS_H_ */