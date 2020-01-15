#include "all.h" 

/*关于电机控制的相关函数*/




//将轮子调到 WheelDiraction ，角度制
void Set_WheelLoc (int WheelID , double WheelDiraction)
{
	Mode[WheelID] = Location_Mode ;
	set_loc[WheelID] = 8192.0f * 140.0f / 360.0f * WheelDiraction ;
}


//赋给轮子速度 ，mm/s
void Set_OdriveSpd ( int WheelID , double OdriveSpeed )
{
	double n ; //达到OdriveSpeed所需赋给odrive的对应的值
	n = OdriveSpeed * 8192.0 /PI / 105.0 ;
	
 	if ( WheelID == 0 )
	{
		USART_printf( USART2 , "v 0 %lf 0\n",n) ;
	}
	
	 	if ( WheelID == 1 )
	{
		USART_printf( USART2 , "v 1 %lf 0\n",n) ;
	}

	 	if ( WheelID == 2 )
	{
		USART_printf( USART3 , "v 1 %lf 0\n",n) ;
	}
	
	 	if ( WheelID == 3 )
	{
		USART_printf( USART3 , "v 0 %lf 0\n",n) ;
	}
}


