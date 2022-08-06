#include<stdint.h>
#include "stm32f4xx.h"
#include "gpio.h"
#include "7seg.h"
#include "keypad.h"
int main(void)
{

	sev_seg_init(GPIOA,0,1,2,3,0);
	KeyPad_INIT();

	// super loop
	while(1)
	{
		KeyPad_MANAGE();

	}

}
