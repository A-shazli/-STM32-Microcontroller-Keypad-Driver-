#include "stm32f4xx.h"
#include "gpio.h"
#include "7seg.h"
#define num_rows 4 // these are now complie time since array size must be set in compile time while const is a runtime object definer
#define num_cols 3
char KeyPad_GET_VALUE(void);
void KeypadCallouts_KeyPressNotificaton(void);
char rows[num_rows]={1,2,4,5}; //fill the array
char cols[num_cols]={5,6,7}; //fill the array

char lookupTable[num_rows][num_cols]={{1,2,3},{4,5,6},{7,8,9},{'*',0,'#'}};// fill the array
char arr[] = {0,1,2,3};
char currentvalue;


void KeyPad_INIT(void)
{
	// set input and ouput pins
		// get pins from raw and set it as input
		// get pins from cols and set it as output
	// hint use gpio driver functions
	GPIO_Init(GPIOB,rows[0],1,1);
	GPIO_Init(GPIOB,rows[1],1,1);
	GPIO_Init(GPIOB,rows[2],1,1);
	GPIO_Init(GPIOB,rows[3],1,1);

	GPIO_Init(GPIOA,cols[0],0,0);
	GPIO_Init(GPIOA,cols[1],0,0);
	GPIO_Init(GPIOA,cols[2],0,0);

	GPIO_Write(GPIOB, rows[0], 1);
	GPIO_Write(GPIOB, rows[1], 1);
	GPIO_Write(GPIOB, rows[2], 1);
	GPIO_Write(GPIOB, rows[3], 1);



}

void KeyPad_MANAGE(void)
{
	//nested for loop to check which button is pressed
	//if pressed wait until released then change the value;
	//call KeypadCallouts_KeyPressNotificaton
	for(int i = 0; i<4; i++){
			GPIO_Write(GPIOB,rows[i],0);
			for(int j = 0; j<3; j++){
				if(!(GPIO_Read(GPIOA, cols[j]))){
					currentvalue = lookupTable[i][j];
					while(GPIO_Read(GPIOA,cols[j]) == 0);
				}
				KeypadCallouts_KeyPressNotificaton();
			}

			GPIO_Write(GPIOB,rows[i],1);
		}

}

char KeyPad_GET_VALUE(void)
{
	return currentvalue;
}

void KeypadCallouts_KeyPressNotificaton(void)
{
	// set seven segment
	sev_seg(GPIOA, arr, KeyPad_GET_VALUE());
}

