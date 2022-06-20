/*interrupt examples
 * https://users.ece.utexas.edu/~valvano/Volume1/E-Book/C12_Interrupts.htm*/

#include "main.h"

#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef SET_CLEAR_BIT

	#define SET_BIT      (1)
	#define CLEAR_BIT    (0)
#endif

#ifndef MACROS
	#define IDLE_TEMP_MAX							(80)
	#define DOSA_MATIC_MIN_TEMP    					(155) //155
	#define DOSA_MATIC_MAX_TEMP						(175) //171
	#define DOSA_HIGH_ADJ							(2100)

	#define POWDER_DISP_SEC                         (9)
	#define WATER_FLOW_SEC                          (40)
	#define DOSA_BLENDER_SEC                        (15)

	#define COOKING_MAX_TIME                        (100) // previous value = 120;
	#define ROTI_PR_ENCODER_CNT_MAX					(4450)	//chapathi pressing force previous value 4450
/*Roti maker temperature*/
	#define ROTI_IDLE_MODE_MAX_TEMP                 (165) //  chapathi start temp
	#define DOSA_IDLE_MODE_MIN_TEMP                 (150) // //Cut off temp  dosa plate max temp
/*
	 * PR - PRESSING
	 *
	 * */
	#define ROTI_PR_INIT_UP_TIME                    (500) //400ms  previous 400
	#define ROTI_PR_INIT_DOWN_TIME                  (300)
	#define ROTI_POWDER_DISP_CNT                    (158) //Motor shaft encoder count.
	#define ROTI_PR_WAITING_TIME                    (2)   //Press waiting time per sec.  previous 2s
	/*ROTI COOKING TIME */
	#define ROTI_COOKING_TIME                       (110)  //Cooking time. previou 90
	#define ROTI_COOKING_TIME_DOWN_SIDE             (10)

	#define ARM_MOVING_FOR_CNT 						(13500)

/*Dough make*/
	#define ROTI_W_O_FIRST_INJECT_ON                (3)//Previous value = 3
	#define ROTI_W_O_FIRST_INJECT_OFF				(3)////wait for 6sec

	#define ROTI_W_O_SECOND_INJECT_ON               (3)////Previous value = 3
	#define ROTI_W_O_SECOND_INJECT_OFF				(3)////wait for 6sec

	#define ROTI_W_O_THIRED_INJECT_ON				(6)//Previous value = 3
	#define ROTI_W_O_THIRED_INJECT_OFF				(3)//wait for 6sec

	#define ROTI_W_O_FOUR_INJECT_ON                 (5) ////Previous value = 3
	#define ROTI_W_O_FOUR_INJECT_OFF 				(3) //wait for 6sec

	#define ROTI_W_O_FIVE_INJECT_ON                 (0)
	#define ROTI_W_O_FIVE_INJECT_OFF				(2)

	#define ROTI_W_O_SIX_INJECT_ON					(0) ////Previous value = 3
	#define ROTI_W_O_SIX_INJECT_OFF					(2)

	#define ROTI_W_O_SEVEN_INJECT_ON				(0)
	#define ROTI_W_O_SEVEN_INJECT_OFF				(2)

	#define ROTI_W_O_EIGHT_INJECT_ON				(0)
	#define ROTI_W_O_EIGHT_INJECT_OFF				(2)

	#define DOUGH_MAKE_TIME                         (60)  // previous 40

#endif
/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

#ifndef DOSA_TRAILS_FLAG
	#define DOSA_TRAILS_ROUTINE_FLAG_1               (1)
	#define DOSA_TRAILS_ROUTINE_FLAG_2               (2)
	#define DOSA_TRAILS_ROUTINE_FLAG_3               (3)
	#define DOSA_TRAILS_ROUTINE_FLAG_4               (4)
	#define DOSA_TRAILS_ROUTINE_FLAG_5               (5)
	#define DOSA_TRAILS_ROUTINE_FLAG_6               (6)
	#define DOSA_TRAILS_ROUTINE_FLAG_7               (7)
	#define DOSA_TRAILS_ROUTINE_FLAG_8               (8)
	#define DOSA_TRAILS_ROUTINE_FLAG_9               (9)
	#define DOSA_TRAILS_ROUTINE_FLAG_10              (10)
	#define DOSA_TRAILS_ROUTINE_FLAG_11              (11)
	#define DOSA_TRAILS_ROUTINE_FLAG_12              (12)
	#define DOSA_TRAILS_ROUTINE_FLAG_13              (13)
	#define DOSA_TRAILS_ROUTINE_FLAG_14              (14)
	#define DOSA_TRAILS_ROUTINE_FLAG_15              (15)
	#define DOSA_TRAILS_ROUTINE_FLAG_16              (16)
	#define DOSA_TRAILS_ROUTINE_FLAG_17              (17)
	#define DOSA_TRAILS_ROUTINE_FLAG_18              (18)
	#define DOSA_TRAILS_ROUTINE_FLAG_19              (19)
	#define DOSA_TRAILS_ROUTINE_FLAG_20              (20)
	#define DOSA_TRAILS_ROUTINE_FLAG_21              (21)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef DOSA_MOTOR_PIN_CONFIG
	#define PORT0_MOTOR_1_ON			(0x01)
	#define PORT0_MOTOR_2_ON			(0x02)
	#define PORT0_MOTOR_3_ON			(0x04)
	#define PORT0_MOTOR_4_ON			(0x08)
	#define PORT0_MOTOR_5_ON			(0x10)
	#define PORT0_MOTOR_6_ON			(0x20)
	#define PORT0_MOTOR_7_ON			(0x40)
	#define PORT0_MOTOR_8_ON			(0x80)

	#define PORT1_MOTOR_9_ON			(0x01)
	#define PORT2_MOTOR_10_ON			(0x02)
	#define PORT3_MOTOR_11_ON			(0x04)
	#define PORT4_MOTOR_12_ON			(0x08)
	#define PORT5_MOTOR_13_ON			(0x10)
	#define PORT6_MOTOR_14_ON			(0x20)
	#define PORT7_MOTOR_15_ON			(0x40)
	#define PORT8_MOTOR_16_ON			(0x80)
#endif

/***************************************************************************************************************************
 * * *************************************************************************************************************************
 * * *************************************************************************************************************************
* *****************************************************END*****************************************************************
* */
#ifndef DOSA_MOTOR_PIN_CONFIG
	#define PORT0_MOTOR_1_OFF		    (0x00)
	#define PORT0_MOTOR_2_OFF			(0x00)
	#define PORT0_MOTOR_3_OFF			(0x00)
	#define PORT0_MOTOR_4_OFF			(0x00)
	#define PORT0_MOTOR_5_OFF			(0x00)
	#define PORT0_MOTOR_6_OFF			(0x00)
	#define PORT0_MOTOR_7_OFF			(0x00)
	#define PORT0_MOTOR_8_OFF			(0x00)


	#define PORT1_MOTOR_9_OFF			(0x00)
	#define PORT1_MOTOR_10_OFF			(0x00)
	#define PORT1_MOTOR_11_OFF			(0x00)
	#define PORT1_MOTOR_12_OFF			(0x00)
	#define PORT1_MOTOR_13_OFF			(0x00)
	#define PORT1_MOTOR_14_OFF			(0x00)
	#define PORT1_MOTOR_15_OFF			(0x00)
	#define PORT1_MOTOR_16_OFF			(0x00)
#endif

/***************************************************************************************************************************
 * * *************************************************************************************************************************
 * * *************************************************************************************************************************
* *****************************************************END*****************************************************************
* */

#ifndef CHAPATI_TRAILS_FLAG
	#define CHAPATI_TRAILS_ROUTINE_FLAG_1               (1)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_2               (2)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_3               (3)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_4               (4)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_5               (5)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_6               (6)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_7               (7)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_8               (8)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_9               (9)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_10              (10)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_11              (11)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_12              (12)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_13              (13)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_14              (14)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_15              (15)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_16              (16)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_17              (17)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_18              (18)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_19              (19)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_20              (20)
	#define CHAPATI_TRAILS_ROUTINE_FLAG_21              (21)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef CHAPATI_MOTOR_PIN_CONFIG
	#define PORT0_MOTOR_1_ON			(0x01)
	#define PORT0_MOTOR_2_ON			(0x02)
	#define PORT0_MOTOR_3_ON			(0x04)
	#define PORT0_MOTOR_4_ON			(0x08)
	#define PORT0_MOTOR_5_ON			(0x10)
	#define PORT0_MOTOR_6_ON			(0x20)
	#define PORT0_MOTOR_7_ON			(0x40)
	#define PORT0_MOTOR_8_ON			(0x80)

	#define PORT0_MOTOR_9_ON			(0x01)
	#define PORT0_MOTOR_10_ON			(0x02)
	#define PORT0_MOTOR_11_ON			(0x04)
	#define PORT0_MOTOR_12_ON			(0x08)
	#define PORT0_MOTOR_13_ON			(0x10)
	#define PORT0_MOTOR_14_ON			(0x20)
	#define PORT0_MOTOR_15_ON			(0x40)
	#define PORT0_MOTOR_16_ON			(0x80)
#endif

/***************************************************************************************************************************
 * * *************************************************************************************************************************
 * * *************************************************************************************************************************
* *****************************************************END*****************************************************************
* */
#ifndef CHAPATI_MOTOR_PIN_CONFIG
	#define PORT0_MOTOR_1_OFF		    (0x00)
	#define PORT0_MOTOR_2_OFF			(0x00)
	#define PORT0_MOTOR_3_OFF			(0x00)
	#define PORT0_MOTOR_4_OFF			(0x00)
	#define PORT0_MOTOR_5_OFF			(0x00)
	#define PORT0_MOTOR_6_OFF			(0x00)
	#define PORT0_MOTOR_7_OFF			(0x00)
	#define PORT0_MOTOR_8_OFF			(0x00)


	#define PORT0_MOTOR_9_OFF			(0x00)
	#define PORT0_MOTOR_10_OFF			(0x00)
	#define PORT0_MOTOR_11_OFF			(0x00)
	#define PORT0_MOTOR_12_OFF			(0x00)
	#define PORT0_MOTOR_13_OFF			(0x00)
	#define PORT0_MOTOR_14_OFF			(0x00)
	#define PORT0_MOTOR_15_OFF			(0x00)
	#define PORT0_MOTOR_16_OFF			(0x00)
#endif



/***************************************************************************************************************************
 * * *************************************************************************************************************************
 * * *************************************************************************************************************************
* *****************************************************END*****************************************************************
**/


/***************************************************************************************************************************
 * * *************************************************************************************************************************
 * * *************************************************************************************************************************
* *****************************************************END*****************************************************************
**/

#ifndef ROTARY_ENCODER_GLOBAL_VARIABLE

	unsigned int ROTARY_CURRENT_STATUS_B;
	unsigned int ROTARY_INIT_STATUS_B;
	unsigned int ROTARY_CURRENT_STATUS_A;
	unsigned int RotaryEncodeCount = CLEAR_BIT;
	unsigned int Sel_Customize_Menu = CLEAR_BIT;
	unsigned int Dosa_No_Cnt = CLEAR_BIT;

	unsigned int ROTARY_CURRENT_STATUS_B1;
	unsigned int ROTARY_INIT_STATUS_B1;
	unsigned int ROTARY_CURRENT_STATUS_A1;
#endif

/***************************************************************************************************************************
*************************************************************************************************************************
*************************************************************************************************************************
*****************************************************END*****************************************************************
*****************************************************END******************************************************************/

#ifndef ESP8266_AT_CMD_GLOBAL_VARIABLE
	//Free server used to the ubidots
	#define TCP_SERVER_QUERYS  ("Microchip/1.0|POST|BBFF-prqZevX65YLcK7X5xhkiD0IEUD3mhy|devicecontrol=>sensor:250|end")

	#define  TCP_SERVER_START  ("AT+CIPSTART=")
	#define  TCP_SERVER_CMD    ("\"TCP\",\"")
	#define  TCP_SERVER_URLS   ("industrial.api.ubidots.com\",\"")
	#define  TCP_SERVER_PORT   ("9012\r\n")

	char TCP_SERVER_CONNECTION[100] = {0};
#endif
/***************************************************************************************************************************
* *************************************************************************************************************************
* *************************************************************************************************************************
* *****************************************************END*****************************************************************
*/
#ifndef DOSA_AUTO_INIT_NOTI
	const char *AUTOMATIC_INIT_NOTI = "Auto Initalization..";
	const char *DOSA_PLATE_SPREAD_NOTI = "D_Plate...";
	const char *DOSA_MM_NOTI = "H-Adj.....";
	const char *BATTER_NOTI = "B_Move....";
	const char *BATTER_MIX = "B_Mixer...";
	const char *CLEANING_NOTI = "Cleaning..";
	const char *WATER_NOTI = "Water...";
	const char *OIL_NOTI = "Oil.....";
	const char *POWDER_NOTI = "Powder..";
	const char *SERVO_NOTI = "Servo...";
	const char *POWDER_MIX_NOTI = "P_Mixer..";
	/*Chapati maker notification*/
	const char *C_PRESSING = "C_Press..";
	const char *C_UP_DOWN = "C_up_down.";

	/*Notification error*/
	const char *WATER_LEVEL = "A_Water/M  ";
	const char *OIL_LEVEL = "A_Oil/M  ";
	const char *POWDER_LEVEL = "A_Pow/M  ";

	const char *TEMP_IDLE = "Temp_idle_mode";
	const char *TEMP_COOK = "Cooking_mode  ";

/*	const char P_MIXER = "C_Mixer..";
	const char SERVO_OP_CL = "P_Outlet_O/C";
*/



#endif

/***************************************************************************************************************************
*************************************************************************************************************************
*************************************************************************************************************************
*****************************************************END*****************************************************************
*/

#ifndef TIMER_GLOBAL_VARIABLE

	volatile unsigned int TIM1_MS_CNT = CLEAR_BIT;
	volatile unsigned int TIM2_MS_CNT = CLEAR_BIT;
	volatile unsigned int TIM3_MS_CNT = CLEAR_BIT;
	volatile unsigned int TIM4_MS_CNT = CLEAR_BIT;
	volatile unsigned int  REQ_MS_CNT = CLEAR_BIT;
	volatile unsigned int TEMP_REQ_MS_CNT = CLEAR_BIT;
	volatile unsigned int TIM2_MS_CNT_MM = CLEAR_BIT;
#endif

#ifndef ISR_GLOBAL_VARIABLE

	volatile unsigned int INITI_TRIALS_FLAG = CLEAR_BIT;
	volatile unsigned int TEMPERATURE_FLAG = CLEAR_BIT;
	volatile unsigned int PRESSING_CNT_FLAG = CLEAR_BIT;

	volatile uint16_t CountValue1 = 0;
	volatile uint16_t Sec1 = 0;

	volatile unsigned int TIMER2_FLAG_CNT = CLEAR_BIT;
	volatile unsigned int TIMER2_SEC_CNT = CLEAR_BIT;
	volatile unsigned int TIMER2_ISR_SEC_CNT = CLEAR_BIT;
	volatile unsigned int TIMER2_THREAD_EN = CLEAR_BIT;

	volatile unsigned int TIM3_SEC = CLEAR_BIT;
	volatile unsigned int TIM3_SEC1 = CLEAR_BIT;
	volatile unsigned int TIM3_FLAG = CLEAR_BIT;
	bool POWDER_CNT_FLAG = false;
	volatile unsigned int TIM3_MS_CNT1 = CLEAR_BIT;

	volatile unsigned int PowderCount = CLEAR_BIT;
	volatile unsigned int Findout_rpm = CLEAR_BIT;
	volatile unsigned int Ex_Count = CLEAR_BIT;
	volatile unsigned int Pressing_cnt = CLEAR_BIT;
	bool CH_PRESS_FLAG = false;
	volatile unsigned int CH_CNT_FLAG_CHECK = CLEAR_BIT;
	volatile unsigned int PRESSING_ENCODER_CNT = ROTI_PR_ENCODER_CNT_MAX;

	volatile unsigned int CH_ISR_FLAG = CLEAR_BIT;
	volatile unsigned int CH_DISH_CNT = CLEAR_BIT;
	volatile unsigned int ISR_PR_FLAG = CLEAR_BIT;
	volatile unsigned int ISR_PRALL_RUN_FLAG = CLEAR_BIT;

	volatile unsigned int PRESS_FLAG = CLEAR_BIT;
	volatile unsigned int ROTI_MAKE_FLAG = CLEAR_BIT;
	volatile unsigned int sample_test = CLEAR_BIT;
	volatile unsigned int SEC_SEQ_FLAG = CLEAR_BIT;
	volatile unsigned int DOUGH_DISABLE_FLAG = CLEAR_BIT;
	volatile unsigned int DOUGH_ENABLE_FLAG = CLEAR_BIT;

	volatile unsigned int ARM_MOVING_CNT = CLEAR_BIT;
	unsigned int ARM_MOVE_CNT_FLAG_EN = CLEAR_BIT;
	volatile unsigned int PRESSING_TOP_MOVE_ENCODER_CNT = CLEAR_BIT;
	volatile unsigned int PRESSING_TOP_MOVE_FLAG_EN = CLEAR_BIT;

	volatile unsigned int CNT = CLEAR_BIT;



#endif
/***************************************************************************************************************************
 * * *************************************************************************************************************************
 * * *************************************************************************************************************************
* *****************************************************END*****************************************************************
* */

#ifndef RESET_CLOCK_COUNT

	#define RCC_BASE    (0x40023800)
#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef POWER_CONTROL_CONFIG
	#define PWR_BASR_ADD  	(0x40007000)
	#define PWR_CR_OFFSET 	(0x00)
	#define PWR_CSR_OFFSET 	(0x04)

	#define PWR_CR    	*(volatile uint32_t *)(PWR_BASR_ADD + PWR_CR_OFFSET)
	#define PWR_CSR     *(volatile uint32_t *)(PWR_BASR_ADD + PWR_CSR_OFFSET)
	#define PWR_CR_VOS   (1 << 14)
	#define PWR_CSR_VOS_RDY   (1 << 14)


#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef GPIO_CONFIG

	#define GPIO_CONFIG_OUT  (1)
	#define GPIOA_ADDR  (0x40020000)
	#define GPIOB_ADDR  (0x40020400)
	#define GPIOC_ADDR  (0x40020800)
	#define GPIOD_ADDR  (0x40020C00)
	#define GPIOE_ADDR  (0x40021000)
	#define GPIOF_ADDR  (0x40021400)
	#define GPIOG_ADDR  (0x40021800)
	#define GPIOH_ADDR  (0x40021C00)

#endif


#ifndef I2C_ADDR
	#define I2C1_ADDR   (0x40005400)
	#define I2C2_ADDR   (0x40005800)
	#define I2C3_ADDR   (0x40005C00)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef SPI_ADDR

	#define SPI1_ADDR   (0x40013000)
	#define SPI4_ADDR   (0x40013400)
	#define SPI5_ADDR   (0x40015000)
	#define SPI6_ADDR   (0x40015400)
#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef UART_ADDR
	#define USART1_MEM_ADDR  (0x40011000)
	#define USART2_MEM_ADDR  (0x40004400)
	#define USART3_MEM_ADDR  (0x40004800)


	#define UART4_MEM_ADDR  (0x40004C00)
	#define UART5_MEM_ADDR  (0x40005000)

	#define UART7_MEM_ADDR  (0x40007800)
	#define UART8_MEM_ADDR  (0x40007C00)
#endif


/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

#ifndef TIMER6_REG_CONFIG

	#define TIM6_ADDR           (0x40001000)

	#define TIMx_CR1_OFFSET     (0x00)
	#define TIMx_CR2_OFFSET     (0x04)
	#define TIMx_SR_OFFSET      (0x10)
	#define TIMx_CNT_OFFSET     (0x24)
	#define TIMx_PSC_OFFSET     (0x28)
	#define TIMx_ARR_OFFSET     (0x2C)

	#define TIM6_CR1			*(volatile uint32_t *) (TIM6_ADDR + TIMx_CR1_OFFSET)
    #define TIM6_CR2            *(volatile uint32_t *) (TIM6_ADDR + TIMx_CR2_OFFSET)
    #define TIM6_SR             *(volatile uint32_t *) (TIM6_ADDR + TIMx_SR_OFFSET)
    #define TIM6_CNT            *(volatile uint32_t *) (TIM6_ADDR + TIMx_CNT_OFFSET)
	#define TIM6_PSC            *(volatile uint32_t *) (TIM6_ADDR + TIMx_PSC_OFFSET)
	#define TIM6_ARR            *(volatile uint32_t *) (TIM6_ADDR + TIMx_ARR_OFFSET)

	#define TIMER6_EN           (1 << 4)




#endif


#ifndef TIMER7_REG_CONFIG

	#define TIM7_REG_MAP 		(0x40001400)

	#define TIMx_CR1_OFFSET     (0x00)
	#define TIMx_CR2_OFFSET     (0x04)
	#define TIMx_SR_OFFSET      (0x10)
	#define TIMx_CNT_OFFSET     (0x24)
	#define TIMx_PSC_OFFSET     (0x28)
	#define TIMx_ARR_OFFSET     (0x2C)

	#define TIM7_CR1			*(volatile uint32_t *) (TIM7_REG_MAP + TIMx_CR1_OFFSET)
    #define TIM7_CR2            *(volatile uint32_t *) (TIM7_REG_MAP + TIMx_CR2_OFFSET)
    #define TIM7_SR             *(volatile uint32_t *) (TIM7_REG_MAP + TIMx_SR_OFFSET)
    #define TIM7_CNT            *(volatile uint32_t *) (TIM7_REG_MAP + TIMx_CNT_OFFSET)
	#define TIM7_PSC            *(volatile uint32_t *) (TIM7_REG_MAP + TIMx_PSC_OFFSET)
	#define TIM7_ARR            *(volatile uint32_t *) (TIM7_REG_MAP + TIMx_ARR_OFFSET)

	#define TIMER7_EN           (1 << 5)


#endif



#ifndef TIMER9_REG_CONFIG

	#define TIM9_REG_MAP 		(0x40014000)

	#define TIMx_CR1_OFFSET     (0x00)
	#define TIMx_CR2_OFFSET     (0x04)
	#define TIMx_SR_OFFSET      (0x10)
	#define TIMx_CNT_OFFSET     (0x24)
	#define TIMx_PSC_OFFSET     (0x28)
	#define TIMx_ARR_OFFSET     (0x2C)

	#define TIM9_CR1			*(volatile uint32_t *) (TIM9_REG_MAP + TIMx_CR1_OFFSET)
    #define TIM9_CR2            *(volatile uint32_t *) (TIM9_REG_MAP + TIMx_CR2_OFFSET)
    #define TIM9_SR             *(volatile uint32_t *) (TIM9_REG_MAP + TIMx_SR_OFFSET)
    #define TIM9_CNT            *(volatile uint32_t *) (TIM9_REG_MAP + TIMx_CNT_OFFSET)
	#define TIM9_PSC            *(volatile uint32_t *) (TIM9_REG_MAP + TIMx_PSC_OFFSET)
	#define TIM9_ARR            *(volatile uint32_t *) (TIM9_REG_MAP + TIMx_ARR_OFFSET)

	#define TIMER9_EN            (1 << 16)

	//PWM GENERATE;
	#define TIMx_CCR1_OFFSET     (0x34)
	#define TIMx_CCER_OFFSET     (0x20)
	#define TIMx_CCMR1_OFFSET    (0x18)

	#define TIM9_CCR1            *(volatile uint32_t *) (TIM9_REG_MAP + TIMx_CCR1_OFFSET)
	#define TIM9_CCER            *(volatile uint32_t *) (TIM9_REG_MAP + TIMx_CCER_OFFSET)
	#define TIM9_CCMR1           *(volatile uint32_t *) (TIM9_REG_MAP + TIMx_CCMR1_OFFSET)

   /*110: PWM mode 1 - Channel 1 is active as long as TIMx_CNT < TIMx_CCR1 else inactive.
    * 111: PWM mode 2 - Channel 1 is inactive as long as TIMx_CNT < TIMx_CCR1 else active.
    * */
	#define PWM_MODE_1            ((SET_BIT << 6)|(SET_BIT << 5)) //



#endif

// #ifndef NVIC_BASE_ADD

// 	#define NVIC_BASE_ADDRESS     (0xE000E100UL)

// 	#define __NVIC_OFFSET_ADD     (0x04)

// 	#define NVIC_EnableIRQ        *(volatile uint32_t *)(NVIC_BASE_ADDRESS + __NVIC_OFFSET_ADD)
// 	#define TIMER_1_ISR_ENABLE    (1UL << 54)

// 	#define ISR_ENABLE (IRQn){\ unsigned int Reminder = IRQn%31;\
// 		unsigned int ISR_REMINDER_VALUE = (IRQn - )

// 	}

// #endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

#ifndef TIMER1_REG_CONFIG

	#define TIMER1_ADDR_MAP    (0x40010000)
	#define RCC_ADDR_MAP       (0x40023800)

	#define RCC_APB2ENR_OFFSET (0x44)

	#define TIM1_CR1_OFFSET    (0x00)
	#define TIM1_CR2_OFFSET    (0x04)
	#define TIM1_DIER_OFFSET   (0x0C)
	#define TIM1_SR_OFFSET     (0x10)
	#define TIM1_CNT_OFFSET    (0x24)
	#define TIM1_PSC_OFFSET    (0x28)
	#define TIM1_ARR_OFFSET    (0x2C)

	#define TIM1_CR1_REG       *(volatile uint32_t *)(TIMER1_ADDR_MAP + TIM1_CR1_OFFSET)
	#define TIM1_CR2_REG       *(volatile uint32_t *)(TIMER1_ADDR_MAP + TIM1_CR2_OFFSET)
	#define TIM1_DIER_REG      *(volatile uint32_t *)(TIMER1_ADDR_MAP + TIM1_DIER_OFFSET)
	#define TIM1_SR_REG        *(volatile uint32_t *)(TIMER1_ADDR_MAP + TIM1_SR_OFFSET)
	#define TIM1_CNT_REG       *(volatile uint32_t *)(TIMER1_ADDR_MAP + TIM1_CNT_OFFSET)
	#define TIM1_PSC_REG       *(volatile uint32_t *)(TIMER1_ADDR_MAP + TIM1_PSC_OFFSET)
	#define TIM1_ARR_REG       *(volatile uint32_t *)(TIMER1_ADDR_MAP + TIM1_ARR_OFFSET)

	#define RCC_APB2ENR_PER_BUS *(volatile uint32_t *)(RCC_ADDR_MAP + RCC_APB2ENR_OFFSET)

	#define TIMER1_EN          (1 << 0)

	#define UIE                (1 << 0)
	#define CC1IE              (1 << 1)
	#define CC2IE              (1 << 2)
	#define CC3IE              (1 << 3)
	#define CC4IE              (1 << 4)
	#define COMIE              (1 << 5)
	#define TIE                (1 << 6)
	#define BIE                (1 << 7)
	#define UDE                (1 << 8)
	#define CC1DE              (1 << 9)
	#define CC2DE              (1 << 10)
	#define CC3DE              (1 << 11)
	#define CC4DE              (1 << 12)
	#define COMDE              (1 << 14)
	#define TDE                (1 << 15)

	#define TIM1_IRQ           (0x000000A4)

	// #define NVIC_BASE_ADDRESS     (0xE000E100UL)

	// #define __NVIC_OFFSET_ADD     (0x00)

	// #define NVIC_EnableIRQ        *(volatile uint32_t *)(NVIC_BASE_ADDRESS + __NVIC_OFFSET_ADD)
	// #define TIMER_1_ISR_ENABLE    (1UL << 25)



#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

#ifndef TIMER2_REG_CONFIG

	#define TIMER2_ADDR_MAP    (0x40000000)
	#define RCC_ADDR_MAP       (0x40023800)

	#define RCC_APB1ENR_OFFSET (0x40)

	#define TIM2_CR1_OFFSET    (0x00)
	#define TIM2_CR2_OFFSET    (0x04)
	#define TIM2_DIER_OFFSET   (0x0C)
	#define TIM2_SR_OFFSET     (0x10)
	#define TIM2_CNT_OFFSET    (0x24)
	#define TIM2_PSC_OFFSET    (0x28)
	#define TIM2_ARR_OFFSET    (0x2C)

	#define TIM2_CR1_REG       *(volatile uint32_t *)(TIMER2_ADDR_MAP + TIM2_CR1_OFFSET)
	#define TIM2_CR2_REG       *(volatile uint32_t *)(TIMER2_ADDR_MAP + TIM2_CR2_OFFSET)
	#define TIM2_DIER_REG      *(volatile uint32_t *)(TIMER2_ADDR_MAP + TIM2_DIER_OFFSET)
	#define TIM2_SR_REG        *(volatile uint32_t *)(TIMER2_ADDR_MAP + TIM2_SR_OFFSET)
	#define TIM2_CNT_REG       *(volatile uint32_t *)(TIMER2_ADDR_MAP + TIM2_CNT_OFFSET)
	#define TIM2_PSC_REG       *(volatile uint32_t *)(TIMER2_ADDR_MAP + TIM2_PSC_OFFSET)
	#define TIM2_ARR_REG       *(volatile uint32_t *)(TIMER2_ADDR_MAP + TIM2_ARR_OFFSET)

	#define RCC_APB1ENR_PER_BUS *(volatile uint32_t *)(RCC_ADDR_MAP + RCC_APB1ENR_OFFSET)

	#define TIMER2_EN          (1 << 0)

	#define UIE                (1 << 0)
	#define CC1IE              (1 << 1)
	#define CC2IE              (1 << 2)
	#define CC3IE              (1 << 3)
	#define CC4IE              (1 << 4)
	#define COMIE              (1 << 5)
	#define TIE                (1 << 6)
	#define BIE                (1 << 7)
	#define UDE                (1 << 8)
	#define CC1DE              (1 << 9)
	#define CC2DE              (1 << 10)
	#define CC3DE              (1 << 11)
	#define CC4DE              (1 << 12)
	#define COMDE              (1 << 14)
	#define TDE                (1 << 15)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef TIMER3_REG_CONFIG

	#define TIMER3_ADDR_MAP    (0x40000400)
	#define RCC_ADDR_MAP       (0x40023800)

	#define RCC_APB1ENR_OFFSET (0x40)

	#define TIM3_CR1_OFFSET    (0x00)
	#define TIM3_CR2_OFFSET    (0x04)
	#define TIM3_DIER_OFFSET   (0x0C)
	#define TIM3_SR_OFFSET     (0x10)
	#define TIM3_CNT_OFFSET    (0x24)
	#define TIM3_PSC_OFFSET    (0x28)
	#define TIM3_ARR_OFFSET    (0x2C)

	#define TIM3_CR1_REG       *(volatile uint32_t *)(TIMER3_ADDR_MAP + TIM3_CR1_OFFSET)
	#define TIM3_CR2_REG       *(volatile uint32_t *)(TIMER3_ADDR_MAP + TIM3_CR2_OFFSET)
	#define TIM3_DIER_REG      *(volatile uint32_t *)(TIMER3_ADDR_MAP + TIM3_DIER_OFFSET)
	#define TIM3_SR_REG        *(volatile uint32_t *)(TIMER3_ADDR_MAP + TIM3_SR_OFFSET)
	#define TIM3_CNT_REG       *(volatile uint32_t *)(TIMER3_ADDR_MAP + TIM3_CNT_OFFSET)
	#define TIM3_PSC_REG       *(volatile uint32_t *)(TIMER3_ADDR_MAP + TIM3_PSC_OFFSET)
	#define TIM3_ARR_REG       *(volatile uint32_t *)(TIMER3_ADDR_MAP + TIM3_ARR_OFFSET)

	#define RCC_APB1ENR_PER_BUS *(volatile uint32_t *)(RCC_ADDR_MAP + RCC_APB1ENR_OFFSET)

	#define TIMER3_EN          (1 << 1)

	#define UIE                (1 << 0)
	#define CC1IE              (1 << 1)
	#define CC2IE              (1 << 2)
	#define CC3IE              (1 << 3)
	#define CC4IE              (1 << 4)
	#define COMIE              (1 << 5)
	#define TIE                (1 << 6)
	#define BIE                (1 << 7)
	#define UDE                (1 << 8)
	#define CC1DE              (1 << 9)
	#define CC2DE              (1 << 10)
	#define CC3DE              (1 << 11)
	#define CC4DE              (1 << 12)
	#define COMDE              (1 << 14)
	#define TDE                (1 << 15)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef TIMER4_REG_CONFIG

	#define TIMER4_ADDR_MAP    (0x40000800)
	#define RCC_ADDR_MAP       (0x40023800)

	#define RCC_APB1ENR_OFFSET (0x40)

	#define TIM4_CR1_OFFSET    (0x00)
	#define TIM4_CR2_OFFSET    (0x04)
	#define TIM4_DIER_OFFSET   (0x0C)
	#define TIM4_SR_OFFSET     (0x10)
	#define TIM4_CNT_OFFSET    (0x24)
	#define TIM4_PSC_OFFSET    (0x28)
	#define TIM4_ARR_OFFSET    (0x2C)

	#define TIM4_CR1_REG       *(volatile uint32_t *)(TIMER4_ADDR_MAP + TIM4_CR1_OFFSET)
	#define TIM4_CR2_REG       *(volatile uint32_t *)(TIMER4_ADDR_MAP + TIM4_CR2_OFFSET)
	#define TIM4_DIER_REG      *(volatile uint32_t *)(TIMER4_ADDR_MAP + TIM4_DIER_OFFSET)
	#define TIM4_SR_REG        *(volatile uint32_t *)(TIMER4_ADDR_MAP + TIM4_SR_OFFSET)
	#define TIM4_CNT_REG       *(volatile uint32_t *)(TIMER4_ADDR_MAP + TIM4_CNT_OFFSET)
	#define TIM4_PSC_REG       *(volatile uint32_t *)(TIMER4_ADDR_MAP + TIM4_PSC_OFFSET)
	#define TIM4_ARR_REG       *(volatile uint32_t *)(TIMER4_ADDR_MAP + TIM4_ARR_OFFSET)

	#define RCC_APB1ENR_PER_BUS *(volatile uint32_t *)(RCC_ADDR_MAP + RCC_APB1ENR_OFFSET)

	#define TIMER4_EN          (1 << 2)

	#define UIE                (1 << 0)
	#define CC1IE              (1 << 1)
	#define CC2IE              (1 << 2)
	#define CC3IE              (1 << 3)
	#define CC4IE              (1 << 4)
	#define COMIE              (1 << 5)
	#define TIE                (1 << 6)
	#define BIE                (1 << 7)
	#define UDE                (1 << 8)
	#define CC1DE              (1 << 9)
	#define CC2DE              (1 << 10)
	#define CC3DE              (1 << 11)
	#define CC4DE              (1 << 12)
	#define COMDE              (1 << 14)
	#define TDE                (1 << 15)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef TIMER

//	#define TIM1_ADDR  (0x40012C00)
//	#define TIM3_MEM_ADD	 (0x40000400)



	// #define PORT_CONFIG_REG_HI 			(0x04) //ADDRESS OFFSET VALUES;
	// #define RCC_APB2ENR_OFFSET 			(0x18)



	#define RCC_CR_OFFSET               (0x00)
	#define RCC_GFGR_OFFSET             (0x04)



	/*bit_word_addr = bit_band_base + (byte_offset x 32) + (bit_number × 4)
	where:
		bit_word_addr is the address of the word in the alias memory region that maps to the
		targeted bit.
		bit_band_base is the starting address of the alias region
		byte_offset is the number of the byte in the bit-band region that contains the targeted
		bit
		bit_number is the bit position (0-7) of the targeted bit.
		Example:
		The following example shows how to map bit 2 of the byte located at SRAM address
		0x20000300 in the alias region:
		0x22006008 = 0x22000000 + (0x300*32) + (2*4).
		Writing to address 0x22006008 has the same effect as a read-modify-write operation on bit
		2 of the byte at SRAM address 0x20000300.
		Reading address 0x22006008 returns the value (0x0
	*/

	/*RCC CLOCK ACTIVATE  RCC_CR_REG This control register's set bit*/
	#define HSI_ON                               (1 << 0)
	#define HSE_ON                              (1 << 16)
	#define HSE_RDY                              (1 << 17)
	#define CSS_ON                              (1 << 19)
	#define PLLON                               (1 << 24)
	#define PLLRDY                               (1 << 25)

	/*RCC_CFGR */
	#define RCC_AHB1ENR_GPIO_OFFSET 	(0x30)
	#define RCC_APB1ENR_PER_OFFSET      (0x40)


	#define RCC_CR_REG              *(volatile uint32_t *) (RCC_BASE + RCC_CR_OFFSET)
	#define RCC_GFGR_REG            *(volatile uint32_t *) (RCC_BASE + RCC_GFGR_OFFSET)

	#define RCC_AHB1ENR_GPIO  	 	*(volatile uint32_t *) (RCC_BASE + RCC_AHB1ENR_GPIO_OFFSET)
	#define RCC_APB1ENR_PER         *(volatile uint32_t *) (RCC_BASE + RCC_APB1ENR_PER_OFFSET)

	#define RCC_APB2ENR    		    *(volatile uint32_t *) (RCC_BASE + RCC_APB2ENR_OFFSET)

	#define RCC_APB1ENR_PWREN     (1 << 28)
	#define RCC_GFCR_SW           (1 << 1)
	#define RCC_HSEBYP            (1 << 18)


	#define RCC_HPRE              (0x00000000)
	#define RCC_PPRE1			  (0x00000000)
	#define RCC_PPRE2             (0x00000000)


#endif


/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef RCC_PORT_ENABLE

	#define RCC_IOPAEN        (SET_BIT << 0)
	#define RCC_IOPBEN        (SET_BIT << 1)
	#define RCC_IOPCEN	      (SET_BIT << 2)
	#define RCC_IOPDEN        (SET_BIT << 3)
	#define RCC_IOPEEN        (SET_BIT << 4)
	#define RCC_IOPFEN        (SET_BIT << 5)
	#define RCC_IOPGEN        (SET_BIT << 6)
	#define RCC_IOPHEN        (SET_BIT << 7)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef GPIOA_IN_OUT_CONFIG

	#define PORT_ODR_OFFSET 			(0x14)
	#define PORT_IDR_OFFSET    			(0x10)

	#define RCC_GPIOx_MODER_OFFSET      (0x00)
	#define GPIOx_OTYPER_OFFSET         (0x04)
	#define RCC_GPIOx_OSPEED_OFFSET     (0x08)
	#define RCC_GPIOx_PUPDR_OFFSET      (0x0C)
	#define RCC_GPIOx_AFRL_OFFSET       (0x20)
	#define RCC_GPIOx_AFRH_OFFSET       (0x24)


	#define GPIOA_ODR      		 *(volatile uint32_t *) (GPIOA_ADDR + PORT_ODR_OFFSET)
	#define GPIOA_MODER          *(volatile uint32_t *) (GPIOA_ADDR + RCC_GPIOx_MODER_OFFSET)
	#define GPIOA_OTYPER		 *(volatile uint32_t *) (GPIOA_ADDR + GPIOx_OTYPER_OFFSET)
	#define GPIOA_OSPEEDR        *(volatile uint32_t *) (GPIOA_ADDR + RCC_GPIOx_OSPEED_OFFSET)
	#define GPIOA_PUPDR          *(volatile uint32_t *) (GPIOA_ADDR + RCC_GPIOx_PUPDR_OFFSET)
	#define GPIOA_AFRL           *(volatile uint32_t *) (GPIOA_ADDR + RCC_GPIOx_AFRL_OFFSET)
	#define GPIOA_AFRH           *(volatile uint32_t *)(GPIOA_ADDR + RCC_GPIOx_AFRH_OFFSET)
	//This register is used as input register.
	#define GPIOA_IDR  		     *(volatile uint32_t *) (GPIOA_ADDR + PORT_IDR_OFFSET)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */


