#include "BasicMovement.h"

struct wheel WheelsSpeed[2];//WheelsSpeed[0]保留各轮最新速度,WheelsSpeed[1]上一次速度

/*
 * 函数名: InitWheelsSpeed
 * 描  述: 初始化变量WheelsSpeed[2]。
 * 输  入：向量P
 * 输  出: 向量P与车身坐标系y轴正方向夹角
 * 调  用: 外部调用
 */
void InitWheelsSpeed(void)
{
	int i = 0;
	for (; i < 2; i++)
	{
		WheelsSpeed[i].bl.wheelangle = 0;
		WheelsSpeed[i].bl.wheelvel = 0;
		WheelsSpeed[i].fl.wheelangle = 0;
		WheelsSpeed[i].fl.wheelvel = 0;
		WheelsSpeed[i].br.wheelangle = 0;
		WheelsSpeed[i].br.wheelvel = 0;
		WheelsSpeed[i].fr.wheelangle = 0;
		WheelsSpeed[i].fr.wheelvel = 0;
	}
}

/*
 * 函数名: GetVectorRadian
 * 描  述: 求向量P与车身坐标系y轴正方向夹角，顺时针为正,采用弧度制。
 * 输  入：向量P
 * 输  出: 向量P与车身坐标系y轴正方向夹角
 * 调  用: 外部调用
 */
double GetVectorRadian(Position P)
{
	double radian = 0;
	if (P.x > 0)
		radian = pi / 2 - atan(P.y / P.x);
	else if (P.x < 0)
		radian = -pi / 2 - atan(P.y / P.x);
	else
	{
		if (P.y > 0)
			radian = 0;
		else if (P.y < 0)
			radian = pi;
	}
	return radian;
}

/*
 * 函数名: WheelsSpeed_Cycle
 * 描  述: 求绕M点以角速度w0(顺时针为正，弧度制）旋转时四个轮子的速度大小和以及速度与车身坐标系y轴正方向夹角，顺时针为正
           夹角位于-pi/2~pi/2,采用弧度制。
 * 输  入：点P绝对空间坐标以及角速度w0，车身GPS坐标b变量GPS
 * 输  出: 四个轮子的速度大小和以及速度与车身坐标系y轴夹角变量WheelsSpeed[0]
 * 调  用: 外部调用
 */
