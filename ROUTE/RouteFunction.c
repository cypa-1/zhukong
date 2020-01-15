#include "all.h"
 

#define NODE_2      1188
#define NODE_4      2468


#define SPEEDCHANGE 3593
#define NODE51      3881    //3675

#define PASS_NODE   3718

#define NODE_51_X    4913    //节点6正确点的XY
#define NODE_51_Y    7718

#define NODE_61     4600     //节点61正确点和其X
#define NODE_61_X   5400

#define NODE_71     5174    //节点71正确点和其XY坐标

#define NODE_71_X   5400
#define NODE_71_Y   7718
#define SHOOTNODE   9400

extern float S_Factor;
u8 shaGaiGet = 0;

/* 
 * 函数名: noAction
 * 描  述: 没有其他操作，纯走路径
 * 输  入: 无
 * 输  出: 无
 * 调  用: 外部调用
 */
void noAction(void)
{
    if(GameState[Now_Process].LaserIndex != 0)
    {
        LaserGoRoute(GameState[Now_Process].RouteIndex,GameState[Now_Process + 1].RouteIndex,Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID],GameState[Now_Process].LaserIndex);
    }
    else
    {
        NormalGoRoute(GameState[Now_Process].RouteIndex,GameState[Now_Process + 1].RouteIndex,Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID]);
    }        
}


/* 
 * 函数名: closeFile
 * 描  述: 走路径之外还关闭文件，进行这步操作是因为f_write是写入缓存里，要真正写到文件需要fflush或关闭文件
 * 输  入: 无
 * 输  出: 无
 * 调  用: 外部调用
 */

void closeFile(void)
{
    SD_Printf_MQ(&TestRoute,"//THE END");
    noAction();
}


void diffPidInForest(void)
{
    NormalGoRoute(GameState[Now_Process].RouteIndex,    NODE_2  ,   Pid_List[GameState[Now_Process].anglePID],  Pid_List[GameState[Now_Process].disPID]);
    
    NormalGoRoute(NODE_2    ,   GameState[Now_Process + 1].RouteIndex,  Pid_List[20],  Pid_List[21]);//第三个转弯
}


void diffPidInBridge(void)
{
    NormalGoRoute(GameState[Now_Process].RouteIndex,    NODE_4  ,   Pid_List[GameState[Now_Process].anglePID],  Pid_List[GameState[Now_Process].disPID]);
    
    NormalGoRoute(NODE_4    ,   GameState[Now_Process + 1].RouteIndex,  Pid_List[22],  Pid_List[23]);//过桥后转弯
}


/* 
 * 函数名: Keep2Shagai6_7
 * 描  述: 第一次用激光标定位置
 * 输  入: 无
 * 输  出: 无
 * 调  用: 外部调用
 */
void fpassGerege(void)
{
    SetPointPath(GameState[Now_Process].RouteIndex,GameState[Now_Process + 1].RouteIndex);
    while (HANDLE_MODE_AUTO)
    {
        GoPointPath(Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID]);
        if(Point_NowNum>Point_EndNum-2)
        {
            RouteFinish=1;
            break;
        }
        if(Point_NowNum > SPEEDCHANGE)
        {
            if(GPS.position.x < 0)
            {
                SetSpeed(-400,50,0);
            }
            else
            {
                SetSpeed(400,50,0);                
            }
            Delay_ms(500);
            Delay_ms(300);

            break;
        }
        Delay_ms(2);
    }
      
    
    MOSI_GPS_Y.f64_data = NODE_51_Y;
    Write_Database(W_GPS_Y_ID);
    NormalGoRoute(NODE51,GameState[Now_Process + 1].RouteIndex,Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID]);
    correct_times++;
            
    SD_Printf_MQ(&TestRoute,"//THE END");
}


void Keep2Shagai(void)
{
    

    u32 cur_time = 0; 
    double Last_X;
    double Last_Y;
    
    shaGaiGet = 0;
    SetPointPath(GameState[Now_Process].RouteIndex,GameState[Now_Process + 1].RouteIndex);
    Last_X = GPS.position.x;
    Last_Y = GPS.position.y;    
    while (HANDLE_MODE_AUTO)
    {
        GoPointPath(Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID]);
//         if(Point_NowNum>Point_EndNum-2)
//         {
//             RouteFinish=1;
//             break;
//         }
        if(Abs(Last_X-GPS.position.x)<1.5 && Point_NowNum > NODE_61 - 350)//节点61前某个点，最好从开始走直线开始
        {
            cur_time++;
        }
        else
        {
            cur_time = 0;
        }
        if(cur_time > 20)
        {

            if(GPS.position.x > 0)  //blue
            {
                SetSpeed(-100,0,0);
                Delay_ms(500);
                Delay_ms(500);
                MOSI_GPS_X.f64_data = NODE_61_X;
                Write_Database(W_GPS_X_ID);

            }
            else                    //red
            {
                SetSpeed(100,0,0);
                Delay_ms(500);
                Delay_ms(500);
                MOSI_GPS_X.f64_data = -NODE_61_X;
                Write_Database(W_GPS_X_ID);              
            }
            
//             MOSI_GPS_Y.f64_data = 8165;
//             Write_Database(W_GPS_Y_ID);
            correct_times++;
//             Delay_ms(750);           
            break;
        }
        Last_X = GPS.position.x;
        Last_Y = GPS.position.y;
        Delay_ms(2);
    }
    
    SetPointPath(NODE_61,GameState[Now_Process + 1].RouteIndex);//节点61正确点
    while (HANDLE_MODE_AUTO && (shaGaiGet == 0))
    {
        GoPointPath(Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID]);
        if(Point_NowNum>Point_EndNum-2)
        {
            RouteFinish=1;
            break;
        }
        Delay_ms(2);
    }
    while (HANDLE_MODE_AUTO && (shaGaiGet == 0))
    {
        SetSpeed(0,-100,0);
    }
    SetSpeed(0,0,0);
    
}


