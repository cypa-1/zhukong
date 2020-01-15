 #include "all.h"
 /* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "PointRoute.h"
#include "math.h"
#include "m_route.h"
#include "m_sys.h"
#include "stdio.h"
#include "goroute.h"
#include "RouteFunction.h"

extern float S_Factor;
u8 Route_Num=1;
u8 Reach_the_peak=0;
u8 correct_times = 0;
u8 goRouteing = 0;
extern u8 stickFlag;

struct Route RouteParemeter=
//Escon_Duty    Grab_Loc    Grab_Speed    Cover_Speed        Handspike_location
    {800,       80000,      500,            0 ,                    0}; 

u16 *Flag_Address[]={&MISO_CONTINUE_FLAG};
char *RouteName = "//4.29nightRectangle1.0";

struct Process GameState[]={
//process               LaserIndex  flag_type1      Speed_factor    anglePID    disPID      Name                    Func                RouteIndex    
    {Preparation,       0,          PreparationOK,      0.8,        6,          7,          "Preparation",          noAction,           0       },                    //0
    {ForestGo,          0,          Nothing,            0.8,        8,          9,          "ForestGo",             diffPidInForest,    188   },//??1        //1
    {Bridge,            0,          Nothing,            0.8,        10,         11,         "Bridge",               diffPidInBridge,    2188    },//??3      //2
    {PassGerege,        0,          Gerege_Prep_OK,     0.86,        12,         13,         "PassGerege",          fpassGerege,       2668    },//??5        //3
    {GrabShagai_1,      0,          GrabShagaiOK_1,     0.8,        12,         13,         "GrabShagai_1",         Keep2Shagai,        4081    },//??6???        //4
    {WatingForDog,      0,          Nothing,            0.8,        14,         15,         "WatingForDog",         WatingtoCorrect,    4915    },//??7        //5
    {GoThrowingZone_1,  0,          Nothing,            0.8,        14,         15,         "GoThrowingZone_1",     beforeThrowShagai,  5936    },//??8        //6
    {ThrowShagai_1,     0,          ThrowShagaiOK_1,    0.8,        14,         15,         "ThrowShagai_1",        noAction,           6801    },//??9        //7
    {Back2Gobi_1,       0,          Grab_Prep_OK_1,     0.6,        16,         17,         "Back2Gobi_1",          fGetShagai,         6801    },//??9        //8
    {GrabShagai_2,      0,          GrabShagaiOK_2,     0.8,        16,         17,         "GrabShagai_2",         noAction,           7782    },//??11    //9
    {GoThrowingZone_2,  0,          Nothing,            0.8,        18,         19,         "GoThrowingZone_2",     fGoZone,            7782    },//??11    //10
    {ThrowShagai_2,     0,          ThrowShagaiOK_2,    0.8,        18,         19,         "ThrowShagai_2",        noAction,           8793    },//??13    //11
    {Back2Gobi_2,       0,          Grab_Prep_OK_2,     0.6,        16,         17,         "Back2Gobi_2",          fGetShagai,         8793    },//??13    //12
    {GrabShagai_3,      0,          GrabShagaiOK_3,     0.8,        16,         17,         "GrabShagai_3",         noAction,            9994    },//??15    //13
    {GoThrowingZone_3,  0,          Nothing,            0.8,        18,         19,         "GoThrowingZone_3",     fGoZone,           9994    },//??15    //14
    {ThrowShagai_3,     0,          ThrowShagaiOK_3,    0.8,        18,         19,         "ThrowShagai_3",        noAction,           10995    } //??17    //15
};
u8 RouteFinish;
extern UserTimer *globalTimer;
extern struct PID Pid_List[];



/* 
 * ???: Go_Route
 * ?  ?: ????
 * ?  ?: route_num?????@1,2,3,4,5,6,7,8
                    Model @1???,0???
 * ?  ?: ?
 * ?  ?: ????
 */