#ifndef GPIOB_IN_OUT_CONFIG

	#define PORT_ODR_OFFSET 			(0x14)
	#define PORT_IDR_OFFSET    			(0x10)

	#define RCC_GPIOx_MODER_OFFSET      (0x00)
	#define GPIOx_OTYPER_OFFSET         (0x04)
	#define RCC_GPIOx_OSPEED_OFFSET     (0x08)
	#define RCC_GPIOx_PUPDR_OFFSET      (0x0C)
	#define RCC_GPIOx_AFRL_OFFSET       (0x20)
	#define RCC_GPIOx_AFRH_OFFSET       (0x24)


	#define GPIOB_ODR      		 *(volatile uint32_t *) (GPIOB_ADDR + PORT_ODR_OFFSET)
	#define GPIOB_MODER          *(volatile uint32_t *) (GPIOB_ADDR + RCC_GPIOx_MODER_OFFSET)
	#define GPIOB_OTYPER		 *(volatile uint32_t *) (GPIOB_ADDR + GPIOx_OTYPER_OFFSET)
	#define GPIOB_OSPEEDR        *(volatile uint32_t *) (GPIOB_ADDR + RCC_GPIOx_OSPEED_OFFSET)
	#define GPIOB_PUPDR          *(volatile uint32_t *) (GPIOB_ADDR + RCC_GPIOx_PUPDR_OFFSET)
	#define GPIOB_AFRL           *(volatile uint32_t *) (GPIOB_ADDR + RCC_GPIOx_AFRL_OFFSET)
	#define GPIOB_AFRH           *(volatile uint32_t *)(GPIOB_ADDR + RCC_GPIOx_AFRH_OFFSET)
	//This register is used as input register.
	#define GPIOB_IDR  		     *(volatile uint32_t *) (GPIOB_ADDR + PORT_IDR_OFFSET)

	#define GPIOD_ODR            *(volatile uint32_t *) (GPIOD_ADDR + PORT_ODR_OFFSET)
	#define GPIOD_MODER		     *(volatile uint32_t *) (GPIOD_ADDR + RCC_GPIOx_MODER_OFFSET)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

#ifndef GPIOc_IN_OUT_CONFIG

	#define PORT_ODR_OFFSET 			(0x14)
	#define PORT_IDR_OFFSET    			(0x10)

	#define RCC_GPIOx_MODER_OFFSET      (0x00)
	#define GPIOx_OTYPER_OFFSET         (0x04)
	#define RCC_GPIOx_OSPEED_OFFSET     (0x08)
	#define RCC_GPIOx_PUPDR_OFFSET      (0x0C)
	#define RCC_GPIOx_AFRL_OFFSET       (0x20)
	#define RCC_GPIOx_AFRH_OFFSET       (0x24)


	#define GPIOC_ODR      		 *(volatile uint32_t *) (GPIOC_ADDR + PORT_ODR_OFFSET)
	#define GPIOC_MODER          *(volatile uint32_t *) (GPIOC_ADDR + RCC_GPIOx_MODER_OFFSET)
	#define GPIOC_OTYPER		 *(volatile uint32_t *) (GPIOC_ADDR + GPIOx_OTYPER_OFFSET)
	#define GPIOC_OSPEEDR        *(volatile uint32_t *) (GPIOC_ADDR + RCC_GPIOx_OSPEED_OFFSET)
	#define GPIOC_PUPDR          *(volatile uint32_t *) (GPIOC_ADDR + RCC_GPIOx_PUPDR_OFFSET)
	#define GPIOC_AFRL           *(volatile uint32_t *) (GPIOC_ADDR + RCC_GPIOx_AFRL_OFFSET)
	#define GPIOC_AFRH           *(volatile uint32_t *)(GPIOC_ADDR + RCC_GPIOx_AFRH_OFFSET)
	//This register is used as input register.
	#define GPIOC_IDR  		     *(volatile uint32_t *) (GPIOC_ADDR + PORT_IDR_OFFSET)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef GPIOD_IN_OUT_CONFIG

	#define PORT_ODR_OFFSET 			(0x14)
	#define PORT_IDR_OFFSET    			(0x10)

	#define RCC_GPIOx_MODER_OFFSET      (0x00)
	#define GPIOx_OTYPER_OFFSET         (0x04)
	#define RCC_GPIOx_OSPEED_OFFSET     (0x08)
	#define RCC_GPIOx_PUPDR_OFFSET      (0x0C)
	#define RCC_GPIOx_AFRL_OFFSET       (0x20)
	#define RCC_GPIOx_AFRH_OFFSET       (0x24)


	#define GPIOD_ODR      		 *(volatile uint32_t *) (GPIOD_ADDR + PORT_ODR_OFFSET)
	#define GPIOD_MODER          *(volatile uint32_t *) (GPIOD_ADDR + RCC_GPIOx_MODER_OFFSET)
	#define GPIOD_OTYPER		 *(volatile uint32_t *) (GPIOD_ADDR + GPIOx_OTYPER_OFFSET)
	#define GPIOD_OSPEEDR        *(volatile uint32_t *) (GPIOD_ADDR + RCC_GPIOx_OSPEED_OFFSET)
	#define GPIOD_PUPDR          *(volatile uint32_t *) (GPIOD_ADDR + RCC_GPIOx_PUPDR_OFFSET)
	#define GPIOD_AFRL           *(volatile uint32_t *) (GPIOD_ADDR + RCC_GPIOx_AFRL_OFFSET)
	#define GPIOD_AFRH           *(volatile uint32_t *)(GPIOD_ADDR + RCC_GPIOx_AFRH_OFFSET)
	//This register is used as input register.
	#define GPIOD_IDR  		     *(volatile uint32_t *) (GPIOD_ADDR + PORT_IDR_OFFSET)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef GPIOE_IN_OUT_CONFIG

	#define PORT_ODR_OFFSET 			(0x14)
	#define PORT_IDR_OFFSET    			(0x10)

	#define RCC_GPIOx_MODER_OFFSET      (0x00)
	#define GPIOx_OTYPER_OFFSET         (0x04)
	#define RCC_GPIOx_OSPEED_OFFSET     (0x08)
	#define RCC_GPIOx_PUPDR_OFFSET      (0x0C)
	#define RCC_GPIOx_AFRL_OFFSET       (0x20)
	#define RCC_GPIOx_AFRH_OFFSET       (0x24)


	#define GPIOE_ODR      		 *(volatile uint32_t *) (GPIOE_ADDR + PORT_ODR_OFFSET)
	#define GPIOE_MODER          *(volatile uint32_t *) (GPIOE_ADDR + RCC_GPIOx_MODER_OFFSET)
	#define GPIOE_OTYPER		 *(volatile uint32_t *) (GPIOE_ADDR + GPIOx_OTYPER_OFFSET)
	#define GPIOE_OSPEEDR        *(volatile uint32_t *) (GPIOE_ADDR + RCC_GPIOx_OSPEED_OFFSET)
	#define GPIOE_PUPDR          *(volatile uint32_t *) (GPIOE_ADDR + RCC_GPIOx_PUPDR_OFFSET)
	#define GPIOE_AFRL           *(volatile uint32_t *) (GPIOE_ADDR + RCC_GPIOx_AFRL_OFFSET)
	#define GPIOE_AFRH           *(volatile uint32_t *)(GPIOE_ADDR + RCC_GPIOx_AFRH_OFFSET)
	//This register is used as input register.
	#define GPIOE_IDR  		     *(volatile uint32_t *) (GPIOE_ADDR + PORT_IDR_OFFSET)

#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

#ifndef RCC_GPIO_MODE
	//#define RCC_APB2ENR     (RCC_IOPCEN)
	/**/


	#define GPIOAx_TYPE       (SET_BIT << 1)
	#define GPIOAx_SPEED      (SET_BIT << 1)
	/*#define GPIOBx_TYPE       (SET_BIT << 11)
	 #define GPIOBx_SPEED      (SET_BIT << 22)*/
	#define GPIOA1_MODE       (SET_BIT << 2)
	#define GPIOA1			  (1UL << 1)


	#define GPIOA3_MODE  	  (SET_BIT << 6)
	#define GPIOA3_PULL 	  (SET_BIT << 6)
	#define GPIOA3 			  (1UL << 3)


	#define GPIOA4_MODE  	  (SET_BIT << 8)
	#define GPIOA4_PULL 	  (SET_BIT << 8)
	#define GPIOA4 			  (1UL << 4)


	#define GPIOA5_MODE       (SET_BIT << 10)
	#define GPIOA5_PULL		  (SET_BIT << 10)
	#define GPIOA5   		  (1UL << 5)

	#define GPIOA6_MODE       (SET_BIT << 12)
	#define GPIOA6_PULL		  (SET_BIT << 12)
	#define GPIOA6   		  (1UL << 6)

	#define GPIOA8_MODE       (SET_BIT << 16)
	#define GPIOA8            (1UL << 8)

	/*PORTB_9*/
	#define GPIOA9_MODE      (SET_BIT << 18)
	#define GPIOA9_PULL      (SET_BIT << 18)
	#define GPIOA9           (1UL << 9)

	/*PORTB_10*/
	#define GPIOA10_MODE      (SET_BIT << 20)
	#define GPIOA10_PULL      (SET_BIT << 20)
	#define GPIOA10           (1UL << 10)

	/*PORTB_11*/
	#define GPIOA11_MODE      (SET_BIT << 22)
	#define GPIOA11_PULL      (SET_BIT << 22)
	#define GPIOA11           (1UL << 11)
	/*PORTB_12*/
	#define GPIOA12_MODE      (SET_BIT << 24)
	#define GPIOA12_PULL      (SET_BIT << 24)
	#define GPIOA12           (1UL << 12)

	/*PORTB_13*/
	#define GPIOA13_MODE      (SET_BIT << 26)
	#define GPIOA13_PULL      (SET_BIT << 26)
	#define GPIOA13           (1UL << 13)

	/*PORTB_14*/
	#define GPIOA14_MODE      (SET_BIT << 28)
	#define GPIOA14_PULL      (SET_BIT << 28)
	#define GPIOA14           (1UL << 14)

	#define GPIOA15_MODE      (SET_BIT << 31)|(SET_BIT << 30)
	#define GPIOA15           (SET_BIT << 15)



#endif


#ifndef RCC_GPIO_MODE
	//#define RCC_APB2ENR     (RCC_IOPCEN)
	/**/


	#define GPIOBx_TYPE       (SET_BIT << 1)
	#define GPIOBx_SPEED      (SET_BIT << 1)
	/*#define GPIOBx_TYPE       (SET_BIT << 11)
	 #define GPIOBx_SPEED      (SET_BIT << 22)*/
	#define GPIOB1_MODE       (SET_BIT << 2)
	#define GPIOB1			  (1UL << 1)

	#define GPIOB3_MODE  	  (SET_BIT << 6)
	#define GPIOB3_PULL 	  (SET_BIT << 6)
	#define GPIOB3 			  (1UL << 3)


	#define GPIOB5_MODE       (SET_BIT << 10)
	#define GPIOB5_PULL		  (SET_BIT << 10)
	#define GPIOB5   		  (1UL << 5)

	#define GPIOB6_MODE       (SET_BIT << 12)
	#define GPIOB6_PULL		  (SET_BIT << 12)
	#define GPIOB6   		  (1UL << 6)

	#define GPIOB8_MODE       (SET_BIT << 16)
	#define GPIOB8            (1UL << 8)

	#define GPIOB9_MODE		  (SET_BIT << 18)
	#define GPIOB9_PULL		  (SET_BIT << 18)
	#define GPIOB9			  (SET_BIT << 9)

	#define GPIOB10_MODE      (SET_BIT << 20)
	#define GPIOB10_PULL      (SET_BIT << 20)
	#define GPIOB10           (1UL << 10)
	/*PORTB_11*/
	#define GPIOB11_MODE      (SET_BIT << 22)
	#define GPIOB11_PULL      (SET_BIT << 22)
	#define GPIOB11           (1UL << 11)
	/*PORTB_12*/
	#define GPIOB12_MODE      (SET_BIT << 24)
	#define GPIOB12_PULL      (SET_BIT << 24)
	#define GPIOB12           (1UL << 12)

	/*PORTB_13*/
	#define GPIOB13_MODE      (SET_BIT << 26)
	#define GPIOB13_PULL      (SET_BIT << 26)
	#define GPIOB13           (1UL << 13)

	/*PORTB_14*/
	#define GPIOB14_MODE      (SET_BIT << 28)
	#define GPIOB14_PULL      (SET_BIT << 28)
	#define GPIOB14           (1UL << 14)

	#define GPIOB15_MODE      (SET_BIT << 31)|(SET_BIT << 30)
	#define GPIOB15           (SET_BIT << 15)


	//**********************************/
	//PortE
	#define GPIOEx_TYPE       (SET_BIT << 1)
	#define GPIOEx_SPEED      (SET_BIT << 1)

	//PORTE -1
	#define GPIOE0_MODE      (SET_BIT << 1)
	#define GPIOE0_PULL      (SET_BIT << 1)
	#define GPIOE0           (1UL << 1)

	#define GPIOE1_MODE      (SET_BIT << 2)
	#define GPIOE1_PULL      (SET_BIT << 2)
	#define GPIOE1           (1UL << 2)

	/*PORTE_15*/
	#define GPIOE15_MODE      (SET_BIT << 30)
	#define GPIOE15_PULL      (SET_BIT << 30)
	#define GPIOE15           (1UL << 15)



#endif

#ifndef PORTC_CONFIG

	#define GPIOCx_TYPE       (SET_BIT << 1)
	#define GPIOCx_SPEED      (SET_BIT << 1)
	/*#define GPIOBx_TYPE       (SET_BIT << 11)
	 #define GPIOBx_SPEED      (SET_BIT << 22)*/
	#define GPIOC1_MODE       (SET_BIT << 2)
	#define GPIOC1			  (1UL << 1)


	#define GPIOC3_MODE  	  (SET_BIT << 6)
	#define GPIOC3_PULL 	  (SET_BIT << 6)
	#define GPIOC3 			  (1UL << 3)


	#define GPIOC4_MODE  	  (SET_BIT << 8)
	#define GPIOC4_PULL 	  (SET_BIT << 8)
	#define GPIOC4 			  (1UL << 4)


	#define GPIOC5_MODE       (SET_BIT << 10)
	#define GPIOC5_PULL		  (SET_BIT << 10)
	#define GPIOC5   		  (1UL << 5)

	#define GPIOC6_MODE       (SET_BIT << 12)
	#define GPIOC6_PULL		  (SET_BIT << 12)
	#define GPIOC6   		  (1UL << 6)

	#define GPIOC7_MODE       (SET_BIT << 14)
	#define GPIOC7_PULL		  (SET_BIT << 14)
	#define GPIOC7   		  (1UL << 7)

	#define GPIOC8_MODE       (SET_BIT << 16)
	#define GPIOC8_PULL		  (SET_BIT << 16)
	#define GPIOC8            (1UL << 8)

	/*PORTB_9*/
	#define GPIOC9_MODE      (SET_BIT << 18)
	#define GPIOC9_PULL      (SET_BIT << 18)
	#define GPIOC9           (1UL << 9)

	/*PORTB_10*/
	#define GPIOC10_MODE      (SET_BIT << 20)
	#define GPIOC10_PULL      (SET_BIT << 20)
	#define GPIOC10           (1UL << 10)

	/*PORTB_11*/
	#define GPIOC11_MODE      (SET_BIT << 22)
	#define GPIOC11_PULL      (SET_BIT << 22)
	#define GPIOC11           (1UL << 11)
	/*PORTB_12*/
	#define GPIOC12_MODE      (SET_BIT << 24)
	#define GPIOC12_PULL      (SET_BIT << 24)
	#define GPIOC12           (1UL << 12)

	/*PORTB_13*/
	#define GPIOC13_MODE      (SET_BIT << 26)
	#define GPIOC13_PULL      (SET_BIT << 26)
	#define GPIOC13           (1UL << 13)

	/*PORTB_14*/
	#define GPIOC14_MODE      (SET_BIT << 28)
	#define GPIOC14_PULL      (SET_BIT << 28)
	#define GPIOC14           (1UL << 14)

	#define GPIOC15_MODE      (SET_BIT << 31)|(SET_BIT << 30)
	#define GPIOC15           (SET_BIT << 15)

#endif



#ifndef PORTD_CONFIG

	#define GPIODx_TYPE       (SET_BIT << 1)
	#define GPIODx_SPEED      (SET_BIT << 1)
	/*#define GPIOBx_TYPE       (SET_BIT << 11)
	 #define GPIOBx_SPEED      (SET_BIT << 22)*/
	#define GPIOD1_MODE       (SET_BIT << 2)
	#define GPIOD1			  (1UL << 1)


	#define GPIOD3_MODE  	  (SET_BIT << 6)
	#define GPIOD3_PULL 	  (SET_BIT << 6)
	#define GPIOD3 			  (1UL << 3)


	#define GPIOD4_MODE  	  (SET_BIT << 8)
	#define GPIOD4_PULL 	  (SET_BIT << 8)
	#define GPIOD4 			  (1UL << 4)


	#define GPIOD5_MODE       (SET_BIT << 10)
	#define GPIOD5_PULL		  (SET_BIT << 10)
	#define GPIOD5   		  (1UL << 5)

	#define GPIOD6_MODE       (SET_BIT << 12)
	#define GPIOD6_PULL		  (SET_BIT << 12)
	#define GPIOD6   		  (1UL << 6)

	#define GPIOD7_MODE       (SET_BIT << 14)
	#define GPIOD7_PULL		  (SET_BIT << 14)
	#define GPIOD7   		  (1UL << 7)

	#define GPIOD8_MODE       (SET_BIT << 16)
	#define GPIOD8_PULL		  (SET_BIT << 16)
	#define GPIOD8            (1UL << 8)

	/*PORTB_9*/
	#define GPIOD9_MODE      (SET_BIT << 18)
	#define GPIOD9_PULL      (SET_BIT << 18)
	#define GPIOD9           (1UL << 9)

	/*PORTB_10*/
	#define GPIOD10_MODE      (SET_BIT << 20)
	#define GPIOD10_PULL      (SET_BIT << 20)
	#define GPIOD10           (1UL << 10)

	/*PORTB_11*/
	#define GPIOD11_MODE      (SET_BIT << 22)
	#define GPIOD11_PULL      (SET_BIT << 22)
	#define GPIOD11           (1UL << 11)
	/*PORTB_12*/
	#define GPIOD12_MODE      (SET_BIT << 24)
	#define GPIOD12_PULL      (SET_BIT << 24)
	#define GPIOD12           (1UL << 12)

	/*PORTB_13*/
	#define GPIOD13_MODE      (SET_BIT << 26)
	#define GPIOD13_PULL      (SET_BIT << 26)
	#define GPIOD13           (1UL << 13)

	/*PORTB_14*/
	#define GPIOD14_MODE      (SET_BIT << 28)
	#define GPIOD14_PULL      (SET_BIT << 28)
	#define GPIOD14           (1UL << 14)

	#define GPIOD15_MODE      (SET_BIT << 30)
	#define GPIOD15_PULL      (SET_BIT << 30)
	#define GPIOD15           (SET_BIT << 15)

#endif


/***************************************************************************************************************************
* *************************************************************************************************************************
* * *************************************************************************************************************************
* *****************************************************END*****************************************************************
*/
#ifndef SET_GPIOx_PIN

	#define GPIOx_PIN_0 	   	(1UL << 0)
	#define GPIOx_PIN_1	 		(1UL << 1)
	#define GPIOx_PIN_2    		(1UL << 2)
	#define GPIOx_PIN_3	 		(1UL << 3)
	#define GPIOx_PIN_4    		(1UL << 4)
	#define GPIOx_PIN_5	 		(1UL << 5)
	#define GPIOx_PIN_6    		(1UL << 6)
	#define GPIOx_PIN_7	 		(1UL << 7)
	#define GPIOx_PIN_8    		(1UL << 8)
	#define GPIOx_PIN_9	 		(1UL << 9)
	#define GPIOx_PIN_10    	(1UL << 10)
	#define GPIOx_PIN_11	 	(1UL << 11)
	#define GPIOx_PIN_12    	(1UL << 12)
	#define GPIOx_PIN_13	 	(1UL << 13)
	#define GPIOx_PIN_14    	(1UL << 14)
	#define GPIOx_PIN_15	 	(1UL << 15)

#endif
/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
#ifndef I2C1_GPIO_CONFIG_PCF8575
	// #define _I2C1_SDA       (PB7)
	// #define _I2C1_SCL       (PB6)


	#define GPIOB6_MODE     (SET_BIT << 12)
	#define GPIOB6_PULL     (SET_BIT << 12)
	#define GPIOB6          (1UL << 6)

	#define GPIOB7_MODE     (SET_BIT << 14)
	#define GPIOB7_PULL     (SET_BIT << 15)
	#define GPIOB7          (1UL << 7)


	#define _I2C1_SDA       (1UL << 7)
	#define _I2C1_SCL       (1UL << 6)

	#define GPIOB7_IN_MODE  (SET_BIT << 15)|(SET_BIT << 14)

	#define GPIOB_AFRL_EN   (0x76000000)

	#define PCF8575_WR_SlaveAdd   (0x4E) //4E
	#define PCF8575_RD_SlaveAdd   (0x4F) //4F

	/*External GPIO as OUTPUT Bit enable L-Byte and H-byte*/

	#define PCF8575_EX_GPIO_P0_0       (0x01)
	#define PCF8575_EX_GPIO_P0_1       (0x02)
	#define PCF8575_EX_GPIO_P0_2       (0x04)
	#define PCF8575_EX_GPIO_P0_3       (0x08)

	#define PCF8575_EX_GPIO_P0_4       (0x10)
	#define PCF8575_EX_GPIO_P0_5       (0x20)
	#define PCF8575_EX_GPIO_P0_6       (0x40)
	#define PCF8575_EX_GPIO_P0_7       (0x80)
	/*External gpio port_1 bit configuration used the macro methods*/
	#define PCF8575_EX_GPIO_P1_0       (0x01)
	#define PCF8575_EX_GPIO_P1_1       (0x02)
	#define PCF8575_EX_GPIO_P1_2       (0x04)
	#define PCF8575_EX_GPIO_P1_3       (0x08)

	#define PCF8575_EX_GPIO_P1_4       (0x10)
	#define PCF8575_EX_GPIO_P1_5       (0x20)
	#define PCF8575_EX_GPIO_P1_6       (0x40)
	#define PCF8575_EX_GPIO_P1_7       (0x80)
	/*Clear the External gpio pins*/
	#define PCF8575_EX_GPIO_P0         (0x00)
	#define PCF8575_EX_GPIO_P1         (0x00)



#endif


/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

#ifndef USART2_REG_CONFIG
//reference link:https://controllerstech.com/how-to-setup-uart-using-registers-in-stm32/

	#define USART_RCC_MEM_ADDR          (0x40023800)
	#define USART_AHB1ENR_OFFSET 		(0x30)
	#define USART_APB1ENR_OFFSET		(0x40)


	#define USART_GPIOA_CLK_EN          (1 << 0)
	#define USART_CLK_EN				(1 << 17)

	#define USART2_AHB1ENR 			   *(volatile uint32_t*)(USART_RCC_MEM_ADDR + USART_AHB1ENR_OFFSET)
	#define USART2_APB1ENR   		   *(volatile uint32_t *)(USART_RCC_MEM_ADDR + USART_APB1ENR_OFFSET)
/*
	#define GPIOA_MODER_OFFSET    		(0x00)
	#define GPIOA_OSPEEDR_OFFSET  		(0x08)
	#define GPIOA_PUPDR_OFFSET          (0x0C)
	#define GPIOA_IDR_OFFSET            (0x10)
	#define GPIOA_ODR_OFFSET            (0x14)
	#define GPIOA_AFRL_OFFSET           (0x20)
	#define GPIOA_AFRH_OFFSET           (0x24)

	#define GPIOA_MODER  			   *(volatile uint32_t *)(GPIOA_ADDR + GPIOA_MODER_OFFSET)
	#define GPIOA_OSPEEDR  		       *(volatile uint32_t *)(GPIOA_ADDR + GPIOA_OSPEEDR_OFFSET)
	#define GPIOA_PUPDR    			   *(volatile uint32_t *)(GPIOA_ADDR + GPIOA_PUPDR_OFFSET)
	#define GPIOA_IDR      			   *(volatile uint32_t *)(GPIOA_ADDR + GPIOA_IDR_OFFSET)
	#define GPIOA_ODR      			   *(volatile uint32_t *)(GPIOA_ADDR + GPIOA_ODR_OFFSET)
	#define GPIOA_AFRL     			   *(volatile uint32_t *)(GPIOA_ADDR + GPIOA_AFRL_OFFSET)
	#define GPIOA_AFRH     			   *(volatile uint32_t *)(GPIOA_ADDR + GPIOA_AFRH_OFFSET)
*/
	#define USART2_SR_OFFSET   			(0x00)
	#define USART2_DR_OFFSET   			(0x04)
	#define USART2_BRR_OFFSET  			(0x08)
	#define USART2_CR1_OFFSET  			(0x0C)
	#define USART2_CR2_OFFSET  			(0x10)
	#define USART2_CR3_OFFSET  			(0x18)

	#define USART2_SR  				   *(volatile uint32_t *)(USART2_MEM_ADDR + USART2_SR_OFFSET)
	#define USART2_DR   			   *(volatile uint32_t *)(USART2_MEM_ADDR + USART2_DR_OFFSET)
	#define USART2_BRR  			   *(volatile uint32_t *)(USART2_MEM_ADDR + USART2_BRR_OFFSET)
	#define USART2_CR1  			   *(volatile uint32_t *)(USART2_MEM_ADDR + USART2_CR1_OFFSET)
	#define USART2_CR2  			   *(volatile uint32_t *)(USART2_MEM_ADDR + USART2_CR2_OFFSET)
	#define USART2_CR3  			   *(volatile uint32_t *)(USART2_MEM_ADDR + USART2_CR3_OFFSET)


	//ENABLE as GPIOA_BIT
	/*MODERy[1:0]: Port x configuration bits (y = 0..15)
	These bits are written by software to configure the I/O direction mode.
	00: Input (reset state)
	01: General purpose output mode
	10: Alternate function
	11: Analog pin
	*/
	#define GPIOA_MODER_PA2    (2 << 4)
	#define GPIOA_MODER_PA3    (2 << 6)
	/*OSPEEDRy[1:0]: Port x configuration bits (y = 0..15)
	These bits are written by software to configure the I/O output speed.
	00: Low speed
	01: Medium speed
	10: High speed
	11: Very high speed
	Note: Refer to the product datas*/
	#define GPIOA_OSPEEDR_PA2_PA3  ((3 << 4)|(3 << 6))
	/*Bits 31:0 AFRLy: Alternate function selection for port x bit y (y = 0..7)
	These bits are written by software to configure alternate function I/Os
	AFRLy selection:
	0000: AF0
	0001: AF1
	0010: AF2
	0011: AF3
	0100: AF4
	0101: AF5
	0110: AF6
	0111: AF7 -> USART2_EN;
	1000: AF8
	1001: AF9
	1010: AF10
	1011: AF11
	1100: AF12
	1101: AF13
	1110: AF14
	1111: AF15*/
	#define GPIOA_AFRL_PA2		(7 << 8)
	#define GPIOA_AFRL_PA3		(7 << 12)
	//USART_STATUS_BIT_CONFIG
	#define CTS    				(1 << 9)
	#define LBD    				(1 << 8)
	#define TXE    				(1 << 7)
	#define TC 	   				(1 << 6)
	#define RXNE   				(1 << 5)
	#define IDLE   				(1 << 4)
	#define ORE	   				(1 << 3)
	#define NF	   				(1 << 2)
	#define FE     				(1 << 1)
	#define PE	   				(1 << 0)
	//USART_CONTROL_REG
	#define OVER8				(1 << 15)
	#define UE					(1 << 13)
	#define M 					(1 << 12)
	#define WAKE				(1 << 11)
	#define PCE					(1 << 10)
	#define PS					(1 << 9)
	#define PEIE				(1 << 8)
	#define TXEIE				(1 << 7)
	#define TCIE				(1 << 6)
	#define RXNEIE				(1 << 5)
	#define IDLEIE				(1 << 4)
	#define TE					(1 << 3)
	#define RE					(1 << 2)
	#define RWU					(1 << 1)
	#define SBK					(1 << 0)

	//#define BAUD_RATE_115200    (138)    //((5 << 0)|(4<<4))
	#define BAUD_RATE_115200    ((5 << 0)|(4<<4))
#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

//
//typedef enum
//{
///******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
//  NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
//  MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
//  BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
//  UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
//  SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
//  DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
//  PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
//  SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
///******  STM32 specific Interrupt Numbers **********************************************************************/
//  WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
//  PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
//  TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
//  RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
//  FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
//  RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
#define  EXTI0_IRQn              (6)      /*!< EXTI Line0 Interrupt                                              */
#define  EXTI1_IRQn              (7)      /*!< EXTI Line1 Interrupt                                              */
#define  EXTI2_IRQn              (8)      /*!< EXTI Line2 Interrupt                                              */
#define  EXTI3_IRQn              (9)      /*!< EXTI Line3 Interrupt                                              */
#define  EXTI4_IRQn              (10)     /*!< EXTI Line4 Interrupt                                              */
//  DMA1_Stream0_IRQn           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
//  DMA1_Stream1_IRQn           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
//  DMA1_Stream2_IRQn           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
//  DMA1_Stream3_IRQn           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
//  DMA1_Stream4_IRQn           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
//  DMA1_Stream5_IRQn           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
//  DMA1_Stream6_IRQn           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
//  ADC_IRQn                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
//  CAN1_TX_IRQn                = 19,     /*!< CAN1 TX Interrupt                                                 */
//  CAN1_RX0_IRQn               = 20,     /*!< CAN1 RX0 Interrupt                                                */
//  CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                                */
//  CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                                */
#define  EXTI9_5_IRQn            (23)     /*!< External Line[9:5] Interrupts                                     */
//  TIM1_BRK_TIM9_IRQn          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
#define  TIM1_UP_TIM10_IRQn      (25)     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
//  TIM1_TRG_COM_TIM11_IRQn     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
//  TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
#define  TIM2_IRQn               (28)     /*!< TIM2 global Interrupt                                             */
#define  TIM3_IRQn               (29)     /*!< TIM3 global Interrupt                                             */
#define  TIM4_IRQn               (30)     /*!< TIM4 global Interrupt                                             */
//  I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
//  I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
//  I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
//  I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
//  SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
//  SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
//  USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
//  USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
//  USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                                           */
#define  EXTI15_10_IRQn          (40)     /*!< External Line[15:10] Interrupts                                   */
//  RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
//  OTG_FS_WKUP_IRQn            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
//  TIM8_BRK_TIM12_IRQn         = 43,     /*!< TIM8 Break Interrupt and TIM12 global interrupt                   */
//  TIM8_UP_TIM13_IRQn          = 44,     /*!< TIM8 Update Interrupt and TIM13 global interrupt                  */
//  TIM8_TRG_COM_TIM14_IRQn     = 45,     /*!< TIM8 Trigger and Commutation Interrupt and TIM14 global interrupt */
//  TIM8_CC_IRQn                = 46,     /*!< TIM8 Capture Compare global interrupt                             */
//  DMA1_Stream7_IRQn           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
//  FSMC_IRQn                   = 48,     /*!< FSMC global Interrupt                                             */
//  SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
//  TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                             */
//  SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
//  UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                                            */
//  UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                                            */
//  TIM6_DAC_IRQn               = 54,     /*!< TIM6 global and DAC1&2 underrun error  interrupts                 */
//  TIM7_IRQn                   = 55,     /*!< TIM7 global interrupt                                             */
//  DMA2_Stream0_IRQn           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
//  DMA2_Stream1_IRQn           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
//  DMA2_Stream2_IRQn           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
//  DMA2_Stream3_IRQn           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
//  DMA2_Stream4_IRQn           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
//  ETH_IRQn                    = 61,     /*!< Ethernet global Interrupt                                         */
//  ETH_WKUP_IRQn               = 62,     /*!< Ethernet Wakeup through EXTI line Interrupt                       */
//  CAN2_TX_IRQn                = 63,     /*!< CAN2 TX Interrupt                                                 */
//  CAN2_RX0_IRQn               = 64,     /*!< CAN2 RX0 Interrupt                                                */
//  CAN2_RX1_IRQn               = 65,     /*!< CAN2 RX1 Interrupt                                                */
//  CAN2_SCE_IRQn               = 66,     /*!< CAN2 SCE Interrupt                                                */
//  OTG_FS_IRQn                 = 67,     /*!< USB OTG FS global Interrupt                                       */
//  DMA2_Stream5_IRQn           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
//  DMA2_Stream6_IRQn           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
//  DMA2_Stream7_IRQn           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
//  USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
//  I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
//  I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
//  OTG_HS_EP1_OUT_IRQn         = 74,     /*!< USB OTG HS End Point 1 Out global interrupt                       */
//  OTG_HS_EP1_IN_IRQn          = 75,     /*!< USB OTG HS End Point 1 In global interrupt                        */
//  OTG_HS_WKUP_IRQn            = 76,     /*!< USB OTG HS Wakeup through EXTI interrupt                          */
//  OTG_HS_IRQn                 = 77,     /*!< USB OTG HS global interrupt                                       */
//  DCMI_IRQn                   = 78,     /*!< DCMI global interrupt                                             */
//  RNG_IRQn                    = 80,     /*!< RNG global Interrupt                                              */
//  FPU_IRQn                    = 81      /*!< FPU global interrupt                                               */
//} IRQn_Type;
//
//
//typedef struct
//{
//   uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
//        uint32_t RESERVED0[24U];
//   uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
//        uint32_t RSERVED1[24U];
//   uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
//        uint32_t RESERVED2[24U];
//   uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
//        uint32_t RESERVED3[24U];
//   uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
//        uint32_t RESERVED4[56U];
//   uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
//        uint32_t RESERVED5[644U];
//   uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
//}  NVIC_Type;
//
//
//#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
//
//
//#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct */
//#define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */
//
//
//#define assert_param(expr) ((void)0U)
//#define IS_NVIC_DEVICE_IRQ(IRQ)       ((IRQ) >= (IRQn_Type)0x00U)
//
//inline void NVIC_EnableIRQ(IRQn_Type IRQn)
//{
//  if ((int32_t)(IRQn) >= 0)
//  {
//    NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
//  }
//}


/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

#ifndef ROTARY_ENCODER

	#define ROTARY_ENCODE_CLK_B  ((GPIOB_IDR & GPIOB7))
	#define ROTARY_ENCODE_DIN_A  ((GPIOB_IDR & GPIOB8))
	#define ROTARY_SWITCH        ((GPIOB_IDR & GPIOB6))

	#define ROTARY_ENCODE_CLK_B1 ((GPIOE_IDR & GPIOE0))
	#define ROTARY_ENCODE_DIN_A1 ((GPIOE_IDR & GPIOE1))
	#define ROTARY_SWITCH_1		 ((GPIOB_IDR & GPIOB9))
#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

