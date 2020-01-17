 #ifndef _ROUTE_H
 #define _ROUTE_H
 #include "all.h"
 typedef struct
{
	float wheelvel;
	float wheelangle;
}wheel_para;
 
 struct wheel
{
	wheel_para fl;
	wheel_para fr;
	wheel_para bl;
	wheel_para br;
	
};
float aatan(float x,float y);
void Wheel_Vel(float vel,float direction,float omega,float pose_angle);
void set_motor(struct wheel Wheel);



#endif



