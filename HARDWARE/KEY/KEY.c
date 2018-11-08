#include "KEY.h"
#include "delay.h"

//按键初始化函数

void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
  GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_15;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
}
// 没有按键按下 0
// KEY0_PRES 1
// KEY1_PRES 2
// WKUP_PRES 3
// mode:0,不支持连续按；1，支持连续按
u8 Key_scan(u8 mode)
{
	static u8 key_up=1;//按键松开标志
	if(mode) key_up=1;//支持连按
	if(key_up&&(KEY0==0||KEY1==0||WKUP==1))
	{
		delay_ms(10);//去抖动
		key_up=0;
		if(KEY0==0) return KEY0_PRES;
		else if(KEY1==0) return KEY1_PRES;
		else if(WKUP==1) return WKUP_PRES;
	}else if(KEY0==1&&KEY1==1&&WKUP==0) key_up=1;
	return 0;//无按键按下
	
}