void WatingtoCorrect(void)
{
    u32 cur_time = 0; 
    double Last_X;
    double Last_Y;
    u32 i;
    u32 count = 0;
    S_Factor = 0.6;

    for(i=0;i<400;i++)
    {
        if((PointRoute[GameState[Now_Process].RouteIndex + count].position.y - GPS.position.y) < 0)
        {
            break;
        }
        count++;
    }
    
    
    SetPointPath(GameState[Now_Process].RouteIndex + count,GameState[Now_Process+1].RouteIndex);


    Last_X = GPS.position.x;
    Last_Y = GPS.position.y;    
    while (HANDLE_MODE_AUTO)
    {
         GoPointPath(Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID]);
//         if(Point_NowNum>Point_EndNum-2)
//         {
//             RouteFinish=1;
//             break;
//         }
        if(Abs(Last_X-GPS.position.x)<2 && Abs(Last_Y-GPS.position.y)<2 && Point_NowNum > (NODE_71-45))//节点7后50个点
        {
            cur_time++;
        }
        else
        {
            cur_time = 0;
        }
        if(cur_time > 10)
        {

            if(GPS.position.x > 0)
            {
                SetSpeed(-100,100,0);
                Delay_ms(1000);
//                 Delay_ms(1000);
//                 Delay_ms(1000); 
                Delay_ms(1000); 
                MOSI_GPS_X.f64_data = NODE_71_X;
                Write_Database(W_GPS_X_ID);

            }
            else
            {
                SetSpeed(100,100,0);
                Delay_ms(1000);
//                 Delay_ms(1000);
//                 Delay_ms(1000); 
                Delay_ms(1000); 
                MOSI_GPS_X.f64_data = -NODE_71_X;
                Write_Database(W_GPS_X_ID);
            }
            
            MOSI_GPS_Y.f64_data = NODE_71_Y;
            Write_Database(W_GPS_Y_ID);
            correct_times++;
//             Delay_ms(750);
            break;
            
        }
        Last_X = GPS.position.x;
        Last_Y = GPS.position.y;
        Delay_ms(2);
    }
    SD_Printf_MQ(&TestRoute,"//THE END");
    S_Factor = 0.8;
    NormalGoRoute(NODE_71,GameState[Now_Process + 1].RouteIndex,Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID]);//节点91正确点
    SetSpeed(0,0,0);
}

u8 lostPoint = 2;
void fGetShagai(void)
{
    shaGaiGet = 0;
    SetPointPath(GameState[Now_Process].RouteIndex,GameState[Now_Process + 1].RouteIndex);//节点61正确点
    while (HANDLE_MODE_AUTO && (shaGaiGet == 0))
    {
        GoPointPath(Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID]);
        if(Point_NowNum>Point_EndNum- lostPoint)
        {
            RouteFinish=1;
            break;
        }
        Delay_ms(2);
    }
    SetSpeed(0,0,0);

}


void fGoZone(void)
{
    int i;
    int count;
    for(i=0;i<400;i++)
    {
        if((PointRoute[GameState[Now_Process].RouteIndex + count].position.y - GPS.position.y) < 0)
        {
            break;
        }
        count++;
    }
    
    
    SetPointPath(GameState[Now_Process].RouteIndex + count,GameState[Now_Process+1].RouteIndex);
    while (HANDLE_MODE_AUTO)
    {
        GoPointPath(Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID]);
        if(Point_NowNum>Point_EndNum-2)
        {
            RouteFinish=1;
            break;
        }
        Delay_ms(2);
    }
    SetSpeed(0,300,0);
    Delay_ms(500);
    SetSpeed(0,0,0);
    
       
}


void runToShoot(void)
{
    NormalGoRoute(GameState[Now_Process].RouteIndex,SHOOTNODE,Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID]);//节点91正确点
    Com_SendByte(4, ThrowShagai_3);
    NormalGoRoute(SHOOTNODE,GameState[Now_Process + 1].RouteIndex,Pid_List[GameState[Now_Process].anglePID],Pid_List[GameState[Now_Process].disPID]);//节点91正确点
    MISO_CONTINUE_FLAG = Nothing;
}

void beforeThrowShagai(void)
{
    noAction();
    SetSpeed(0,300,0);
    Delay_ms(500);
    SetSpeed(0,0,0);
    
}

void Back2Auto(void)
{
    
    Now_Process = GrabShagai_1;
    Com_SendByte(4, Now_Process);
    shaGaiGet = 0;
    
    if(GPS.position.x > 0)  //blue
    {
        SetSpeed(-100,0,0);
        Delay_ms(500);
        MOSI_GPS_X.f64_data = NODE_61_X;
        Write_Database(W_GPS_X_ID);

    }
    else                    //red
    {
        SetSpeed(100,0,0);
        Delay_ms(500);
        MOSI_GPS_X.f64_data = -NODE_61_X;
        Write_Database(W_GPS_X_ID);              
    }
    
    while (HANDLE_MODE_AUTO && (shaGaiGet == 0))
    {
        if(GPS.position.x > 0)  //blue
        {
            SetSpeed(-20,-200,0);
        }
        else                    //red
        {
            SetSpeed(20,-200,0);
        }
        Delay_ms(2);
    }
    SetSpeed(0,0,0);
        
}

