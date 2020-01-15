#ifndef _BASICMOVEMENT_H
#define _BASICMOVEMENT_H

#include "all.h"

//点结构体
typedef struct Point Position;

typedef struct
{
    double wheelvel;  //轮毂速度，可正可负，为负电机转动方向反向
    double wheelangle; //轮毂平面与车身纵轴正前方夹角，顺时针为正，大小位于-pi/2至pi/2之间
}wheelspeed_para;

struct wheel
{
    wheelspeed_para fl;//前左轮
    wheelspeed_para fr;//前右轮
    wheelspeed_para bl;//后左轮
    wheelspeed_para br;//后右轮
};


#define LENGTH_FB 4  //车身前后轮长度
#define LENGTH_LR 4  //车身左右轮长度
extern struct wheel WheelsSpeed[2];

void InitWheelsSpeed(void);
void InitGPS_List(void);
double GetVectorRadian(Position P);
void GetWheelsSpeed_Cycle(struct Point M, double w0);
void GetWheelsSpeed_Line(double v, double theta);
#endif 
