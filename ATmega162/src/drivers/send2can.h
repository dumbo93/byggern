/*
 * send2can.h.h
 *
 * Created: 25.10.2017 10:35:24
 *  Author: ingunnjv
 */ 


#ifndef SEND2CAN_H_
#define SEND2CAN_H_

#define NEGATIVE 0
#define POSITIVE 1
void SEND2CAN_send_joy_pos_x();
void SEND2CAN_send_slider_pos();
void SEND2CAN_touch_button_pressed();
void SEND2CAN_send_speed(int speed);

#endif /* SEND2CAN_H_ */