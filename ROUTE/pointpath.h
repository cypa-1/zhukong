/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __POINTPATH_H
#define __POINTPATH_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "MyTypeDef.h"
/* Exported macro ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
extern int Point_NowNum;
extern int Point_StartNum;
extern int Point_EndNum;


/* Exported function prototype -----------------------------------------------*/
void SetPointPath(int sta_num,int end_num);
void GoPointPath(struct PID Pid_ang,struct PID Pid_dis);
void handleToSide(struct PID Pid_ang,struct PID Pid_dis,int startNode);


#endif 

/**********************************END OF FILE*********************************/
