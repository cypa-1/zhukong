
/* Includes ------------------------------------------------------------------*/
#include "all.h"


 /*作者：李辰瑞
   描述：算出相近两点间的速度，速度方向，角速度(弧度)并赋值给四个轮子
   输入：两点 坐标 速度 速度方向 车体方向 PID角度，距离参数
	 输出：无
	 */
	 
	void point_vel( struct Path_Point start,struct Path_Point end,struct PID Pid_ang,struct PID Pid_dis)
	{
		struct Point Speed_start,Speed_end,Speed_delta,err_outspd;
		float err_dis,err_angle,Vout_angle,Vout_dis,err_outw,outspd,outspddir;
		
		Speed_start.x = start.speed*sin(start.pos);
		Speed_start.y = start.speed*cos(start.pos);
		
		Speed_end.x = end.speed*sin(start.pos);
		Speed_end.y = end.speed*cos(start.pos);
		
		Speed_delta.x = Speed_end.x-Speed_start.x;
		Speed_delta.y = Speed_end.y-Speed_start.y;
		
		err_angle = start.pos - GPS.radian;
		err_dis = (GPS.position.x-start.position.x)*cos(start.speeddir)
             -(GPS.position.y-start.position.y)*sin(start.speeddir);
		
		while(err_angle>pi)
        err_angle-=2*pi;
    while(err_angle<-pi)
        err_angle+=2*pi;
		
		Vout_angle = 1000*AnglePID(err_angle,Pid_ang);
		Vout_dis = DistancePID(err_dis,Pid_dis);
		
		err_outspd.x = -Vout_dis*cos(start.speeddir);
		err_outspd.y =  Vout_dis*sin(start.speeddir);
		
		Speed_delta.x += err_outspd.x;
		Speed_delta.x += err_outspd.y;
		
		outspd = sqrtf(Speed_delta.x*Speed_delta.x+Speed_delta.y*Speed_delta.y);
		outspddir = aatan(Speed_delta.x,Speed_delta.y);
		err_outw = Vout_angle;
		 
		Wheel_Vel( outspd, outspddir, err_outw, start.pos);
	}

	