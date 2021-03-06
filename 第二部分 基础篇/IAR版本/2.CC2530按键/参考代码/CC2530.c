/**
  ******************************************************************************
  * @file        CC2530.c
  * @author      BruceOu
  * @version     V1.0
  * @date        2017-12
  * @brief       按键控制流水灯
  ******************************************************************************
  */
/**Includes*********************************************************************/
#include <ioCC2530.h>

/**宏定义***********************************************************************/
//定义数据类型
#define uint  unsigned int
#define uchar unsigned char

//定义控制灯的端口
#define LED1   P1_0	  //定义LED1为P10口控制
#define LED2   P1_1	  //定义LED2为P11口控制
#define LED3   P0_4	  //定义LED3为P04口控制
#define KEY1   P0_1       //定义按键为P01口控制

/**函数声明*********************************************************************/
void Delay(uint);	      //延时函数声明
void InitIO(void);            //初始化函数声明
void InitKey(void);           //初始化按键函数声明
uchar KeyScan(void);          //按键扫描函数声明

/**全局变量*********************************************************************/
uchar Keyvalue = 0 ;          //定义变量记录按键动作
uint  KeyTouchtimes = 0 ;     //定义变量记录按键次数

/**
  * @brief     主函数
  * @param     None
  * @retval    None
  */
void main(void)
{
  InitIO();		//初始化LED灯控制IO口	
  InitKey();             //初始化按键控制IO口
  while(1)
  {
    Keyvalue = KeyScan();       //读取按键动作
    
    if(Keyvalue == 1)           //按下按键S1设置为LED3,LED2,LED1倒序流水闪烁
    {           
      LED3 = !LED3;           
      Delay(50000); 
      LED2 = !LED2;                
      Delay(50000);           
      LED1 = !LED1;           
      Delay(50000);       
    }  
  }
}
  
/**
  * @brief     普通延时函数
  * @param     n 延时长度
  * @retval    None
  */
void Delay(uint n)
{
	uint i;
	for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
        for(i = 0;i<n;i++);
}

/**
  * @brief     按键初始化
  * @param     None
  * @retval    None
  */
void InitKey(void)
{
  P0SEL &= ~0X02;  
  P0DIR &= ~0X02;  //按键在P01口，设置为输入模式
  P0INP |= 0x02;   //上拉      
  
}

/**
  * @brief     初始化程序,将P10、P11、P04定义为输出口，并将LED灯初始化为灭
  * @param     None
  * @retval    None
  */
void InitIO(void)
{
    P1DIR |= 0x03; //P10、P11定义为输出
    P0DIR |= 0x10; //P04定义为输出
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;	    //LED灯初始化为灭
}

/**
  * @brief     按键操作函数
  * @param     None
  * @retval    None
  */
uchar KeyScan(void)
{
   if(KEY1 == 0)    //高电平有效
  {
    Delay(100);     //检测到按键
    if(KEY1 == 0)
    {
      while(!KEY1);   //直到松开按键      
      return(1);
    }
  }
  return(0);
}