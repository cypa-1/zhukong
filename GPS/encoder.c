#include "all.h"
#define    EncoderAmount 2
struct Encoder_State Encoder[2];

/*
 * ������: Encoder_Init
 * ��  ��: ���̱궨ϵ��
 * ��  ��: ��
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void Encoder_Init_Con(void)
{
	u8 tp_last, key_value, i=0, is_key = 0;
		LCD_Clear(WHITE);
		LCD_printf(0,6+36*9,300,24,24,"X+");
    LCD_printf(0,6+36*0,300,24,24,"Find a refrence line and press OK");
	  LCD_printf(0,6+36*1,300,24,24,"to mark the start position");
		while(i==0)
		{
			if (Is_USART_Key_Receive)
			{
				Is_USART_Key_Receive = 0;
				key_value = Key_RxBuffer[0];
				if (key_value != keyempty1)
					is_key = 1;
			}
			if (is_key)
			{
				is_key = 0;
				switch(key_value)
					{		
							case keyOK :
								i=1;
								MOSI_CMD = ENC_L_INIT;
								Write_Database(M_G_CMD_ID);
								break;
							case keyback:
								return;
					}
			}
		}
		i=0;
	  delay_ms(10);
		LCD_Clear(WHITE);
    LCD_printf(0,6+36*0,300,24,24,"X+:Push 3m");
	  LCD_printf(0,6+36*1,300,24,24,"Press OK to end");
		while(i==0)
		{	
			LCD_printf(0,6+36*2,300,24,24,"Encoder[0].dis:%lf",Encoder[0].dis);
			LCD_printf(0,6+36*3,300,24,24,"Encoder[1].dis:%lf",Encoder[1].dis);
			if (Is_USART_Key_Receive)
			{
				Is_USART_Key_Receive = 0;
				key_value = Key_RxBuffer[0];
				if (key_value != keyempty1)
					is_key = 1;
			}
			if (is_key)
			{
				is_key = 0;
				switch(key_value)
					{		
							case keyOK :
								i=1;
								Write_Database(M_G_CMD_ID);
								break;
							case keyback:
								return;
					}
			}
		}
		i=0;
	  delay_ms(10);
		LCD_Clear(WHITE);
		LCD_printf(0,6+36*9,300,24,24,"Y+");
    LCD_printf(0,6+36*0,300,24,24,"Find a refrence line and press OK");
	  LCD_printf(0,6+36*1,300,24,24,"to mark the start position");
		
		while(i==0)
		{
			if (Is_USART_Key_Receive)
			{
				Is_USART_Key_Receive = 0;
				key_value = Key_RxBuffer[0];
				if (key_value != keyempty1)
					is_key = 1;
			}
			if (is_key)
			{
				is_key = 0;
				switch(key_value)
					{		
							case keyOK :
								i=1;
								Write_Database(M_G_CMD_ID);
								break;
							case keyback:
								return;
					}
			}
		}
		i=0;
	  delay_ms(10);
		LCD_Clear(WHITE);
    LCD_printf(0,6+36*0,300,24,24,"Y+:Push 3m");
	  LCD_printf(0,6+36*1,300,24,24,"Press OK to end");
		while(i==0)
		{
			LCD_printf(0,6+36*2,300,24,24,"Encoder[0].dis:%lf",Encoder[0].dis);
			LCD_printf(0,6+36*3,300,24,24,"Encoder[1].dis:%lf",Encoder[1].dis);
			if (Is_USART_Key_Receive)
			{
				Is_USART_Key_Receive = 0;
				key_value = Key_RxBuffer[0];
				if (key_value != keyempty1)
					is_key = 1;
			}
			if (is_key)
			{
				is_key = 0;
				switch(key_value)
					{		
							case keyOK :
								i=1;
								Write_Database(M_G_CMD_ID);
								break;
							case keyback:
								return;
					}
			}
		}
		delay_ms(10);
		LCD_Clear(WHITE);
		LCD_printf(0,6+36*0,300,24,24,"Press any key to continue...");
	 	LCD_printf(0,6+36*1,300,24,24,"Invoke Encoder_View to check");
				while(1) 
		{
				if (Is_USART_Key_Receive)
			{
				Is_USART_Key_Receive = 0;
				key_value = Key_RxBuffer[0];
				if (key_value != keyempty1)
					is_key = 1;
			}
			if (is_key)
			{
				return;
			}
		}
}
/*
 * ������: Encoder_Init_R
 * ��  ��: ���̱궨��ת�뾶
 * ��  ��: ��
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */

