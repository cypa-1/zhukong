#include "all.h"


typedef struct
	{
		double x;
		double y;
	}Positio;
double car_para[3]={300.0f,365.0f,0.8828330147f};//长 ，宽 ，y轴与车对角线角度（正）
double r=236.2334650;
//规定顺时针omega为正，direction，1，4象限为正，2，3象限为负
double factor=1.0f;// 电机正反转因子

double aatan(double x,double y) 
{
	double a;
	if(x==0)
		{
		if(y>0)
			a=PI/2;
		else
			a=-PI/2;
		}
	else
		{a=atan(y/x);
	   if(y<0&&x<0)
		{
		a=a;
		factor=-1.0;
		} 
	   if(y<0&&x>0)
		{a=a+PI;
		factor=-1.0; 
		} 
	   if(y>0&&x>0)
		{
		a=a;
		factor=1.0;
		} 
	   if(y>0&&x<0)
		{a=a+PI;
		factor=1.0;
		} 
        }
 
		return a;
}
 
 
/*
描述：将绝对坐标系车速度，自转分解为四个直轮的速度方向
输入：绝对坐标系的目标速度，目标速度方向，目标角速度，车相对于绝对坐标系方向（目前的）
输出：每个轮子的速度及速度方向（车身坐标系）
*/
void Wheel_Vel(double vel,double direction,double omega,double pose_angle) //角度相关为弧度制
{
	Positio p,p1;
 struct wheel WHEEL;
	double v;
	double d;
	double w;
 //转换至车身坐标系
	v=vel;
	d=direction-pose_angle;
	w=omega;
	//四轮分速度
		v=vel;
	d=direction-pose_angle;
	w=omega;
 
	p1.x=v*sin(d);
	p1.y=v*cos(d);
 
	p.x=w*r*sin(car_para[2]);
	p.y=w*r*cos(car_para[2]);
 
	
	WHEEL.fl.wheelangle=-90.0+aatan((p1.x+p.x),(p1.y+p.y))/PI*180.0;
  WHEEL.fl.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
		
	p.x=w*r*sin(car_para[2]);
	p.y=-w*r*cos(car_para[2]);
	
	WHEEL.fr.wheelangle=-90.0+aatan((p1.x+p.x),(p1.y+p.y))/PI*180.0;
	WHEEL.fr.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	
	p.x=-w*r*sin(car_para[2]);
	p.y=w*r*cos(car_para[2]);
	
	WHEEL.bl.wheelangle=-90.0+aatan((p1.x+p.x),(p1.y+p.y))/PI*180.0;
	WHEEL.bl.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	
	p.x=-w*r*sin(car_para[2]);
	p.y=-w*r*cos(car_para[2]);
	
	
	WHEEL.br.wheelangle=-90.0+aatan((p1.x+p.x),(p1.y+p.y))/PI*180.0;
	WHEEL.br.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	
	set_motor(WHEEL);
}


/*
描述：将四轮速度及方向赋给电机
输入：四轮分速度及方向
输出：无
*/
void set_motor(struct wheel Wheel)
{
	Set_WheelLoc(0,Wheel.fl.wheelangle);
	Set_WheelLoc(1,Wheel.fr.wheelangle);
	Set_WheelLoc(2,Wheel.bl.wheelangle);
	Set_WheelLoc(3,Wheel.br.wheelangle);
	
	Set_OdriveSpd(0,Wheel.fl.wheelvel);
	Set_OdriveSpd(1,Wheel.fr.wheelvel);
	Set_OdriveSpd(2,Wheel.bl.wheelvel);
	Set_OdriveSpd(3,Wheel.br.wheelvel);
}
