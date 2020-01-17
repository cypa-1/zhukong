/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MYTYPEDEF_H
#define __MYTYPEDEF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

//��ṹ��
struct Point
{
	double x;
	double y;
};

//·����Ϣ�ṹ��
struct Path_Point
{
	struct Point position;	//λ��
	double speeddir;		//�ٶȷ���
	double pos;			//���巽��
	double speed;			//�ٶȴ�С
};

//PID�ṹ��
struct PID
{
	double p;
	double i;
	double d;
	double mend;
	double ep1;
	double ep2;
};
 

struct Encoder_State
{
    double dis;                //����
    double convert1;        //��תϵ��
    double convert2;        //��תϵ��
    double r;                //������תʱ���̵���ת�뾶
    double radian;  //�ı�����ת�����������Ҫ�ķ�������1��������-1��
};


//CCD�ṹ��
struct CCD_State
{	
	uint8_t ADC_Channel_Index;
	
	uint8_t Line_Left_Edge_Pos_Threshold;
	uint8_t Line_Right_Edge_Pos_Threshold;
	uint8_t Line_Median_Pos_Threshold;
	
	uint8_t Line_Left_Edge_Pos;
	uint8_t Line_Right_Edge_Pos;
	uint8_t Line_Median_Pos;
	
	uint16_t Line_ADC_Threshold;
	uint16_t Place_ADC_Threshold;
	uint16_t Difference_ADC_Threshold;
	
	uint16_t ADC_Max;
	uint16_t ADC_Min;
	uint16_t ADC_Median;
};

//����
enum Route_Direction
{
	ROUTE_FRONT = 0,
	ROUTE_BACK,
	ROUTE_LEFT,
	ROUTE_RIGHT,
};

//����ֵ
enum M_KeyNumType
{
    key1 = 1,
    key2,
    key3,
    key4,
    keyback,//5
    emergency,//6
    
    key5,//7
    key6,//8
    key7,//9
    key8,//10
    keyempty1,//11
    keyempty2,//12
    
    key9,//13
    key0,
    keypoint,
    keysign,
    keydelete,
    keyOK,
	keyboardtab
};
#define pageup point
#define pagedown sign

typedef enum {
 		Type_Fp64 = 1 ,
 		Type_Int64,
 		Type_Fp32 ,
 		Type_Int32,
 		Type_Uint32,
 		Type_Int16,
 		Type_Uint16,
 		Type_Int8,
 		Type_Uint8,
 		Type_Gyro,
 		Type_Encoder,
 		Type_PID,
 		Type_Mecanum,
}SD_Value_Type;


typedef enum {
		TYPE_INT8	=  1,
		TYPE_UINT8	,
		TYPE_INT16	,
		TYPE_UINT16	,
		TYPE_INT32	,
		TYPE_UINT32	,
		TYPE_INT64	,
		TYPE_UINT64	,
		TYPE_FP32		,
		TYPE_FP64		,
//     TYPE_POINTFP32,
//     TYPE_POINTFP64,
}Value_Type;

//�б���ʾ�����
struct Input_ListValue
{
	void *value;
	Value_Type type;
	char *name;
};

#endif 

/**********************************END OF FILE*********************************/