void Encoder_Init_R(void)
{
	u8 tp_last, key_value, i=0, is_key = 0;
		LCD_Clear(WHITE);
		LCD_printf(0,6+36*0,300,24,24,"Find a refrence");
	 	LCD_printf(0,6+36*1,300,24,24,"Press OK to continue");	  	
		while(i==0)
		{
			if (Is_USART_Key_Receive)
			{
				Is_USART_Key_Receive = 0;
				key_value = Key_RxBuffer[0];
				if (key_value != keyempty1)
					is_key = 1;
			}
			if (is_key)
			{
				is_key = 0;
				switch(key_value)
					{		
							case keyOK :
								i=1;
								MOSI_CMD = ENC_R_INIT;
								Write_Database(M_G_CMD_ID);
								break;
							case keyback:
								return;
					}
			}
		}
		i=0;
	  delay_ms(10);
		LCD_Clear(WHITE);
    LCD_printf(0,6+36*0,300,24,24,"press OK to turn 5+ circles.");
		
		while(i==0)
		{
			if (Is_USART_Key_Receive)
			{
				Is_USART_Key_Receive = 0;
				key_value = Key_RxBuffer[0];
				if (key_value != keyempty1)
					is_key = 1;
			}
			if (is_key)
			{
				is_key = 0;
				switch(key_value)
					{		
							case keyOK :
								i=1;
								break;
							case keyback:
								return;
					}
			}
		}
		i=0;
	  delay_ms(10);
					LCD_Clear(WHITE);
				  LCD_printf(0,6+36*0,300,24,24,"turning...");
					LCD_printf(0,6+36*1,300,24,24,"Press OK to end");
				  LCD_printf(0,6+36*2,300,24,24,"Gyro.angle:%lf",Gyro.angle) ;
		while(i==0)
			{		
					LCD_printf(0,6+36*3,300,24,24,"Encoder[0].dis:%lf",Encoder[0].dis);
					LCD_printf(0,6+36*4,300,24,24,"Encoder[1].dis:%lf",Encoder[1].dis);
          //��һ�������ٶȵĺ���
			if (Is_USART_Key_Receive)
			{
				Is_USART_Key_Receive = 0;
				key_value = Key_RxBuffer[0];
				if (key_value != keyempty1)
					is_key = 1;
			}
			if (is_key)
			{
				is_key = 0;
				switch(key_value)
					{		
							case keyOK :
								i=1;
								Write_Database(M_G_CMD_ID);
							//��һ���ر����е���ĺ���
								break;
							case keyback:
								return;
					}
			}
		}
		i=0;
	  delay_ms(10);
		LCD_Clear(WHITE);		
    LCD_printf(0,6+36*0,300,24,24,"R1:%lf",Encoder[0].r);
	  LCD_printf(0,6+36*1,300,24,24,"R2:%lf",Encoder[1].r);
	  LCD_printf(0,6+36*2,300,24,24,"over");	
		while(1) 
		{
				if (Is_USART_Key_Receive)
			{
				Is_USART_Key_Receive = 0;
				key_value = Key_RxBuffer[0];
				if (key_value != keyempty1)
					is_key = 1;
			}
			if (is_key)
			{
				return;
			}
		}
}	


/*
 * ������: Encoder_View
 * ��  ��: �鿴���̵���Ϣ
 * ��  ��: ��
 * ��  ��: ��
 * ��  ��: �ⲿ����
 */
void Encoder_View(void)
{
	u8 tp_last, key_value, i=0, is_key = 0;
		LCD_Clear(WHITE);
		LCD_printf(0,6+36*0,300,24,24,"Convert11:%lf",Encoder[0].convert1);
	 	LCD_printf(0,6+36*1,300,24,24,"Convert12:%lf",Encoder[0].convert2);
		LCD_printf(0,6+36*2,300,24,24,"Radius1:%lf",Encoder[0].r);
	 	LCD_printf(0,6+36*2,300,24,24,"radian1:",Encoder[0].radian);
		LCD_printf(0,6+36*2,300,24,24,"Convert21:%lf",Encoder[1].convert1);
	 	LCD_printf(0,6+36*3,300,24,24,"Convert22:%lf",Encoder[1].convert2);
		LCD_printf(0,6+36*2,300,24,24,"Radius2:%lf",Encoder[1].r);
	 	LCD_printf(0,6+36*2,300,24,24,"radian2:",Encoder[1].radian);
		while(1) 
		{
				if (Is_USART_Key_Receive)
			{
				Is_USART_Key_Receive = 0;
				key_value = Key_RxBuffer[0];
				if (key_value != keyempty1)
					is_key = 1;
			}
			if (is_key)
			{
				return;
			}
		}
}

void Encoder_Set(void)
{
	
}