#ifndef EXTRNAL_INTERRUPT

	#define RCC_MEM_ADDR			(0x40023800)

	#define RCC_APB2ENR_OFFSET 		(0x44)
	#define RCC_AHB1ENR_OFFSET      (0x30)

	#define RCC_GPIOA_EN			(1 << 0)         //clock pp8
	#define RCC_GPIOB_EN			(1 << 1)
	#define RCC_GPIOC_EN            (1 << 2)
	#define RCC_GPIOD_EN			(1 << 3)         //clock pp8
	#define RCC_GPIOE_EN			(1 << 4)
	#define RCC_GPIOF_EN            (1 << 5)
	#define RCC_GPIOG_EN			(1 << 6)         //clock pp8
	#define RCC_GPIOH_EN			(1 << 7)
	#define RCC_GPIOI_EN            (1 << 8)

	#define SYSCFGEN_EN	            (1 << 14)

	#define EXTI_GPIO_MEM_ADDR 		(0x40020000)
	#define EXTI_GPIOB_MEM_ADDR 	(0x40020400)
	#define EXTI_GPIOC_MEM_ADDR		(0x40020800)
	#define EXTI_GPIOD_MEM_ADDR     (0x40020C00)
	#define EXTI_GPIOE_MEM_ADDR     (0x40021000)

	#define EX_GPIOx_MODER_OFFSET   (0x00)
	#define EX_GPIOx_PUPDR_OFFSET   (0X0C)

	#define GPIOA_PIN_1   		    (3 << 2)
	//#define GPIOA_PUPDR				(1 << 2)


	#define RCC_GPIOx_ENABLE       *(volatile uint32_t*)(RCC_MEM_ADDR + RCC_AHB1ENR_OFFSET)
	#define EX_GPIOx_MODER     	   *(volatile uint32_t*)(EXTI_GPIO_MEM_ADDR + EX_GPIOx_MODER_OFFSET)
	#define EX_GPIOx_PUPDR	 	   *(volatile uint32_t*)(EXTI_GPIO_MEM_ADDR + EX_GPIOx_PUPDR_OFFSET)
	#define EXTI_RCC_APB2ENR       *(volatile uint32_t*)(RCC_MEM_ADDR+ RCC_APB2ENR_OFFSET)

	#define RCC_GPIOx_ENABLE       *(volatile uint32_t*)(RCC_MEM_ADDR + RCC_AHB1ENR_OFFSET)
	#define EX_GPIOB_MODER     	   *(volatile uint32_t*)(EXTI_GPIOD_MEM_ADDR + EX_GPIOx_MODER_OFFSET)
	#define EX_GPIOB_PUPDR	 	   *(volatile uint32_t*)(EXTI_GPIOD_MEM_ADDR + EX_GPIOx_PUPDR_OFFSET)
	#define EXTI_RCC_APB2ENR       *(volatile uint32_t*)(RCC_MEM_ADDR+ RCC_APB2ENR_OFFSET)

	#define RCC_GPIOC_ENABLE       *(volatile uint32_t*)(RCC_MEM_ADDR + RCC_AHB1ENR_OFFSET)
	#define EX_GPIOC_MODER     	   *(volatile uint32_t*)(EXTI_GPIOC_MEM_ADDR + EX_GPIOx_MODER_OFFSET)
	#define EX_GPIOC_PUPDR	 	   *(volatile uint32_t*)(EXTI_GPIOC_MEM_ADDR + EX_GPIOx_PUPDR_OFFSET)
	#define EXTI_RCC_APB2ENR       *(volatile uint32_t*)(RCC_MEM_ADDR+ RCC_APB2ENR_OFFSET)

	#define RCC_GPIOx_ENABLE       *(volatile uint32_t*)(RCC_MEM_ADDR + RCC_AHB1ENR_OFFSET)
	#define EX_GPIOD_MODER     	   *(volatile uint32_t*)(EXTI_GPIOD_MEM_ADDR + EX_GPIOx_MODER_OFFSET)
	#define EX_GPIOD_PUPDR	 	   *(volatile uint32_t*)(EXTI_GPIOD_MEM_ADDR + EX_GPIOx_PUPDR_OFFSET)
	#define EXTI_RCC_APB2ENR       *(volatile uint32_t*)(RCC_MEM_ADDR+ RCC_APB2ENR_OFFSET)

	#define RCC_GPIOx_ENABLE       *(volatile uint32_t*)(RCC_MEM_ADDR + RCC_AHB1ENR_OFFSET)
	#define EX_GPIOE_MODER     	   *(volatile uint32_t*)(EXTI_GPIOE_MEM_ADDR + EX_GPIOx_MODER_OFFSET)
	#define EX_GPIOE_PUPDR	 	   *(volatile uint32_t*)(EXTI_GPIOE_MEM_ADDR + EX_GPIOx_PUPDR_OFFSET)
	#define EXTI_RCC_APB2ENR       *(volatile uint32_t*)(RCC_MEM_ADDR+ RCC_APB2ENR_OFFSET)

	/*System SYSCFG register maps for*/

	#define SYSCFG_MEM_ADDR			(0x40013800)

	#define SYSCFG_EXTICR1_OFFSET   (0x08)
	#define SYSCFG_EXTICR2_OFFSET	(0x0C)
	#define SYSCFG_EXTICR3_OFFSET	(0x10)
	#define SYSCFG_EXTICR4_OFFSET 	(0x14)


	#define SYSCFG_EXTICR1		   *(volatile uint32_t*)(SYSCFG_MEM_ADDR + SYSCFG_EXTICR1_OFFSET)
	#define SYSCFG_EXTICR2		   *(volatile uint32_t*)(SYSCFG_MEM_ADDR + SYSCFG_EXTICR2_OFFSET)
	#define SYSCFG_EXTICR3		   *(volatile uint32_t*)(SYSCFG_MEM_ADDR + SYSCFG_EXTICR3_OFFSET)
	#define SYSCFG_EXTICR4		   *(volatile uint32_t*)(SYSCFG_MEM_ADDR + SYSCFG_EXTICR4_OFFSET)

	#define SYSCFG_EXTI1_EN     	(1 << 4);
	#define EXTI_ENABLE             (0xF << 4)
	#define EXTI3_ENABLE            (0x1 << 12)
	#define EXTI8_ENABLE 			(0xF << 0)
	#define EXTI9_ENABLE			(0x2 << 4)
	#define EXTI12_ENABLE           (0xF << 0)
	#define EXTI15_ENABLE           (0x3 << 12)
	//#define EXTI15_ENABLE           (0x3 << 12)


	#define EXTI_MEM_ADDR     		(0x40013C00)
	#define EXTI_IMR_OFFSET   		(0x00)
	#define EXTI_EMR_OFFSET   		(0x04)
	#define EXTI_RTSR_OFFSET  		(0x08)
	#define EXTI_FTSR_OFFSET  		(0x0C)
	#define EXTI_SWIER_OFFSET     	(0x10)
	#define EXTI_PR_OFFSET          (0x14)


	#define  EXTI_IMR     		   *(volatile uint32_t*)(EXTI_MEM_ADDR + EXTI_IMR_OFFSET)
	#define  EXTI_EMR      		   *(volatile uint32_t*)(EXTI_MEM_ADDR + EXTI_EMR_OFFSET)
	#define  EXTI_RTSR     		   *(volatile uint32_t*)(EXTI_MEM_ADDR + EXTI_RTSR_OFFSET)
	#define  EXTI_FTSR             *(volatile uint32_t*)(EXTI_MEM_ADDR + EXTI_FTSR_OFFSET)
	#define  EXTI_SWIER            *(volatile uint32_t*)(EXTI_MEM_ADDR + EXTI_SWIER_OFFSET)
	#define  EXTI_PR               *(volatile uint32_t*)(EXTI_MEM_ADDR + EXTI_PR_OFFSET)


//Interrupt mask register (EXTI_IMR) && //Event mask register (EXTI_EMR)

	#define MR0                 	(1 << 0)
	#define MR1						(1 << 1)
	#define MR2						(1 << 2)
	#define MR3						(1 << 3)
	#define MR4						(1 << 4)
	#define MR5  					(1 << 5)
	#define MR6						(1 << 6)
	#define MR7						(1 << 7)
	#define MR8						(1 << 8)
	#define MR9						(1 << 9)
	#define MR10					(1 << 10)
	#define MR11					(1 << 11)
	#define MR12					(1 << 12)
	#define MR13					(1 << 13)
	#define MR14 					(1 << 14)
	#define MR15					(1 << 15)
	#define MR16					(1 << 16)
	#define MR17					(1 << 17)
	#define MR18					(1 << 18)
	#define MR19					(1 << 19)
	#define MR20					(1 << 20)
	#define MR21					(1 << 21)
	#define MR22					(1 << 22)

/*
 * Bits 22:0 MRx: Event mask on line x
0: Event request from line x is masked
1: Event request from line x is not masked*/

//Rising trigger selection register (EXTI_RTSR)
//Falling trigger selection register (EXTI_FTSR)
	#define TR0                 (1 << 0)
	#define TR1					(1 << 1)
	#define TR2					(1 << 2)
	#define TR3					(1 << 3)
	#define TR4					(1 << 4)
	#define TR5  				(1 << 5)
	#define TR6					(1 << 6)
	#define TR7					(1 << 7)
	#define TR8					(1 << 8)
	#define TR9					(1 << 9)
	#define TR10				(1 << 10)
	#define TR11				(1 << 11)
	#define TR12				(1 << 12)
	#define TR13				(1 << 13)
	#define TR14 				(1 << 14)
	#define TR15				(1 << 15)
	#define TR16				(1 << 16)
	#define TR17				(1 << 17)
	#define TR18				(1 << 18)
	#define TR19				(1 << 19)
	#define TR20				(1 << 20)
	#define TR21				(1 << 21)
	#define TR22				(1 << 22)

/*
 * Bits 22:0 TRx: Falling  AND Rising trigger event configuration bit of line x
0: Falling trigger disabled (for Event and Interrupt) for input line
1: Falling trigger enabled (for Event and Interrupt) for input line.*/


//Software interrupt event register (EXTI_SWIER)
	#define SWIER0                  (1 << 0)
	#define SWIER1					(1 << 1)
	#define SWIER2					(1 << 2)
	#define SWIER3					(1 << 3)
	#define SWIER4					(1 << 4)
	#define SWIER5  				(1 << 5)
	#define SWIER6					(1 << 6)
	#define SWIER7					(1 << 7)
	#define SWIER8					(1 << 8)
	#define SWIER9					(1 << 9)
	#define SWIER10					(1 << 10)
	#define SWIER11					(1 << 11)
	#define SWIER12					(1 << 12)
	#define SWIER13					(1 << 13)
	#define SWIER14 				(1 << 14)
	#define SWIER15					(1 << 15)
	#define SWIER16					(1 << 16)
	#define SWIER17					(1 << 17)
	#define SWIER18					(1 << 18)
	#define SWIER19					(1 << 19)
	#define SWIER20					(1 << 20)
	#define SWIER21					(1 << 21)
	#define SWIER22					(1 << 22)

/*
 * Bits 22:0 SWIERx: Software Interrupt on line x
If interrupt are enabled on line x in the EXTI_IMR register, writing '1' to SWIERx bit when it is
set at '0' sets the corresponding pending bit in the EXTI_PR register, thus resulting in an
interrupt request generation.
This bit is cleared by clearing the corresponding bit in EXTI_PR (by writing a 1 to the bit).*/


//Pending register (EXTI_PR)
	#define PR0                 (1 << 0)
	#define PR1					(1 << 1)
	#define PR2					(1 << 2)
	#define PR3					(1 << 3)
	#define PR4					(1 << 4)
	#define PR5  				(1 << 5)
	#define PR6					(1 << 6)
	#define PR7					(1 << 7)
	#define PR8					(1 << 8)
	#define PR9					(1 << 9)
	#define PR10				(1 << 10)
	#define PR11				(1 << 11)
	#define PR12				(1 << 12)
	#define PR13				(1 << 13)
	#define PR14 				(1 << 14)
	#define PR15				(1 << 15)
	#define PR16				(1 << 16)
	#define PR17				(1 << 17)
	#define PR18				(1 << 18)
	#define PR19				(1 << 19)
	#define PR20				(1 << 20)
	#define PR21				(1 << 21)
	#define PR22				(1 << 22)
/*
 * PRx: Pending bit
0: No trigger request occurred
1: selected trigger request occurred
This bit is set when the selected edge event arrives on the external interrupt line.
This bit is cleared by programming it to ‘1’.*/



#endif

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

#ifndef I2C_REG_CONFIG

	/*STM32F407 user manual if you need to all data & configuration instruction flow, please download the user manual pdf file.
	Here is attched I2C1 Reference link
	https://sites.google.com/site/johnkneenmicrocontrollers/18b-i2c/i2c_stm32f407#linki2cpins
	Reference c code.
	https://docs.google.com/viewer?a=v&pid=sites&srcid=ZGVmYXVsdGRvbWFpbnxqb2hua25lZW5taWNyb2NvbnRyb2xsZXJzfGd4OjQzYjhkNWZkNDI3YjgxZDA
	*/


	#define I2Cx_CR1_OFFSET     (0x00)
	#define I2Cx_CR2_OFFSET     (0x04)
	#define I2Cx_DATA_OFFSET    (0x10)
	#define I2Cx_STATUS1_OFFSET (0x14)
	#define I2Cx_STATUS2_OFFSET (0x18)


	/*Clock Control register*/
	#define I2Cx_CCR_OFFSET     (0x1C)
	/**/
	#define I2Cx_TRISE_OFFSET   (0x20)


	#define RCC_I2C1EN      (SET_BIT << 21)
	#define RCC_I2C2EN      (SET_BIT << 22)
	#define RCC_I2C3EN		(SET_BIT << 23)


	#define _I2C1_CR1    	*(volatile uint32_t *)(I2C1_ADDR + I2Cx_CR1_OFFSET)
	#define _I2C1_CR2		*(volatile uint32_t *)(I2C1_ADDR + I2Cx_CR2_OFFSET)
	#define _I2C1_DATA      *(volatile uint32_t *)(I2C1_ADDR + I2Cx_DATA_OFFSET)
	#define _I2C1_SR1  	    *(volatile uint32_t *)(I2C1_ADDR + I2Cx_STATUS1_OFFSET)
	#define _I2C1_SR2       *(volatile uint32_t *)(I2C1_ADDR + I2Cx_STATUS2_OFFSET)
	#define _I2C1_CCR       *(volatile uint32_t *)(I2C1_ADDR + I2Cx_CCR_OFFSET)
	#define _I2C1_TRISE     *(volatile uint32_t *)(I2C1_ADDR + I2Cx_TRISE_OFFSET)


	#define _I2C2EN    		*(volatile uint32_t *)(I2C2_ADDR + RCC_I2C2_OFFSET)
	#define _I2C3EN    		*(volatile uint32_t *)(I2C3_ADDR + RCC_I2C3_OFFSET)

	#define _I2C1_START      (SET_BIT << 8)
	#define _I2C1_STOP   	 (SET_BIT << 9)

	#define _I2C1_SB     	 (0x01)
	#define _I2C1_BUSY    	 (SET_BIT << 1)

	#define _I2C1_TEX_EM     (SET_BIT << 7)  /*Transmission buffer is empty*/
 	#define _I2C1_RTX_EM     (SET_BIT << 6)	 /*Receiving buffer is empty*/

	#define _I2C1_ACK_EN     (SET_BIT << 10)

	#define _I2C1_ADDR_EN    (SET_BIT << 3)

	#define _FREQ_CONFIG     (0x0008) /*Set frequency value 8MHZ*///Min_FREQ 2MHZ. MAX_FREQ 50MHZ

	/*For instance: in Sm mode, to generate a 100 kHz SCL frequency:
	If FREQ = 8MHZ, T PCLK1 = 125 ns so CCR must be programmed with 0x28
	(0x28 <=> 40d x 125 ns = 5000 ns.) */
	#define _I2C1_CCR_SM      (0x28)
	/*For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
	If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and T PCLK1 = 125 ns
	therefore the TRISE[5:0] bits must be programmed with 09h.
	(1000 ns / 125 ns = 8 + 1)*/
	#define _I2C1_TRISE_FREQ  (0x09)
	#define _I2C1_PER_EN      (SET_BIT << 0)



#endif


/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */


#ifndef EXTERNAL_PCA9685

	#ifndef I2C_BUS_COMMAND_MODE

		#define DEFAULT_I2C_ADDR          (0xE0)
		#define I2C_BUS_READ_MODE 		  (0xE1)
		#define CONTROL_REG 			  (0x00)
		#define MODE1_REG                 (0X21) // AI = 1 and ALLCALL = 1;
		#define MODE2_REG                 (0X01)
		#define LED_ON_LOW 				  (0X06)
		#define PRESCALE 				  (0xFE)



		#define SLEEP_BIT    			  (0x10)
		#define EXTCLK_BIT      		  (0x40)
		#define RESTART_BIT     		  (0x80)

	#endif

	#ifndef BIT_SHIF_MODE

		#define LowByte(w) 			((uint8_t) ((w) & 0xff))
		#define HighByte(w) 		((uint8_t) ((w) >> 8))

	#endif

	#ifndef LED_STATE_MODE
	  #define GPIO_ON  4096 //each Led_pin contains 12bit values int (4096);
	  #define GPIO_OFF 0
	#endif

	#ifndef EXTERNAL_GPIO_PIN
	  #define EX_GPIO0_PIN  		(0)
	  #define EX_GPIO1_PIN  		(1)
	  #define EX_GPIO2_PIN  		(2)
	  #define EX_GPIO3_PIN  		(3)
	  #define EX_GPIO4_PIN  		(4)
	  #define EX_GPIO5_PIN  		(5)
	  #define EX_GPIO6_PIN  		(6)
	  #define EX_GPIO7_PIN  		(7)
	  #define EX_GPIO8_PIN  		(8)
	  #define EX_GPIO9_PIN  		(9)
	  #define EX_GPIO10_PIN 		(10)
	  #define EX_GPIO11_PIN 		(11)
	  #define EX_GPIO12_PIN 		(12)
	  #define EX_GPIO13_PIN 		(13)
	  #define EX_GPIO14_PIN 		(14)
	  #define EX_GPIO15_PIN 		(15)

	#endif

#endif


/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */




#ifndef PCF8574

	#define I2C2_SCK    (GPIOB14)
	#define I2C2_SDA 	(GPIOB13)

	#define DATA_DIRECTION_OUTPUT() (I2C2_SCK | I2C2_SDA)
	#define DATA_DIRECTION_INPUT() (I2C2_SDA)


	#define SERIAL_CLOCK_HIGH() (GPIOB_ODR |= I2C2_SCK)
	#define SERIAL_CLOCK_LOW() (GPIOB_ODR &= ~ I2C2_SCK)

	#define SERIAL_DATA_HIGH() (GPIOB_ODR |= I2C2_SDA)
	#define SERIAL_DATA_LOW()  (GPIOB_ODR &= ~ I2C2_SDA)

	#define SERIAL_READ_DATA() ((GPIOB_IDR & GPIOB14))

	/*
	 * Lcd command mode
	 */
	#define LCD_4BITMODE 				(0X00)
	#define LCD_FUNCTIONSET 			(0x28)
	#define LCD_DISPLAYON 				(0x04)
	#define LCD_CURSOROFF 				(0x00)
	#define LCD_BLINKOFF 				(0x00)
	#define LCD_DISPLAYCONTROL 			(0x08)
	#define LCD_CLEARDISPLAY 			(0x01)
	#define LCD_ENTRYLEFT 				(0x02)
	#define LCD_ENTRYSHIFTDECREMENT 	(0x00)
	#define LCD_ENTRYMODESET 			(0x04)
	#define LCD_RETURNHOME 				(0x02)

	#define LCD_1LINE 					(0x00)
	#define LCD_2LINE 					(0x08)
	#define LCD_5x10DOTS 				(0x04)
	#define LCD_5x8DOTS 				(0x00)

	#define LCD_BACKLIGHT 				(0x08)



	/*
	 * Data read and write operation bit cobfiguration.
	 */
	 #define ENABLE 				   (0B00000100)
	 #define READ_WRITE 			   (0B00000010)
	 #define REGISTER_SELECT 		   (0B00000001)


	uint8_t _WriteModeAddr;
	uint8_t _LcdCols;
	uint8_t _Lcd_Rows;
	uint8_t Display_Function;
	uint8_t BackLightVal;
	uint8_t _charsize;

#endif

/***************************************************************************************************************************
**************************************************************************************************************************
***************************************************************************************************************************
******************************************************END*****************************************************************
*/

#ifndef PCF8575

	#define I2C1_SCK    (GPIOB12)
	#define I2C1_SDA 	(GPIOB11)

	#define PCF8575_DATA_DIRECTION_OUTPUT() (I2C1_SCK | I2C1_SDA)
	#define PCF8575_DATA_DIRECTION_INPUT()  (I2C1_SDA)


	#define PCF8575_SERIAL_CLOCK_HIGH() (GPIOB_ODR |= I2C1_SCK)
	#define PCF8575_SERIAL_CLOCK_LOW()  (GPIOB_ODR &= ~ I2C1_SCK)

	#define PCF8575_SERIAL_DATA_HIGH()  (GPIOB_ODR |= I2C1_SDA)
	#define PCF8575_SERIAL_DATA_LOW()   (GPIOB_ODR &= ~ I2C1_SDA)

	#define PCF8575_SERIAL_READ_DATA()  ((GPIOB_IDR & GPIOB12))


#endif

/***************************************************************************************************************************
**************************************************************************************************************************
***************************************************************************************************************************
******************************************************END*****************************************************************
*/

#ifndef PCA9685_EX_PWM

	#define I2C3_SCK    (GPIOB10)
	#define I2C3_SDA 	(GPIOE15)

	#define PCA9685_DATA_DIRECTION_OUTPUT() (I2C3_SCK | I2C3_SDA)
	#define PCA9685_DATA_DIRECTION_INPUT() (I2C3_SDA)

	#define PCA9685_SERIAL_CLOCK_HIGH() (GPIOB_ODR |= (I2C3_SCK))
	#define PCA9685_SERIAL_CLOCK_LOW()  (GPIOB_ODR &= ~ (I2C3_SCK))

	#define PCA9685_SERIAL_DATA_HIGH() (GPIOE_ODR |= (I2C3_SDA))
	#define PCA9685_SERIAL_DATA_LOW()  (GPIOE_ODR &= ~ (I2C3_SDA))

	#define PCA9685_SERIAL_READ_DATA() ((GPIOE_IDR & GPIOE15))


#endif


/***************************************************************************************************************************
* *************************************************************************************************************************
* * *************************************************************************************************************************
* *****************************************************END*****************************************************************
*/

#ifndef SPI_GPIO_MODE_CONFIG
//
	#define SPI_CS_PIN        		(GPIOA10)
	#define SPI_SCL_PIN		  		(GPIOA11)
	#define SPI_SDA_PIN       		(GPIOA9)

	/*CS select as use for data transmission*/
	#define SPI_CHIP_SELECT_HI     (GPIOA_ODR |= (SPI_CS_PIN))
	#define SPI_CHIP_SELECT_LO	   (GPIOA_ODR &= ~(SPI_CS_PIN))
	/*SCL select as use for clock pulse generation
	4.5MHZ data transmission*/
	#define SPI_CLOCK_HI		   (GPIOA_ODR |= (SPI_SCL_PIN))
	#define SPI_CLOCK_LO		   (GPIOA_ODR &= ~ (SPI_SCL_PIN))
	/*SDA select as use for Read Data */
	#define SPI_SDA_IN             ((GPIOA_IDR & SPI_SDA_PIN))
//	/*********************************************************************************
//	 * *******************************************************************************
//	 * *******************************************************************************
//	 */
//
	/*Chapati maker top plate heating temperature*/
	#define CH_SPI_CS_PIN        		(GPIOC7)
	#define CH_SPI_SCL_PIN		  		(GPIOC8)
	#define CH_SPI_SDA_PIN       		(GPIOC6)

	/*CS select as use for data transmission*/
	#define CH_SPI_CHIP_SELECT_HI      (GPIOC_ODR |= (CH_SPI_CS_PIN))
	#define CH_SPI_CHIP_SELECT_LO	   (GPIOC_ODR &= ~(CH_SPI_CS_PIN))
	/*SCL select as use for clock pulse generation
	4.5MHZ data transmission*/
	#define CH_SPI_CLOCK_HI		  	   (GPIOC_ODR |= (CH_SPI_SCL_PIN))
	#define CH_SPI_CLOCK_LO		       (GPIOC_ODR &= ~ (CH_SPI_SCL_PIN))
	/*SDA select as use for Read Data */
	#define CH_SPI_SDA_IN              ((GPIOC_IDR & CH_SPI_SDA_PIN))

/*Chapati maker Temperature sensor*/


#endif




/****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************DS18B20_IN/OUT*************************************************/
/*
 * DATA DIRECTION PIN IT IS USED GPIO INPUT OR OUTPUT CONFIGURAION
 */

/*
 * port configuration LOW or HIGH configuration
 */
/*#define DS18B20_LOW() (GPIOB_ODR &=~ (DS18B20_SCK_SDA))
#define DS18B20_HIGH() (GPIOB_ODR |= (DS18B20_SCK_SDA))
*/

#define DS18B20_INPUT() ((GPIOB_IDR & DS18B20_SCK_SDA))

/*
 * Register command
 */
#define SKIP_ROM 0XCC

#define THERM_CMD_CONVERTTEMP 0x44
#define THERM_CMD_RSCRATCHPAD 0xBE
#define THERM_CMD_SKIPROM 0xCC


/****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************GPIOA_IN/OUT*************************************************/

#define GPIOA_OUTPUT_DIR(GPIOA_MODEx ,GPIOAx_PULL, GPIOAx){ \
	RCC_AHB1ENR_GPIO |= RCC_IOPAEN; \
	GPIOA_MODER |= GPIOA_MODEx; \
	GPIOA_OTYPER &= ~(GPIOAx_TYPE * GPIOAx); \
	GPIOA_OSPEEDR  &= ~ (GPIOAx_SPEED * GPIOAx_PULL);  \
	GPIOA_PUPDR |= GPIOAx_PULL; \
	GPIOA_ODR |= GPIOAx; \
}

#define GPIOA_INPUT_DIR(GPIOAx_MODE ,GPIOx){\
	GPIOA_MODER &= ~ (GPIOAx_MODE);\
	GPIOA_IDR &= ~GPIOx;\
}


/****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************GPIOB_IN/OUT*************************************************/

#define GPIOB_OUTPUT_DIR(GPIOB_MODEx ,GPIOBx_PULL, GPIOBx){ \
	RCC_AHB1ENR_GPIO |= RCC_IOPBEN; \
	GPIOB_MODER |= GPIOB_MODEx; \
	GPIOB_OTYPER &= ~(GPIOBx_TYPE * GPIOBx); \
	GPIOB_OSPEEDR  &= ~ (GPIOBx_SPEED * GPIOBx_PULL);  \
	GPIOB_PUPDR |= GPIOBx_PULL; \
	GPIOB_ODR |= GPIOBx; \
}

#define GPIOB_INPUT_DIR(GPIOBx_MODE ,GPIOx){\
	GPIOB_MODER &= ~ (GPIOBx_MODE);\
	GPIOB_IDR &= ~GPIOx;\
}

/****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************GPIOC_IN/OUT*************************************************/


#define GPIOC_OUTPUT_DIR(GPIOC_MODEx ,GPIOCx_PULL, GPIOCx){ \
	RCC_AHB1ENR_GPIO |= RCC_IOPCEN; \
	GPIOC_MODER |= GPIOC_MODEx; \
	GPIOC_OTYPER &= ~(GPIOCx_TYPE * GPIOCx); \
	GPIOC_OSPEEDR  &= ~ (GPIOCx_SPEED * GPIOCx_PULL);  \
	GPIOC_PUPDR |= GPIOCx_PULL; \
	GPIOC_ODR |= GPIOCx; \
}

#define GPIOC_INPUT_DIR(GPIOCx_MODE ,GPIOx){\
	GPIOC_MODER &= ~ (GPIOCx_MODE);\
	GPIOC_IDR &= ~GPIOx;\
}

/****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************GPIOD_IN/OUT*************************************************/

#define GPIOD_OUTPUT_DIR(GPIOD_MODEx ,GPIODx_PULL, GPIODx){ \
	RCC_AHB1ENR_GPIO |= RCC_IOPDEN; \
	GPIOD_MODER |= GPIOD_MODEx; \
	GPIOD_OTYPER &= ~(GPIODx_TYPE * GPIODx); \
	GPIOD_OSPEEDR  &= ~ (GPIODx_SPEED * GPIODx_PULL);  \
	GPIOD_PUPDR |= GPIODx_PULL; \
	GPIOD_ODR |= GPIODx; \
}

#define GPIOD_INPUT_DIR(GPIODx_MODE ,GPIOx){\
	GPIOD_MODER &= ~ (GPIODx_MODE);\
	GPIOD_IDR &= ~GPIOx;\
}


/****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************
*****************************************GPIOE_IN/OUT*************************************************/
#define GPIOE_OUTPUT_DIR(GPIOE_MODEx ,GPIOEx_PULL, GPIOEx){ \
	RCC_AHB1ENR_GPIO |= RCC_IOPEEN; \
	GPIOE_MODER |= GPIOE_MODEx; \
	GPIOE_OTYPER &= ~(GPIOEx_TYPE * GPIOEx); \
	GPIOE_OSPEEDR  &= ~ (GPIOEx_SPEED * GPIOEx_PULL);  \
	GPIOE_PUPDR |= GPIOEx_PULL; \
	GPIOE_ODR |= GPIOEx; \
}

#define GPIOE_INPUT_DIR(GPIOEx_MODE ,GPIOx){\
	GPIOE_MODER &= ~ (GPIOEx_MODE);\
	GPIOE_IDR &= ~GPIOx;\
}
/***************************************************************************************************************************
*************************************************************************************************************************
*************************************************************************************************************************
*****************************************************END*****************************************************************
*/

#ifndef AUTO_TRIAL_GLOBAL_VARIABLE
	unsigned int AUTO_TRIAL_FLAG_CNT_EN = CLEAR_BIT;
	unsigned int DOSA_SPREAD_SEQ_TEST = CLEAR_BIT;
	unsigned int TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
	unsigned int ELSE_AUTO_TRIAL_FLAG_CNT_EN = CLEAR_BIT;
	unsigned int REVERSE_SEC_CNT = CLEAR_BIT;

	unsigned int CHAPATI_AUTO_TRIAL_FLAG_CNT_EN = CLEAR_BIT;
#endif
/***************************************************************************************************************************
*************************************************************************************************************************
**************************************************************************************************************************************************************************************************************************************************
*****************************************************END*****************************************************************
*/
#ifndef AUTO_TRIAL_TIMER_GLOBLE_VARIABLE
	/*I have also calculated the timer value as TIMER_1*/
	#define WAIT_FOR_300SEC_TIMER_EN                    (8) //Orginal value 300;
	#define WAIT_FOR_150SEC_TIMER_EN 			        (2) //Orginal value 150;
	#define WAIT_FOR_75SEC_TIMER_EN						(7)  //Orginal value 75;
	#define WAIT_FOR_30SEC_TIMER_EN                     (3) //Orginal value 30;
	#define WAIT_FOR_100SEC_TIMER_EN					(10) //Orginal value 100;
	#define WAIT_FOR_60SEC_TIMER_EN					 	(60) //orginal value 60;
#endif
/***************************************************************************************************************************
*************************************************************************************************************************
*************************************************************************************************************************
*****************************************************END*****************************************************************
*/
#ifndef INPUT_CONFIG_AS_DOSA_MATIC

	#define DOSA_U_SLOT_SEN_SPREAD     			((GPIOD_IDR & GPIOx_PIN_6))
	#define DOSA_U_SLOT_SEN_MM      			((GPIOB_IDR & GPIOx_PIN_5))
	#define DOSA_U_SLOT_SEN_BATTER  			((GPIOD_IDR & GPIOx_PIN_7))
	#define CHAPATI_PRESS_HOME_SEN 				((GPIOB_IDR & GPIOx_PIN_3))

	//	/*DC-MOTOR HEALTH MANAGEMENT'S SENSOR*/
	#define DOSA_POWDER_DISP_SEN  				((GPIOB_IDR & GPIOx_PIN_6))
	#define DOSA_BATTER_MIX_SEN   				((GPIOB_IDR & GPIOx_PIN_5))

	#define DOSA_LINEAR_SPRD_SEN   				((GPIOD_IDR & GPIOx_PIN_3))
	#define DOSA_MAVU_SPRD_SEN   				((GPIOD_IDR & GPIOx_PIN_7))
	#define DOSA_CLEANING_SEN   				((GPIOD_IDR & GPIOx_PIN_6))

	//	/*DC-MOTOR HEALTH MANAGEMENT'S SENSOR*/
	#define D_WATER_FLOW_SEN    				((GPIOD_IDR & GPIOx_PIN_4))
	#define C_WATER_FLOW_SEN   				    ((GPIOC_IDR & GPIOx_PIN_12))

	/*FLOW SENSOR AS GPIO_CONFIG*/
	#define D_OIL_FLOW_SEN      				((GPIOD_IDR & GPIOx_PIN_1))
	#define C_OIL_FLOW_SEN						((GPIOD_IDR & GPIOx_PIN_0))

	/*INPUT SENSOR CONFIG INDICATION as WATER and OIL*/
	#define WATER_LEVEL_SEN     				((GPIOC_IDR & GPIOx_PIN_11))
	#define OIL_LEVEL_SEN    					((GPIOD_IDR & GPIOx_PIN_3))
	#define C_POWDER_LEVEL_SEN    				((GPIOD_IDR & GPIOx_PIN_2))
	#define D_POWDER_LEVEL_SEN                  ((GPIOC_IDR & GPIOx_PIN_10))

	/*Chapati Dought up and down position move the motor*/
	#define C_DOUGH_UP							((GPIOA_IDR & GPIOx_PIN_15))
	#define C_DOUGH_DOWN						((GPIOC_IDR & GPIOx_PIN_10))

	/*External interrupt setup*/
	#define External_step                       ((GPIOA_IDR & GPIOx_PIN_8))
//	#define External_Rpm_step 					((GPIOA_IDR & GPIOx_PIN_12))

	#define temp_test 							((GPIOC_IDR & GPIOx_PIN_7))

	#define ARM_MOVE_PULSE_CNT					((GPIOD_IDR & GPIOx_PIN_15))

	#define CHAPATI_ARM_HOME					((GPIOD_IDR & GPIOx_PIN_14))

	#define ARM_MOVE_FWD_HI	                	(GPIOD_ODR |= (GPIOx_PIN_13))
	#define ARM_MOVE_FWD_LO						(GPIOD_ODR &= ~(GPIOx_PIN_13))

	#define ARM_MOVE_REV_HI						(GPIOD_ODR  |= (GPIOx_PIN_12))
	#define ARM_MOVE_REV_LO						(GPIOD_ODR  &= ~(GPIOx_PIN_12))

	#define DOSA_OIL_SPRY_HI					((GPIOD_ODR |= GPIOx_PIN_10))
	#define DOSA_OIL_SPRY_LO					((GPIOD_ODR &= ~GPIOx_PIN_10))

	#define DOSA_WATER_SPRY_HI 					((GPIOD_ODR |= GPIOx_PIN_11))
	#define DOSA_WATER_SPRY_LO 					((GPIOD_ODR &= ~GPIOx_PIN_11))

	#define DOSA_U_SLOT_REV_SPREAD     			((GPIOD_IDR & GPIOx_PIN_9))

	#define CLEAN_HI							(GPIOD_ODR  |= (GPIOx_PIN_8))
	#define CLEAN_LO							(GPIOD_ODR  &= ~(GPIOx_PIN_8))

	#define EXTERNAL_ISR_DEMO                   ((GPIOE_IDR & GPIOx_PIN_13))

	#define PRESS_DOWN_POS_HI                   (GPIOD_ODR  |= (GPIOx_PIN_15))
	#define PRESS_DOWN_POS_LO					(GPIOD_ODR  &= ~(GPIOx_PIN_15))

#endif
/***************************************************************************************************************************
*************************************************************************************************************************
*************************************************************************************************************************
*****************************************************END*****************************************************************
*/

	#ifndef OUTPUT_CONFIG_AS_DOSA_MATIC

		#define DOSA_POWDER_DISP_RELAY_HI            ()
		#define DOSA_POWDER_DISP_RELAY_LO			 ()

		#define DOSA_OIL_AS_DC_MOTOR_HI				 ()
		#define DOSA_OIL_AS_DC_MOTOR_LO				 ()

		#define DOSA_WATER_AS_DC_MOTOR_HI			 ()
		#define DOSA_WATER_AS_DC_MOTOR_LO			 ()

		#define DOSA_BATTER_MIX_HI					 ()
		#define DOSA_BATTER_MIX_LO					 ()

		#define DOSA_BATTER_SPRD_HI					 ()
		#define DOSA_BATTER_SPRD_LO					 ()

		#define DOSA_HIGH_ADJ_HI					 ()
		#define DOSA_HIGH_ADJ_LO					 ()

		#define DOSA_MAVU_SPRD_HI					 ()
		#define DOSA_MAVU_SPRD_LO					 ()

		#define DOSA_CLEAN_HI						 ()
		#define DOSA_CLEAN_LO						 ()

		#define _2KVA_COIL_HI
		#define _2KVA_COIL_LO


	#endif

/***************************************************************************************************************************
* *************************************************************************************************************************
**************************************************************************************************************************
*****************************************************END*****************************************************************
*
*/

#ifndef AUTO_TRIAL_GLOBAL_VARIABLE
	unsigned int CHAPATI_SPREAD_SEQ_TEST = CLEAR_BIT;
	unsigned int TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
	volatile unsigned int Sec3 = CLEAR_BIT;
	unsigned int TEMP_READ_DA = CLEAR_BIT;
	unsigned int TEMP2 = CLEAR_BIT;
	unsigned int TIMER_FLAG = SET_BIT;
	unsigned int FINAL_VALUE = CLEAR_BIT;
	unsigned int ROTI_READ_TEMP_LO = CLEAR_BIT;
	unsigned int ROTI_TEMP_LO = CLEAR_BIT;



#endif
/***************************************************************************************************************************
*************************************************************************************************************************
*************************************************************************************************************************
******************************************************************************************************************************************************************************END*****************************************************************
*/
#ifndef CHAPATI_PIN_CONFIG

	#define CHAPATI_U_SLOT_SEN_UP				((GPIOD_IDR & GPIOx_PIN_3))
	#define CHAPATI_U_SLOT_SEN_DOWN				((GPIOD_IDR & GPIOx_PIN_2))
	#define CHAPATI_U_SLOT_UP_DOWN_SEN			((GPIOD_IDR & GPIOx_PIN_1))
	//POWDER_DISP
	#define POWDER_DISP_SEN						((GPIOD_IDR & GPIOx_PIN_0))

	#define CHAPATI_BALL_ROLL_SEN				((GPIOC_IDR & GPIOx_PIN_12))
	#define CHAPATI_BALL_HOME_SEN               ((GPIOC_IDR & GPIOx_PIN_11))
//	#define CHAPATI_PRESS_HOME_SEN				((GPIOB_IDR & GPIOx_PIN_3))
//	#define CHAPATI_PRESSING_SEN				((GPIOB_IDR & GPIOx_PIN_3))
	#define CHAPATI_W_FLOW_SEN					((GPIOA_IDR & GPIOx_PIN_12))
	#define CHAPATI_OIL_FLOW_SEN				((GPIOA_IDR & GPIOx_PIN_11))


#endif

#ifndef SERVO_MACRO
	#define SERVO_MOTOR_SPD0				   	(2304)
	#define SERVO_MOTOR_SPD1					(2560)
	#define SERVO_MOTOR_SPD2					(2816)
	#define SERVO_MOTOR_SPD3					(3072)

	#define SERVO_MOTOR_ON				        (3072)
	#define SERVO_MOTOR_OF    					(2048)
	#define SERVO_MOTOR_EN    					(7)

	/*Internal timer used as PWM*/
	#define SERVO_MOTOR_0_DEG       (3999)
	#define SERVO_MOTOR_60_DEG      (2399)
	#define SERVO_MOTOR_50_DEG      (1999)
	#define SERVO_MOTOR_30_DEG      (1199)
#endif
/***************************************************************************************************************************
*************************************************************************************************************************
*************************************************************************************************************************
******************************************************************************************************************************************************************************END*****************************************************************
*/
#ifndef CHAPATI_OUTPUT_CONFIG

#define CHAPATI_POWDER_DISP_DC_MOTOR_HI			()
#define CHAPATI_POWDER_DISP_DC_MOTOR_LO			()

#define CHAPATI_DOUGH_RAIL_DC_MOTOR_HI			()
#define CHAPATI_DOUGH_RAIL_DC_MOTOR_LO			()

#define CHAPATI_ARM_MOVING_DC_MOTOR_HI			()
#define CHAPATI_ARM_MOVING_DC_MOTOR_LO			()

#define CHAPATI_PRESSING_DC_MOTOR_HI			()
#define CHAPATI_PRESSING_DC_MOTOR_LO			()

#endif

/**********************************************AUTO_TRIALS_FLAG_CONFIG***************************************************
*************************************************************************************************************************
*************************************************************************************************************************
*****************************************************END******************************************************************/
#ifndef AUTO_TRIAL_FLAGS
	#define AUTO_TRIAL_FLAG_0   	(0)
	#define AUTO_TRIAL_FLAG_1   	(1)
	#define AUTO_TRIAL_FLAG_2   	(2)
	#define AUTO_TRIAL_FLAG_3   	(3)
	#define AUTO_TRIAL_FLAG_4   	(4)
	#define AUTO_TRIAL_FLAG_5   	(5)
	#define AUTO_TRIAL_FLAG_6   	(6)
	#define AUTO_TRIAL_FLAG_7   	(7)
	#define AUTO_TRIAL_FLAG_8   	(8)
	#define AUTO_TRIAL_FLAG_9   	(9)
	#define AUTO_TRIAL_FLAG_10   	(10)

	#define AUTO_TRIAL_FLAG_11   	(11)
	#define AUTO_TRIAL_FLAG_12   	(12)
	#define AUTO_TRIAL_FLAG_13   	(13)
	#define AUTO_TRIAL_FLAG_14  	(14)
	#define AUTO_TRIAL_FLAG_15   	(15)
	#define AUTO_TRIAL_FLAG_16   	(16)
	#define AUTO_TRIAL_FLAG_17   	(17)
	#define AUTO_TRIAL_FLAG_18   	(18)
	#define AUTO_TRIAL_FLAG_19   	(19)
	#define AUTO_TRIAL_FLAG_20   	(20)

	#define AUTO_TRIAL_FLAG_21   	(21)
	#define AUTO_TRIAL_FLAG_22   	(22)
	#define AUTO_TRIAL_FLAG_23   	(23)

	#define AUTO_TRIAL_FLAG_24   	(24)
	#define AUTO_TRIAL_FLAG_25   	(25)
	#define AUTO_TRIAL_FLAG_26   	(26)

	#define AUTO_TRIAL_FLAG_27   	(27)
	#define AUTO_TRIAL_FLAG_28   	(28)
	#define AUTO_TRIAL_FLAG_29   	(29)


	#define AUTO_TRIAL_FLAG_30   	(30)
	#define AUTO_TRIAL_FLAG_31   	(31)
	#define AUTO_TRIAL_FLAG_32   	(31)