void GetWheelsSpeed_Cycle(struct Point M, double w0)
{
	WheelsSpeed[1] = WheelsSpeed[0];
	
	struct Point TempPosition, TempPosition1;
//TempPosition存储轮子到转圈的向量
	TempPosition1.x = (GPS.position.y - M.y - LENGTH_LR / 2 * sin(GPS.radian) + LENGTH_FB / 2 * cos(GPS.radian));
	TempPosition1.y = (-GPS.position.x + M.x - LENGTH_FB / 2 * sin(GPS.radian) - LENGTH_LR / 2 * cos(GPS.radian));
	TempPosition.x = -TempPosition1.y;
	TempPosition.y = TempPosition1.x;
	WheelsSpeed[0].fr.wheelvel = GetLength(M, TempPosition) * fabs(w0);	
	WheelsSpeed[0].fr.wheelangle = GetVectorRadian(TempPosition1)-GPS.radian;	
	if (WheelsSpeed[0].fr.wheelangle > pi / 2)
	{
		WheelsSpeed[0].fr.wheelangle -= pi;
		WheelsSpeed[0].fr.wheelvel = -WheelsSpeed[0].fr.wheelvel;
	}
	if (WheelsSpeed[0].fr.wheelangle < -pi / 2)
	{
		WheelsSpeed[0].fr.wheelangle += pi;
		WheelsSpeed[0].fr.wheelvel = -WheelsSpeed[0].fr.wheelvel;
	}
	WheelsSpeed[0].fr.wheelangle = WheelsSpeed[0].fr.wheelangle / pi * 180;
	/**********************************/

	TempPosition1.x = (GPS.position.y - M.y + LENGTH_LR / 2 * sin(GPS.radian) + LENGTH_FB / 2 * cos(GPS.radian));
	TempPosition1.y = (-GPS.position.x + M.x - LENGTH_FB / 2 * sin(GPS.radian) + LENGTH_LR / 2 * cos(GPS.radian));
	TempPosition.x = -TempPosition1.y;
	TempPosition.y = TempPosition1.x;
	
	WheelsSpeed[0].fl.wheelvel = GetLength(M, TempPosition) * fabs(w0);
	WheelsSpeed[0].fl.wheelangle = GetVectorRadian(TempPosition1) - GPS.radian;

	if (WheelsSpeed[0].fl.wheelangle > pi / 2)
	{
		WheelsSpeed[0].fl.wheelangle -= pi;
		WheelsSpeed[0].fl.wheelvel = -WheelsSpeed[0].fl.wheelvel;
	}
	if (WheelsSpeed[0].fl.wheelangle < -pi / 2)
	{
		WheelsSpeed[0].fl.wheelangle += pi;
		WheelsSpeed[0].fl.wheelvel = -WheelsSpeed[0].fl.wheelvel;
	}

	/**********************************/

	TempPosition1.x = (GPS.position.y - M.y + LENGTH_LR / 2 * sin(GPS.radian) - LENGTH_FB / 2 * cos(GPS.radian));
	TempPosition1.y = (-GPS.position.x + M.x + LENGTH_FB / 2 * sin(GPS.radian) + LENGTH_LR / 2 * cos(GPS.radian));
	TempPosition.x = -TempPosition1.y;
	TempPosition.y = TempPosition1.x;
	
	WheelsSpeed[0].bl.wheelvel = GetLength(M, TempPosition) * fabs(w0);
	WheelsSpeed[0].bl.wheelangle = GetVectorRadian(TempPosition1) - GPS.radian;
	
	if (WheelsSpeed[0].bl.wheelangle > pi / 2)
	{
		WheelsSpeed[0].bl.wheelangle -= pi;
		WheelsSpeed[0].bl.wheelvel = -WheelsSpeed[0].bl.wheelvel;
	}
	if (WheelsSpeed[0].bl.wheelangle < -pi / 2)
	{
		WheelsSpeed[0].bl.wheelangle += pi;
		WheelsSpeed[0].bl.wheelvel = -WheelsSpeed[0].bl.wheelvel;
	}
	
	/**********************************/

	TempPosition1.x = (GPS.position.y - M.y - LENGTH_LR / 2 * sin(GPS.radian) - LENGTH_FB / 2 * cos(GPS.radian));
	TempPosition1.y = (-GPS.position.x + M.x + LENGTH_FB / 2 * sin(GPS.radian) - LENGTH_LR / 2 * cos(GPS.radian));
	TempPosition.x = -TempPosition1.y;
	TempPosition.y = TempPosition1.x;
	
	WheelsSpeed[0].br.wheelvel = GetLength(M, TempPosition) * fabs(w0);
	WheelsSpeed[0].br.wheelangle = GetVectorRadian(TempPosition1) - GPS.radian;
	
	if (WheelsSpeed[0].br.wheelangle > pi / 2)
	{
		WheelsSpeed[0].br.wheelangle -= pi;
		WheelsSpeed[0].br.wheelvel = -WheelsSpeed[0].br.wheelvel;
	}
	if (WheelsSpeed[0].br.wheelangle < -pi / 2)
	{
		WheelsSpeed[0].br.wheelangle += pi;
		WheelsSpeed[0].br.wheelvel = -WheelsSpeed[0].br.wheelvel;
	}

}

/*
 * 函数名: GetWheelsSpeed_Line
 * 描  述: 求车子以速率v,沿与绝对坐标系y轴正方向夹角theta方向直行时四个轮子的速度大小和以及速度与车身坐标系y轴正方向夹角，顺时针为正
		   夹角位于-90~90,采用角度制。
 * 输  入：速率v，夹角theta
 * 输  出: 四个轮子的速度大小和以及速度与车身坐标系y轴夹角变量WheelsSpeed[0]
 * 调  用: 外部调用
 */
void GetWheelsSpeed_Line(double v,double theta)
{
	WheelsSpeed[1] = WheelsSpeed[0];
	WheelsSpeed[0].bl.wheelvel = WheelsSpeed[0].br.wheelvel = WheelsSpeed[0].fl.wheelvel = WheelsSpeed[0].fl.wheelvel = v;
	theta = (theta - GPS.radian);
	if (theta> pi/2)
	{
		WheelsSpeed[0].br.wheelangle =theta- pi;
		WheelsSpeed[0].bl.wheelvel = WheelsSpeed[0].br.wheelvel = WheelsSpeed[0].fl.wheelvel = WheelsSpeed[0].fl.wheelvel = -v;
	}
	if (theta <- pi/2)
	{
		WheelsSpeed[0].br.wheelangle = theta + pi;
		WheelsSpeed[0].bl.wheelvel = WheelsSpeed[0].br.wheelvel = WheelsSpeed[0].fl.wheelvel = WheelsSpeed[0].fl.wheelvel = -v;
	}
}

