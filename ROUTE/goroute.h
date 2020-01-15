/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GOROUTE_H
#define __GOROUTE_H

/* Includes ------------------------------------------------------------------*/
#include <stm32f4xx.h>
 


/* Exported macro ------------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
extern u8 Route_Num;
extern u8 RouteFinish;
extern struct Path_Point *PointRoute;
extern struct Route RouteParemeter;
extern struct Process GameState[];
extern char *RouteName;
extern u8 correct_times;


struct Route
    {
        int Escon_Duty;
        int Grab_Loc;
        int Grab_Speed;
        int Cover_Speed;
        int Handspike_location;
    };

typedef enum
{
     Preparation            = 0,
     ForestGo               = 1,
     Bridge                 = 2,    
     PassGerege             = 3,
     GrabShagai_1           = 4,
     WatingForDog           = 5,
     GoThrowingZone_1       = 6,
     ThrowShagai_1          = 7,
     Back2Gobi_1            = 8,
     GrabShagai_2           = 9,
     GoThrowingZone_2       = 10,
     ThrowShagai_2          = 11,
     Back2Gobi_2            = 12,
     GrabShagai_3           = 13,
     GoThrowingZone_3       = 14,
     ThrowShagai_3          = 15
}Process_TYPE;

typedef enum
{
     PreparationOK      = 0,
     Gerege_Prep_OK     = 1,
     GrabShagaiOK_1     = 2,
     ThrowShagaiOK_1    = 3,
     Grab_Prep_OK_1     = 4,
     GrabShagaiOK_2     = 5,
     ThrowShagaiOK_2    = 6,
     Grab_Prep_OK_2     = 7,
     GrabShagaiOK_3     = 8,
     ThrowShagaiOK_3    = 9,
    
   GeregeOK                    = 125,
     Nothing                    = 0

}MISO_Achieve;

struct Process
    {
        Process_TYPE    process;
        u8              LaserIndex; //某段路径结束的时候是否用激光来更新坐标信息
        MISO_Achieve    flag_type1;
        float           Speed_factor;
        u8              anglePID;
        u8              disPID;
        char*           name;
        void            (*MenuFunc)(void);            //入口函数        
        int             RouteIndex;//指某段路径开头对应的节点
    };
/* Exported function prototype -----------------------------------------------*/
/* Exported function prototype -----------------------------------------------*/

void Go_RouteV1(u8 start_process);
void Keep2Shagai(void);
void NormalGoRoute(int start_point, int end_point,struct PID ang_pid,struct PID dis_pid);
 
    
#endif 

/**********************************END OF FILE*********************************/