#endif


#ifndef MOTOR_DRIVE_ENABLE

#endif

#ifndef EXTERNAL_ISR_PIN
	#define EX_DOSA_SPREAD_CNT          (GPIOA_IDR & GPIOx_PIN_8)
#endif

/*********************************************Global variable decleration********************************/
#ifndef GLOBAL_VARIABLE_USE_MAIN_FUN
	unsigned int SEL_DISH = CLEAR_BIT;
	volatile unsigned int SET_DISH_CNT = CLEAR_BIT;
	volatile unsigned int DISH_CNT = CLEAR_BIT;
	volatile unsigned int Count_Disp = CLEAR_BIT;
	volatile unsigned int ISR_FLAG_CNT = CLEAR_BIT;
#endif

#ifndef ISR_GLOBAL_VARIABLE

	volatile unsigned int CountValue = 0;
	volatile unsigned int TIM1_PRESS_CNT = 0;
	volatile unsigned int COOKING_TIME = CLEAR_BIT;
	volatile unsigned int COOKING_FLAG_EN = CLEAR_BIT;
	volatile unsigned int Sec4 = CLEAR_BIT;
#endif

#ifndef KALMAN_FILTER_GLOBAL_VARIABLE
		//Thermocoupler kalman filter
	float Raw_Variation;// = 0.050625; //Now The Data is Not Fixed
	float Raw_Convarience = 1e-2;
	float Current_Convarience = 0.0;
	float Gain = 0.0;
	float P = 1.0;
	float Previous_Temperature = 0.0;
	float Final_Temperature = 0.0;
	float _Current_Temperature;

#endif

/************************/

#ifndef MOTOR_EN_DIS
#define ROTI_WATER_ON    (EX_GPIO_OFF(EX_GPIO4_PIN))  //Oil inject;
#define ROTI_WATER_OFF   (EX_GPIO_ON(EX_GPIO4_PIN))  //Oil inject;

#define ROTI_OIL_ON      (PCF8575_LCD_OFF(0x00 ,0x40))
#define ROTI_OIL_OFF     (PCF8575_LCD_OFF(0x00 ,0x60))
#endif
/***************************************************************************************************************************
* *************************************************************************************************************************
* *************************************************************************************************************************
* *****************************************************END*****************************************************************
*/

uint8_t AT_Commands(const char *cmd ,const char *str1 ,const char  *str2 ,unsigned int Timeout)
{
	  char recBuff[100];
	  unsigned int BufferSize = 0;
	  unsigned int ReturnFlag = 0;

	  memset(recBuff, 0, sizeof(recBuff));

	  USART2_STRING(cmd);
	  BufferSize = 0;
	  memset(recBuff, 0, sizeof(recBuff));

	  do{
		  if(USART2_SR & (1 << 5)){
	      recBuff[BufferSize] = USART2_DR;
	      BufferSize++;
	     // TRANMITE_BYTE(count%10+0x30);

	      if(strstr(recBuff ,str1) != NULL){
	    	  /*This flags used for Strstr value findout*/
	    	  ReturnFlag = 1;
	      }

	      if(strstr(recBuff ,str2) != NULL){
	    	  ReturnFlag = 2;
	      }
	    }
	  }while(Delay_us(Timeout));
	  recBuff[100] = '\0';
	  return ReturnFlag;
	}

/***************************************************************************************************************************
* *************************************************************************************************************************
* *************************************************************************************************************************
* *****************************************************END*****************************************************************
*/
void ESP8266_AT_CMD_INIT(void){

	while(AT_Commands("AT\r\n" ,"OK" ,"ERROR" ,500) == 0);

	while(AT_Commands("AT+RST\r\n", "ready", "ERROR", 1000) == 0);

	while(AT_Commands("AT+RST\r\n", "WIFI CONNECTED", "WIFI GOT IP", 1000) == 0);

	while(AT_Commands("AT+CIPMUX=0\r\n", "OK", "ERROR", 1000) == 0);

	while(AT_Commands("AT+CWMODE=3\r\n", "OK", "ERROR", 1000) == 0);

	while(AT_Commands("AT+CWJAP?\r\n", "OK", "ERROR", 500) == 0);

	while(AT_Commands("AT+CWLAP=\"Antos pravin\"\r\n", " ", " ", 1000) == 0);

	while(AT_Commands("AT+CWJAP=\"Antos pravin\",\"Antos@4491\"\r\n" ,"CONNECT" ,"ERROR" ,500) == 0);

	while (AT_Commands(TCP_SERVER_CMD,"CONNECT", "OK", 1000) == 0);

	while (AT_Commands("AT+CIPSEND\r",">", ">", 1000) == 0);

	USART2_STRING(TCP_SERVER_QUERYS);
	USART2_SEND_TO_CHAR(0x1A); // enter command

}

/***************************************************************************************************************************
* *************************************************************************************************************************
* *************************************************************************************************************************
* *****************************************************END*****************************************************************/
void GPIOx_CLOCK_ENABLE(void){
	RCC_AHB1ENR_GPIO |= RCC_IOPAEN;
	RCC_AHB1ENR_GPIO |= RCC_IOPBEN;
	RCC_AHB1ENR_GPIO |= RCC_IOPCEN;
	RCC_AHB1ENR_GPIO |= RCC_IOPDEN;
	RCC_AHB1ENR_GPIO |= RCC_IOPEEN;
	RCC_AHB1ENR_GPIO |= RCC_IOPFEN;
}

/***************************************************************************************************************************
* *************************************************************************************************************************
* *************************************************************************************************************************
* *****************************************************END*****************************************************************

/********************************************SYSTEM_CLOCK_CONFIGURATION***************************/

void SYSTEM_CONFIG(void){

	RCC_CR_REG |= HSE_ON;
	while(!(RCC_CR_REG & HSE_RDY));

	RCC_CR_REG |= CSS_ON;
		   //while(!(RCC_CR_REG & RCC_HSEBYP));

		  // 2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	RCC_APB1ENR_PER |= RCC_APB1ENR_PWREN;
	PWR_CR |= PWR_CR_VOS;
	while(!(PWR_CSR & PWR_CSR_VOS_RDY));
		  /*01: HSE oscillator selected as system clock*/

	RCC_GFGR_REG |= (1 <<12) |(1 << 10); // set APB1 = 42 MHz
	RCC_GFGR_REG |= (1 << 15); // set APB2 = 84 MHz

	RCC_GFGR_REG |= RCC_GFCR_SW;
}


/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************TIMER1******************************************************************
 */

void TIMER1_CONFIG(void){
	/************** STEPS TO FOLLOW *****************
	 * Total time trick = 1ms;
	 * Please fllowing the formula used to timer overflow value upadte the preloaded or shadow values;
	 * Updatefrequency = TIM clk/((PSC+1)*(ARR+1));
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/
	// 1. Enable Timer clock
	RCC_APB2ENR_PER_BUS |= TIMER1_EN;
	TIM1_CR1_REG = 0;
	// 2. Set the prescalar and the ARR
	TIM1_PSC_REG = (8-1);//  System core clock/1000KHZ values - 1;
	TIM1_ARR_REG = (2000-1); //2kHZ value
	//TIM1_ARR_REG = (2000-1); //2kHZ value
	//3.Enable TIMER1_ISR
	TIM1_DIER_REG |= UIE;

	TIM1_SR_REG &= ~(1 << 0);
	// 3. Enable the Timer, and wait for the update Flag to set
	TIM1_CR1_REG |=  (1 << 0);

	//while (!(TIM1_SR_REG & (1<<0)));  //TIM1_SR_REG

}
uint32_t delay_Count = 0;


void Time_Delay_ms (uint16_t ms)
{
	uint32_t i;
	delay_Count++;
	TIM1_CNT_REG = 0;
	while(TIM1_CNT_REG < ms);
}



void Time_Delay_us(uint16_t us)
{
	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us,
		 the total waiting time will be the required us delay
	************************************************/
	TIM1_CNT_REG |= 0;
	while (TIM1_CNT_REG < us);
}

/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************TIMER2******************************************************************
 */
