 #include "all.h"
 
 typedef struct
{
	double wheelvel;
	double wheelangle;
}wheel_para;
 
 struct wheel
{
	wheel_para fl;
	wheel_para fr;
	wheel_para bl;
	wheel_para br;
	
};
double aatan(double x,double y);
void Wheel_Vel(double vel,double direction,double omega,double pose_angle);
void set_motor(struct wheel Wheel);




 