void Go_RouteV1(u8 start_process)
{
    uint8_t Next_Game_Process;
    rt_uint32_t HandleOff;
    rt_uint32_t Gothrowing;
    Next_Game_Process = start_process;
    Now_Process = start_process;
    Com_SendByte(4, Now_Process);
    MISO_CONTINUE_FLAG = Nothing;
    Reach_the_peak = 0;
    goRouteing = 1;
    stickFlag = 0;

    while(1)
    {
        
        /****************************???******************************/
        if(Now_Process == Next_Game_Process)
        {
            Next_Game_Process++;
            S_Factor = GameState[Now_Process].Speed_factor;
            if(S_Factor > 1.2)
            {
                S_Factor = 0.2;
            }
            GameState[Now_Process].MenuFunc();            
        }
        
        /****************************LCD??******************************/
        LCD_Clear();
        LCD_SetXY(0,0);
        LCD_WriteString("Now:");
        LCD_WriteInt(Now_Process);
        LCD_SetXY(0,1);
        LCD_WriteString("Next:");
        LCD_WriteInt(Next_Game_Process);
        LCD_SetXY(0,2);
        LCD_WriteString("ContinueFlag:");
        LCD_WriteInt(MISO_CONTINUE_FLAG);
        LCD_SetXY(0,3);
        LCD_WriteString("Correct:");
        LCD_WriteInt(correct_times);
    
        
        /****************************Handledetect******************************/        
        if(HANDLE_MODE_MANUAL)
        {
//            level = rt_hw_interrupt_disable();    
//            rt_thread_handle_init();                        //??????
//            rt_hw_interrupt_enable(level);
            if(rt_mb_recv(&Mb_Handle, &HandleOff, RT_WAITING_FOREVER) == RT_EOK)
            {            
//                level = rt_hw_interrupt_disable();    
//                rt_thread_detach(&thread_handle);    //??????
//                rt_hw_interrupt_enable(level);
            }
           Back2Auto();        //???????
        }
        

        /****************************????******************************/        
        if((Reach_the_peak == 0) && (Now_Process == WatingForDog))
        {
                while(1)
                {
                    SetSpeed(0,0,0);
                    LCD_Clear();
                    LCD_SetXY(0,0);
                    LCD_WriteString("Wating for the dog ! Let us go to the top!! Win!!!");
                    SetSpeed(0,0,0);

                    
                    if(rt_mb_recv(&Mb_Key, &Gothrowing, RT_WAITING_NO) == RT_EOK)
                    {
                        if(Gothrowing == keyOK || Gothrowing == keyHandle4 || Gothrowing == keydelete)
                        {
                            Reach_the_peak = 1;
                            break;
                        }
                    }
                }
        }
        
        /****************************flagdetect******************************/
        if(MISO_CONTINUE_FLAG == GameState[Now_Process].flag_type1)
        {
                if(Now_Process == ThrowShagai_3)
                {
//                     Elmo_Shut_Down(All);
                    goRouteing = 0;
                    stickFlag = 0;

                    return;
                }
                MISO_CONTINUE_FLAG = Nothing;
                Now_Process++;
                Com_SendByte(4, Now_Process);

                
        }
        else
        {
            SetSpeed(0,0,0);
        }
        Delay_ms(10);
    } 
    
}


/* 
 * ???: NormalGoRoute
 * ?  ?: ???????????????
 * ?  ?: ???????
 * ?  ?: 
 * ?  ?: ????
 */

void NormalGoRoute(int start_point, int end_point,struct PID ang_pid,struct PID dis_pid)
{
        SetPointPath(start_point,end_point);
        while (HANDLE_MODE_AUTO)
        {
            GoPointPath(ang_pid,dis_pid);
            if(Point_NowNum>Point_EndNum-2)
            {
                RouteFinish=1;
                break;
            }
            Delay_ms(2);
        }
        return;
}

/* 
 * ???: LaserGoRoute
 * ?  ?: ???????????????????
 * ?  ?: ???????
 * ?  ?: ????????
 * ?  ?: ????
 */
void LaserGoRoute(int start_point, int end_point,struct PID ang_pid,struct PID dis_pid, u8 Index)
{
    int times;
    int i;
    int NextTerminal;
    int NowPoint;

    times = LaserPara[Index].DetectTimes;
    NowPoint = start_point;
    if((times * LaserPara[Index].DetectLength) < (end_point - start_point))  //???????????,???????????n?,???????????
    {
        for(i=0;i<times;i++)
        {
            NextTerminal = start_point + i *  LaserPara[Index].DetectLength;
            SetPointPath(NowPoint,NextTerminal);    //????????????????            
            while (HANDLE_MODE_AUTO)    //??????
            {
                GoPointPath(ang_pid,dis_pid);
                LCD_SetXY(0,3);
                LCD_WriteString("NextTerminal:");
                LCD_WriteInt(NextTerminal);
                if(Point_NowNum>Point_EndNum-2)
                {
                    RouteFinish=1;
                    break;
                }
                Delay_ms(5);
            }
            
            NowPoint = LaserCorrectGPS(Index); //??????????????
        }
        
        SetPointPath(NowPoint,end_point);    //??????????????????
        while (HANDLE_MODE_AUTO)
            {
                GoPointPath(ang_pid,dis_pid);
                if(Point_NowNum>Point_EndNum-2)
                {
                    RouteFinish=1;
                    break;
                }
                Delay_ms(1);
            }
    }
    else//??????????,?????,?????
    {
        SetPointPath(start_point,end_point);
        while (HANDLE_MODE_AUTO)
        {
            GoPointPath(ang_pid,dis_pid);
            if(Point_NowNum>Point_EndNum-2)
            {
                RouteFinish=1;
                break;
            }
            Delay_ms(1);
        }
    }
    return;
}