void TIMER2_CONFIG(void){
	/************** STEPS TO FOLLOW *****************
	 * Total time trick = 1ms;
	 * Please fllowing the formula used to timer overflow value upadte the preloaded or shadow values;
	 * Updatefrequency = TIM clk/((PSC+1)*(ARR+1));
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/
	// 1. Enable Timer clock
	RCC_APB1ENR_PER_BUS |= TIMER2_EN;
	TIM2_CR2_REG = 0;
	// 2. Set the prescalar and the ARR
	TIM2_PSC_REG = (8-1);//  System core clock/1000KHZ values - 1;
	TIM2_ARR_REG = (2000-1); //2kHZ value
	//3.Enable TIMER1_ISR
	TIM2_DIER_REG |= UIE;

	TIM2_SR_REG &= ~(1 << 0);
	// 3. Enable the Timer, and wait for the update Flag to set
	TIM2_CR1_REG |=  (1 << 0);

	//while (!(TIM1_SR_REG & (1<<0)));  //TIM1_SR_REG

}

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************TIMER3******************************************************************
 */
void TIMER3_CONFIG(void){
	/************** STEPS TO FOLLOW *****************
	 * Total time trick = 1ms;
	 * Please fllowing the formula used to timer overflow value upadte the preloaded or shadow values;
	 * Updatefrequency = TIM clk/((PSC+1)*(ARR+1));
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/
	// 1. Enable Timer clock
	RCC_APB1ENR_PER_BUS |= TIMER3_EN;
	TIM3_CR2_REG = 0;
	// 2. Set the prescalar and the ARR
	TIM3_PSC_REG = (8-1);//  System core clock/1000KHZ values - 1;
	TIM3_ARR_REG = (2000-1); //2kHZ value
	//3.Enable TIMER1_ISR
	TIM3_DIER_REG |= UIE;

	TIM3_SR_REG &= ~(1 << 0);
	// 3. Enable the Timer, and wait for the update Flag to set
	TIM3_CR1_REG |=  (1 << 0);


}


/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************TIMER3******************************************************************
 */
void TIMER4_CONFIG(void){
	/************** STEPS TO FOLLOW *****************
	 * Total time trick = 1ms;
	 * Please fllowing the formula used to timer overflow value upadte the preloaded or shadow values;
	 * Updatefrequency = TIM clk/((PSC+1)*(ARR+1));
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/
	// 1. Enable Timer clock
	RCC_APB1ENR_PER_BUS |= TIMER4_EN;
	TIM4_CR2_REG = CLEAR_BIT;
	// 2. Set the prescalar and the ARR
	TIM4_PSC_REG = (8-1);//  System core clock/1000KHZ values - 1;
	TIM4_ARR_REG = (0); //2kHZ value
	//3.Enable TIMER1_ISR
	TIM4_DIER_REG |= UIE;

	TIM4_SR_REG &= ~(1 << 0);
	// 3. Enable the Timer, and wait for the update Flag to set
	TIM4_CR1_REG |=  (1 << 0);


}


/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************TIMER6******************************************************************
 */


void TIMER6_CONFIG(void){

	/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/
	/**
	*Updatefrequency = TIM clk/((PSC+1)*(ARR+1))
	TIM_CLK = 42000KHZ
	PSC ->
	ARR ->
	*/
// 1. Enable Timer clock
	RCC_APB1ENR_PER |= TIMER6_EN;  // Enable the timer6 clock
	TIM6_CR1 = 0;                  //Timer-3 Control register cleared;
// 2. Set the prescalar and the ARR
	TIM6_PSC = (8-1);
	TIM6_ARR = (0xFFFF-1);  // MAX ARR value 19

// 3. Enable the Timer, and wait for the update Flag to set
	TIM6_CR1 |= (1<<0); // Enable the Counter
	while (!(TIM6_SR & (1<<0)));  // UIF: Update interrupt flag..  This bit is set by hardware when the registers are updated
}

void Delay_us (uint16_t us)
{
	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us,
		 the total waiting time will be the required us delay
	************************************************/
	// delay_Count++;
	TIM6_CNT = 0;
	while(TIM6_CNT < us);
}

void Delay_ms (uint16_t ms)
{
	uint32_t i;
	for(i =0; i< ms;i++){
		Delay_us(1000);
	}
}

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************TIMER7******************************************************************
 */
void TIMER7_CONFIG(void){

	/************** STEPS TO FOLLOW *****************
	1. Enable Timer clock
	2. Set the prescalar and the ARR
	3. Enable the Timer, and wait for the update Flag to set
	************************************************/
	/**
	*Updatefrequency = TIM clk/((PSC+1)*(ARR+1))
	TIM_CLK = 42000KHZ
	PSC ->
	ARR ->
	*/
// 1. Enable Timer clock
	RCC_APB1ENR_PER |= TIMER7_EN;  // Enable the timer6 clock
	TIM7_CR1 = 0;                  //Timer-3 Control register cleared;
// 2. Set the prescalar and the ARR
	TIM7_PSC = (8-1);
	TIM7_ARR = (8000-1);//(0xFFFF-1);  // MAX ARR value 19

// 3. Enable the Timer, and wait for the update Flag to set
	TIM7_CR1 |= (1<<0); // Enable the Counter
	while (!(TIM7_SR & (1<<0)));  // UIF: Update interrupt flag..  This bit is set by hardware when the registers are updated
}


void _Delay_us (uint16_t us)
{
	/************** STEPS TO FOLLOW *****************
	1. RESET the Counter
	2. Wait for the Counter to reach the entered value. As each count will take 1 us,
		 the total waiting time will be the required us delay
	************************************************/
	// delay_Count++;
	TIM7_CNT = 0;
	while(TIM7_CNT < us);
}

void TIMER_9_CONFIG(void){

	/************** STEPS TO FOLLOW *****************
		 * Total time trick = 1ms;
		 * Please fllowing the formula used to timer overflow value upadte the preloaded or shadow values;
		 * Updatefrequency = TIM clk/((PSC+1)*(ARR+1));
		1. Enable Timer clock
		2. Set the prescalar and the ARR
		3. Enable the Timer, and wait for the update Flag to set
		************************************************/
		/* 1. Enable GPIO clock enable
		 * 2. Enable Timer clock enable.
		 */
	RCC_APB2ENR_PER_BUS |= TIMER9_EN;
	RCC_GPIOx_ENABLE |= RCC_GPIOE_EN;

	GPIOE_MODER |= (SET_BIT << 11);   //10: Alternate function mode
	GPIOE_OTYPER &= ~(SET_BIT << 10); //0: Output push-pull (reset state)
	GPIOE_OSPEEDR |= (SET_BIT << 11); //10: High speed
	GPIOE_PUPDR |= (SET_BIT << 10); //01: Pull-up



	GPIOE_AFRL  |= (3 << 20);
	/**/

/*	 Set timer period when it have reset
    First you have to know max value for timer
    In our case it is 16bit = 65535
    To get your frequency for PWM, equation is simple

    PWM_frequency = timer_tick_frequency / (TIM_Period + 1)

    If you know your PWM frequency you want to have timer period set correct

    TIM_Period = timer_tick_frequency / PWM_frequency - 1

    In our case, for 10Khz PWM_frequency, set Period to

    TIM_Period = 84000000 / 10000 - 1 = 8399

    If you get TIM_Period larger than max timer value (in our case 65535),
    you have to choose larger prescaler and slow down timer tick frequency
*/
	TIM9_CR1 = CLEAR_BIT;
	TIM9_CNT = CLEAR_BIT;
	TIM9_PSC |= (8-1);
	TIM9_ARR |= (3999);
	TIM9_CR1 |= (SET_BIT << CLEAR_BIT);

	/*
	    To get proper duty cycle, you have simple equation

	    pulse_length = ((TIM_Period + 1) * DutyCycle) / 100 - 1

	    where DutyCycle is in percent, between 0 and 100%

	    25% duty cycle:     pulse_length = ((8399 + 1) * 25) / 100 - 1 = 2099
	    50% duty cycle:     pulse_length = ((8399 + 1) * 50) / 100 - 1 = 4199
	    75% duty cycle:     pulse_length = ((8399 + 1) * 75) / 100 - 1 = 6299
	    100% duty cycle:    pulse_length = ((8399 + 1) * 100) / 100 - 1 = 8399

	    Remember: if pulse_length is larger than TIM_Period, you will have output HIGH all the time
	*/


   /*Capture/Compare 1 output enable.*/
	TIM9_CCER |= (1 << CLEAR_BIT);
	TIM9_CCMR1 |= PWM_MODE_1;
	TIM9_CCMR1 |= (SET_BIT << 3);

	/**/
	TIM9_CCR1 = 0;


}
/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
void USART2_CONFIG(void){
	//reference Link:https://controllerstech.com/how-to-setup-uart-using-registers-in-stm32/

	/*Here we will enable the Clock for the GPIOA Port
    Then select the Pins PA2 and PA3 in the Alternate Function mode
    This is done by writing ‘1 0’ (2) in the 4th and 6th positions.
	 * */

	USART2_AHB1ENR |= USART_GPIOA_CLK_EN;
	USART2_APB1ENR |= USART_CLK_EN;

	GPIOA_MODER |= GPIOA_MODER_PA2;
	GPIOA_MODER |= GPIOA_MODER_PA3;

	GPIOA_OSPEEDR |= GPIOA_OSPEEDR_PA2_PA3;
/*
 *  Here First we have to look up for which alternate function is associated with the UART 2
    In this case it’s AF7
    Now in the Alternate Function Register, we will choose the AF7 (0111) for the Respective Pins
 *
 */
	GPIOA_AFRL |= GPIOA_AFRL_PA2;
	GPIOA_AFRL |= GPIOA_AFRL_PA3;

	USART2_CR1 = 0X00; // Clear ALL
	USART2_CR1 |= UE;  //UE = 1... Enable USART
	USART2_CR1 &=~ (M);

/*  Here the UART2 is connected to the APB1 Clock, and therefore the Fck = 8 MHz (APB1 Peripheral Frequency)
    Now If we want the Baud Rate of 115200, the MENSTISSA will come equal to 4, and the FRACTION = 5
    We will program these values in the 0th Position (for FRACTION) and in the 4th position (for MENTISSA) in the BRR Register.
 * */
	USART2_BRR |=  138;//((5 << 0)|(4<<4));

	USART2_CR1 |= RE; // RE=1.. Enable the Receiver
	USART2_CR1 |= TE; // TE=1.. Enable Transmitter


}

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************EXTERNAL_INTERRUPT_CONFIG***********************************************
 */
void USART2_SEND_TO_CHAR(uint8_t ch){

	USART2_DR = ch;
	while(!(USART2_SR & TC));

}


/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************EXTERNAL_INTERRUPT_CONFIG***********************************************
 */
void USART2_STRING(char Str[]){
	unsigned int Length = strlen(Str);
	for(unsigned int i = 0; i < Length; i++){
		USART2_SEND_TO_CHAR(Str[i]);
	}

}
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************EXTERNAL_INTERRUPT_CONFIG***********************************************
 */
//
//void EXTERNAL_INTERRUPT_CONFIG(void){
//	/*reference web link:
//	 * https://controllerstech.com/external-interrupt-using-registers/
//	 */
//	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
//	 *1.ENABLE_GPIO_CLOCK
//	 *2.SET THE REQUIRED PIN IN THE INPUT MODE
//	 *2.CONFIGURATION THE PULL_UP/PULL_DOWN ACCORDING TO YOUR REQUESTED;
//	 */
//	//SET to GPIO_PIN_CONFIGURATION;
//	RCC_GPIOx_ENABLE |= RCC_GPIOA_EN;
//	EX_GPIOx_MODER &= ~(GPIOA_PIN_1);
//	EX_GPIOx_PUPDR |= GPIOA_PUPDR;
//	/*	1. Enable the SYSCFG/AFIO bit in RCC register
//		2. Configure the EXTI configuration Register in the SYSCFG/AFIO
//		3. Disable the EXTI Mask using Interrupt Mask Register (IMR)
//		4. Configure the Rising Edge / Falling Edge Trigger
//		5. Set the Interrupt Priority
//		6. Enable the interrupt
//
//		********************************************************/
//	EXTI_RCC_APB2ENR |= SYSCFG_EXTI1_EN;
//	SYSCFG_EXTICR1 &= ~EXTI_ENABLE;
//	EXTI_IMR |= MR1;
//	EXTI_RTSR |= TR1;
//	EXTI_FTSR &= ~(TR1);
//	NVIC_SetPriority(EXTI1_IRQn ,1);
//	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
//}

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************EXTERNAL_INTERRUPT_CONFIG***********************************************
 */
//
//void EX_ISR8_CONFIG(void){
//	/*reference web link:
//	 * https://controllerstech.com/external-interrupt-using-registers/
//	 */
//	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
//	 *1.ENABLE_GPIO_CLOCK
//	 *2.SET THE REQUIRED PIN IN THE INPUT MODE
//	 *2.CONFIGURATION THE PULL_UP/PULL_DOWN ACCORDING TO YOUR REQUESTED;
//	 */
//	//SET to GPIO_PIN_CONFIGURATION;
//	RCC_GPIOx_ENABLE |= RCC_GPIOA_EN;
//	EX_GPIOx_MODER &= ~(1 << EX_GPIO8_PIN);
//	//EX_GPIOA_PUPDR |= GPIOA_PUPDR;
//	/*	1. Enable the SYSCFG/AFIO bit in RCC register
//		2. Configure the EXTI configuration Register in the SYSCFG/AFIO
//		3. Disable the EXTI Mask using Interrupt Mask Register (IMR)
//		4. Configure the Rising Edge / Falling Edge Trigger
//		5. Set the Interrupt Priority
//		6. Enable the interrupt
//
//		********************************************************/
//	EXTI_RCC_APB2ENR |= SYSCFGEN_EN;
//	SYSCFG_EXTICR3 &= ~EXTI8_ENABLE;
//	EXTI_IMR |= MR8;
//	EXTI_RTSR |= TR8;
//	EXTI_FTSR &= ~(TR8);
//	NVIC_SetPriority(EXTI9_5_IRQn ,1);
//	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
//
//}

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************EXTERNAL_INTERRUPT_CONFIG***********************************************
 */


void EX_ISR9_CONFIG(void){
//	/*reference web link:
//	 * https://controllerstech.com/external-interrupt-using-registers/
//	 */
//	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
//	 *1.ENABLE_GPIO_CLOCK
//	 *2.SET THE REQUIRED PIN IN THE INPUT MODE
//	 *2.CONFIGURATION THE PULL_UP/PULL_DOWN ACCORDING TO YOUR REQUESTED;
//	 */
//	//SET to GPIO_PIN_CONFIGURATION;
//	RCC_GPIOC_ENABLE |= RCC_GPIOC_EN;
//	EX_GPIOC_MODER &= ~((1 << 19) | (1 << 18));
//	EX_GPIOC_PUPDR |= (1 << 19);
//	/*	1. Enable the SYSCFG/AFIO bit in RCC register
//		2. Configure the EXTI configuration Register in the SYSCFG/AFIO
//		3. Disable the EXTI Mask using Interrupt Mask Register (IMR)
//		4. Configure the Rising Edge / Falling Edge Trigger
//		5. Set the Interrupt Priority
//		6. Enable the interrupt
//
//		********************************************************/
//	EXTI_RCC_APB2ENR |= SYSCFGEN_EN;
//	SYSCFG_EXTICR3 |= EXTI9_ENABLE;
//	EXTI_IMR |= MR9;
//	EXTI_RTSR |= TR9;
//	EXTI_FTSR &= ~(TR9);
//	EXTI_PR |= TR9;	//Clear the pending status;
//	NVIC_SetPriority(EXTI9_5_IRQn ,1);
//	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * **************************************************EXTERNAL_INTERRUPT_CONFIG***********************************************
 */


void EX_ISR12_CONFIG(void){
	/*reference web link:
	 * https://controllerstech.com/external-interrupt-using-registers/
	 */
	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
	 *1.ENABLE_GPIO_CLOCK
	 *2.SET THE REQUIRED PIN IN THE INPUT MODE
	 *2.CONFIGURATION THE PULL_UP/PULL_DOWN ACCORDING TO YOUR REQUESTED;
	 */
	//SET to GPIO_PIN_CONFIGURATION;
	RCC_GPIOx_ENABLE |= RCC_GPIOA_EN;
	EX_GPIOx_MODER &= ~(1 << EX_GPIO12_PIN);
	//EX_GPIOA_PUPDR |= GPIOA_PUPDR;
	/*	1. Enable the SYSCFG/AFIO bit in RCC register
		2. Configure the EXTI configuration Register in the SYSCFG/AFIO
		3. Disable the EXTI Mask using Interrupt Mask Register (IMR)
		4. Configure the Rising Edge / Falling Edge Trigger
		5. Set the Interrupt Priority
		6. Enable the interrupt

		********************************************************/
	EXTI_RCC_APB2ENR |= SYSCFGEN_EN;
	SYSCFG_EXTICR4 &= ~EXTI12_ENABLE;
	EXTI_PR |= TR12;	//Clear the pending status;
	EXTI_IMR |= MR12;		//Interrupt mask disable
	EXTI_RTSR |= TR12;	   //Enable rising edge
	EXTI_FTSR &= ~(TR12);  //Disable Falling edge
	EXTI_PR |= TR12;	//Clear the pending status;
	NVIC_SetPriority(EXTI15_10_IRQn ,1);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);



}
/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *************************************************************************************************************************
 * *****************************************************END*****************************************************************
 */
void EX_ISR15_CONFIG(void){

	/*reference web link:
	 * https://controllerstech.com/external-interrupt-using-registers/
	*/
	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
	*1.ENABLE_GPIO_CLOCK
	*2.SET THE REQUIRED PIN IN THE INPUT MODE
	*2.CONFIGURATION THE PULL_UP/PULL_DOWN ACCORDING TO YOUR REQUESTED;
	*/
	RCC_GPIOx_ENABLE |= RCC_GPIOD_EN;
	EX_GPIOD_MODER &= ~ GPIOD15_MODE;
	EX_GPIOD_PUPDR |= (1 << 31);

	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************

		1. Enable the SYSCFG/AFIO bit in RCC register
		2. Configure the EXTI configuration Register in the SYSCFG/AFIO
		3. Disable the EXTI Mask using Interrupt Mask Register (IMR)
		4. Configure the Rising Edge / Falling Edge Trigger
		5. Set the Interrupt Priority
		6. Enable the interrupt

	 ********************************************************/
	EXTI_RCC_APB2ENR |= SYSCFGEN_EN;
	SYSCFG_EXTICR4 |= EXTI15_ENABLE;
	EXTI_IMR |= MR15;
	EXTI_RTSR |= TR15;
	EXTI_FTSR &= ~(TR15);
	EXTI_PR |= TR15;	//Clear the pending status;

}
//
//void EX_ISR3_CONFIG(void){
////#define CHAPATI_PRESS_HOME_SEN 				((GPIOB_IDR & GPIOx_PIN_3))
//	/*reference web link:
//	* https://controllerstech.com/external-interrupt-using-registers/
//	*/
//	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
//	*1.ENABLE_GPIO_CLOCK
//	*2.SET THE REQUIRED PIN IN THE INPUT MODE
//	*2.CONFIGURATION THE PULL_UP/PULL_DOWN ACCORDING TO YOUR REQUESTED;
//	*/
//	RCC_GPIOx_ENABLE |= RCC_GPIOB_EN;
//	EX_GPIOB_MODER &= ~(1 << EX_GPIO3_PIN);
//
//	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
//
//		1. Enable the SYSCFG/AFIO bit in RCC register
//		2. Configure the EXTI configuration Register in the SYSCFG/AFIO
//		3. Disable the EXTI Mask using Interrupt Mask Register (IMR)
//		4. Configure the Rising Edge / Falling Edge Trigger
//		5. Set the Interrupt Priority
//		6. Enable the interrupt
//
//	********************************************************/
//	EXTI_RCC_APB2ENR |= SYSCFGEN_EN;
//	SYSCFG_EXTICR1 |= EXTI3_ENABLE;
//	EXTI_IMR |= MR3;
//	EXTI_RTSR |= TR3;
//	EXTI_FTSR &= ~(TR3);
//	NVIC_SetPriority(EXTI3_IRQn ,1);
//	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
//}
/**********************************PE14_ISR***************************/
void EX_ISRPE14_CONFIG(void){
	/*reference web link:
	 * https://controllerstech.com/external-interrupt-using-registers/
	 */
	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
	 *1.ENABLE_GPIO_CLOCK
	 *2.SET THE REQUIRED PIN IN THE INPUT MODE
	 *2.CONFIGURATION THE PULL_UP/PULL_DOWN ACCORDING TO YOUR REQUESTED;
	 */
	//SET to GPIO_PIN_CONFIGURATION;
	RCC_GPIOx_ENABLE |= RCC_GPIOE_EN;
	EX_GPIOx_MODER &= ~((1 << 29)|(1 << 28));
	EX_GPIOE_PUPDR |= (1 << 29);
	/*	1. Enable the SYSCFG/AFIO bit in RCC register
		2. Configure the EXTI configuration Register in the SYSCFG/AFIO
		3. Disable the EXTI Mask using Interrupt Mask Register (IMR)
		4. Configure the Rising Edge / Falling Edge Trigger
		5. Set the Interrupt Priority
		6. Enable the interrupt

		********************************************************/
	EXTI_RCC_APB2ENR |= SYSCFGEN_EN;
	SYSCFG_EXTICR4 |= (4 << 8);
	EXTI_IMR |= MR14;
	EXTI_RTSR |= TR14;
	EXTI_FTSR &= ~(TR14);
	EXTI_PR |= TR14;	//Clear the pending status;


/************************************************************************
 * External isr use for PE13-pin
 */
	/*reference web link:
	* https://controllerstech.com/external-interrupt-using-registers/
	*/
	/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
		 *1.ENABLE_GPIO_CLOCK
		 *2.SET THE REQUIRED PIN IN THE INPUT MODE
		 *2.CONFIGURATION THE PULL_UP/PULL_DOWN ACCORDING TO YOUR REQUESTED;
	*/
		//SET to GPIO_PIN_CONFIGURATION;
	RCC_GPIOx_ENABLE |= RCC_GPIOE_EN;
	EX_GPIOx_MODER &= ~((1 << 27)|(1 << 26));
	EX_GPIOE_PUPDR |= (1 << 27);
	/*	1. Enable the SYSCFG/AFIO bit in RCC register
		2. Configure the EXTI configuration Register in the SYSCFG/AFIO
		3. Disable the EXTI Mask using Interrupt Mask Register (IMR)
		4. Configure the Rising Edge / Falling Edge Trigger
		5. Set the Interrupt Priority
		6. Enable the interrupt

	********************************************************/
	EXTI_RCC_APB2ENR |= SYSCFGEN_EN;
	SYSCFG_EXTICR4 |= (4 << 4);
	EXTI_IMR |= MR13;
	EXTI_RTSR |= TR13;
	EXTI_FTSR &= ~(TR13);
	EXTI_PR |= TR13;	//Clear the pending status;


}

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************I2C1_INIT***********************************************************
 */

//
//void I2C1_INIT(void){
//	/*I2c_Clock frequency .stand mode and i2c_perpherial enable  */
//	/*
//	The following is the required sequence in master mode.
//	/**** STEPS FOLLOWED  ************
//1. Enable the I2C CLOCK and GPIO CLOCK
//2. Configure the I2C PINs for ALternate Functions
//	a) Select Alternate Function in MODER Register
//	b) Select Open Drain Output
//	c) Select High SPEED for the PINs
//	d) Select Pull-up for both the Pins
//	e) Configure the Alternate Function in AFR Register
//3. Reset the I2C
//4. Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
//5. Configure the clock control registers
//6. Configure the rise time register
//7. Program the I2C_CR1 register to enable the peripheral
//*/
//
//
//	RCC_AHB1ENR_GPIO |= (RCC_IOPBEN);
//	RCC_APB1ENR_PER |= (RCC_I2C1EN);
//	GPIOB_MODER |= (1 << 14)|(1 << 12);
//	GPIOB_OTYPER &= ~ (1 << 7) | (1 << 6);
//	GPIOB_OSPEEDR &= ~ (1 << 14)|(1 << 12);
//	GPIOB_PUPDR |= ((1 << 7)|(1 << 6));
//	GPIOB_AFRL |= GPIOB_AFRL_EN;
//
//	// //RESET  SWS REGISTER
//	// _I2C1_CR1 |= (1 << 15);
//	// _I2C1_CR1 &= ~(1 << 15);
//	// // GPIOB_MODER |= (0x0000A000);
//	// // GPIOB_OTYPER |= (0x00C0);
//
//
//	// _I2C1_CR2 |=_FREQ_CONFIG;
//	// _I2C1_CCR |= _I2C1_CCR_SM;
//	// _I2C1_TRISE |= _I2C1_TRISE_FREQ;
//	// _I2C1_CR1 |=_I2C1_PER_EN;
//
//	//_I2C1_CR1 &= ~(1 << 10);
//}
//
///***************************************************************************************************************************
// * *************************************************************************************************************************
// * *************************************************************************************************************************
// * *****************************************************END*****************************************************************
// */
//
//
//void I2C1_START(void){
//
//	// while((_I2C1_SR2 & _I2C1_BUSY)); //wait for Busy set;
//
//	_I2C1_CR1 |= (_I2C1_START);
//	while(!(_I2C1_SR1 & _I2C1_SB)); //wait for start bit as master;
//	// GPIOB_ODR |= GPIOB11;
//}
///***************************************************************************************************************************
// * *************************************************************************************************************************
// * *************************************************************************************************************************
// * *****************************************************END*****************************************************************
// */
//
//void I2C1_STOP(void){
//
//	_I2C1_CR1 |= (_I2C1_STOP);
//	while((_I2C1_SR2 & _I2C1_BUSY)); //wait for Busy set;
//}
///***************************************************************************************************************************
// * *************************************************************************************************************************
// * *************************************************************************************************************************
// * *****************************************************END*****************************************************************
// */
//
//
//void I2C1_ADDR_BYTE(unsigned char I2C_Addr ){
//
//	uint8_t RES;
//
//	_I2C1_DATA |= I2C_Addr; //Write to I2C Address register;
//	while(!(_I2C1_SR1 & _I2C1_ADDR_EN)); //wait until address send
//
//	RES = (_I2C1_SR2 | _I2C1_SR1);   //Dummu read to clear;
//
//	if(_I2C1_CR1 & (1 << 10)){
//		GPIOB_ODR |= GPIOB11;
//	}
//	else{
//		GPIOB_ODR |= GPIOB11;
//	}
//
//}
///***************************************************************************************************************************
// * *************************************************************************************************************************
// * *************************************************************************************************************************
// * *****************************************************END*****************************************************************
// */
//
//void I2C1_WRITE_BYTE(unsigned char W_Byte){
//
//
//	while(!(_I2C1_SR1 & _I2C1_TEX_EM));  //wait for txbuffer;
//	_I2C1_DATA |= W_Byte;
//}
///***************************************************************************************************************************
// * *************************************************************************************************************************
// * *************************************************************************************************************************
// * *****************************************************END*****************************************************************
// */
//
//void I2C1_ACK_BIT(void){
//
//	while(!(_I2C1_SR1 & (1 << 10)));
//	 GPIOB_ODR |= GPIOB11;
//
//}
///***************************************************************************************************************************
// * *************************************************************************************************************************
// * *************************************************************************************************************************
// * *****************************************************END*****************************************************************
// */
//
//void I2C1_WRITE_BYTE1(unsigned char W_Byte) {
//
//	_I2C1_DATA |= W_Byte;
// 	while(!(_I2C1_SR1 & _I2C1_TEX_EM));  //wait for txbuffer;
//
//
//	// GPIOB_ODR |= GPIOB11;
//  	//while(!(_I2C1_SR1 & (1 << 2)));
//}
///***************************************************************************************************************************
// * *************************************************************************************************************************
// * *************************************************************************************************************************
// * *****************************************************END*****************************************************************
// */
//
//unsigned char I2C1_DATA_READ(int I2C1_Ack_bit){
//
//	if(I2C1_Ack_bit){
//
//		_I2C1_CR1 |= _I2C1_ACK_EN;
//	}
//	else {
//		 /*Ack bit is disabled*/
//		_I2C1_CR1 &= ~(_I2C1_ACK_EN);
//	}
//	while(!(_I2C1_SR1 & _I2C1_RTX_EM));
//
//	return _I2C1_DATA;
//}
//
/********************************************EXTERNAL************************************************/

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void I2C3_INIT()
  {
  	GPIOB_OUTPUT_DIR(GPIOB10_MODE, GPIOB10_PULL ,GPIOB10);
  	GPIOE_OUTPUT_DIR(GPIOE15_MODE, GPIOE15_PULL ,GPIOE15);
  }

//Start cionditional sda and scl data transfers.
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void I2C3_START(void)
  {
	PCA9685_SERIAL_CLOCK_HIGH();
	PCA9685_SERIAL_DATA_HIGH();
    Delay_us(4.7);
    PCA9685_SERIAL_DATA_LOW();
    Delay_us(4);
    PCA9685_SERIAL_CLOCK_LOW();
  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void I2C3_STOP(void)
  {
	PCA9685_SERIAL_CLOCK_HIGH();
	PCA9685_SERIAL_DATA_LOW();
    Delay_us(4);
    PCA9685_SERIAL_DATA_HIGH();
    Delay_us(4.7);


  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void I2C3_RESTART(void){
  I2C3_START();        //I2c_bus communication start;
  PCA9685_ADDRESS_WRITE(RESTART_BIT);
  I2C3_STOP();          //I2c_bus_communication stop;
}
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void I2C3_ACK(void)
  {
	PCA9685_SERIAL_DATA_LOW();
    Delay_us(4);
    PCA9685_SERIAL_CLOCK_HIGH();
    Delay_us(4);
    PCA9685_SERIAL_CLOCK_LOW();
    Delay_us(4);

  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

 void I2C3_NACK(void)
  {
	 PCA9685_SERIAL_CLOCK_HIGH();
	 PCA9685_SERIAL_DATA_LOW();
	 Delay_us(4);
	 PCA9685_SERIAL_DATA_HIGH();
  }

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************PCA9685_INIT********************************************************
*/
void PCA9685_ADDRESS_WRITE(uint8_t Addr)
  {
    uint8_t temp ,i;
    for(i = 0; i<8; i++)
      {
        temp = ((Addr & 0x80)?1:0);

        if(temp){PCA9685_SERIAL_DATA_HIGH();}
        else {PCA9685_SERIAL_DATA_LOW();}

        Delay_us(4.7);
        PCA9685_SERIAL_CLOCK_HIGH();
        Delay_us(4.7);
        PCA9685_SERIAL_CLOCK_LOW();
        Delay_us(4.7);

        Addr <<= 1;
      }
     I2C3_ACK();
  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

uint8_t PCA9685_ADDRESS_READ(void)
  {
	PCA9685_DATA_DIRECTION_INPUT();
    uint8_t RECEIVING_DATA ,DATA_SIFTING;
    uint8_t i;

    for(i = 0; i < 8; i++)
      {
         RECEIVING_DATA |= PCA9685_SERIAL_READ_DATA();
         if(i < 7){
          DATA_SIFTING = RECEIVING_DATA >> 1;
         }
         PCA9685_SERIAL_CLOCK_LOW();
         Delay_us(4.7);
         PCA9685_SERIAL_CLOCK_HIGH();
         Delay_us(4);

      }
     I2C3_ACK();
     return DATA_SIFTING;
  }

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

/*
 * Sequence c methodes i have used. if you anydoubt,you see PDF.
 */
void PCA9685_INIT(void){
	  /*
	   * if you anydoubt refer the datasheet.
	   */
	I2C3_START();        //I2c_bus communication start;
	PCA9685_ADDRESS_WRITE(DEFAULT_I2C_ADDR); //specifying slave address in write mode
	PCA9685_ADDRESS_WRITE(CONTROL_REG); //control register set to address = 0x00;
	PCA9685_ADDRESS_WRITE(MODE1_REG); //Mode 1 configured  to with Autoincrement(AI = 1) and ALLCALL = 1
	I2C3_STOP();
//	GPIOB_ODR |= GPIOB11;

	//     //I2c_bus_communication stop;

}

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void WRITE_12BIT_ADDR(char GPIOx_PIN, uint16_t GPIOx_ON_MODE, uint16_t GPIOx_OFF_MODE){

    I2C3_START();         //I2c_bus communication start;
    PCA9685_ADDRESS_WRITE(DEFAULT_I2C_ADDR); //specifying slave address in write mode
    PCA9685_ADDRESS_WRITE(LED_ON_LOW+4*GPIOx_PIN); //Control register set to address Ledn_on_L
    PCA9685_ADDRESS_WRITE(LowByte(GPIOx_ON_MODE)); //8Lsb LED_ON_L count;
    PCA9685_ADDRESS_WRITE(HighByte(GPIOx_ON_MODE));//8Msb LED_ON_H count;
    PCA9685_ADDRESS_WRITE(LowByte(GPIOx_OFF_MODE)); ////8Lsb LED_OFF_count;
    PCA9685_ADDRESS_WRITE(HighByte(GPIOx_OFF_MODE));//8Lsb LED_OFF_count;
    I2C3_STOP();   //I2c_bus_communication stop;
}

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void EX_GPIO_PWM_ON(char PIN ,unsigned int DUTYCYCLE){
   /*
    * write Led 12bit function used to ledon_l and led_off state handle the user;
    */
   WRITE_12BIT_ADDR(PIN ,DUTYCYCLE, GPIO_OFF);
}
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void EX_GPIO_ON(char PIN){
   /*
    * write Led 12bit function used to ledon_l and led_off state handle the user;
    */
   WRITE_12BIT_ADDR(PIN ,GPIO_ON, GPIO_OFF);
}
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void EX_GPIO_OFF(char PIN){
  /*
    * write Led 12bit function used to ledon_l and led_off state handle the user;
    *example : first pin ,Led_On ,Led_Off;
    */
   WRITE_12BIT_ADDR(PIN ,GPIO_OFF, GPIO_ON);
}


/********************************************EXTERNAL************************************************/

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void I2C1_INIT()
  {
  	GPIOB_OUTPUT_DIR(GPIOB11_MODE, GPIOB11_PULL ,GPIOB11);
  	GPIOB_OUTPUT_DIR(GPIOB12_MODE, GPIOB12_PULL ,GPIOB12);
  }

//Start conditional SDA and SCL data transfers.
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void I2C1_START(void)
  {
	PCF8575_SERIAL_CLOCK_HIGH();
	PCF8575_SERIAL_DATA_HIGH();
    Delay_us(4.7);
    PCF8575_SERIAL_DATA_LOW();
    Delay_us(4);
    PCF8575_SERIAL_CLOCK_LOW();
  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void I2C1_STOP(void)
  {
	PCF8575_SERIAL_CLOCK_HIGH();
	PCF8575_SERIAL_DATA_LOW();
    Delay_us(4);
    PCF8575_SERIAL_DATA_HIGH();
    Delay_us(4.7);


  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void I2C1_ACK(void)
  {
	PCF8575_SERIAL_DATA_LOW();
    Delay_us(4);
    PCF8575_SERIAL_CLOCK_HIGH();
    Delay_us(4);
    PCF8575_SERIAL_CLOCK_LOW();
    Delay_us(4);

  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

 void I2C1_NACK(void)
  {
	 PCF8575_SERIAL_CLOCK_HIGH();
	 PCF8575_SERIAL_DATA_LOW();
	 Delay_us(4);
	 PCF8575_SERIAL_DATA_HIGH();
  }

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************PCA9685_INIT********************************************************
*/
void PCF8575_ADDRESS_WRITE(uint8_t Addr)
  {
    uint8_t temp ,i;
    for(i = 0; i<8; i++)
      {
        temp = ((Addr & 0x80)?1:0);

        if(temp){PCF8575_SERIAL_DATA_HIGH();}
        else {PCF8575_SERIAL_DATA_LOW();}

        Delay_us(4.7);
        PCF8575_SERIAL_CLOCK_HIGH();
        Delay_us(4.7);
        PCF8575_SERIAL_CLOCK_LOW();
        Delay_us(4.7);

        Addr <<= 1;
      }
     I2C1_ACK();
  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

uint8_t PCF8575_ADDRESS_READ(void)
  {
	PCF8575_DATA_DIRECTION_INPUT();
    uint8_t RECEIVING_DATA ,DATA_SIFTING;
    uint8_t i;

    for(i = 0; i < 8; i++)
      {
         RECEIVING_DATA |= PCF8575_SERIAL_READ_DATA();
         if(i < 7){
          DATA_SIFTING = RECEIVING_DATA >> 1;
         }
         PCF8575_SERIAL_CLOCK_LOW();
        Delay_us(4.7);
        PCF8575_SERIAL_CLOCK_HIGH();
        Delay_us(4);

      }
     I2C1_ACK();
     return DATA_SIFTING;
  }

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void I2C2_INIT()
  {
  	GPIOB_OUTPUT_DIR(GPIOB13_MODE, GPIOB13_PULL ,GPIOB13);
  	GPIOB_OUTPUT_DIR(GPIOB14_MODE, GPIOB14_PULL ,GPIOB14);
  }

//Start cionditional sda and scl data transfers.
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void I2C2_START(void)
  {
    SERIAL_CLOCK_HIGH();
    SERIAL_DATA_HIGH();
    Delay_us(4.7);
    SERIAL_DATA_LOW();
    Delay_us(4);
   	SERIAL_CLOCK_LOW();
  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void I2C2_STOP(void)
  {
     SERIAL_CLOCK_HIGH();
     SERIAL_DATA_LOW();
     Delay_us(4);
     SERIAL_DATA_HIGH();
     Delay_us(4.7);


  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void I2C2_ACK(void)
  {
    SERIAL_DATA_LOW();
    Delay_us(4);
    SERIAL_CLOCK_HIGH();
    Delay_us(4);
    SERIAL_CLOCK_LOW();
    Delay_us(4);

  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

 void I2C2_NACK(void)
  {
    SERIAL_CLOCK_HIGH();
    SERIAL_DATA_LOW();
    Delay_us(4);
    SERIAL_DATA_HIGH();
  }

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************PCA9685_INIT********************************************************
*/
void ADDRESS_WRITE(uint8_t Addr)
  {
    uint8_t temp ,i;
    for(i = 0; i<8; i++)
      {
        temp = ((Addr & 0x80)?1:0);

        if(temp){SERIAL_DATA_HIGH();}
        else {SERIAL_DATA_LOW();}

        Delay_us(4.7);
        SERIAL_CLOCK_HIGH();
        Delay_us(4.7);
        SERIAL_CLOCK_LOW();
        Delay_us(4.7);

        Addr <<= 1;
      }
     I2C2_ACK();
  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

uint8_t ADDRESS_READ(void)
  {
    DATA_DIRECTION_INPUT();
    uint8_t RECEIVING_DATA ,DATA_SIFTING;
    uint8_t i;

    for(i = 0; i < 8; i++)
      {
         RECEIVING_DATA |= SERIAL_READ_DATA();
         if(i < 7){
          DATA_SIFTING = RECEIVING_DATA >> 1;
         }
         SERIAL_CLOCK_LOW();
        Delay_us(4.7);
        SERIAL_CLOCK_HIGH();
        Delay_us(4);

      }
     I2C2_ACK();
     return DATA_SIFTING;
  }

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
volatile void PCF8575_LCD_ON(uint8_t LedOn_HI ,uint8_t LedOn_LO){
	I2C1_START();
	PCF8575_ADDRESS_WRITE(PCF8575_WR_SlaveAdd);
	PCF8575_ADDRESS_WRITE(LedOn_HI);
	PCF8575_ADDRESS_WRITE(LedOn_LO);
    I2C1_STOP();
}
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

volatile void PCF8575_LCD_OFF(uint8_t LedOff_HI, uint8_t LedOff_LO){
	I2C1_START();
	PCF8575_ADDRESS_WRITE(PCF8575_WR_SlaveAdd);
	PCF8575_ADDRESS_WRITE(LedOff_HI);
	PCF8575_ADDRESS_WRITE(LedOff_LO);
    I2C1_STOP();
}
/*
 * I2c with Lcd protocols were working.
 */
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void LCD20x4_INIT(uint8_t _lcd_data, uint8_t _lcd_cols ,uint8_t _lcd_rows)
  {
     _WriteModeAddr = _lcd_data;
     _LcdCols = _lcd_cols;
     _Lcd_Rows = _lcd_rows;
     _charsize = LCD_5x8DOTS;
     BackLightVal = LCD_BACKLIGHT;
  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void LCD20x4_EXPANDWRITE(uint8_t _writeValue)
  {
    I2C2_START();
    ADDRESS_WRITE(_WriteModeAddr);
    ADDRESS_WRITE((int)(_writeValue )| BackLightVal);
    I2C2_STOP();
  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void LCD20x4_ENABLE_CLOCK(uint8_t clocks)
  {
     LCD20x4_EXPANDWRITE(clocks | ENABLE);
     Delay_us(10);

     LCD20x4_EXPANDWRITE(clocks & ~ENABLE);
     Delay_us(10);

  }
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */

void LCD20x4_WRITE_4BITS(uint8_t bitdata ,uint8_t REGISTER)
  {
    uint8_t highbit = ((bitdata) & 0xF0);
    uint8_t lowbit = ((bitdata << 4) & 0xF0);

    LCD20x4_EXPANDWRITE((highbit) | REGISTER);
    LCD20x4_ENABLE_CLOCK(highbit | REGISTER);

    LCD20x4_EXPANDWRITE((lowbit) | REGISTER);
    LCD20x4_ENABLE_CLOCK(lowbit | REGISTER);
  }

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void Print(const char *character)
  {
    while(*character != '\0')
        LCD20x4_WRITE_4BITS(*character++, 1);
  }


void PRINTF(unsigned int CMD ,char CharBuf[]){
	unsigned int Length = strlen(CharBuf);

	for(unsigned int i = 0; i < Length; i++){
		LCD20x4_WRITE_4BITS(CMD + i ,CLEAR_BIT);
		LCD20x4_WRITE_4BITS(CharBuf[i] ,SET_BIT);

	}
}
/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void LCD20x4_BEGIN(void)
  {
    //I2C_INIT(); // PORT DIRECTION ENBALES.S
    Display_Function = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

    if(_Lcd_Rows > 1){
       Display_Function |= LCD_2LINE;
    }

    if((_charsize != 0) && _Lcd_Rows == 1){
      Display_Function |= LCD_5x10DOTS;
    }
    //accroding to datasheet, we need at least 40ms after power rises above 2.7v
     Delay_us(50);
     LCD20x4_EXPANDWRITE(BackLightVal);
     Delay_us(10);

     LCD20x4_WRITE_4BITS((LCD_CLEARDISPLAY) ,0);

     LCD20x4_WRITE_4BITS(LCD_RETURNHOME ,0);
     Delay_us(120);

     Display_Function = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
     LCD20x4_WRITE_4BITS((LCD_ENTRYMODESET | Display_Function) ,0);

     LCD20x4_WRITE_4BITS((0x02) ,0); //Reset Display

      //WRITE_4BITS((LCD_FUNCTIONSET | Display_Function) ,0);
     LCD20x4_WRITE_4BITS((LCD_FUNCTIONSET) ,0);

     // // // turn the display on with no cursor or blinking default
     Display_Function = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
     // Display_Function = LCD_DISPLAYON;
     LCD20x4_WRITE_4BITS((LCD_DISPLAYCONTROL | LCD_DISPLAYON) ,0);
     Delay_us(10);


}

/****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************
 */
void BACK_LIGHT(void)
  {
      BackLightVal=LCD_BACKLIGHT;
      LCD20x4_EXPANDWRITE(0);
  }


/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************PCA9685_INIT********************************************************/
void DECIMAL_TO_CHAR(unsigned int Cmd ,unsigned char Dec){
	LCD20x4_WRITE_4BITS(Cmd , 0);LCD20x4_WRITE_4BITS((Dec)%1000/100+0x30 , 1);
	LCD20x4_WRITE_4BITS(Cmd+1 , 0);LCD20x4_WRITE_4BITS((Dec)%100/10+0x30 , 1);
	LCD20x4_WRITE_4BITS(Cmd+2 , 0);LCD20x4_WRITE_4BITS((Dec)%10+0x30 , 1);
}

 /****************************************************************************************************************************
 * **************************************************************************************************************************
 * ******************************************************PCA9685_INIT********************************************************/

uint8_t  ResetInitalization(void)
  {
    uint8_t SignBit;
    GPIOB_OUTPUT_DIR(GPIOB5_MODE ,GPIOB5_PULL ,GPIOB5);
    // DATA_DIRECTION_OUTPUT(); //Reset pullup resiger low position.
    DS18B20_LOW();
    Delay_us(480);          //wait for 480us

    GPIOB_INPUT_DIR(GPIOB5_MODE ,GPIOB5);
   // DATA_DIRECTION_INPUT();  //Release bus(input , pull up);
    DS18B20_HIGH();
    Delay_us(60);
    SignBit = ((GPIOB_IDR & GPIOB5)); //if a 0 is detected, sensor is detected.
    Delay_us(420);

    return SignBit;
  }


/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************PCA9685_INIT********************************************************/

void OneWireWrite(short FlagEnable)
  {
    if(FlagEnable == 1)
      {
      	 GPIOB_INPUT_DIR(GPIOB5_MODE ,GPIOB5);
         //DATA_DIRECTION_INPUT();
         DS18B20_HIGH();
         Delay_us(60);
      }
     else
      {
      	 GPIOB_OUTPUT_DIR(GPIOB5_MODE ,GPIOB5_PULL ,GPIOB5);
         //DATA_DIRECTION_OUTPUT(); //Reset pullup resiger low position.
         DS18B20_LOW();
         Delay_us(1);
      }
  }

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************PCA9685_INIT********************************************************/

short OneWireRead(void)
  {
         short recovery;
         GPIOB_OUTPUT_DIR(GPIOB5_MODE ,GPIOB5_PULL ,GPIOB5);
         //DATA_DIRECTION_OUTPUT(); //Reset pullup resiger low position.
         DS18B20_LOW();
         Delay_us(1);

         GPIOB_INPUT_DIR(GPIOB5_MODE ,GPIOB5);
         //DATA_DIRECTION_INPUT();
         DS18B20_HIGH();
         Delay_us(14);

        recovery = ((GPIOB_IDR & GPIOB5));
        Delay_us(45);

        return  recovery;

   }

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************PCA9685_INIT********************************************************/

 void DS18B20_WriteByte(uint8_t bytes)
  {
    uint8_t i = 8;

    while(i--)
      {
        OneWireWrite(bytes & 0x01);
        bytes >>= 1;
      }
  }

uint8_t DS18B20_readByte(void)
  {
    uint8_t i=8, n=0;
    while(i--)
      {
        n>>=1;
        n|=(OneWireRead()<<7);
      }
     return n;
  }


/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/

/***************************************SPI_PROTOCOLS******************************************/



void SPI_GPIO_CONFIG(void){

	GPIOB_OUTPUT_DIR(GPIOB5_MODE ,GPIOB5_PULL ,GPIOB5);
	GPIOB_OUTPUT_DIR(GPIOB6_MODE ,GPIOB6_PULL ,GPIOB6);
	//GPIOB_INPUT_DIR(GPIOB8_MODE ,GPIOB8);

}

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/
unsigned int CUZTOMIZE_MENU(void){

	GPIOB_INPUT_DIR(GPIOB6_MODE ,GPIOB6);
	GPIOB_INPUT_DIR(GPIOB7_MODE ,GPIOB7);
	GPIOB_INPUT_DIR(GPIOB8_MODE ,GPIOB8);

	RotaryEncodeCount = 0;
    PRINTF(0x80 ,"What do u want?     ");

	do{
    	ROTARY_CURRENT_STATUS_B = ROTARY_ENCODE_CLK_B;

    	if(ROTARY_CURRENT_STATUS_B != ROTARY_INIT_STATUS_B){

    	   if(ROTARY_CURRENT_STATUS_B == CLEAR_BIT){
    		   if(!(ROTARY_ENCODE_DIN_A)){
    		   RotaryEncodeCount++;
    	   	   }
			   else if(ROTARY_ENCODE_DIN_A)
			   {
				   RotaryEncodeCount--;
			   }
    	   }
    	   ROTARY_INIT_STATUS_B = ROTARY_CURRENT_STATUS_B;
    	}

    	if(RotaryEncodeCount > 2){
    		LCD20x4_WRITE_4BITS(0xc0 , CLEAR_BIT);
    		Print("           ");
    		RotaryEncodeCount = CLEAR_BIT;
    	}

    	else if(RotaryEncodeCount <= CLEAR_BIT){
    		RotaryEncodeCount = CLEAR_BIT;
    	}

    	switch(RotaryEncodeCount){

    	case 1:
    		PRINTF(0xC0 ,"No of dosa          ");
    		Sel_Customize_Menu = 1;
    		break;

    	case 2:
    	    Sel_Customize_Menu = 2;
    		PRINTF(0xC0 ,"No of roti          ");
    		break;

    	default:
    		RotaryEncodeCount = CLEAR_BIT;
    		break;
    	}

//ROTARY_SWITCH
	}while(ROTARY_SWITCH);

	if(Sel_Customize_Menu <= 0){
		CUZTOMIZE_MENU();
	}

    PRINTF(0x80 ,"AUTO FOOD VENDING   ");
	return (Sel_Customize_Menu);
}


/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/
unsigned int CUZTOMIZE_DISC_CNT(unsigned int Sel_dish){


	GPIOB_INPUT_DIR(GPIOB6_MODE ,GPIOB6);
	GPIOB_INPUT_DIR(GPIOB7_MODE ,GPIOB7);
	GPIOB_INPUT_DIR(GPIOB8_MODE ,GPIOB8);

	RotaryEncodeCount = 0;
    LCD20x4_WRITE_4BITS(0xC0 , 0);
    if(Sel_dish == 1){
    	PRINTF(0xC0 ,"No.of.Dosa:         ");
    }
    if(Sel_dish == 2){
    	PRINTF(0xC0 ,"No.of.Roti:         ");
    }
    Delay_ms(5000);

	do{
    	ROTARY_CURRENT_STATUS_B = ROTARY_ENCODE_CLK_B;

    	if(ROTARY_CURRENT_STATUS_B != ROTARY_INIT_STATUS_B){

    	   if(ROTARY_CURRENT_STATUS_B == CLEAR_BIT){
    		   if(!(ROTARY_ENCODE_DIN_A)){
    			   Dosa_No_Cnt++;
    	   	   }
			   else if(ROTARY_ENCODE_DIN_A)
			   {
				   Dosa_No_Cnt--;
			   }
    	   }
    	   ROTARY_INIT_STATUS_B = ROTARY_CURRENT_STATUS_B;
    	}

    	else if(Dosa_No_Cnt >= 254){
    		Dosa_No_Cnt = 0;
    	}

    	else if(Dosa_No_Cnt <= 0){
    		Dosa_No_Cnt = CLEAR_BIT;
    	}

    	else{
    		LCD20x4_WRITE_4BITS(0XCB , 0);
    	    LCD20x4_WRITE_4BITS(Dosa_No_Cnt%100/10+0x30 , 1);
    	    LCD20x4_WRITE_4BITS(Dosa_No_Cnt%10+0x30 , 1);

    	}

//ROTARY_SWITCH
	}while(ROTARY_SWITCH);
	if(Dosa_No_Cnt <= 0){
		CUZTOMIZE_DISC_CNT(SEL_DISH);
	}
    PRINTF(0x80 ,"AUTO FOOD VENDING   ");
	return (Dosa_No_Cnt);
}


/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/
unsigned int CUZTOMIZE_MENU_1(void){

	GPIOB_INPUT_DIR(GPIOB9_MODE ,GPIOB9);
	GPIOB_INPUT_DIR(GPIOE0_MODE ,GPIOE0);
	GPIOB_INPUT_DIR(GPIOE1_MODE ,GPIOE1);

	RotaryEncodeCount = 0;
    LCD20x4_WRITE_4BITS(0x80 , 0);
    Print("Would u like anyone?");

	do{
    	ROTARY_CURRENT_STATUS_B1 = ROTARY_ENCODE_CLK_B1;

    	LCD20x4_WRITE_4BITS(0x94 , 0);
       	LCD20x4_WRITE_4BITS(ROTARY_ENCODE_CLK_B1%100/10+0x30 , 1);
    	LCD20x4_WRITE_4BITS(ROTARY_ENCODE_CLK_B1%10+0x30 , 1);


    	if(ROTARY_CURRENT_STATUS_B1 != ROTARY_INIT_STATUS_B1){

    	   if(ROTARY_CURRENT_STATUS_B1 == CLEAR_BIT){
    		   if(!(ROTARY_ENCODE_DIN_A1)){
    		   RotaryEncodeCount++;
    	   	   }
			   else if(ROTARY_ENCODE_DIN_A1)
			   {
				   RotaryEncodeCount--;
			   }
    	   }
    	   ROTARY_INIT_STATUS_B1 = ROTARY_CURRENT_STATUS_B1;
    	}

    	if(RotaryEncodeCount > 2){
    		LCD20x4_WRITE_4BITS(0xc0 , CLEAR_BIT);
    		Print("           ");
    		RotaryEncodeCount = CLEAR_BIT;
    	}

    	else if(RotaryEncodeCount <= CLEAR_BIT){
    		RotaryEncodeCount = CLEAR_BIT;
    	}

    	switch(RotaryEncodeCount){

    	case 1:
    		PRINTF(0xC0 ,"No of dosa          ");
    		break;

    	case 2:
    		PRINTF(0xC0 ,"No of roti          ");
    		break;

    	default:
    		RotaryEncodeCount = CLEAR_BIT;
    		break;
    	}

//ROTARY_SWITCH
	}while(ROTARY_SWITCH_1);

	return (RotaryEncodeCount);
}


/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/

void PRESSING_CHECK(void){
    int PRESS_FLAG = CLEAR_BIT;
    PCF8575_LCD_ON(0x00 ,0x04); //Initial stop the pressing mechanisham;
	//PCF8575_LCD_ON(0x00 ,0x00);
	//PRESS_UP_POS_LO;
	EX_GPIO_ON(EX_GPIO3_PIN);
	EX_GPIO_ON(EX_GPIO4_PIN);


	do{
		if(!(CHAPATI_PRESS_HOME_SEN)){
				PCF8575_LCD_ON(0x00 ,0x00);
				//PRESS_UP_POS_HI;
				EX_GPIO_ON(EX_GPIO13_PIN);
				PRESS_FLAG--;
			}

	    if(CHAPATI_PRESS_HOME_SEN){
				PCF8575_LCD_ON(0x00 ,0x04);
				PRESS_FLAG--;
			}
	}while(!(CHAPATI_PRESS_HOME_SEN));
	EX_GPIO_OFF(EX_GPIO13_PIN);
	//PRESS_UP_POS_LO;

}
/************************************ARM_INIT_POSITION_FINDOUT************************************
 * ***********************************************************************************************
 */
void ARM_POSITION_CHECK(void){

		do{
			if(!(CHAPATI_ARM_HOME)){
				ARM_MOVE_FWD_LO;
				ARM_MOVE_REV_HI;
			}

			if((CHAPATI_ARM_HOME)){
				ARM_MOVE_FWD_LO;
				ARM_MOVE_REV_LO;
			}

		}while(!(CHAPATI_ARM_HOME));
		ARM_MOVE_FWD_LO;
		ARM_MOVE_REV_LO;
}

void DOUGH_UP_DOWN(void){
	  unsigned int DOUGH_FLAG = CLEAR_BIT;
	  do{
		  if(((C_DOUGH_DOWN)) && DOUGH_FLAG == CLEAR_BIT){
				PCF8575_LCD_OFF(0X00 ,0x6C);
				PRINTF(0xD9 ,C_UP_DOWN);
				DOUGH_FLAG++;
			}

			if(((C_DOUGH_UP)) && DOUGH_FLAG == CLEAR_BIT){
				PCF8575_LCD_OFF(0X00 ,0x74); //DOWN_MOVE
				DOUGH_FLAG++;
			}


			if(((C_DOUGH_UP)) && DOUGH_FLAG == 1){
				PCF8575_LCD_OFF(0X00 ,0x74); //DOWN_MOVE
				DOUGH_FLAG++;
			}

			if((C_DOUGH_DOWN) && DOUGH_FLAG == 2){
				PCF8575_LCD_OFF(0X00 ,0x64); //DOWN_MOVE
				DOUGH_FLAG++;
				//EX_GPIO_OFF(EX_GPIO3_PIN);
			}

			if((!(C_DOUGH_UP)) && (!(C_DOUGH_DOWN)) && DOUGH_FLAG == CLEAR_BIT){
				PCF8575_LCD_OFF(0X00 ,0x74);

			}
			LCD20x4_WRITE_4BITS(0xE6 , 0);
			LCD20x4_WRITE_4BITS(DOUGH_FLAG%100/10+0x30 , 1);
		    LCD20x4_WRITE_4BITS(DOUGH_FLAG%10+0x30 , 1);

	  }while((DOUGH_FLAG < 3));

}

/****************************************DOSA_MATIC_AUTO TRIALS******************************************
 *
 */
void DOSA_MATIC_AUTO_INIT(void){

	PRESSING_CHECK();

	EX_GPIO_ON(EX_GPIO3_PIN);
	EX_GPIO_ON(EX_GPIO4_PIN);
	CLEAN_LO;
	TIM1_MS_CNT = CLEAR_BIT;
	INITI_TRIALS_FLAG = SET_BIT;
	AUTO_TRIAL_FLAG_CNT_EN = CLEAR_BIT;
	TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;

	PRINTF(0x80 ,AUTOMATIC_INIT_NOTI);
	do{
		//INIT_CHECK THE SENSOR STATUS OR MOVE TO NEXT STEPS;
		if((DOSA_U_SLOT_SEN_SPREAD) && AUTO_TRIAL_FLAG_CNT_EN == CLEAR_BIT){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			AUTO_TRIAL_FLAG_CNT_EN++;DOSA_SPREAD_SEQ_TEST++;
			PRINTF(0xD9 ,DOSA_PLATE_SPREAD_NOTI);

		}
		//INIT_CHECK THE SENSOR STATUS OR MOVE TO NEXT STEPS;
		if((!(DOSA_U_SLOT_SEN_SPREAD)) && AUTO_TRIAL_FLAG_CNT_EN == CLEAR_BIT){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			//AUTO_TRIAL_FLAG_CNT_EN++;ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PCF8575_LCD_ON(0x02 ,0x64);
			PRINTF(0xD9 ,DOSA_PLATE_SPREAD_NOTI);

		}


/****************************************DOSA_PLATE_SPREAD_METHOS_***********************************************************************
***************************************************************************************************************************
*******************************************************END*****************************************************************/

		//FIRST_METHODE CHECKED THAT OR MOVE TO NEXT STEP
		else if(AUTO_TRIAL_FLAG_CNT_EN == 1 && DOSA_SPREAD_SEQ_TEST == 1){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_300SEC_TIMER_EN;
			AUTO_TRIAL_FLAG_CNT_EN++;
			PCF8575_LCD_ON(0x01 ,0x64);
			//PRINTF(0x94 ,"A1");
			}
		else if((DOSA_U_SLOT_REV_SPREAD) && AUTO_TRIAL_FLAG_CNT_EN == 2){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_300SEC_TIMER_EN;
			AUTO_TRIAL_FLAG_CNT_EN++;
			PCF8575_LCD_ON(0x02 ,0x64);
					//PRINTF(0x94 ,"A2");
			}
		else if(AUTO_TRIAL_FLAG_CNT_EN == 3){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			AUTO_TRIAL_FLAG_CNT_EN++;
					//PRINTF(0x94 ,"A3");
			}

		else if((DOSA_U_SLOT_SEN_SPREAD) && AUTO_TRIAL_FLAG_CNT_EN == 4) {
			AUTO_TRIAL_FLAG_CNT_EN++;
			PCF8575_LCD_ON(0x00 ,0x64);
			//PRINTF(0x94 ,"A4");
		}


/**********************************************DOSA_PLATE_SPREAD_METHODS**************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/

//		//SECOND_METHODS_CHECK THAT OR  MOVE TO NEXT STEPS;
		else if(AUTO_TRIAL_FLAG_CNT_EN == 1 && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 1){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_150SEC_TIMER_EN;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"B1");
		}

		else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_150SEC_TIMER_EN && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 2){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_300SEC_TIMER_EN;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"B2");
		}

		//		//THIRED_MOTHOD RUNING OR MOVE TO NEXT STEPS
		else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_300SEC_TIMER_EN && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 3){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"B3");
		}

		else if((DOSA_U_SLOT_SEN_SPREAD) && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 4) {
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"B4");
		}

/****************************************************************************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/

		//INIT_CHECK THE SENSOR STATUS OR MOVE TO NEXT STEPS;
		if((DOSA_U_SLOT_SEN_MM) && AUTO_TRIAL_FLAG_CNT_EN == 5){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			AUTO_TRIAL_FLAG_CNT_EN++;DOSA_SPREAD_SEQ_TEST++;
			PRINTF(0xD9 ,DOSA_MM_NOTI);

		}
		//INIT_CHECK THE SENSOR STATUS OR MOVE TO NEXT STEPS;
	   if((!(DOSA_U_SLOT_SEN_MM)) && AUTO_TRIAL_FLAG_CNT_EN == 5){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			PCF8575_LCD_ON(0x08 ,0x64);
			PRINTF(0xD9 ,DOSA_MM_NOTI);
		}

/*********************************************MM_METHODS*********************************************************************
***************************************************************************************************************************
*******************************************************END*****************************************************************/

		//FIRST_METHODE CHECKED THAT OR MOVE TO NEXT STEP
		else if(AUTO_TRIAL_FLAG_CNT_EN == 6 && DOSA_SPREAD_SEQ_TEST == 2){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_150SEC_TIMER_EN;
			PCF8575_LCD_ON(0x04 ,0x64);
			AUTO_TRIAL_FLAG_CNT_EN++;
			//PRINTF(0x94 ,"A6");
			}
		else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_150SEC_TIMER_EN && AUTO_TRIAL_FLAG_CNT_EN == 7){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_150SEC_TIMER_EN;
			PCF8575_LCD_ON(0x08 ,0x64);
			AUTO_TRIAL_FLAG_CNT_EN++;

			//PRINTF(0x94 ,"A7");
		}
		//		//THIRED_MOTHOD RUNING OR MOVE TO NEXT STEPS
		else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= 1 && AUTO_TRIAL_FLAG_CNT_EN == 8){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			AUTO_TRIAL_FLAG_CNT_EN++;
			//PRINTF(0x94 ,"A8");
		}

		else if((DOSA_U_SLOT_SEN_MM) && AUTO_TRIAL_FLAG_CNT_EN == 9) {
			PCF8575_LCD_ON(0x00 ,0x64);
			AUTO_TRIAL_FLAG_CNT_EN++;
			//PRINTF(0x94 ,"A9");
		}



/****************************************************************************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/

		//INIT_CHECK THE SENSOR STATUS OR MOVE TO NEXT STEPS;
		if((DOSA_U_SLOT_SEN_BATTER) && AUTO_TRIAL_FLAG_CNT_EN == 10){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			AUTO_TRIAL_FLAG_CNT_EN++;DOSA_SPREAD_SEQ_TEST++;
			PRINTF(0xD9 ,BATTER_NOTI);

		}
		//INIT_CHECK THE SENSOR STATUS OR MOVE TO NEXT STEPS;
	   if((!(DOSA_U_SLOT_SEN_BATTER)) && AUTO_TRIAL_FLAG_CNT_EN == 10){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			//ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PCF8575_LCD_ON(0x20 ,0x64);
			PRINTF(0x94 ,BATTER_NOTI);
		}

/**********************************************BATTER CHECK METHODS*********************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/


		//FIRST_METHODE CHECKED THAT OR MOVE TO NEXT STEP
		else if(AUTO_TRIAL_FLAG_CNT_EN == 11 && DOSA_SPREAD_SEQ_TEST == 3){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_150SEC_TIMER_EN;
			PCF8575_LCD_ON(0x10 ,0x64);
			AUTO_TRIAL_FLAG_CNT_EN++;
			//PRINTF(0x94 ,"A11");
			}
		else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_150SEC_TIMER_EN && AUTO_TRIAL_FLAG_CNT_EN == 12){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_150SEC_TIMER_EN;
			PCF8575_LCD_ON(0x20 ,0x64);
			AUTO_TRIAL_FLAG_CNT_EN++;
			//PRINTF(0x94 ,"A12");
		}
		//		//THIRED_MOTHOD RUNING OR MOVE TO NEXT STEPS
		else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= 1 && AUTO_TRIAL_FLAG_CNT_EN == 13){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			AUTO_TRIAL_FLAG_CNT_EN++;
			//PRINTF(0x94 ,"A13");
		}

		else if((DOSA_U_SLOT_SEN_BATTER) && AUTO_TRIAL_FLAG_CNT_EN == 14) {
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_30SEC_TIMER_EN;
			PCF8575_LCD_ON(0x00 ,0x64);
			PCF8575_LCD_ON(0x40 ,0x64);
			AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0xD9 ,BATTER_MIX);

			//PRINTF(0x94 ,"A14");
		}


//		DOSA_CLEANING_SEN
/************************************************CLEANING METHODS*******************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/
		else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_30SEC_TIMER_EN && AUTO_TRIAL_FLAG_CNT_EN == 15){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_30SEC_TIMER_EN;
			PCF8575_LCD_ON(0x80 ,0x64);
			AUTO_TRIAL_FLAG_CNT_EN++;

		}

		else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_30SEC_TIMER_EN && AUTO_TRIAL_FLAG_CNT_EN == 16){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_30SEC_TIMER_EN;
			PCF8575_LCD_ON(0x00 ,0x64);
			AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0xD9 ,BATTER_MIX);
		}


/************************************************** CHAPATI PRESSING TRIAL*******************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/
		else if(CHAPATI_PRESS_HOME_SEN && AUTO_TRIAL_FLAG_CNT_EN == 17){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			PCF8575_LCD_ON(0x00 ,0x65);
			PRINTF(0xD9 ,C_PRESSING);
			AUTO_TRIAL_FLAG_CNT_EN++;
		}

		else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_150SEC_TIMER_EN && AUTO_TRIAL_FLAG_CNT_EN == 18){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			PCF8575_LCD_ON(0x00 ,0x64);
			//PRESS_UP_POS_HI;
			EX_GPIO_ON(EX_GPIO13_PIN);
			AUTO_TRIAL_FLAG_CNT_EN++;

		}

		else if(CHAPATI_PRESS_HOME_SEN && AUTO_TRIAL_FLAG_CNT_EN == 19){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			PCF8575_LCD_ON(0x00 ,0x64);
			//PRESS_UP_POS_LO;
			EX_GPIO_OFF(EX_GPIO13_PIN);
			AUTO_TRIAL_FLAG_CNT_EN++;

		}


/**************************************************WATER LEVEL_INDICATE METHODS**********************************************************************************************************************************************************************
******************************************************END*****************************************************************/
		else if(AUTO_TRIAL_FLAG_CNT_EN == 20){
			PCF8575_LCD_ON(0x00 ,0x60);
			PRINTF(0xD9 ,POWDER_MIX_NOTI);
			AUTO_TRIAL_FLAG_CNT_EN++;
		}

		else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_150SEC_TIMER_EN && AUTO_TRIAL_FLAG_CNT_EN == 21){
			PCF8575_LCD_ON(0x00 ,0x64);
			AUTO_TRIAL_FLAG_CNT_EN++;

		}

/*********************************************************SERVO MOTOR OPEN/CLOSE************************************************************
**************************************************************************************************************************************************
******************************************************END*****************************************************************************************/


		else if(AUTO_TRIAL_FLAG_CNT_EN == 22){
			PRINTF(0xD9 ,SERVO_NOTI);
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_150SEC_TIMER_EN;
			TIM9_CCR1 = SERVO_MOTOR_30_DEG;
		//	WRITE_12BIT_ADDR(SERVO_MOTOR_EN,SERVO_MOTOR_ON, CLEAR_BIT);
			AUTO_TRIAL_FLAG_CNT_EN++;

		}
	   else if(AUTO_TRIAL_FLAG_CNT_EN == 23 && TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_150SEC_TIMER_EN){
		    TIM9_CCR1 = SERVO_MOTOR_0_DEG;
		   //WRITE_12BIT_ADDR(SERVO_MOTOR_EN,SERVO_MOTOR_OF, CLEAR_BIT); //1024+2048=3072
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			AUTO_TRIAL_FLAG_CNT_EN++;
			PCF8575_LCD_ON(0X00 ,0X64);

		}


/**************************************************ChaptiDoughtUp Down METHODS*******************************************************************
**************************************************************************************************************************
**************************************************************************************************************************
**************************************************************************************************************************
*********************************************************END*****************************************************************/
		if(((C_DOUGH_DOWN)) && AUTO_TRIAL_FLAG_CNT_EN == 24){
			PCF8575_LCD_OFF(0X00 ,0x6C);
			PRINTF(0xD9 ,C_UP_DOWN);
			AUTO_TRIAL_FLAG_CNT_EN++;
		}

		if(((C_DOUGH_UP)) && AUTO_TRIAL_FLAG_CNT_EN == 24){
			PCF8575_LCD_OFF(0X00 ,0x74); //DOWN_MOVE
			AUTO_TRIAL_FLAG_CNT_EN = 24;
		}


		if(((C_DOUGH_UP)) && AUTO_TRIAL_FLAG_CNT_EN == 25){
			PCF8575_LCD_OFF(0X00 ,0x74); //DOWN_MOVE
			AUTO_TRIAL_FLAG_CNT_EN++;
		}

		if(((C_DOUGH_DOWN)) && AUTO_TRIAL_FLAG_CNT_EN == 26){
			PCF8575_LCD_OFF(0X00 ,0x64); //DOWN_MOVE
			AUTO_TRIAL_FLAG_CNT_EN++;
			//EX_GPIO_OFF(EX_GPIO3_PIN);
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_150SEC_TIMER_EN;
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;

		}

		if((!(C_DOUGH_UP)) && (!(C_DOUGH_DOWN)) && AUTO_TRIAL_FLAG_CNT_EN == 24){
			PCF8575_LCD_OFF(0X00 ,0x74);

		}
/****************************************************ARM_MOVING FOR/REV***********************************************
 * *******************************************************************************************************************
 * *******************************************************************************************************************
 */
		if(!(CHAPATI_ARM_HOME) && AUTO_TRIAL_FLAG_CNT_EN == 27){
			ARM_MOVE_FWD_LO;
			ARM_MOVE_REV_HI;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_150SEC_TIMER_EN;
			EX_GPIO_PWM_ON(EX_GPIO8_PIN ,2560);


		}

		if((CHAPATI_ARM_HOME) && AUTO_TRIAL_FLAG_CNT_EN == 27){
			EX_GPIO_PWM_ON(EX_GPIO8_PIN ,2560);
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_150SEC_TIMER_EN;
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			ARM_MOVE_FWD_HI;
			ARM_MOVE_REV_LO;
			AUTO_TRIAL_FLAG_CNT_EN++;
		}

		if(AUTO_TRIAL_FLAG_CNT_EN == 28 && TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_150SEC_TIMER_EN){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			ARM_MOVE_FWD_LO;
			ARM_MOVE_REV_HI;
			AUTO_TRIAL_FLAG_CNT_EN++;
		}

		if((CHAPATI_ARM_HOME) && AUTO_TRIAL_FLAG_CNT_EN == 29){
			ARM_MOVE_FWD_LO;
			ARM_MOVE_REV_LO;
			EX_GPIO_PWM_ON(EX_GPIO8_PIN ,0);
			AUTO_TRIAL_FLAG_CNT_EN++;
		}


/**************************************************WATER LEVEL_INDICATE METHODS*******************************************************************
 **************************************************************************************************************************
 **************************************************************************************************************************
 ******************************************************END*****************************************************************/
	   else if(AUTO_TRIAL_FLAG_CNT_EN == 30){
		   REVERSE_SEC_CNT = CLEAR_BIT;
		   REVERSE_SEC_CNT = WAIT_FOR_150SEC_TIMER_EN;
		   TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
		   CLEAN_HI;
		   AUTO_TRIAL_FLAG_CNT_EN++;
	   }

	   else if(AUTO_TRIAL_FLAG_CNT_EN == 31 && TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_150SEC_TIMER_EN){
		   TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
		   CLEAN_LO;
		   EX_GPIO_OFF(EX_GPIO3_PIN);
		   AUTO_TRIAL_FLAG_CNT_EN++;

	   }

	   else if((D_WATER_FLOW_SEN) && AUTO_TRIAL_FLAG_CNT_EN  == 32){
			PCF8575_LCD_ON(0x00 ,0x64);
			EX_GPIO_ON(EX_GPIO3_PIN);
			EX_GPIO_OFF(EX_GPIO4_PIN);
			AUTO_TRIAL_FLAG_CNT_EN++;
			//PRINTF(0x94 ,"A15");

	   }

	   else if(!(C_WATER_FLOW_SEN) && AUTO_TRIAL_FLAG_CNT_EN == 33){
		   EX_GPIO_ON(EX_GPIO4_PIN);
		   //PCF8575_LCD_ON(0x00 ,0x44);
		   AUTO_TRIAL_FLAG_CNT_EN++;
		   //PRINTF(0x94 ,"A16");


	   }

/**************************************************OIL LEVEL_INDICATE METHODS**********************************************
 * ************************************************************************************************************************
 **************************************************************************************************************************
******************************************************END*****************************************************************/
	   else if((C_OIL_FLOW_SEN) && AUTO_TRIAL_FLAG_CNT_EN == 34){
		   PCF8575_LCD_ON(0x00 ,0x64);
		   AUTO_TRIAL_FLAG_CNT_EN++;
		   //PRINTF(0x94 ,"A17");

	   }

	   else if((D_OIL_FLOW_SEN) && AUTO_TRIAL_FLAG_CNT_EN == 35){
		   AUTO_TRIAL_FLAG_CNT_EN++;
		   //PRINTF(0x94 ,"A18");

	   }

	   else if((WATER_LEVEL_SEN) && AUTO_TRIAL_FLAG_CNT_EN == 36){
		   AUTO_TRIAL_FLAG_CNT_EN++;
		   EX_GPIO_OFF(EX_GPIO15_PIN);
	   }

	   else if(!(WATER_LEVEL_SEN) && AUTO_TRIAL_FLAG_CNT_EN == 36){
		   EX_GPIO_ON(EX_GPIO15_PIN);
		   PRINTF(0xD9 ,WATER_LEVEL);
	   }

	   else if((OIL_LEVEL_SEN) && AUTO_TRIAL_FLAG_CNT_EN == 37){
		   AUTO_TRIAL_FLAG_CNT_EN++;
		   EX_GPIO_OFF(EX_GPIO15_PIN);

	   }

	   else if(!(OIL_LEVEL_SEN) && AUTO_TRIAL_FLAG_CNT_EN == 37){
		   PRINTF(0xD9 ,OIL_LEVEL);
		   EX_GPIO_ON(EX_GPIO15_PIN);
	   }


/**************************************************POWDER LEVEL_INDICATE METHODS********************************************
 * ************************************************************************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/

	   else if((C_POWDER_LEVEL_SEN) && AUTO_TRIAL_FLAG_CNT_EN == 38){
		   AUTO_TRIAL_FLAG_CNT_EN++;
		   EX_GPIO_OFF(EX_GPIO15_PIN);

	   }

	   else if(!(C_POWDER_LEVEL_SEN) && AUTO_TRIAL_FLAG_CNT_EN == 38){
		   PRINTF(0xD9 ,POWDER_LEVEL);
		   EX_GPIO_ON(EX_GPIO15_PIN);

	   }

	   else if((D_POWDER_LEVEL_SEN) && AUTO_TRIAL_FLAG_CNT_EN == 39){
		   AUTO_TRIAL_FLAG_CNT_EN++;
		   EX_GPIO_OFF(EX_GPIO15_PIN);

	   }

	  else if(!(D_POWDER_LEVEL_SEN) && AUTO_TRIAL_FLAG_CNT_EN == 39){
		  PRINTF(0xD9 ,POWDER_LEVEL);
		  EX_GPIO_ON(EX_GPIO15_PIN);
	   }



/**************************************************OIL LEVEL_INDICATE*******************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/

/**************************************************ALL SEQUENCE_COMPLETED**********************************************************
***********************************************************************************************************************************
***************************************************************END*****************************************************************/
		else{
			DECIMAL_TO_CHAR(0xE5 ,(REVERSE_SEC_CNT - TIMER_1_CNT_EN_AS_DOSA_TRIALS));
		}

	}while((AUTO_TRIAL_FLAG_CNT_EN < 39));
	//PRESS_UP_POS_LO;
	EX_GPIO_OFF(EX_GPIO13_PIN);
	PRINTF(0xD9,"          ");
	PRINTF(0x80 ,"AUTO FOOD VENDING   ");
	REVERSE_SEC_CNT = CLEAR_BIT;
	TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
	DECIMAL_TO_CHAR(0xE5 ,(REVERSE_SEC_CNT -TIMER_1_CNT_EN_AS_DOSA_TRIALS));
	INITI_TRIALS_FLAG = CLEAR_BIT;
	TIM1_MS_CNT = CLEAR_BIT;
	AUTO_TRIAL_FLAG_CNT_EN = CLEAR_BIT;
//	TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;

}

/**************************************************ALL SEQUENCE_COMPLETED**********************************************************
***********************************************************************************************************************************
***************************************************************END*****************************************************************/



/**************************************************CHAPATI_MAKER_CODE_WORK**********************************************************
***********************************************************************************************************************************
***************************************************************END*****************************************************************/

void CHAPATI_MAKER_AUTO_INIT(void)
{
	//PRINTF(0x80 ,CHAPATI_INIT_NOTI);
	do{
		//INIT_CHECK THE SENSOR STATUS OR MOVE TO NEXT STEPS;
		if((!(CHAPATI_U_SLOT_SEN_UP)) && CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == CLEAR_BIT){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;
			//PRINTF(0xD9 ,DOSA_PLATE_SPREAD_NOTI);

		}

		else if((!(CHAPATI_U_SLOT_SEN_DOWN)) && CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == CLEAR_BIT){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			//PRINTF(0xD9 ,DOSA_PLATE_SPREAD_NOTI);

		}

		//INIT_CHECK THE SENSOR STATUS OR MOVE TO NEXT STEPS;
		else if((CHAPATI_U_SLOT_SEN_UP) && (CHAPATI_U_SLOT_SEN_DOWN) && ELSE_AUTO_TRIAL_FLAG_CNT_EN == CLEAR_BIT){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x9F ,ELSE_AUTO_TRIAL_FLAG_CNT_EN);
			PRINTF(0xD9 ,"D0");
		}



/**********************************************************************************************************************************
***********************************************************************************************************************************
***********************************************************************************************************************************
***************************************************************END*****************************************************************/

		//FIRST_METHODE CHECKED THAT OR MOVE TO NEXT STEP
		else if(CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == 1 && (!(CHAPATI_U_SLOT_SEN_DOWN))){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"C1");
		}

/**********************************************DOSA_PLATE_SPREAD_METHODS**************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/

		else if((!(CHAPATI_BALL_HOME_SEN)) && CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == 2){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_60SEC_TIMER_EN;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"C2");
		}
		//THIRED_MOTHOD RUNING OR MOVE TO NEXT STEPS
		else if(TIMER_1_CNT_EN_AS_CHAPATI_TRIALS >= WAIT_FOR_60SEC_TIMER_EN && CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == 3){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"C3");
		}


		else if((!(CHAPATI_BALL_HOME_SEN)) && CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == 4){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"C4");
		}

/**********************************************DOSA_PLATE_SPREAD_METHODS**************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/

	/*	else if((!(CHAPATI_PRESS_HOME_SEN)) && CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == 5) {
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_100SEC_TIMER_EN;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"C5");
		}

		else if(TIMER_1_CNT_EN_AS_CHAPATI_TRIALS >= WAIT_FOR_100SEC_TIMER_EN && CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == 6){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"C6");
		}

		else if((!(CHAPATI_PRESS_HOME_SEN)) && CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == 7){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"C7");
		}

*/

/**********************************************DOSA_PLATE_SPREAD_METHODS**************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/
		//INIT_CHECK THE SENSOR STATUS OR MOVE TO NEXT STEPS;
		if((!(DOSA_U_SLOT_SEN_SPREAD)) && CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == 8){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;DOSA_SPREAD_SEQ_TEST++;
			//DECIMAL_TO_CHAR(0x97 ,AUTO_TRIAL_FLAG_CNT_EN);
			PRINTF(0x94 ,"C71");

		}
		//INIT_CHECK THE SENSOR STATUS OR MOVE TO NEXT STEPS;
	/*	else if((!(DOSA_U_SLOT_SEN_SPREAD)) && AUTO_TRIAL_FLAG_CNT_EN == 10){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			AUTO_TRIAL_FLAG_CNT_EN++;ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0xD9 ,DOSA_PLATE_SPREAD_NOTI);
		}*/

/****************************************DOSA_PLATE_SPREAD_METHOS_***********************************************************************
***************************************************************************************************************************
*******************************************************END*****************************************************************/

		//FIRST_METHODE CHECKED THAT OR MOVE TO NEXT STEP
		else if(CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == 9 && DOSA_SPREAD_SEQ_TEST == 1){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_300SEC_TIMER_EN;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"C8");
			}
		else if(TIMER_1_CNT_EN_AS_CHAPATI_TRIALS >= WAIT_FOR_300SEC_TIMER_EN && CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == 10){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"C9");
		}

		else if((!(DOSA_U_SLOT_SEN_SPREAD)) && CHAPATI_AUTO_TRIAL_FLAG_CNT_EN == 11) {
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			CHAPATI_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"C10");
		}



/**********************************************DOSA_PLATE_SPREAD_METHODS**************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/

		//SECOND_METHODS_CHECK THAT OR  MOVE TO NEXT STEPS;
		else if(ELSE_AUTO_TRIAL_FLAG_CNT_EN == 1 && (!(CHAPATI_U_SLOT_SEN_DOWN))){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"D1");
		}

		else if((!(CHAPATI_U_SLOT_SEN_UP)) && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 2){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"D2");
		}

	//THIRED_MOTHOD RUNING OR MOVE TO NEXT STEPS
	   else if((!(CHAPATI_U_SLOT_SEN_DOWN)) && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 3){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"D3");
		}

	   else if((DOSA_U_SLOT_SEN_SPREAD) && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 4) {
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"D4");
		}

/****************************************************************************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/

	   else if((CHAPATI_BALL_HOME_SEN) && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 5){
	   		TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
	   		REVERSE_SEC_CNT = CLEAR_BIT;
	   		REVERSE_SEC_CNT = WAIT_FOR_60SEC_TIMER_EN;
	   		ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
	   		PRINTF(0x94 ,"D5");
	   	}
	   		//THIRED_MOTHOD RUNING OR MOVE TO NEXT STEPS
	  else if(TIMER_1_CNT_EN_AS_CHAPATI_TRIALS >= WAIT_FOR_60SEC_TIMER_EN && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 6){
	   		TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
	   		ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
	   		PRINTF(0x94 ,"D6");
	   	}

	  else if((!(CHAPATI_BALL_HOME_SEN)) && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 7){
		  	TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
		  	ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
	   		PRINTF(0x94 ,"D7");
	   	}


/**********************************************************************************************************************************
***********************************************************************************************************************************
***************************************************************END*****************************************************************/

	/*	else if(((CHAPATI_PRESS_HOME_SEN)) && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 8) {
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_100SEC_TIMER_EN;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"D8");
		}

		else if((!(CHAPATI_PRESS_HOME_SEN)) && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 9){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"D9");
		}
*/


/**********************************************DOSA_PLATE_SPREAD_METHODS**************************************************************
**************************************************************************************************************************
******************************************************END*****************************************************************/

		//FIRST_METHODE CHECKED THAT OR MOVE TO NEXT STEP
		else if(ELSE_AUTO_TRIAL_FLAG_CNT_EN == 10 && DOSA_SPREAD_SEQ_TEST == 1){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_300SEC_TIMER_EN;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"D10");
			}
		else if(TIMER_1_CNT_EN_AS_CHAPATI_TRIALS >= WAIT_FOR_300SEC_TIMER_EN && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 11){
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_300SEC_TIMER_EN;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"D11");
		}

		else if((!(DOSA_U_SLOT_SEN_SPREAD)) && ELSE_AUTO_TRIAL_FLAG_CNT_EN == 12) {
			TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			ELSE_AUTO_TRIAL_FLAG_CNT_EN++;
			PRINTF(0x94 ,"D12");
		}


/**********************************************ALL_PROCESS_COMPLETED**************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/
		else{
			DECIMAL_TO_CHAR(0xE5 ,(REVERSE_SEC_CNT - TIMER_1_CNT_EN_AS_CHAPATI_TRIALS));
		}


	}while(CHAPATI_AUTO_TRIAL_FLAG_CNT_EN <= 10 || ELSE_AUTO_TRIAL_FLAG_CNT_EN <= 12);
	PRINTF(0xD9,"          ");
	REVERSE_SEC_CNT = CLEAR_BIT;
	TIMER_1_CNT_EN_AS_CHAPATI_TRIALS = CLEAR_BIT;
	DECIMAL_TO_CHAR(0xE5 ,(REVERSE_SEC_CNT -TIMER_1_CNT_EN_AS_CHAPATI_TRIALS));

}

/**********************************************************************************************************************************
***********************************************************************************************************************************
***************************************************************END*****************************************************************/
void _Delay_ms(unsigned int Req_Delay){
	REQ_MS_CNT= CLEAR_BIT;

	do{

	}while(REQ_MS_CNT <= Req_Delay);
}

void _Delay_ms_T(unsigned int Req_Delay){
	TEMP_REQ_MS_CNT = CLEAR_BIT;

	do{

	}while(TEMP_REQ_MS_CNT <= Req_Delay);
}

unsigned int _CH_TEMP_RESULT = CLEAR_BIT;


unsigned int SPI_12Bit_READ(void)
  {
// _BIT_SHIFT = 1080;
//_TEMP_RESULT = 135;
//_TEMP_RESULT = 135*0.25;
// 	GPIOB_MODER &= ~ (GPIOB8_MODE);
// 	GPIOB_IDR &= ~GPIOB8;
// 	LCD20x4_WRITE_4BITS(0x94 , 0);
	GPIOA_OUTPUT_DIR(GPIOA11_MODE, GPIOA11_PULL ,GPIOA11);
	GPIOA_OUTPUT_DIR(GPIOA10_MODE, GPIOA10_PULL ,GPIOA10);
	GPIOA_INPUT_DIR(GPIOA9_MODE ,GPIOA9);


	unsigned int _TEMP_RESULT = CLEAR_BIT;
  	unsigned int SHIFTING;
  	unsigned int _BIT_SHIFT;

  	SPI_CHIP_SELECT_LO; //Start the Data conversion

  	 for(SHIFTING = 0X8000; SHIFTING; SHIFTING >>= SET_BIT){
  		SPI_CLOCK_LO;
  		Delay_ms(1);
  		SPI_SDA_IN? (_BIT_SHIFT |= SHIFTING):(_BIT_SHIFT &=~ SHIFTING);
  		SPI_CLOCK_HI;
  		Delay_ms(1);

  	}
  	SPI_CHIP_SELECT_HI;
  	_TEMP_RESULT = ((_BIT_SHIFT >> 3 & 0xFFF)*0.25);
  	Delay_ms(660);

		LCD20x4_WRITE_4BITS(0x96 , 0);
		LCD20x4_WRITE_4BITS(_TEMP_RESULT%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(_TEMP_RESULT%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(_TEMP_RESULT%10+0x30 , 1);

  	return (_TEMP_RESULT);
  }


unsigned int KALMAN_FILTER(void){

	_Current_Temperature = SPI_12Bit_READ();
	Current_Convarience = P + Raw_Convarience;
	Gain = Current_Convarience / (Current_Convarience + Raw_Variation);
	P = (1 - Gain) * Current_Convarience;
	Previous_Temperature = Final_Temperature;
	Final_Temperature = Gain * (_Current_Temperature - Previous_Temperature) + Previous_Temperature;

}

unsigned int DOSA_READ_KALMAN_TEMP(void){
	unsigned int DOSA_READ_12BIT = CLEAR_BIT;
	unsigned int DOSA_KAL_FILTER = CLEAR_BIT;
	TEMPERATURE_FLAG = SET_BIT;
	Sec4 = CLEAR_BIT;

	do{
		DOSA_KAL_FILTER = KALMAN_FILTER();

		LCD20x4_WRITE_4BITS(0x96 , 0);
		LCD20x4_WRITE_4BITS(DOSA_KAL_FILTER%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(DOSA_KAL_FILTER%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(DOSA_KAL_FILTER%10+0x30 , 1);

		LCD20x4_WRITE_4BITS(0x9E , 0);
		LCD20x4_WRITE_4BITS(Sec4%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(Sec4%10+0x30 , 1);

	}while(1);
	TEMPERATURE_FLAG = CLEAR_BIT;
	Sec3 = CLEAR_BIT;
	return DOSA_KAL_FILTER;
}
/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/
/***************************************************************************************************************************
 * *************************************************************************************************************************
 * *********************************************TEMPERATURE_READ_VALUE******************************************************
 */
//unsigned int _CH_TEMP_RESULT = CLEAR_BIT;

unsigned int ROTI_SPI_12Bit_READ(void)
  {
// _BIT_SHIFT = 1080;
//_TEMP_RESULT = 135;
//_TEMP_RESULT = 135*0.25;
// 	GPIOB_MODER &= ~ (GPIOB8_MODE);
// 	GPIOB_IDR &= ~GPIOB8;
// 	LCD20x4_WRITE_4BITS(0x94 , 0);
	GPIOC_OUTPUT_DIR(GPIOC7_MODE, GPIOC7_PULL ,GPIOC7);
	GPIOC_OUTPUT_DIR(GPIOC8_MODE, GPIOC8_PULL ,GPIOC8);
	GPIOC_INPUT_DIR(GPIOC6_MODE ,GPIOC6);

	unsigned int _CH_TEMP_RESULT = CLEAR_BIT;
  	unsigned int _CH_SHIFTING = CLEAR_BIT;
  	unsigned int _CH_BIT_SHIFT = CLEAR_BIT;


  	CH_SPI_CHIP_SELECT_LO; //Start the Data conversion

  	 for(_CH_SHIFTING = 0X8000; _CH_SHIFTING; _CH_SHIFTING >>= SET_BIT){
  		CH_SPI_CLOCK_LO;
  		Delay_ms(1);
  		CH_SPI_SDA_IN? (_CH_BIT_SHIFT |= _CH_SHIFTING):(_CH_BIT_SHIFT &=~ _CH_SHIFTING);
  		CH_SPI_CLOCK_HI;
  		Delay_ms(1);
  	}
  	CH_SPI_CHIP_SELECT_HI;
  	_CH_TEMP_RESULT = ((_CH_BIT_SHIFT >> 3 & 0xFFF)*0.25);
  	Delay_ms(660);

//  	LCD20x4_WRITE_4BITS(0x9A , 0);
//  	LCD20x4_WRITE_4BITS(_CH_TEMP_RESULT%1000/100+0x30 , 1);
//  	LCD20x4_WRITE_4BITS(_CH_TEMP_RESULT%100/10+0x30 , 1);
//  	LCD20x4_WRITE_4BITS(_CH_TEMP_RESULT%10+0x30 , 1);
 /*

  			LCD20x4_WRITE_4BITS(0x9A , 0);
  			LCD20x4_WRITE_4BITS(_CH_BIT_SHIFT%10000/1000+0x30 , 1);
  			LCD20x4_WRITE_4BITS(_CH_BIT_SHIFT%1000/100+0x30 , 1);
  			LCD20x4_WRITE_4BITS(_CH_BIT_SHIFT%100/10+0x30 , 1);
  			LCD20x4_WRITE_4BITS(_CH_BIT_SHIFT%10+0x30 , 1);
*/
  	return (_CH_TEMP_RESULT);
  }


/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************SET_TEMPERATURE_IDEL_MODE*********************************************/
unsigned int TEMPERATURE_IDLE_MODE(void){
//	unsigned int TEMP_READ_DA;
	PRINTF(0xC0, TEMP_IDLE);


	EX_GPIO_ON(EX_GPIO11_PIN);
	EX_GPIO_ON(EX_GPIO12_PIN);
	TIM1_MS_CNT = CLEAR_BIT;
	TEMPERATURE_FLAG = SET_BIT;
	Sec3 = CLEAR_BIT;

	do{
	/*	FINAL_VALUE = SPI_12Bit_READ();

		LCD20x4_WRITE_4BITS(0xE4 , 0);
		LCD20x4_WRITE_4BITS(Sec3%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(Sec3%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(Sec3%10+0x30 , 1);
*/
	/*	ROTI_SPI_12Bit_READ();
*/
		if(FINAL_VALUE >= 750){
			TEMPERATURE_IDLE_MODE();
		}

		if(Sec3 >= 2 && TIMER_FLAG == 1){
			TEMP_READ_DA = SPI_12Bit_READ();
			Sec3 = CLEAR_BIT;
			TIMER_FLAG++;
		}

		if(Sec3 >= 2 && TIMER_FLAG == 2){
			TEMP2 = SPI_12Bit_READ();
			Sec3 = CLEAR_BIT;
			TIMER_FLAG = SET_BIT;
		}

		if(TEMP_READ_DA <= TEMP2){
			 FINAL_VALUE = TEMP_READ_DA;
		}
		else{
			FINAL_VALUE = TEMP2;
		}

		TEMP2 = TEMP_READ_DA;

		LCD20x4_WRITE_4BITS(0x96 , 0);
		LCD20x4_WRITE_4BITS(FINAL_VALUE%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(FINAL_VALUE%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(FINAL_VALUE%10+0x30 , 1);

	}while(FINAL_VALUE <= IDLE_TEMP_MAX);
	TIM1_MS_CNT = CLEAR_BIT;
	TEMPERATURE_FLAG = CLEAR_BIT;

//	EX_GPIO_OFF(EX_GPIO11_PIN);
//	EX_GPIO_OFF(EX_GPIO12_PIN);

}

volatile unsigned int _jung_value_cnt = CLEAR_BIT;
unsigned int TEM_FLAG_EN = CLEAR_BIT;


void TEMP_IDLE_ROTI(void){
	unsigned int DOSA_READ_TEMP = CLEAR_BIT;
	unsigned int ROTI_READ_TEMP	= CLEAR_BIT;

	unsigned int DOSA_READ_TEMP1 = CLEAR_BIT;
	unsigned int ROTI_READ_TEMP1 = CLEAR_BIT;

	unsigned int DOSA_TEMP = CLEAR_BIT;
	unsigned int ROTI_TEMP = CLEAR_BIT;

	EX_GPIO_OFF(EX_GPIO10_PIN);
	TEMPERATURE_FLAG = SET_BIT;
	TIMER_FLAG = SET_BIT;
	TEM_FLAG_EN = SET_BIT;
	Sec3 = CLEAR_BIT;
	Sec4 = CLEAR_BIT;
	CNT = CLEAR_BIT;

	do{
//ROTI_READ_TEMP
//DOSA_READ_TEMP
		if(Sec3 >= 2 && TEM_FLAG_EN == SET_BIT){
			Sec3 = CLEAR_BIT;
			DOSA_READ_TEMP1 = SPI_12Bit_READ();
			TEM_FLAG_EN = 2;
		}

		if(Sec3 >= 2 && (TEM_FLAG_EN == 2)){
			Sec3 = CLEAR_BIT;
			DOSA_TEMP = SPI_12Bit_READ();
			TEM_FLAG_EN = SET_BIT;
		}

		if(DOSA_READ_TEMP1 < DOSA_TEMP){
			DOSA_READ_TEMP = DOSA_READ_TEMP1;

		}

		else{
			DOSA_READ_TEMP = DOSA_TEMP;
		}

		DOSA_TEMP = DOSA_READ_TEMP1;

		if(Sec4 >= 2 && TIMER_FLAG == SET_BIT){
			Sec4 = CLEAR_BIT;
			ROTI_READ_TEMP1 = ROTI_SPI_12Bit_READ();
			TIMER_FLAG++;
		}

		if(Sec4 >= 2 && TEM_FLAG_EN == 2){
			Sec4 = CLEAR_BIT;
			ROTI_TEMP = ROTI_SPI_12Bit_READ();
			TIMER_FLAG = SET_BIT;

		}

		if(ROTI_READ_TEMP1 < ROTI_TEMP){
			ROTI_READ_TEMP = ROTI_READ_TEMP1;

		}

		else{
			ROTI_READ_TEMP = ROTI_TEMP;
		}

		ROTI_TEMP = ROTI_READ_TEMP1;

		if(DOSA_READ_TEMP <= DOSA_IDLE_MODE_MIN_TEMP-30){
			EX_GPIO_ON(EX_GPIO11_PIN);
			EX_GPIO_ON(EX_GPIO12_PIN);

		}

		if(DOSA_READ_TEMP > DOSA_IDLE_MODE_MIN_TEMP-30){
			EX_GPIO_OFF(EX_GPIO11_PIN);
			EX_GPIO_OFF(EX_GPIO12_PIN);

		}

		if(DOSA_READ_TEMP >= 750){
			TEMP_IDLE_ROTI();
		}



		if(ROTI_READ_TEMP <= ROTI_IDLE_MODE_MAX_TEMP-5){
			EX_GPIO_OFF(EX_GPIO10_PIN);
		}
/*
		if(ROTI_READ_TEMP >= ROTI_IDLE_MODE_MAX_TEMP){
			EX_GPIO_ON(EX_GPIO10_PIN);

		}
*/
		LCD20x4_WRITE_4BITS(0x9A , 0);
		LCD20x4_WRITE_4BITS(ROTI_READ_TEMP%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(ROTI_READ_TEMP%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(ROTI_READ_TEMP%10+0x30 , 1);

		LCD20x4_WRITE_4BITS(0x96 , 0);
		LCD20x4_WRITE_4BITS(DOSA_READ_TEMP%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(DOSA_READ_TEMP%100/10+0x30 , 1);
	 	LCD20x4_WRITE_4BITS(DOSA_READ_TEMP%10+0x30 , 1);

	 	LCD20x4_WRITE_4BITS(0x9E , 0);
	 	LCD20x4_WRITE_4BITS(_jung_value_cnt%100/10+0x30 , 1);
	 	LCD20x4_WRITE_4BITS(Sec4%10+0x30 , 1);

		}while(ROTI_READ_TEMP <= ROTI_IDLE_MODE_MAX_TEMP);
		TEMPERATURE_FLAG = CLEAR_BIT;
		EX_GPIO_ON(EX_GPIO10_PIN);
		//EX_GPIO_ON(EX_GPIO10_PIN);

}


void TEMPERATURE_COOKING_MODE(void){

	 //TIMER_1_CNT_EN_AS_DOSA_TRIALS
//	unsigned int FINAL_VALUE = CLEAR_BIT;
	TEMPERATURE_FLAG = SET_BIT;
	TEMP_READ_DA = CLEAR_BIT;
	TEMP2 = CLEAR_BIT;
	FINAL_VALUE = CLEAR_BIT;
	Sec3 = CLEAR_BIT;

	PRINTF(0xC0, TEMP_COOK);
	do{
/*		FINAL_VALUE = SPI_12Bit_READ();

		LCD20x4_WRITE_4BITS(0xE4 , 0);
		LCD20x4_WRITE_4BITS(Sec3%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(Sec3%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(Sec3%10+0x30 , 1);

		LCD20x4_WRITE_4BITS(0xD9 , 0);
		LCD20x4_WRITE_4BITS(sample_test%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(sample_test%10+0x30 , 1);

		LCD20x4_WRITE_4BITS(0xDC , 0);
		LCD20x4_WRITE_4BITS(ARM_MOVING_CNT%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(ARM_MOVING_CNT%10+0x30 , 1);
*/



		if(Sec3 >= 2 && TIMER_FLAG == 1){
			TEMP_READ_DA = SPI_12Bit_READ();
			Sec3 = CLEAR_BIT;
			TIMER_FLAG++;
		}

		if(Sec3 >= 2 && TIMER_FLAG == 2){
			TEMP2 = SPI_12Bit_READ();
			Sec3 = CLEAR_BIT;
			TIMER_FLAG = SET_BIT;
		}

		if(TEMP_READ_DA <= TEMP2){
			 FINAL_VALUE = TEMP_READ_DA;
		}
		else{
			FINAL_VALUE = TEMP2;
		}

		TEMP2 = TEMP_READ_DA;

		LCD20x4_WRITE_4BITS(0x96 , 0);
		LCD20x4_WRITE_4BITS(FINAL_VALUE%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(FINAL_VALUE%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(FINAL_VALUE%10+0x30 , 1);

	}while((FINAL_VALUE <= DOSA_MATIC_MIN_TEMP));
	TIM1_MS_CNT = CLEAR_BIT;
	TEMPERATURE_FLAG = CLEAR_BIT;
}

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/


volatile void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */
	if((TIM1_SR_REG & (1 << CLEAR_BIT)) != CLEAR_BIT){
		TIM1_SR_REG &= ~ (1 << CLEAR_BIT);
		TIM1_MS_CNT++;
		REQ_MS_CNT++;
		TEMP_REQ_MS_CNT++;
	}

	if(TIM1_MS_CNT >= 999 && INITI_TRIALS_FLAG == SET_BIT){
		TIM1_MS_CNT = CLEAR_BIT;
		TIMER_1_CNT_EN_AS_DOSA_TRIALS++;
		TIMER_1_CNT_EN_AS_CHAPATI_TRIALS++;

	}

	if(TIM1_MS_CNT >= 999 && TEMPERATURE_FLAG == SET_BIT){
		TIM1_MS_CNT = CLEAR_BIT;
		Sec3++;
		Sec4++;
		COOKING_TIME++;
	}
	if(TIM1_MS_CNT >= 999 && PRESSING_CNT_FLAG == SET_BIT){
		TIM1_MS_CNT = CLEAR_BIT;
		TIM1_PRESS_CNT++;
	}


}

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/


volatile unsigned int DOSA_NEXT_SEQ_RUN = CLEAR_BIT;

void TIM2_IRQHandler(void)
{
	if(TIM2_SR_REG & (1 << CLEAR_BIT) != CLEAR_BIT){
			TIM2_SR_REG &= ~ (1 << CLEAR_BIT);
			TIM2_MS_CNT++;
			TIM2_MS_CNT_MM++;
	}
	if(TIM2_MS_CNT >= 999){
			TIM2_MS_CNT = CLEAR_BIT;
			TIMER2_SEC_CNT++;
			TIMER2_ISR_SEC_CNT++;
	}


	  //POWDER _Dispenser function;
	  if(TIMER2_FLAG_CNT == SET_BIT){
		  TIMER2_SEC_CNT = CLEAR_BIT;
		  EX_GPIO_OFF(EX_GPIO9_PIN);
		  TIMER2_FLAG_CNT++;

	  }


	  else if(TIMER2_FLAG_CNT == 2 && TIMER2_SEC_CNT >= POWDER_DISP_SEC){
		  EX_GPIO_ON(EX_GPIO9_PIN);
		  TIMER2_SEC_CNT = CLEAR_BIT;
		  TIMER2_FLAG_CNT++;

	  }

	  //Water flow add batter mixer;
	  else if((DOSA_U_SLOT_SEN_BATTER) && TIMER2_FLAG_CNT == 3){
		  PCF8575_LCD_OFF(0X00 ,0x64);
		  EX_GPIO_OFF(EX_GPIO3_PIN);
	  	  TIMER2_SEC_CNT = CLEAR_BIT;
	  	  TIMER2_FLAG_CNT++;

	  }

	  else if(TIMER2_FLAG_CNT == 4 && TIMER2_SEC_CNT >= WATER_FLOW_SEC){
		  PCF8575_LCD_OFF(0X00 ,0x64);
		  EX_GPIO_ON(EX_GPIO3_PIN);
		  TIMER2_SEC_CNT = CLEAR_BIT;
		  TIMER2_FLAG_CNT++;
	  }

	  //Powder mixer and Sensor position check that;
	  else if(TIMER2_FLAG_CNT == 5){
		  PCF8575_LCD_ON(0x44 ,0x64);
	  	  TIMER2_SEC_CNT = CLEAR_BIT;
	  	  TIM2_MS_CNT_MM = CLEAR_BIT;
	  	  TIMER2_FLAG_CNT++;

	  }

	  //High adjustement functions
	  else if(TIMER2_FLAG_CNT == 6 && TIM2_MS_CNT_MM >= DOSA_HIGH_ADJ){
		  PCF8575_LCD_ON(0x40 ,0x64);
		  TIMER2_FLAG_CNT++;

	  }

	  else if(TIMER2_FLAG_CNT == 7 && TIMER2_SEC_CNT >= DOSA_BLENDER_SEC){
		  PCF8575_LCD_ON(0x80 ,0x64);
		  TIMER2_SEC_CNT = CLEAR_BIT;
		  TIMER2_FLAG_CNT++;

	  }

	  //Dosa Maavu spread the dosa plate and linear spread it.;
	  else if(TIMER2_FLAG_CNT == 8 && TIMER2_SEC_CNT >= DOSA_BLENDER_SEC){
		  PCF8575_LCD_ON(0x00 ,0x64);
	  	  TIMER2_FLAG_CNT++;

	  }

	  else if((DOSA_U_SLOT_SEN_SPREAD) && TIMER2_FLAG_CNT == 9){
		  PCF8575_LCD_ON(0x10 ,0x64);
		  TIM9_CCR1 = SERVO_MOTOR_30_DEG;
		  //WRITE_12BIT_ADDR(SERVO_MOTOR_EN,SERVO_MOTOR_SPD0, CLEAR_BIT);
		  TIMER2_ISR_SEC_CNT = CLEAR_BIT;
		  TIMER2_FLAG_CNT = CLEAR_BIT;
		  TIMER2_THREAD_EN = SET_BIT;		//uses ISR_CALL's Variable ;

	  }

	 else if(TIMER2_THREAD_EN == 1 && TIMER2_ISR_SEC_CNT == 0){
		  TIM9_CCR1 = SERVO_MOTOR_30_DEG;
		 //WRITE_12BIT_ADDR(SERVO_MOTOR_EN,SERVO_MOTOR_SPD2, CLEAR_BIT);
		 TIMER2_THREAD_EN++;

	  }

	 else if(TIMER2_THREAD_EN == 2 && TIMER2_ISR_SEC_CNT == 1){
		  TIM9_CCR1 = SERVO_MOTOR_50_DEG;
		 //WRITE_12BIT_ADDR(SERVO_MOTOR_EN,SERVO_MOTOR_SPD2, CLEAR_BIT);
		 TIMER2_THREAD_EN++;

	 }

	 else if(TIMER2_THREAD_EN == 3 && TIMER2_ISR_SEC_CNT == 2){
		  TIM9_CCR1 = SERVO_MOTOR_30_DEG;
		 //WRITE_12BIT_ADDR(SERVO_MOTOR_EN,SERVO_MOTOR_SPD3, CLEAR_BIT);
		 TIMER2_THREAD_EN++;

		  }

	  else if(TIMER2_THREAD_EN == 4 && TIMER2_ISR_SEC_CNT >= 3){
		  TIM9_CCR1 = SERVO_MOTOR_0_DEG;
		  //WRITE_12BIT_ADDR(SERVO_MOTOR_EN,SERVO_MOTOR_SPD1, CLEAR_BIT);
		  PCF8575_LCD_ON(0x21 ,0x64);
		  TIMER2_ISR_SEC_CNT = CLEAR_BIT;
		  TIMER2_THREAD_EN++;

	  }
	  //Batter mixer's do move to sensor position.
	  else if((DOSA_U_SLOT_SEN_BATTER) && TIMER2_THREAD_EN == 5){
		  TIM9_CCR1 = SERVO_MOTOR_0_DEG;
		  //WRITE_12BIT_ADDR(SERVO_MOTOR_EN,SERVO_MOTOR_OF, CLEAR_BIT);
		  //PCF8575_LCD_ON(0x00 ,0x64);
		  PCF8575_LCD_ON(0x01 ,0x64);
		  TIMER2_ISR_SEC_CNT = CLEAR_BIT;
	  	  TIMER2_THREAD_EN++;

	  }

	  else if((DOSA_U_SLOT_REV_SPREAD) && TIMER2_THREAD_EN == 6){
		  TIMER2_ISR_SEC_CNT = CLEAR_BIT;
		  DISH_CNT++;
	  	  ISR_FLAG_CNT = SET_BIT;
	  	  TIM2_MS_CNT_MM = CLEAR_BIT;
		  TIMER2_THREAD_EN++;
		  PCF8575_LCD_ON(0x08 ,0x64);

	  }

	  else if(TIMER2_THREAD_EN == 7 && TIM2_MS_CNT_MM >= 2000){
		  PCF8575_LCD_ON(0x00 ,0x64);
		  TIM2_MS_CNT_MM = CLEAR_BIT;
		  TIMER2_ISR_SEC_CNT = CLEAR_BIT;
		  TIMER2_THREAD_EN++;
		  CLEAN_HI;


	  }

	  else if(TIMER2_THREAD_EN == 8 && TIMER2_ISR_SEC_CNT >= 10){
		 CLEAN_LO;
		 TIM2_MS_CNT_MM = CLEAR_BIT;
		 TIMER2_THREAD_EN++;

	}

	  else if(TIMER2_THREAD_EN == 9 && TIMER2_ISR_SEC_CNT >= 20){
		  DOSA_OIL_SPRY_HI;
		  TIMER2_THREAD_EN++;

	  }

	  else if(TIMER2_THREAD_EN == 10 && TIMER2_ISR_SEC_CNT >= 24){
		  DOSA_OIL_SPRY_LO;
		  COOKING_FLAG_EN = SET_BIT;
		  COOKING_TIME  = TIMER2_ISR_SEC_CNT;
		  TIMER2_THREAD_EN++;

	  }

	  //Maavu spread the Dosa plate and Cooking Dosa;
	  else if(TIMER2_THREAD_EN == 11 && TIMER2_ISR_SEC_CNT >= COOKING_MAX_TIME){
		  PCF8575_LCD_ON(0x02 ,0x64);
		  TIMER2_ISR_SEC_CNT = CLEAR_BIT;
	  	  TIMER2_THREAD_EN++;
		  COOKING_TIME  = CLEAR_BIT;
		  COOKING_FLAG_EN = CLEAR_BIT;

	  }

	  else if((DOSA_U_SLOT_SEN_SPREAD) && TIMER2_THREAD_EN == 12){

		  PCF8575_LCD_ON(0x00 ,0x64);
		  TIMER2_ISR_SEC_CNT = CLEAR_BIT;
		  TIMER2_THREAD_EN = CLEAR_BIT;
		  DOSA_NEXT_SEQ_RUN = SET_BIT;

	  }

	  if(ISR_FLAG_CNT == SET_BIT)
	  {
		  if(SET_DISH_CNT != DISH_CNT){
			  Count_Disp++;
			  TIMER2_FLAG_CNT = SET_BIT;
			  ISR_FLAG_CNT = CLEAR_BIT;
			  TIMER2_ISR_SEC_CNT = CLEAR_BIT;
			  TIMER2_SEC_CNT = CLEAR_BIT;
		  }
		  else if(SET_DISH_CNT == DISH_CNT){
			  Count_Disp = 0;
			  ISR_FLAG_CNT = CLEAR_BIT;
			  TIMER2_FLAG_CNT = CLEAR_BIT;
			  TIMER2_ISR_SEC_CNT = CLEAR_BIT;
			  TIMER2_SEC_CNT = CLEAR_BIT;
		  }
	  }
/*
	  //wait for 1mins TO cook the dosa then Delivery of the Dosa;
	 else if(TIMER2_FLAG_CNT == 16){
	 	  TIMER2_SEC_CNT = CLEAR_BIT;
	 	  TIMER2_FLAG_CNT++;
	 }

	 else if(TIMER2_FLAG_CNT == 14 && TIMER2_SEC_CNT >= 10){
		 TIMER2_SEC_CNT = CLEAR_BIT;
	 	 TIMER2_FLAG_CNT++;
	 }*/
}

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/
volatile unsigned int COOKING_CNT_FLAG_EN = CLEAR_BIT;
volatile unsigned int COOKING_MS_CNT = CLEAR_BIT;
volatile unsigned int COOKING_SEC = CLEAR_BIT;

volatile void TIM3_IRQHandler(void)
{
	if(TIM3_SR_REG & (1 << CLEAR_BIT) != CLEAR_BIT){
			TIM3_SR_REG &= ~ (1 << CLEAR_BIT);
			TIM3_MS_CNT++;
			TIM3_MS_CNT1++;
			COOKING_MS_CNT++;
	}

	if(TIM3_MS_CNT >= 999){
			TIM3_MS_CNT = CLEAR_BIT;
			TIM3_SEC++;
			TIM3_SEC1++;
	}

	if(COOKING_MS_CNT > 999 && COOKING_CNT_FLAG_EN == SET_BIT){
			COOKING_MS_CNT = CLEAR_BIT;
			COOKING_SEC++;;
	}


	if(ROTI_MAKE_FLAG == SET_BIT){
			//Multi mode run time loop conditional;

/**************************************************************************************************
* ************************************************************************************************
* ***********************************MULTI MODE RUN *********************************************
*/


			if(((C_DOUGH_DOWN)) && SEC_SEQ_FLAG == SET_BIT){
				PCF8575_LCD_OFF(0X00 ,0x6D);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;
			}

			if((C_DOUGH_UP) && SEC_SEQ_FLAG == 2){
				PCF8575_LCD_OFF(0X00 ,0x61); //STOP
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;
			}

			if(SEC_SEQ_FLAG == 3){
				sample_test = CLEAR_BIT;
				POWDER_CNT_FLAG = false;
				PCF8575_LCD_OFF(0x00 ,0x61);
				EX_GPIO_OFF(EX_GPIO1_PIN); //Powder dispenser motor on position;
				TIM3_SEC = CLEAR_BIT;
				SEC_SEQ_FLAG++;
			}

			if(SEC_SEQ_FLAG == 4 && POWDER_CNT_FLAG == true){
				CH_DISH_CNT++;
				POWDER_CNT_FLAG = false;
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;
				EX_GPIO_ON(EX_GPIO1_PIN); //Powder dispenser motor on position;
//				PCF8575_LCD_OFF(0x00 ,0x40); //water injected
//				EX_GPIO_OFF(EX_GPIO4_PIN);
				ROTI_WATER_ON;
				ROTI_OIL_ON;

			}

			if(SEC_SEQ_FLAG == 5 && TIM3_SEC >= ROTI_W_O_FIRST_INJECT_ON){ //water and oil' 2sec increased; //(20/12/21) //pervious count = 4
				ROTI_WATER_OFF;
				ROTI_OIL_OFF;
				//PCF8575_LCD_OFF(0x00 ,0x60); //oil and water Stop
				//EX_GPIO_ON(EX_GPIO4_PIN);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(SEC_SEQ_FLAG == 6 && TIM3_SEC >= ROTI_W_O_FIRST_INJECT_OFF){
				ROTI_WATER_ON;
				ROTI_OIL_ON;
				//EX_GPIO_OFF(EX_GPIO4_PIN);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(SEC_SEQ_FLAG == 7 && TIM3_SEC >= ROTI_W_O_SECOND_INJECT_ON){//water and oil' 1sec increased;
				ROTI_WATER_OFF;
				ROTI_OIL_OFF;
				//EX_GPIO_ON(EX_GPIO4_PIN);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(SEC_SEQ_FLAG == 8 && TIM3_SEC >= ROTI_W_O_SECOND_INJECT_OFF){
				ROTI_WATER_ON;
				//PCF8575_LCD_OFF(0x00 ,0x42); //water inject
				//EX_GPIO_OFF(EX_GPIO4_PIN);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(SEC_SEQ_FLAG == 9 && TIM3_SEC >= ROTI_W_O_THIRED_INJECT_ON){//water and oil' 1sec increased; //pervious count = 3
				ROTI_WATER_OFF;
				//PCF8575_LCD_OFF(0x00 ,0x60); //oil and water Stop
				//EX_GPIO_ON(EX_GPIO4_PIN);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(SEC_SEQ_FLAG == 10 && TIM3_SEC >= ROTI_W_O_THIRED_INJECT_OFF){
				ROTI_WATER_ON;
//				EX_GPIO_OFF(EX_GPIO4_PIN);
//				PCF8575_LCD_OFF(0x00 ,0x60);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(SEC_SEQ_FLAG == 11 && TIM3_SEC >= ROTI_W_O_FOUR_INJECT_ON){  //pervious count = 3;
				ROTI_WATER_OFF;
				//EX_GPIO_ON(EX_GPIO4_PIN);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(SEC_SEQ_FLAG == 12 && TIM3_SEC >= ROTI_W_O_FOUR_INJECT_OFF){
				//EX_GPIO_OFF(EX_GPIO4_PIN);
				//PCF8575_LCD_OFF(0x00 ,0x40); //New add water
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(SEC_SEQ_FLAG == 13 && TIM3_SEC >= ROTI_W_O_FIVE_INJECT_ON){
				//EX_GPIO_ON(EX_GPIO4_PIN);
				//PCF8575_LCD_OFF(0x00 ,0x60);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(SEC_SEQ_FLAG == 14 && TIM3_SEC >= ROTI_W_O_FIVE_INJECT_OFF){
				//EX_GPIO_OFF(EX_GPIO4_PIN);
				//PCF8575_LCD_OFF(0x00 ,0x40);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(SEC_SEQ_FLAG == 15 && TIM3_SEC >= ROTI_W_O_SIX_INJECT_ON){
				//EX_GPIO_ON(EX_GPIO4_PIN);
				//PCF8575_LCD_OFF(0x00 ,0x60);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(SEC_SEQ_FLAG == 16 && TIM3_SEC >= ROTI_W_O_SIX_INJECT_OFF){
				//PCF8575_LCD_OFF(0x00 ,0x40);   //Add to oil flow
				//EX_GPIO_OFF(EX_GPIO4_PIN);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(SEC_SEQ_FLAG == 17 && TIM3_SEC >= ROTI_W_O_SEVEN_INJECT_ON){
				//PCF8575_LCD_OFF(0x00 ,0x60);
				SEC_SEQ_FLAG++;
			}

			if(SEC_SEQ_FLAG == 18 && TIM3_SEC >= ROTI_W_O_SEVEN_INJECT_OFF){ //Pervious count = 2
				//EX_GPIO_ON(EX_GPIO4_PIN);
				ROTI_OIL_ON;
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(SEC_SEQ_FLAG == 19 && TIM3_SEC >= ROTI_W_O_EIGHT_INJECT_ON){
						//EX_GPIO_OFF(EX_GPIO4_PIN);
				ROTI_OIL_OFF;
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(SEC_SEQ_FLAG == 20 && TIM3_SEC >= ROTI_W_O_EIGHT_INJECT_OFF){ //Pervious count = 2
				//EX_GPIO_ON(EX_GPIO4_PIN);
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(SEC_SEQ_FLAG == 21 && TIM3_SEC >= DOUGH_MAKE_TIME){
				SEC_SEQ_FLAG++;
				PCF8575_LCD_OFF(0X00 ,0x70); //DOWN_MOVE
				TIM3_SEC = CLEAR_BIT;
				TIM3_MS_CNT1 = CLEAR_BIT;

			}

			if(SEC_SEQ_FLAG == 22 && TIM3_MS_CNT1 >= 200){
				TIM3_SEC = CLEAR_BIT;
				TIM3_MS_CNT1 = CLEAR_BIT;
				SEC_SEQ_FLAG++;
				PCF8575_LCD_OFF(0X00 ,0x60); //DOWN_MOVE

			}

			if(SEC_SEQ_FLAG == 23 && TIM3_SEC >= 10){
				TIM3_SEC = CLEAR_BIT;
				SEC_SEQ_FLAG++;
				PCF8575_LCD_OFF(0X00 ,0x68); //DOWN_MOVE

			}

			if(((C_DOUGH_UP)) && SEC_SEQ_FLAG == 24){
				TIM3_SEC = CLEAR_BIT;
				TIM3_MS_CNT1 = CLEAR_BIT;
				SEC_SEQ_FLAG++;
				PCF8575_LCD_OFF(0X00 ,0x60); //DOWN_MOVE

			}

			if(SEC_SEQ_FLAG == 25 && TIM3_SEC >= 10){
				SEC_SEQ_FLAG++;
				PCF8575_LCD_OFF(0X00 ,0x70); //DOWN_MOVE
				TIM3_SEC = CLEAR_BIT;

			}

			if(((C_DOUGH_DOWN)) && SEC_SEQ_FLAG == 26){
				PCF8575_LCD_OFF(0X00 ,0x64); //DOWN_MOVE
				SEC_SEQ_FLAG++;
				TIM3_SEC = CLEAR_BIT;
			}

			if((CHAPATI_ARM_HOME) && SEC_SEQ_FLAG == 27){
				ARM_MOVING_CNT = CLEAR_BIT;
				PRESSING_ENCODER_CNT = ROTI_PR_ENCODER_CNT_MAX;
				ARM_MOVE_CNT_FLAG_EN = SET_BIT;
				EX_GPIO_PWM_ON(EX_GPIO8_PIN ,2560);
				ARM_MOVE_FWD_HI;
				ARM_MOVE_REV_LO;
				TIM3_SEC = CLEAR_BIT;
				SEC_SEQ_FLAG++;

			}

			if(SEC_SEQ_FLAG == 28 && ARM_MOVE_CNT_FLAG_EN == 2){
				ARM_MOVE_CNT_FLAG_EN = CLEAR_BIT;
				TIM3_SEC = CLEAR_BIT;
				SEC_SEQ_FLAG++;
			}

			if(SEC_SEQ_FLAG == 29 && TIM3_SEC >= 2){
				ARM_MOVE_FWD_LO;
				ARM_MOVE_REV_HI;
				TIM3_SEC = CLEAR_BIT;
				SEC_SEQ_FLAG++;
			}

			if(!(CHAPATI_ARM_HOME) && SEC_SEQ_FLAG == 30){
				ARM_MOVE_FWD_LO;
				ARM_MOVE_REV_HI;
			}

			if((CHAPATI_ARM_HOME) && SEC_SEQ_FLAG == 30){
				EX_GPIO_PWM_ON(EX_GPIO8_PIN ,0);
				ARM_MOVE_FWD_LO;
				ARM_MOVE_REV_LO;
				CH_PRESS_FLAG = false;
				POWDER_CNT_FLAG = false;
				Pressing_cnt = CLEAR_BIT;
				sample_test = CLEAR_BIT;
				ISR_PRALL_RUN_FLAG = SET_BIT;
				TIM3_SEC = CLEAR_BIT;
				SEC_SEQ_FLAG++;
				ISR_PR_FLAG = SET_BIT;

			}

			if(SEC_SEQ_FLAG == 31 ){
				PRESS_FLAG = SET_BIT;
				CH_CNT_FLAG_CHECK = SET_BIT;
				ROTI_MAKE_FLAG = CLEAR_BIT;
				SEC_SEQ_FLAG = CLEAR_BIT;

			}

/**************************************************************************************************
 * ************************************************************************************************
 * ***********************************SINGLE MODE RUN *********************************************
 */

			if(((C_DOUGH_DOWN)) && TIM3_FLAG == SET_BIT){
				PCF8575_LCD_OFF(0X00 ,0x6C);
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;
			}

			if(((C_DOUGH_UP)) && TIM3_FLAG == 2){
				PCF8575_LCD_OFF(0X00 ,0x64); //STOP
				//PCF8575_LCD_OFF(0X00 ,0x74); //DOWN_MOVE
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;
			}

			if(TIM3_FLAG == 3){
				TIM3_FLAG++;
				sample_test = CLEAR_BIT;
				POWDER_CNT_FLAG = false;
				PCF8575_LCD_OFF(0x00 ,0x60);
				EX_GPIO_OFF(EX_GPIO1_PIN); //Powder dispenser motor on position;
				TIM3_SEC = CLEAR_BIT;
			}

			if(TIM3_FLAG == 4 && POWDER_CNT_FLAG == true){
				CH_DISH_CNT++;
				POWDER_CNT_FLAG = false;
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;
				ROTI_WATER_ON;
				ROTI_OIL_ON;
				EX_GPIO_ON(EX_GPIO1_PIN); //Powder dispenser motor on position;
				//PCF8575_LCD_OFF(0x00 ,0x40); //water injected
				//EX_GPIO_OFF(EX_GPIO4_PIN);  //Oil inject;

			}

			if(TIM3_FLAG == 5 && TIM3_SEC >= ROTI_W_O_FIRST_INJECT_ON){ //water and oil' 2sec increased; //(20/12/21) //pervious count = 4
				ROTI_WATER_OFF;
				ROTI_OIL_OFF;
				//PCF8575_LCD_OFF(0x00 ,0x60); //oil and water Stop
				//EX_GPIO_ON(EX_GPIO4_PIN);
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(TIM3_FLAG == 6 && TIM3_SEC >= ROTI_W_O_FIRST_INJECT_OFF){
				ROTI_WATER_ON;
				ROTI_OIL_ON;
				//EX_GPIO_OFF(EX_GPIO4_PIN); //oil inject
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(TIM3_FLAG == 7 && TIM3_SEC >= ROTI_W_O_SECOND_INJECT_ON){//water and oil' 1sec increased;
				ROTI_WATER_OFF;
				ROTI_OIL_OFF;
				//EX_GPIO_ON(EX_GPIO4_PIN); //Onject stop
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(TIM3_FLAG == 8 && TIM3_SEC >= ROTI_W_O_SECOND_INJECT_OFF){
				ROTI_WATER_ON;
				//PCF8575_LCD_OFF(0x00 ,0x40); //water inject
				//EX_GPIO_OFF(EX_GPIO4_PIN);   //oil inject
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(TIM3_FLAG == 9 && TIM3_SEC >= ROTI_W_O_THIRED_INJECT_ON){//water and oil' 1sec increased; //pervious count = 3
				ROTI_WATER_OFF;
				//PCF8575_LCD_OFF(0x00 ,0x60); //oil and water Stop
				//EX_GPIO_ON(EX_GPIO4_PIN);    //oil inject stop
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(TIM3_FLAG == 10 && TIM3_SEC >= ROTI_W_O_THIRED_INJECT_OFF){
				ROTI_WATER_ON;
				//ROTI_OIL_ON;
				//EX_GPIO_OFF(EX_GPIO4_PIN);  //oil inject
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(TIM3_FLAG == 11 && TIM3_SEC >= ROTI_W_O_FOUR_INJECT_ON){  //pervious count = 3;
				ROTI_WATER_OFF;
				//ROTI_OIL_OFF;
				//EX_GPIO_ON(EX_GPIO4_PIN);  //oil inject stop
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(TIM3_FLAG == 12 && TIM3_SEC >= ROTI_W_O_FOUR_INJECT_OFF){
//				ROTI_WATER_ON;
//				ROTI_OIL_ON;
				//	EX_GPIO_OFF(EX_GPIO4_PIN);  //oil inject
			//	PCF8575_LCD_OFF(0x00 ,0x40); //New add water
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(TIM3_FLAG == 13 && TIM3_SEC >= ROTI_W_O_FIVE_INJECT_ON){
//				ROTI_WATER_OFF;
//				ROTI_OIL_OFF;
				//EX_GPIO_ON(EX_GPIO4_PIN);   //oil inject stop
				//PCF8575_LCD_OFF(0x00 ,0x60);
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(TIM3_FLAG == 14 && TIM3_SEC >= ROTI_W_O_FIVE_INJECT_OFF){
		//		ROTI_WATER_ON;
			//	ROTI_OIL_ON;
				//	EX_GPIO_OFF(EX_GPIO4_PIN);  //oil inject
			//	PCF8575_LCD_OFF(0x00 ,0x40);
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(TIM3_FLAG == 15 && TIM3_SEC >= ROTI_W_O_SIX_INJECT_ON){

			//	ROTI_WATER_OFF;
			//	ROTI_OIL_OFF;
				//EX_GPIO_ON(EX_GPIO4_PIN);   //oil inject stop
				//PCF8575_LCD_OFF(0x00 ,0x60);
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(TIM3_FLAG == 16 && TIM3_SEC >= ROTI_W_O_SIX_INJECT_OFF){
			//	PCF8575_LCD_OFF(0x00 ,0x40);   //Add to oil flow
	//			ROTI_WATER_ON;
				//EX_GPIO_OFF(EX_GPIO4_PIN);     //oil inject
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(TIM3_FLAG == 17 && TIM3_SEC >= ROTI_W_O_SEVEN_INJECT_ON){
				//PCF8575_LCD_OFF(0x00 ,0x60);
				//EX_GPIO_ON(EX_GPIO4_PIN);   //oil inject stop
			//	ROTI_WATER_OFF;
				ROTI_OIL_ON;
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;
			}

			if(TIM3_FLAG == 18 && TIM3_SEC >= ROTI_W_O_SEVEN_INJECT_OFF){ //Pervious count = 2
				//EX_GPIO_ON(EX_GPIO4_PIN);   //oil inject stop
			//	ROTI_WATER_OFF;
				ROTI_OIL_OFF;
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}
			if(TIM3_FLAG == 19 && TIM3_SEC >= ROTI_W_O_EIGHT_INJECT_ON){
				//EX_GPIO_OFF(EX_GPIO4_PIN);
			//	ROTI_WATER_ON;
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if(TIM3_FLAG == 20 && TIM3_SEC >= ROTI_W_O_EIGHT_INJECT_OFF){ //Pervious count = 2
				//EX_GPIO_ON(EX_GPIO4_PIN);   //oil inject stop
			//	ROTI_WATER_OFF;
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;
			}

			if(TIM3_FLAG == 21 && TIM3_SEC >= DOUGH_MAKE_TIME){
				TIM3_FLAG++;
				PCF8575_LCD_OFF(0X00 ,0x70); //DOWN_MOVE
				TIM3_SEC = CLEAR_BIT;
				TIM3_MS_CNT1 = CLEAR_BIT;

			}

			if(TIM3_FLAG == 22 && TIM3_MS_CNT1 >= 200){
				TIM3_SEC = CLEAR_BIT;
				TIM3_MS_CNT1 = CLEAR_BIT;
				TIM3_FLAG++;
				PCF8575_LCD_OFF(0X00 ,0x60); //DOWN_MOVE

			}

			if(TIM3_FLAG == 23 && TIM3_SEC >= 10){
				TIM3_SEC = CLEAR_BIT;
				TIM3_FLAG++;
				PCF8575_LCD_OFF(0X00 ,0x68); //DOWN_MOVE

			}

			if(((C_DOUGH_UP)) && TIM3_FLAG == 24){
				TIM3_SEC = CLEAR_BIT;
				TIM3_MS_CNT1 = CLEAR_BIT;
				TIM3_FLAG++;
				PCF8575_LCD_OFF(0X00 ,0x60); //DOWN_MOVE

			}

			if(TIM3_FLAG == 25 && TIM3_SEC >= 10){
				TIM3_FLAG++;
				PCF8575_LCD_OFF(0X00 ,0x70); //DOWN_MOVE
				TIM3_SEC = CLEAR_BIT;

			}

			if(((C_DOUGH_DOWN)) && TIM3_FLAG == 26){
				PCF8575_LCD_OFF(0X00 ,0x64); //DOWN_MOVE
				TIM3_FLAG++;
				TIM3_SEC = CLEAR_BIT;

			}

			if((CHAPATI_ARM_HOME) && TIM3_FLAG == 27){
				ARM_MOVING_CNT = CLEAR_BIT;
				ARM_MOVE_CNT_FLAG_EN = SET_BIT;
				EX_GPIO_PWM_ON(EX_GPIO8_PIN ,2560);
				ARM_MOVE_FWD_HI;
				ARM_MOVE_REV_LO;
				TIM3_SEC = CLEAR_BIT;
				TIM3_FLAG++;

			}

			if(TIM3_FLAG == 28 && ARM_MOVE_CNT_FLAG_EN == 2){
				ARM_MOVE_CNT_FLAG_EN = CLEAR_BIT;
				TIM3_SEC = CLEAR_BIT;
				TIM3_FLAG++;
			}

			if(TIM3_FLAG == 29 && TIM3_SEC >= 2){
				ARM_MOVE_FWD_LO;
				ARM_MOVE_REV_HI;
				TIM3_SEC = CLEAR_BIT;
				TIM3_FLAG++;
			}

			if(!(CHAPATI_ARM_HOME) && TIM3_FLAG == 30){
				ARM_MOVE_FWD_LO;
				ARM_MOVE_REV_HI;
			}

			if((CHAPATI_ARM_HOME) && TIM3_FLAG == 30){
				EX_GPIO_PWM_ON(EX_GPIO8_PIN ,0);
				ARM_MOVE_FWD_LO;
				ARM_MOVE_REV_LO;
				CH_PRESS_FLAG = false;
				POWDER_CNT_FLAG = false;
				Pressing_cnt = CLEAR_BIT;
				sample_test = CLEAR_BIT;
				ISR_PRALL_RUN_FLAG = SET_BIT;
				TIM3_FLAG++;
			}

			if(TIM3_FLAG == 31){
				ISR_PR_FLAG = SET_BIT;
				PRESS_FLAG = SET_BIT;
				CH_CNT_FLAG_CHECK = SET_BIT;
				ROTI_MAKE_FLAG = CLEAR_BIT;
				TIM3_FLAG = CLEAR_BIT;

			}
	}

/**************************************************************************************************
* ************************************************************************************************
* ***********************************PRESSING MODE RUN *********************************************
*/


	if(PRESS_FLAG == SET_BIT){

			if(ISR_PRALL_RUN_FLAG == SET_BIT){
				PCF8575_LCD_ON(0x00 ,0x65);
				CH_PRESS_FLAG = false;
				Pressing_cnt = CLEAR_BIT;
				TIM3_SEC1 = CLEAR_BIT;
				ISR_PRALL_RUN_FLAG++;
			}

			if(ISR_PRALL_RUN_FLAG == 2 && CH_PRESS_FLAG == true ){
				TIM3_SEC1 = CLEAR_BIT;
				CH_PRESS_FLAG = false;
				PCF8575_LCD_ON(0x00 ,0x64);
				TIM3_MS_CNT1 = CLEAR_BIT;
				ISR_PRALL_RUN_FLAG++;
			}

			if(ISR_PRALL_RUN_FLAG == 3 && DOUGH_ENABLE_FLAG == SET_BIT){
				TIM3_SEC1 = CLEAR_BIT;
				TIM3_MS_CNT1 = CLEAR_BIT;
				PCF8575_LCD_ON(0x00 ,0x60);
				ISR_PRALL_RUN_FLAG++;
			}

			if(ISR_PRALL_RUN_FLAG == 4 && TIM3_SEC1 >= ROTI_PR_WAITING_TIME){
				EX_GPIO_ON(EX_GPIO13_PIN);
				TIM3_SEC1 = CLEAR_BIT;
				TIM3_MS_CNT1 = CLEAR_BIT;
				DOUGH_ENABLE_FLAG++; //Previous value = 4;
				ISR_PRALL_RUN_FLAG++;
			}

			if(ISR_PRALL_RUN_FLAG == 3 && DOUGH_DISABLE_FLAG == SET_BIT){
				TIM3_SEC1 = CLEAR_BIT;
				TIM3_MS_CNT1 = CLEAR_BIT;
				ISR_PRALL_RUN_FLAG++;
				DOUGH_DISABLE_FLAG++;

			}

			if(ISR_PRALL_RUN_FLAG == 4 && TIM3_SEC1 >= ROTI_PR_WAITING_TIME){
				TIM3_SEC1 = CLEAR_BIT;
				//PRESS_UP_POS_HI;
				EX_GPIO_ON(EX_GPIO13_PIN);
				TIM3_MS_CNT1 = CLEAR_BIT;
				ISR_PRALL_RUN_FLAG++;
			}

			if(ISR_PRALL_RUN_FLAG == 5 && TIM3_MS_CNT1 >= ROTI_PR_INIT_UP_TIME && DOUGH_ENABLE_FLAG == 2){ //set Previous value = 4;
				PCF8575_LCD_ON(0x00 ,0x60);
				//PRESS_UP_POS_LO;
				EX_GPIO_OFF(EX_GPIO13_PIN);
				TIM3_MS_CNT1 = CLEAR_BIT;
				TIM3_SEC1 = CLEAR_BIT;
				ISR_PRALL_RUN_FLAG++;
				DOUGH_ENABLE_FLAG++;   //set Previous value = 5;
				COOKING_MS_CNT = CLEAR_BIT;
				COOKING_SEC = CLEAR_BIT;
				COOKING_CNT_FLAG_EN = SET_BIT;

			}

			if(ISR_PRALL_RUN_FLAG == 5 && TIM3_MS_CNT1 >= ROTI_PR_INIT_UP_TIME && DOUGH_DISABLE_FLAG == 2){
				TIM3_MS_CNT1 = CLEAR_BIT;
				TIM3_SEC1 = CLEAR_BIT;
				//PRESS_UP_POS_LO;
				EX_GPIO_OFF(EX_GPIO13_PIN);
				PCF8575_LCD_ON(0x00 ,0x64);
				ISR_PRALL_RUN_FLAG++;
				DOUGH_DISABLE_FLAG++;
				COOKING_MS_CNT = CLEAR_BIT;
				COOKING_SEC = CLEAR_BIT;
				COOKING_CNT_FLAG_EN = SET_BIT;
			}

			if(ISR_PRALL_RUN_FLAG == 6 && COOKING_SEC >= ROTI_COOKING_TIME){
				PCF8575_LCD_ON(0x00 ,0x65); //while thre run Move to down position
				//EX_GPIO_ON(EX_GPIO13_PIN); //while thre run Move to top position
				//PRESS_UP_POS_HI;
				COOKING_SEC = CLEAR_BIT;
				TIM3_SEC1 = CLEAR_BIT;
				COOKING_CNT_FLAG_EN = CLEAR_BIT;
				TIM3_MS_CNT1 = CLEAR_BIT;
				ISR_PRALL_RUN_FLAG++;
			}

			if(ISR_PRALL_RUN_FLAG == 7 && TIM3_MS_CNT1 >= ROTI_PR_INIT_DOWN_TIME && DOUGH_ENABLE_FLAG == 3){
				TIM3_MS_CNT1 = CLEAR_BIT;
				PCF8575_LCD_ON(0x00 ,0x60);
				//PRESS_UP_POS_LO;
				//EX_GPIO_OFF(EX_GPIO13_PIN);
				COOKING_SEC = CLEAR_BIT;
				COOKING_MS_CNT = CLEAR_BIT;
				COOKING_SEC = CLEAR_BIT;
				COOKING_CNT_FLAG_EN = SET_BIT;
				ISR_PRALL_RUN_FLAG++;
				DOUGH_ENABLE_FLAG++;
			}

			if(ISR_PRALL_RUN_FLAG == 7 && TIM3_MS_CNT1 >= ROTI_PR_INIT_DOWN_TIME && DOUGH_DISABLE_FLAG == 3){
				TIM3_MS_CNT1 = CLEAR_BIT;
				PCF8575_LCD_ON(0x00 ,0x64);
				//PRESS_UP_POS_LO;
				EX_GPIO_OFF(EX_GPIO13_PIN);
				COOKING_SEC = CLEAR_BIT;
				COOKING_MS_CNT = CLEAR_BIT;
				COOKING_SEC = CLEAR_BIT;
				COOKING_CNT_FLAG_EN = SET_BIT;
				ISR_PRALL_RUN_FLAG++;
				DOUGH_ENABLE_FLAG++;
				DOUGH_DISABLE_FLAG++;
			}

			if(ISR_PRALL_RUN_FLAG == 8 &&  COOKING_SEC >= ROTI_COOKING_TIME_DOWN_SIDE){
				EX_GPIO_ON(EX_GPIO13_PIN);
				COOKING_SEC = CLEAR_BIT;
				TIM3_SEC1 = CLEAR_BIT;
				COOKING_CNT_FLAG_EN = CLEAR_BIT;
				TIM3_MS_CNT1 = CLEAR_BIT;
				ISR_PRALL_RUN_FLAG++;
				PCF8575_LCD_ON(0x00 ,0x60);
				PRESSING_TOP_MOVE_FLAG_EN = SET_BIT;

			}

			if(ISR_PRALL_RUN_FLAG == 9 && (CHAPATI_PRESS_HOME_SEN) && DOUGH_ENABLE_FLAG == 4){
				DOUGH_ENABLE_FLAG = CLEAR_BIT;
				PRESSING_TOP_MOVE_FLAG_EN = CLEAR_BIT;
				//PRESS_UP_POS_LO;
				EX_GPIO_OFF(EX_GPIO13_PIN);
				PCF8575_LCD_ON(0x00 ,0x60);
				TIM3_SEC1 = CLEAR_BIT;
				ISR_PRALL_RUN_FLAG = CLEAR_BIT;
				PRESS_FLAG = CLEAR_BIT;

			}

			if(ISR_PRALL_RUN_FLAG == 9 && (CHAPATI_PRESS_HOME_SEN) && DOUGH_DISABLE_FLAG == 4){
				DOUGH_DISABLE_FLAG = CLEAR_BIT;
				//PRESS_UP_POS_LO;
				EX_GPIO_OFF(EX_GPIO13_PIN);
				PCF8575_LCD_ON(0x00 ,0x64);
				TIM3_SEC1 = CLEAR_BIT;
				ISR_PRALL_RUN_FLAG = CLEAR_BIT;
				PRESS_FLAG = CLEAR_BIT;

			}
	}

			if(CH_CNT_FLAG_CHECK == SET_BIT){

				if(SET_DISH_CNT != CH_DISH_CNT){
					SEC_SEQ_FLAG = SET_BIT;
					TIM3_SEC1 = CLEAR_BIT;
					TIM3_MS_CNT1 = CLEAR_BIT;
					CH_CNT_FLAG_CHECK = CLEAR_BIT;
					ROTI_MAKE_FLAG = SET_BIT;
					DOUGH_ENABLE_FLAG = SET_BIT;
					Pressing_cnt = CLEAR_BIT;

				}

				if(SET_DISH_CNT == CH_DISH_CNT){
					ROTI_MAKE_FLAG = CLEAR_BIT;
					TIM3_FLAG = CLEAR_BIT;
					TIM3_SEC1 = CLEAR_BIT;
					TIM3_MS_CNT1 = CLEAR_BIT;
					CH_CNT_FLAG_CHECK = CLEAR_BIT;
					DOUGH_DISABLE_FLAG = SET_BIT;
				}

			}


}

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/
//volatile uint16_t CountValue3 = 0;
//volatile uint16_t Sec3 = 0;

void TIM4_IRQHandler(void)
{
	if((TIM4_SR_REG & (1 << CLEAR_BIT)) != CLEAR_BIT){
			TIM4_SR_REG &= ~ (1 << CLEAR_BIT);
			TIM4_MS_CNT++;

			if(TIM4_MS_CNT >= 999){
				TIM4_MS_CNT = CLEAR_BIT;
				CNT++;
				//Sec3++;
			}

		}
}

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/
volatile uint16_t ExtenalCount = 0;

void EXTI1_IRQHandler(void)
{
	if((EXTI_PR & TR1)){ //Wait for pending status;
		EXTI_PR |= TR1;	//Clear the pending status;
		ExtenalCount = 1; //External Increment flag enable;
	}
}

/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/

void EXTI3_IRQHandler(void)
{
	if((EXTI_PR & TR3) && PRESSING_TOP_MOVE_FLAG_EN == SET_BIT){ //Wait for pending status;
		EXTI_PR |= TR3;	//Clear the pending status;
		PRESSING_TOP_MOVE_ENCODER_CNT++;; //External Increment flag enable;
	}

	if(PRESSING_TOP_MOVE_ENCODER_CNT >= 10){
		PRESSING_TOP_MOVE_ENCODER_CNT = CLEAR_BIT;
		//PRESS_UP_POS_LO;
		//EX_GPIO_OFF(EX_GPIO13_PIN);
		PRESSING_TOP_MOVE_FLAG_EN = CLEAR_BIT;
	}

}
/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/


void EXTI9_5_IRQHandler(void)
{

	if((EXTI_PR & TR9) && ISR_PR_FLAG == SET_BIT){ //Wait for pending status;
		EXTI_PR |= TR9;	//Clear the pending status;
		Pressing_cnt++; //External Increment flag enable;
	}


//The previous value = 4500;
	if(Pressing_cnt >= PRESSING_ENCODER_CNT){
		Pressing_cnt = CLEAR_BIT;
		PCF8575_LCD_ON(0x00 ,0x64);
		TIM1_PRESS_CNT = CLEAR_BIT;
		TIM3_SEC1 = CLEAR_BIT;
		ISR_PR_FLAG = CLEAR_BIT;
		CH_PRESS_FLAG = true;
	}
	else{
		_jung_value_cnt++;
	}
}


volatile void EXTI15_10_IRQHandler(void)
{
	if((EXTI_PR & TR12)){ //Wait for pending status;
		EXTI_PR |= TR12;	//Clear the pending status;
		//Findout_rpm++; //External Increment flag enable;
		sample_test++;
	}

	if(sample_test >= ROTI_POWDER_DISP_CNT){ //pervious count = 229
		sample_test = CLEAR_BIT;
		EX_GPIO_ON(EX_GPIO1_PIN); //Powder dispenser motor on position;
		POWDER_CNT_FLAG = true;

	}
//
//	if((EXTI_PR & TR15) && ARM_MOVE_CNT_FLAG_EN == SET_BIT){
//		EXTI_PR |= TR15;	//Clear the pending status;
//		ARM_MOVING_CNT++;
//	}

	if(ARM_MOVING_CNT >= ARM_MOVING_FOR_CNT){
		ARM_MOVING_CNT = CLEAR_BIT;
		ARM_MOVE_FWD_LO;
		ARM_MOVE_REV_LO;
		ARM_MOVE_CNT_FLAG_EN = 2;
	}

	if((EXTI_PR & TR14)){ //&& ARM_MOVE_CNT_FLAG_EN == SET_BIT){
		EXTI_PR |= TR14;	//Clear the pending status;
		ARM_MOVING_CNT++;
		//_jung_value_cnt++;
	}

	if((EXTI_PR & TR13)){
		EXTI_PR |= TR13;	//Clear the pending status;
		Pressing_cnt++;
	}

	//The previous value = 4500;
	if(Pressing_cnt >= PRESSING_ENCODER_CNT){
		Pressing_cnt = CLEAR_BIT;
		PCF8575_LCD_ON(0x00 ,0x64);
		TIM1_PRESS_CNT = CLEAR_BIT;
		TIM3_SEC1 = CLEAR_BIT;
		ISR_PR_FLAG = CLEAR_BIT;
		CH_PRESS_FLAG = true;
	}

}


//#define CHAPATI_PRESS_HOME_SEN 				((GPIOB_IDR & GPIOx_PIN_3))

/******************************************************CHAPATI SPREAD_******************************************************
 * *************************************************************************************************************************
 */
unsigned int CHAPATI_FLG  = CLEAR_BIT;


void CHAPATI_INIT(void){
	TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
	REVERSE_SEC_CNT = CLEAR_BIT;
	REVERSE_SEC_CNT = WAIT_FOR_300SEC_TIMER_EN;
	do{

		if((DOSA_U_SLOT_SEN_SPREAD) && CHAPATI_FLG == CLEAR_BIT){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_300SEC_TIMER_EN;
			PCF8575_LCD_ON(0x01 ,0x64);
			CHAPATI_FLG++;

			}

		if((DOSA_U_SLOT_REV_SPREAD) && CHAPATI_FLG == SET_BIT){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			PCF8575_LCD_ON(0x00 ,0x64);
		    CHAPATI_FLG++;

		}
		else{
			DECIMAL_TO_CHAR(0xE5 ,(REVERSE_SEC_CNT - TIMER_1_CNT_EN_AS_DOSA_TRIALS));
		}

	}while((CHAPATI_FLG < 2));
	CHAPATI_FLG = CLEAR_BIT;
	TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;

}


/****************************************************************************************************************************
* **************************************************************************************************************************
* ******************************************************END*****************************************************************/

void demo(void){
		do{


//			 TIM9_CCR1 = 3999;
//			 Delay_ms(1000);
//			 TIM9_CCR1 = 2399;
//			 Delay_ms(1000);
//			 TIM9_CCR1 = 1999;
//			 Delay_ms(1000);
//			 TIM9_CCR1 = 1199;
//			 Delay_ms(1000);



		//	ARM_MOVE_FWD_HI;
		//	ARM_MOVE_REV_LO;
			 CLEAN_HI;
			//TIM9_CCR1 = 3999;
			//ARM_MOVE_FWD_HI;
			//ARM_MOVE_REV_LO;
		//PRESS_DOWN_POS_LO;
		//PCF8575_LCD_ON(0x00 ,0x64);
//	    unsigned int External_temp_value = EXTERNAL_ISR_DEMO1?1:0;
//		LCD20x4_WRITE_4BITS(0x9E , 0);
//		//LCD20x4_WRITE_4BITS(Sec4%100/10+0x30 , 1);
//		LCD20x4_WRITE_4BITS(External_temp_value%10+0x30 , 1);
		}while(1);

}

//void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
//{
//  /* Check the parameters */
//  assert_param(IS_NVIC_DEVICE_IRQ(IRQn));
//
//  /* Enable interrupt */
//  NVIC_EnableIRQ(IRQn);
//}
/************************************END*****************************************************/
void DOSA_ISR_FLAG_CLEAR(void){
	 Count_Disp = CLEAR_BIT;
	 ISR_FLAG_CNT = CLEAR_BIT;
	 TIMER2_FLAG_CNT = CLEAR_BIT;
	 TIMER2_ISR_SEC_CNT = CLEAR_BIT;
	 TIMER2_SEC_CNT = CLEAR_BIT;

}

void DOSA_IST_FLAG_ENABLE(void){
	Count_Disp = CLEAR_BIT;
	ISR_FLAG_CNT = CLEAR_BIT;
	TIM2_MS_CNT = CLEAR_BIT;
	TIM2_MS_CNT_MM = CLEAR_BIT;
	TIMER2_FLAG_CNT = SET_BIT;
	TIMER2_SEC_CNT = CLEAR_BIT;
	SEL_DISH = CLEAR_BIT;
}

//#define D_WATER_FLOW_SEN    ((GPIOD_IDR & GPIOx_PIN_4))
//#define C_WATER_FLOW_SEN    ((GPIOD_IDR & GPIOx_PIN_3))
//#define D_OIL_FLOW_SEN      ((GPIOD_IDR & GPIOx_PIN_2))
//#define C_OIL_FLOW_SEN		((GPIOD_IDR & GPIOx_PIN_1))
//#define NON_CONTACT_SEN     ((GPIOD_IDR & GPIOx_PIN_0))
//#define NON_CONTACT_SEN1    ((GPIOC_IDR & GPIOx_PIN_12))
//#define NON_CONTACT_SEN2    ((GPIOC_IDR & GPIOx_PIN_11))

unsigned int COOKING_TEMP_DOSA = CLEAR_BIT;
unsigned int COOKING_TEMP_ROTI = CLEAR_BIT;

int main ( ) {

	sprintf(TCP_SERVER_CONNECTION ,"%s%s%s%s",TCP_SERVER_START ,TCP_SERVER_CMD ,TCP_SERVER_URLS ,TCP_SERVER_PORT);

#ifndef BASIC_REG_CONFIG
	SYSTEM_CONFIG();
	GPIOx_CLOCK_ENABLE();
	TIMER6_CONFIG();
	Delay_us(5000); //500ms value uploaded.
	Delay_us(5000); //500ms value uploaded
#endif

#ifndef _20x4_LCD_CONFIG
	I2C1_INIT();
	I2C2_INIT();
	LCD20x4_INIT(0x4E ,20 ,4); //Lcd device ID Address pin High = 0x4E. address pin low = 0x7E.
	LCD20x4_BEGIN();   //user select to address mode 4bit address and 8bit address choise the hex decimal values.
    BACK_LIGHT();  //
    PRINTF(0x80 ,"AUTO FOOD VENDING   ");
    PRINTF(0xD4 ,"Noti:");
    PRINTF(0xE3 ,"S:");
    PRINTF(0x94 ,"T:          Sec:");
    //94 95 96 98 99 A0 A1 A2 A3 A4 A5 A6 A7 A8 a9 aa ab
   // ESP8266_AT_CMD_INIT();
    //WRITE_4BITS(0x99 , 0);
#endif

#ifndef TIMERS_CONFIG
    TIMER1_CONFIG();
    TIMER2_CONFIG();
    TIMER3_CONFIG();
    TIMER4_CONFIG();
    TIMER6_CONFIG();
    TIMER_9_CONFIG();
#endif


#ifndef EX_GPIO_PCA9685
	I2C3_INIT();
	I2C3_RESTART();Delay_us(5);
	PCA9685_INIT();
	EX_GPIO_ON(EX_GPIO1_PIN); //Powder dispenser motor on position;

#endif

#ifndef CLEAR_TO_ALL_PIN_DISABLE


	//Extrnal GPIO as Cleared;
	EX_GPIO_ON(EX_GPIO1_PIN); //Powder dispenser motor on position;
	EX_GPIO_ON(EX_GPIO3_PIN);
	EX_GPIO_ON(EX_GPIO4_PIN);
	EX_GPIO_ON(EX_GPIO5_PIN);
	EX_GPIO_ON(EX_GPIO6_PIN);
	EX_GPIO_OFF(EX_GPIO8_PIN);  //This pin used as chapathi roller.(OFF_state)

	EX_GPIO_ON(EX_GPIO9_PIN);
	EX_GPIO_ON(EX_GPIO10_PIN);
	EX_GPIO_OFF(EX_GPIO11_PIN);
	EX_GPIO_OFF(EX_GPIO12_PIN);
	//EX_GPIO_ON(EX_GPIO8_PIN); //This pin used as chapathi roller.(ON_state)
//	EX_GPIO_PWM_ON(EX_GPIO8_PIN ,2560);

	PCF8575_LCD_ON(0x00 ,0x64);

	/*ARM_FOR/REV CMD GPIO as OUTPUT*/
	GPIOD_OUTPUT_DIR(GPIOD15_MODE, GPIOD15_PULL ,GPIOD15);
	GPIOD_OUTPUT_DIR(GPIOD13_MODE, GPIOD13_PULL ,GPIOD13);
	GPIOD_OUTPUT_DIR(GPIOD12_MODE, GPIOD12_PULL ,GPIOD12);
	GPIOD_OUTPUT_DIR(GPIOD11_MODE, GPIOD11_PULL ,GPIOD11);
	GPIOD_OUTPUT_DIR(GPIOD10_MODE, GPIOD10_PULL ,GPIOD10);
	GPIOD_OUTPUT_DIR(GPIOD8_MODE, GPIOD8_PULL ,GPIOD8);
	CLEAN_LO; //Dosa Spread cleaning;
	DOSA_WATER_SPRY_LO; //Dosa plate spread the water.
	DOSA_OIL_SPRY_LO;
	//PRESS_UP_POS_LO;



#endif

#ifndef TIMER_ISR_CALLED
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
//    HAL_NVIC_EnableIRQ (TIM4_IRQn);  // Enable Interrupt
    HAL_NVIC_EnableIRQ (TIM2_IRQn);  // Enable Interrupt
    HAL_NVIC_EnableIRQ (TIM3_IRQn);  // Enable Interrupt
    /*Call the external interrupt*/


#endif

	//	EX_GPIO_OFF(EX_GPIO13_PIN);
	    //		PCF8575_LCD_ON(0x00 ,0x04);
#ifndef USART_CONFIG
	USART2_CONFIG();
	USART2_STRING("Working fine");
	USART2_STRING("Working fine");
	USART2_STRING("Working fine");
	USART2_STRING("Working fine");
#endif

#ifndef AUTO_TRAILS_AND_MENU

	    HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);

	    PRESSING_CHECK();
	    PCF8575_LCD_ON(0x00 ,0x64);
	    ARM_POSITION_CHECK();
	    DOUGH_UP_DOWN();
	    DOSA_MATIC_AUTO_INIT();    // auto trial stop
	   // demo(); //For testing purpose as External isr.
	    TEMPERATURE_IDLE_MODE();
	    ROTARY_INIT_STATUS_B = ROTARY_ENCODE_CLK_B;
	    SEL_DISH = CUZTOMIZE_MENU();
	    SET_DISH_CNT = CUZTOMIZE_DISC_CNT(SEL_DISH);
#endif


	USART2_STRING("Working fine");

#ifndef EX_ISR_CONFIG
	//https://hackaday.com/2021/03/26/bare-metal-stm32-please-mind-the-interrupt-event/
	//EX_ISR3_CONFIG(); //External isr use for pressing top sensor's position pointout. (Uslot sensor)
   // EX_ISR8_CONFIG(); //Not used.
 //   EX_ISR9_CONFIG(); //External pressing encoder count position pointout.
    EX_ISR12_CONFIG();  // external chapathi powder count
 //   EX_ISR15_CONFIG(); //External Arm moving encoder's count position pointout.
    EX_ISRPE14_CONFIG();
#endif

    //unsigned int data, data1;
    Delay_ms(5000);
  	GPIOA_OUTPUT_DIR(GPIOA11_MODE, GPIOA11_PULL ,GPIOA11);
  	GPIOA_OUTPUT_DIR(GPIOA10_MODE, GPIOA10_PULL ,GPIOA10);

//EX_GPIO_OFF(EX_GPIO1_PIN); //Powder dispenser motor on position;
#ifndef TIMER2_ISR_FLAG_EN

  	if(SEL_DISH == 1){
  		TEMPERATURE_COOKING_MODE();
		TIM2_MS_CNT = CLEAR_BIT;
  		TIM2_MS_CNT_MM = CLEAR_BIT;
  		TIMER2_FLAG_CNT = SET_BIT;
  		TIMER2_SEC_CNT = CLEAR_BIT;
  		SEL_DISH = CLEAR_BIT;
  	}

  	if(SEL_DISH == 2){
  		TEMP_IDLE_ROTI();
  		//CHAPATI_INIT();                 // Chapathi delivery movement stop
  		ROTI_MAKE_FLAG = SET_BIT;
  		TIM3_FLAG = SET_BIT;
  		SEL_DISH = CLEAR_BIT;
  	}

#endif


 	TIM1_MS_CNT = CLEAR_BIT;
 	TEMPERATURE_FLAG = SET_BIT;
    TEMP_READ_DA = CLEAR_BIT;
 	TEMP2 = CLEAR_BIT;
 	COOKING_TEMP_DOSA = CLEAR_BIT;
 	Sec3 = CLEAR_BIT;
 	TEM_FLAG_EN = SET_BIT;
 	TIMER_FLAG = SET_BIT;
 	DOSA_NEXT_SEQ_RUN = SET_BIT;
	while (1){

		//The reducse spike doing well by the conditional operation;
//		COOKING_TEMP_ROTI = ROTI_SPI_12Bit_READ();
//

/***********************************************************************************
 * *********************************************************************************
 * MAin code running
 */
		//COOKING_TEMP_DOSA = SPI_12Bit_READ();

		if(Sec3 >= 2 && TIMER_FLAG == 1){
			TIM1_MS_CNT = CLEAR_BIT;
			Sec3 = CLEAR_BIT;
			TEMP_READ_DA = SPI_12Bit_READ();
			TIMER_FLAG++;
		}

		if(Sec3 >= 2 && TIMER_FLAG == 2){
			TIM1_MS_CNT = CLEAR_BIT;
			Sec3 = CLEAR_BIT;
			TEMP2 = SPI_12Bit_READ();
			Sec3 = CLEAR_BIT;
			TIMER_FLAG = SET_BIT;
		}


		if(Sec4 >= 1 && TEM_FLAG_EN == SET_BIT){
			TIM1_MS_CNT = CLEAR_BIT;
			Sec4 = CLEAR_BIT;
			ROTI_READ_TEMP_LO = ROTI_SPI_12Bit_READ();
			TEM_FLAG_EN++;
		}

		if(Sec4 >= 1 && TEM_FLAG_EN ==2){
			TIM1_MS_CNT = CLEAR_BIT;
			Sec4 = CLEAR_BIT;
			ROTI_TEMP_LO = ROTI_SPI_12Bit_READ();
			TEM_FLAG_EN = SET_BIT;

		}

		if(ROTI_READ_TEMP_LO < ROTI_TEMP_LO){
			COOKING_TEMP_ROTI = ROTI_READ_TEMP_LO;

		}

		else{
			COOKING_TEMP_ROTI = ROTI_TEMP_LO;
		}


		if(TEMP_READ_DA <= TEMP2){
			COOKING_TEMP_DOSA = TEMP_READ_DA;
		}
		else{
			COOKING_TEMP_DOSA = TEMP2;
		}

		TEMP2 = TEMP_READ_DA;
		ROTI_TEMP_LO = ROTI_READ_TEMP_LO;


		LCD20x4_WRITE_4BITS(0x96 , 0);
		LCD20x4_WRITE_4BITS(COOKING_TEMP_DOSA%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(COOKING_TEMP_DOSA%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(COOKING_TEMP_DOSA%10+0x30 , 1);

		LCD20x4_WRITE_4BITS(0x9A , 0);
		LCD20x4_WRITE_4BITS(COOKING_TEMP_ROTI%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(COOKING_TEMP_ROTI%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(COOKING_TEMP_ROTI%10+0x30 , 1);

	 	LCD20x4_WRITE_4BITS(0x9E , 0);
		LCD20x4_WRITE_4BITS(Sec4%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(Sec4%10+0x30 , 1);




		if(COOKING_TEMP_DOSA >= DOSA_MATIC_MAX_TEMP){ //previous value = 180
			EX_GPIO_OFF(EX_GPIO11_PIN);
			EX_GPIO_OFF(EX_GPIO12_PIN);

		}

		if(COOKING_TEMP_ROTI >= 180){
			EX_GPIO_ON(EX_GPIO10_PIN);
		}


		if(COOKING_TEMP_DOSA < DOSA_MATIC_MAX_TEMP){ //previous value = 179
			EX_GPIO_ON(EX_GPIO11_PIN);
			EX_GPIO_ON(EX_GPIO12_PIN);

		}

		if(COOKING_TEMP_ROTI < 175){
			EX_GPIO_OFF(EX_GPIO10_PIN);
		}


	/*	if(DOSA_NEXT_SEQ_RUN == SET_BIT){
			DOSA_ISR_FLAG_CLEAR();
			ROTARY_INIT_STATUS_B = ROTARY_ENCODE_CLK_B;
			SEL_DISH = CUZTOMIZE_MENU();
			SET_DISH_CNT = CUZTOMIZE_DISC_CNT(SEL_DISH);
			DOSA_MATIC_AUTO_INIT();
			//TEMPERATURE_COOKING_MODE();

			if(SEL_DISH == SET_BIT){
				DOSA_IST_FLAG_ENABLE();
				DOSA_NEXT_SEQ_RUN = CLEAR_BIT;
			}

		}
		*/

	/*	LCD20x4_WRITE_4BITS(0xD7 , 0);
		LCD20x4_WRITE_4BITS((ARM_MOVING_CNT)%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS((ARM_MOVING_CNT)%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS((ARM_MOVING_CNT)%10+0x30 , 1);
*/
/*****************************************************************************************************
 * *****************************************END*******************************************************
 */

	/*	if(ROTARY_SWITCH){
			ROTARY_INIT_STATUS_B = ROTARY_ENCODE_CLK_B;
			SEL_DISH = CUZTOMIZE_MENU();
			SET_DISH_CNT = CUZTOMIZE_DISC_CNT(SEL_DISH);

		}

		if(SEL_DISH == 1){
	  		TEMPERATURE_COOKING_MODE();
			TIM2_MS_CNT = CLEAR_BIT;
	  		TIM2_MS_CNT_MM = CLEAR_BIT;
	  		TIMER2_FLAG_CNT = SET_BIT;
	  		TIMER2_SEC_CNT = CLEAR_BIT;
	  		SEL_DISH = CLEAR_BIT;
	  	}
*/



			//	ARM_MOVE_FWD_HI;

			//ARM_MOVE_REV_LO();
		//ARM_MOVE_FWD_HI

		//temp = SPI_SDA_IN?1:0;
	/*	test = DOSA_U_SLOT_REV_SPREAD?1:0;
		LCD20x4_WRITE_4BITS(0xE5 , 0);
		LCD20x4_WRITE_4BITS(test%10+0x30 , 1);

	/*	DATA_READ = SPI_12Bit_READ();
		ROTI_SPI_12Bit_READ();

		if(CH_PRESS_FLAG == 1){
			CH_PRESS_FLAG++;
			TIM1_PRESS_CNT = 0;
			PCF8575_LCD_ON(0x00 ,0x66);

		}
		if(CH_PRESS_FLAG == 2 && TIM1_PRESS_CNT >= 2){
			TIM1_PRESS_CNT = 0;
			CH_PRESS_FLAG = 0;
			PCF8575_LCD_ON(0x00 ,0x64);

		}*/

//		EX_GPIO_ON(EX_GPIO9_PIN);
//		EX_GPIO_ON(EX_GPIO10_PIN);
//		EX_GPIO_ON(EX_GPIO11_PIN);
//		EX_GPIO_ON(EX_GPIO12_PIN);
		//test = External_step?1:0;

//		if(((GPIOA_IDR & GPIOx_PIN_12))){
//			sample_test++;
//		}
//
//		if(sample_test >= 15){
//			PCF8575_LCD_ON(0x00 ,0x64);
//
//		}
//		test = C_WATER_FLOW_SEN?1:0; //PowderCount
//		LCD20x4_WRITE_4BITS(0xE6 , 0);
//		LCD20x4_WRITE_4BITS(test%10+0x30 , 1);

//		if(test >= 5){
//			PCF8575_LCD_ON(0x00 ,0x64);
//		}

	/*	if(Sec >= 59){
			PCF8575_LCD_ON(0x00 ,0x64);
			Sec = 0;
		}
*/
	/*	unsigned int tempValue = ARM_MOVE_PULSE_CNT?1:0;
		LCD20x4_WRITE_4BITS(0xA4 , 0);
		LCD20x4_WRITE_4BITS(tempValue%10+0x30 ,1);
*/

		LCD20x4_WRITE_4BITS(0xDC , 0);
		LCD20x4_WRITE_4BITS(Pressing_cnt%10000/1000+0x30 , 1);
		LCD20x4_WRITE_4BITS(Pressing_cnt%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(Pressing_cnt%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(Pressing_cnt%10+0x30 , 1);
	//	ARM_MOVING_CNT
	//	sample_test
    //COOKING_SEC
		LCD20x4_WRITE_4BITS(0xA4 , 0);
		//LCD20x4_WRITE_4BITS(TIM3_SEC1%10000/1000+0x30 , 1);
		LCD20x4_WRITE_4BITS(ARM_MOVING_CNT%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(ARM_MOVING_CNT%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(ARM_MOVING_CNT%10+0x30 , 1);

		LCD20x4_WRITE_4BITS(0xE2 , 0);
		//LCD20x4_WRITE_4BITS(ExtenalCount%10000/1000+0x30 , 1);
		LCD20x4_WRITE_4BITS(sample_test%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(sample_test%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(sample_test%10+0x30 ,1);

/*
		LCD20x4_WRITE_4BITS(0xCD , 0);
		LCD20x4_WRITE_4BITS('/' , 1);
		LCD20x4_WRITE_4BITS(0xCE , 0);
		LCD20x4_WRITE_4BITS(DISH_CNT%100/10+0x30 , 1);
		LCD20x4_WRITE_4BITS(DISH_CNT%10+0x30 , 1);
*/
		if(COOKING_FLAG_EN == SET_BIT){
			LCD20x4_WRITE_4BITS(0xE5 , 0);
			LCD20x4_WRITE_4BITS((COOKING_MAX_TIME - COOKING_TIME)%1000/100+0x30 , 1);
			LCD20x4_WRITE_4BITS((COOKING_MAX_TIME - COOKING_TIME)%100/10+0x30 , 1);
			LCD20x4_WRITE_4BITS((COOKING_MAX_TIME - COOKING_TIME)%10+0x30 , 1);
		}

	/*	LCD20x4_WRITE_4BITS(0xE4 , 0);
		LCD20x4_WRITE_4BITS(SEC_SEQ_FLAG%100/10+0x30 , 1);
	    LCD20x4_WRITE_4BITS(SEC_SEQ_FLAG%10+0x30 , 1);
*/
	 //   LCD20x4_WRITE_4BITS(0xE7 , 0);
	 //   LCD20x4_WRITE_4BITS(CH_DISH_CNT%100/10+0x30 , 1);
	 //   LCD20x4_WRITE_4BITS(CH_DISH_CNT%10+0x30 , 1);


/*

		LCD20x4_WRITE_4BITS(0xD9 , 0);
		LCD20x4_WRITE_4BITS(TIMER2_SEC_CNT%100/10+0x30 , 1);
	    LCD20x4_WRITE_4BITS(TIMER2_SEC_CNT%10+0x30 , 1);

	    LCD20x4_WRITE_4BITS(0xDD , 0);
	    LCD20x4_WRITE_4BITS(Count_Disp%100/10+0x30 , 1);
	    LCD20x4_WRITE_4BITS(Count_Disp%10+0x30 , 1);
*/


/*
		LCD20x4_WRITE_4BITS(0xA4 , 0);
		LCD20x4_WRITE_4BITS(Sec%10000/1000+0x30 , 1);
		LCD20x4_WRITE_4BITS(Sec%1000/100+0x30 , 1);
		LCD20x4_WRITE_4BITS(Sec%100/10+0x30 , 1);
    	LCD20x4_WRITE_4BITS(Sec%10+0x30 , 1);

*/

//		LCD20x4_WRITE_4BITS(0xD4 , 0);
//    	LCD20x4_WRITE_4BITS(ExtenalCount%100/10+0x30 , 1);
//    	LCD20x4_WRITE_4BITS(ExtenalCount%10+0x30 , 1);





//    	GPIOB_ODR |= GPIOB14;
//		Delay_ms(1000); //1us -> 1000us -1ms - 1000-ms 1sec
//     		//for(i = 0; i < 500000; i++); //1sec
//     	GPIOB_ODR &= ~ GPIOB14;
//     	Delay_ms(1000);
//    	//Time_Delay_us(10);

	}
}

/*



// void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
// {
//   /* Check the parameters */
//   assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

//   /* Enable interrupt */
//   NVIC_EnableIRQ(IRQn);
// }

// _STATIC_INLINE void __NVIC_EnableIRQ(IRQn_Type IRQn)
// {
//   if ((int32_t)(IRQn) >= 0)
//   {
//     NVIC_BASE_ADDRESS = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
//   }
// }
/*




/**
  \brief   Enable Interrupt
  \details Enables a device specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */






/*__STATIC_INLINE void __NVIC_EnableIRQ(IRQn_Type IRQn)
{
  if ((int32_t)(IRQn) >= 0)
  {
    NVIC->ISER[(((uint32_t)IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)IRQn) & 0x1FUL));
  }
}



// #define NVIC_BASE_ADDRESS     (0xE000E100UL)
// #define __NVIC_OFFSET_ADD     (0x04);

// #define NVIC_EnableIRQ        *(volatile uint32_t *)(NVIC_BASE_ADDRESS + __NVIC_OFFSET_ADD)
// #define TIMER_1_ISR_ENABLE    (1UL << 25)


// NVIC_EnableIRQ |= NVIC_EnableIRQ;

/* Memory mapping of Core Hardware */
// #define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
// #define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address */
// #define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address */
// #define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */

// #define SCnSCB              ((SCnSCB_Type    *)     SCS_BASE      )   /*!< System control Register not in SCB */
// #define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct */
// #define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct */
// #define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct */


/*
	// uint8_t temperature[2];
  //       uint8_t digit ;
  //       uint16_t decimal;
  //       //Reset, skip ROM and start temperature conversion
  //       ResetInitalization();
  //       DS18B20_WriteByte(THERM_CMD_SKIPROM);
  //       DS18B20_WriteByte(THERM_CMD_CONVERTTEMP);
  //       //Wait until conversion is complete
  //       while(!OneWireRead());
  //       //Reset, skip ROM and send command to read Scratchpad
  //       ResetInitalization();
  //       DS18B20_WriteByte(THERM_CMD_SKIPROM);
  //       DS18B20_WriteByte(THERM_CMD_RSCRATCHPAD);
  //       //Read Scratchpad (only 2 first bytes)
  //       temperature[0]=DS18B20_readByte();
  //       temperature[1]=DS18B20_readByte();
  //       ResetInitalization();
  //       //Store temperature integer digits and decimal digits
  //        //digit=(temperature[0]>>4);
  //        //digit |=((temperature[1] & 0x7) <<4);
  //        digit =(temperature[1]);
	//PCF8575_LCD_ON(0x00 ,0x00);


    //GPIOB_ODR &= ~ SET_BIT << 5;
    //2048,1024,512,256,128,64,32,16,8,4,2,1 => 12bit value; 70912 ,36447



 	//  for(SHIFTING = 0X8000; SHIFTING; SHIFTING >>= SET_BIT){
 	// 	SPI_CLOCK_LO;
 	// 	Delay_us(4);
 	// 	if((GPIOB_IDR & GPIOB8)){_BIT_SHIFT |= SHIFTING;}
 	// 	if(!(GPIOB_IDR & GPIOB8)){_BIT_SHIFT &=~ SHIFTING;}
 	// 	// (GPIOB_IDR & GPIOB8)? (_BIT_SHIFT |= SHIFTING):(_BIT_SHIFT &=~ SHIFTING);
 	// 	SPI_CLOCK_HI;
 	// 	Delay_us(4);
 	// }
 	// SPI_CHIP_SELECT_HI;
//  	// Delay_ms(220);
//  	  data = SPI_12Bit_READ();
//  	  double data2f = (data*1.0f);

// // //		_12Bit_SHIFT = (data * 0.25);
// // 		//(float) _12Bit_SHIFT = (data >> 3);
		// LCD20x4_WRITE_4BITS(0x99 , 0);
		// LCD20x4_WRITE_4BITS(digit%100000/10000+0x30 ,1);
		// LCD20x4_WRITE_4BITS(digit%10000/1000+0x30 ,1);
		// LCD20x4_WRITE_4BITS(digit%1000/100+0x30 ,1);
		// LCD20x4_WRITE_4BITS(digit%100/10+0x30 , 1);
		// LCD20x4_WRITE_4BITS(digit%10+0x30 , 1);

		// if((GPIOB_IDR & GPIOB8)){
		// 	LCD20x4_WRITE_4BITS(0x94 , 0);
		// 	LCD20x4_WRITE_4BITS('A' ,1);		}
		// if(!(GPIOB_IDR & GPIOB8)){
		// 	LCD20x4_WRITE_4BITS(0x94 , 0);
		// 	LCD20x4_WRITE_4BITS(' ' ,1);
		// 	LCD20x4_WRITE_4BITS(0x94 , 0);
  //   		LCD20x4_WRITE_4BITS('B' ,1);
		// }


/*
 * Baudrate 9600
 * Select USART Mode operation
 * Normal mode was selected.
 * External clock frequency FOSC = 16MHZ
 * Bardrate formula or calculate,
 * UBRRnx = (FOSC/16(BAUDRATE))-1;
 * UBRRnx = (16000000HZ/16*9600))-1
 * UBRRnx = (16000000HZ/153600) -1
 * UBRRnx = 103;

// #define BAUDRATE 103

// uint8_t Present_pulse;

// void USART_Init(unsigned int ubrr)
//   {
//
//       UBRR0H = (unsigned char)(ubrr>>8);
//       UBRR0L = (unsigned char)ubrr;
//       /*Enable receiver and transmitter */
//       UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
//       /* Set frame format: 8data, 2stop bit */
//       /*
//        * character size of bit start and stop bit
//        */
//       UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
//   }

// void USART_TRANSMIT(unsigned char data)
// {
//       /* Wait for empty transmit buffer */
//       while (!(UCSR0A & (1<<UDRE0)));
//       /* Put data into buffer, sends the data */
//       UDR0 = data;
// }


// uint8_t  ResetInitalization(void)
//   {
//     uint8_t SignBit;
//     GPIOB_OUTPUT_DIR(GPIOB5_MODE ,GPIOB5_PULL ,GPIOB5);
//     // DATA_DIRECTION_OUTPUT(); //Reset pullup resiger low position.
//     DS18B20_LOW();
//     Delay_us(480);          //wait for 480us

//     GPIOB_INPUT_DIR(GPIOB5_MODE ,GPIOB5);
//    // DATA_DIRECTION_INPUT();  //Release bus(input , pull up);
//     DS18B20_HIGH();
//     Delay_us(60);
//     SignBit = (DS18B20_INPUT()); //if a 0 is detected, sensor is detected.
//     Delay_us(420);

//     return SignBit;
//   }

// void OneWireWrite(short FlagEnable)
//   {
//     if(FlagEnable == 1)
//       {
//       	 GPIOB_INPUT_DIR(GPIOB5_MODE ,GPIOB5);
//          //DATA_DIRECTION_INPUT();
//          DS18B20_HIGH();
//          Delay_us(60);
//       }
//      else
//       {
//       	 GPIOB_OUTPUT_DIR(GPIOB5_MODE ,GPIOB5_PULL ,GPIOB5);
//          //DATA_DIRECTION_OUTPUT(); //Reset pullup resiger low position.
//          DS18B20_LOW();
//          Delay_us(1);
//       }
//   }

// short OneWireRead(void)
//   {
//          short recovery;
//          GPIOB_OUTPUT_DIR(GPIOB5_MODE ,GPIOB5_PULL ,GPIOB5);
//          //DATA_DIRECTION_OUTPUT(); //Reset pullup resiger low position.
//          DS18B20_LOW();
//          Delay_us(1);

//          GPIOB_INPUT_DIR(GPIOB5_MODE ,GPIOB5);
//          //DATA_DIRECTION_INPUT();
//          DS18B20_HIGH();
//          Delay_us(14);

//         recovery = DS18B20_INPUT();
//         Delay_us(45);

//         return  recovery;

//    }


//  void DS18B20_WriteByte(uint8_t bytes)
//   {
//     uint8_t i = 8;

//     while(i--)
//       {
//         OneWireWrite(bytes & 0x01);
//         bytes >>= 1;
//       }
//   }

// uint8_t DS18B20_readByte(void)
//   {
//     uint8_t i=8, n=0;
//     while(i--)
//       {
//         n>>=1;
//         n|=(OneWireRead()<<7);
//       }
//      return n;
//   }



// int main()
//   {
//     USART_Init(BAUDRATE);
//     USART_TRANSMIT('A');

//     while(true)
//       {
//          uint8_t temperature[2];
//          uint8_t digit;
//          uint16_t decimal;
//         //Reset, skip ROM and start temperature conversion
//         ResetInitalization();
//         WriteByte(THERM_CMD_SKIPROM);
//         WriteByte(THERM_CMD_CONVERTTEMP);
//         //Wait until conversion is complete
//         while(!OneWireRead());
//         //Reset, skip ROM and send command to read Scratchpad
//         ResetInitalization();
//         WriteByte(THERM_CMD_SKIPROM);
//         WriteByte(THERM_CMD_RSCRATCHPAD);
//         //Read Scratchpad (only 2 first bytes)
//         temperature[0]=readByte();
//         temperature[1]=readByte();
//         ResetInitalization();
//         //Store temperature integer digits and decimal digits
//         digit=temperature[0]>>4;
//         digit|=(temperature[1]&0x7)<<4;

//         Serial.print("temperature = ");
//         Serial.println(float(digit));
//     }
//       }


///* USER CODE BEGIN Header */
///**
//  ******************************************************************************
//  * @file           : main.c
//  * @brief          : Main program body
//  ******************************************************************************
//  * @attention
//  *
//  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
//  * All rights reserved.</center></h2>
//  *
//  * This software component is licensed by ST under BSD 3-Clause license,
//  * the "License"; You may not use this file except in compliance with the
//  * License. You may obtain a copy of the License at:
//  *                        opensource.org/licenses/BSD-3-Clause
//  *
//  ******************************************************************************
//  */
///* USER CODE END Header */
///* Includes ------------------------------------------------------------------*/
//#include "main.h"
//
///* Private includes ----------------------------------------------------------*/
///* USER CODE BEGIN Includes */
//
///* USER CODE END Includes */
//
///* Private typedef -----------------------------------------------------------*/
///* USER CODE BEGIN PTD */
//
///* USER CODE END PTD */
//
///* Private define ------------------------------------------------------------*/
///* USER CODE BEGIN PD */
///* USER CODE END PD */
//
///* Private macro -------------------------------------------------------------*/
///* USER CODE BEGIN PM */
//
///* USER CODE END PM */
//
///* Private variables ---------------------------------------------------------*/
//TIM_HandleTypeDef htim1;
//
///* USER CODE BEGIN PV */
//
///* USER CODE END PV */
//
///* Private function prototypes -----------------------------------------------*/
//void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
//static void MX_TIM1_Init(void);
//static void MX_NVIC_Init(void);
///* USER CODE BEGIN PFP */
//
///* USER CODE END PFP */
//
///* Private user code ---------------------------------------------------------*/
///* USER CODE BEGIN 0 */
//
///* USER CODE END 0 */
//
///**
//  * @brief  The application entry point.
//  * @retval int
//  */
//int main(void)
//{
//  /* USER CODE BEGIN 1 */
//
//  /* USER CODE END 1 */
//
//  /* MCU Configuration--------------------------------------------------------*/
//
//  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
//  HAL_Init();
//
//  /* USER CODE BEGIN Init */
//
//  /* USER CODE END Init */
//
//  /* Configure the system clock */
//  SystemClock_Config();
//
//  /* USER CODE BEGIN SysInit */
//
//  /* USER CODE END SysInit */
//
//  /* Initialize all configured peripherals */
//  MX_GPIO_Init();
//  MX_TIM1_Init();
//
//  /* Initialize interrupts */
//  MX_NVIC_Init();
//  /* USER CODE BEGIN 2 */
//
//  /* USER CODE END 2 */
//
//  /* Infinite loop */
//  /* USER CODE BEGIN WHILE */
//  while (1)
//  {
//    /* USER CODE END WHILE */
//
//    /* USER CODE BEGIN 3 */
//  }
//  /* USER CODE END 3 */
//}
//
///**
//  * @brief System Clock Configuration
//  * @retval None
//  */
//void SystemClock_Config(void)
//{
//  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//
//  /** Configure the main internal regulator output voltage
//  */
//  __HAL_RCC_PWR_CLK_ENABLE();
//  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
//  /** Initializes the RCC Oscillators according to the specified parameters
//  * in the RCC_OscInitTypeDef structure.
//  */
//  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
//  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /** Initializes the CPU, AHB and APB buses clocks
//  */
//  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
//  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
//  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
//
//  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
//  {
//    Error_Handler();
//  }
//}
//
///**
//  * @brief NVIC Configuration.
//  * @retval None
//  */
//static void MX_NVIC_Init(void)
//{
//  /* TIM1_UP_TIM10_IRQn interrupt configuration */
//  HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 0, 0);
//  HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
//}
//
///**
//  * @brief TIM1 Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_TIM1_Init(void)
//{
//
//  /* USER CODE BEGIN TIM1_Init 0 */
//
//  /* USER CODE END TIM1_Init 0 */
//
//  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
//  TIM_MasterConfigTypeDef sMasterConfig = {0};
//
//  /* USER CODE BEGIN TIM1_Init 1 */
//
//  /* USER CODE END TIM1_Init 1 */
//  htim1.Instance = TIM1;
//  htim1.Init.Prescaler = 0;
//  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim1.Init.Period = 65535;
//  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//  htim1.Init.RepetitionCounter = 0;
//  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN TIM1_Init 2 */
//
//  /* USER CODE END TIM1_Init 2 */
//
//}
//
///**
//  * @brief GPIO Initialization Function
//  * @param None
//  * @retval None
//  */
//static void MX_GPIO_Init(void)
//{
//  GPIO_InitTypeDef GPIO_InitStruct = {0};
//
//  /* GPIO Ports Clock Enable */
//  __HAL_RCC_GPIOH_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();
//
//  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
//
//  /*Configure GPIO pin : PB13 */
//  GPIO_InitStruct.Pin = GPIO_PIN_13;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//}
//
///* USER CODE BEGIN 4 */
//
///* USER CODE END 4 */
//
///**
//  * @brief  This function is executed in case of error occurrence.
//  * @retval None
//  */
//void Error_Handler(void)
//{
//  /* USER CODE BEGIN Error_Handler_Debug */
//  /* User can add his own implementation to report the HAL error return state */
//  __disable_irq();
//  while (1)
//  {
//  }
//  /* USER CODE END Error_Handler_Debug */
//}
//
//#ifdef  USE_FULL_ASSERT
///**
//  * @brief  Reports the name of the source file and the source line number
//  *         where the assert_param error has occurred.
//  * @param  file: pointer to the source file name
//  * @param  line: assert_param error line source number
//  * @retval None
//  */
//void assert_failed(uint8_t *file, uint32_t line)
//{
//  /* USER CODE BEGIN 6 */
//  /* User can add his own implementation to report the file name and line number,
//     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//  /* USER CODE END 6 */
//}
//#endif /* USE_FULL_ASSERT */
//
///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
/*/*
 * timer based on dosa spreading codes. noe this codes has been changed.
 *  *	else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= WAIT_FOR_300SEC_TIMER_EN && AUTO_TRIAL_FLAG_CNT_EN == 2){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			REVERSE_SEC_CNT = CLEAR_BIT;
			REVERSE_SEC_CNT = WAIT_FOR_300SEC_TIMER_EN;
			AUTO_TRIAL_FLAG_CNT_EN++;
			PCF8575_LCD_ON(0x02 ,0x64);
			//PRINTF(0x94 ,"A2");
		}*/
		//		//THIRED_MOTHOD RUNING OR MOVE TO NEXT STEPS
	/*	else if(TIMER_1_CNT_EN_AS_DOSA_TRIALS >= 1 && AUTO_TRIAL_FLAG_CNT_EN == 3){
			TIMER_1_CNT_EN_AS_DOSA_TRIALS = CLEAR_BIT;
			AUTO_TRIAL_FLAG_CNT_EN++;
			//PRINTF(0x94 ,"A3");
		}
*/