void Set_WheelLoc (int WheelID , float WheelDiraction)
{
	Mode[WheelID] = Location_Mode ;
	set_loc[WheelID] = 8192.0 * 140.0 / 360.0 * WheelDiraction ;
}


//赋给轮子速度 ，mm/s
void Set_OdriveSpd ( int WheelID , float OdriveSpeed )
{
	double n ; //达到OdriveSpeed所需赋给odrive的对应的值
	n = OdriveSpeed * 8192.0 / 3.1415926 / 105.0 ;
	
 	if ( WheelID == 0 )
	{
		USART_printf( USART1 , " v 0 %lf 0\n ",n) ;
	}
	
	 	if ( WheelID == 1 )
	{
		USART_printf( USART3 , " v 0 %lf 0\n ",n) ;
	}

	 	if ( WheelID == 2 )
	{
		USART_printf( USART1 , " v 1 %lf 0\n ",n) ;
	}
	
	 	if ( WheelID == 3 )
	{
		USART_printf( USART3 , " v 1 %lf 0\n ",n) ;
	}
}


/*
描述：将四轮速度及方向赋给电机
输入：四轮分速度及方向
输出：无
*/
void set_motor(struct wheel Wheel)
{
	Set_WheelLoc(1,Wheel.fl.wheelangle);
	Set_WheelLoc(2,Wheel.fr.wheelangle);
	Set_WheelLoc(3,Wheel.bl.wheelangle);
	Set_WheelLoc(4,Wheel.br.wheelangle);
	
	Set_OdriveSpd(0,Wheel.fl.wheelvel);
	Set_OdriveSpd(1,Wheel.fr.wheelvel);
	Set_OdriveSpd(2,Wheel.bl.wheelvel);
	Set_OdriveSpd(3,Wheel.br.wheelvel);
}


double car_para[3]={300.0f,365.0f,0.8828330147f};//长 ，宽 ，y轴与车对角线角度（正）
float r=236.2334650;
//规定顺时针omega为正，direction，1，4象限为正，2，3象限为负
float factor=1.0f;// 

float aatan(float x,float y) 
{
	double a;
	if(x==0)
		{
		if(y>0)
			a=pi/2;
		else
			a=-pi/2;
		}
	else
		{a=atan(y/x);
	   if(y<0&&x<0)
		{
		a=a;
		factor=-1.0;
		} 
	   if(y<0&&x>0)
		{a=a+pi;
		factor=-1.0; 
		} 
	   if(y>0&&x>0)
		{
		a=a;
		factor=1.0;
		} 
	   if(y>0&&x<0)
		{a=a+pi;
		factor=1.0;
		} 
        }
 
		return a;
}
 
struct wheel anotherWheelsSpeed;


/*
输入：绝对坐标系的目标速度，目标速度方向，目标角速度，车相对于绝对坐标系方向（目前的）
输出：每个轮子的速度及速度方向（车身坐标系）
*/
struct wheel Wheel_vel(float vel,float direction,float omega,float pose_angle) //角度相关为弧度制
{
	Position p,p1;
 struct wheel WHEEL;
	float v;
	float d;
	float w;
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
 
	WHEEL.fl.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	WHEEL.fl.wheelangle=90.0-aatan((p1.x+p.x),(p1.y+p.y))/PI*180.0;
 
		
	p.x=w*r*sin(car_para[2]);
	p.y=-w*r*cos(car_para[2]);
	WHEEL.fr.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	WHEEL.fr.wheelangle=90.0f-aatan((p1.x+p.x),(p1.y+p.y))/PI*180;
	
	p.x=-w*r*sin(car_para[2]);
	p.y=w*r*cos(car_para[2]);
	WHEEL.bl.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	WHEEL.bl.wheelangle=90.0f-aatan((p1.x+p.x),(p1.y+p.y))/PI*180;
	
	p.x=-w*r*sin(car_para[2]);
	p.y=-w*r*cos(car_para[2]);
	WHEEL.br.wheelvel=factor*sqrtf((p1.x+p.x)*(p1.x+p.x)+(p1.y+p.y)*(p1.y+p.y));
	WHEEL.br.wheelangle=90.0f-aatan((p1.x+p.x),(p1.y+p.y))/PI*180;
	
	return WHEEL;
}
