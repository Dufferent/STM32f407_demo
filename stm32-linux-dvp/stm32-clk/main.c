#include "stdio.h"
#include "./User/led.h"
#include "./User/delay.h"
//[第一个Linux下的STM32项目] -------- [Light LED]
//[日期 ：] ---- [ 2020.9.16 ] ----  [ 16:34 ]
//[作者 ：] ---- [ 熊诺晔 ] ---- [ Xiong Nuoye ]
//[版本 ：] ---- [ V1.0  ]
//[License :] ---- [GPL]
int main(void)
{
    Sys_Clock_Set(336,8,2,7);
    delay_init(168);
    Led_Init();

    while(1)
    {
        //Led_Flow();
        Led_Flash();
    }
    
    return 0;
}
