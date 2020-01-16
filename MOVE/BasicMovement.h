#ifndef _BASICMOVEMENT_H
#define _BASICMOVEMENT_H

#include "all.h"

//点结构体
typedef struct Point Position;



#define LENGTH_FB 4  //车身前后轮长度
#define LENGTH_LR 4  //车身左右轮长度
extern struct wheel WheelsSpeed;

void InitWheelsSpeed(void);
void InitGPS_List(void);
double GetVectorRadian(Position P);
void GetWheelsSpeed_Cycle(struct Point M, double w0);
void GetWheelsSpeed_Line(double v, double theta);
void Run_Line(double v,double theta);
void Run_Cycle(struct Point M, double w0);
#endif 
