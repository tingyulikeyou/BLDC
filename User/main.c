

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/bldc_tim.h"
#include "./BSP/KEY/key.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/BLDC/bldc.h"

int main(void)
{
    uint8_t key,t;
    char buf[32];
    int16_t pwm_duty_temp = 0;

    HAL_Init();                              /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);      /* ����ʱ��,168Mhz */
    delay_init(168);                         /* ��ʱ��ʼ�� */
    usart_init(115200);                      /* ���ڳ�ʼ��Ϊ115200 */
    led_init();                              /* ��ʼ��LED */
    key_init();                              /* ��ʼ������ */
    lcd_init();                              /* ��ʼ��LCD */
    bldc_init(10000-1,0);
    bldc_ctrl(MOTOR_1,CCW,0);                /* ��ʼ��ˢ����ӿ�1�ٶ� */
    HAL_TIM_Base_Start_IT(&g_atimx_handle);  /* �����߼���ʱ��1 */

    /* ��ʾ��ʾ��Ϣ */
    g_point_color = WHITE;
    g_back_color  = BLACK;
    lcd_show_string(10, 10, 200, 16, 16, "BLDC Motor Test",g_point_color);
    lcd_show_string(10, 30, 200, 16, 16, "KEY0:Start forward", g_point_color);
    lcd_show_string(10, 50, 200, 16, 16, "KEY1:Start backward", g_point_color);
    lcd_show_string(10, 70, 200, 16, 16, "KEY2:Stop", g_point_color);

    printf("����KEY0 ��ʼ��ת����\r\n");
    printf("����KEY1 ��ʼ��ת����\r\n");
    printf("����KEY2 ֹͣ���\r\n");
		
		printf("����\r\n");
    
    while (1)
    {
        t++;
        if(t % 20 == 0)
        {
            sprintf(buf,"PWM_Duty:%.1f%%",(float)((g_bldc_motor1.pwm_duty/MAX_PWM_DUTY)*100));/* ��ʾ����PWMռ�ձ� */
            lcd_show_string(10,110,200,16,16,buf,g_point_color);
            LED0_TOGGLE();                          /* LED0(���) ��ת */
        }

        key = key_scan(0);
        if(key == KEY0_PRES)                        /* ����KEY0���ñȽ�ֵ+500 */
        {
            pwm_duty_temp += 500;
            if(pwm_duty_temp >= MAX_PWM_DUTY/2)     /* ���� */
                pwm_duty_temp = MAX_PWM_DUTY/2;
            if(pwm_duty_temp > 0)                   /* ͨ���ж�������������ת���� */
            {
                g_bldc_motor1.pwm_duty = pwm_duty_temp;
                g_bldc_motor1.dir = CW;
            }
            else
            {
                g_bldc_motor1.pwm_duty = -pwm_duty_temp;
                g_bldc_motor1.dir = CCW;
            }
            g_bldc_motor1.run_flag = RUN;           /* �������� */
            start_motor1();                         /* �������� */
        }
        else if(key == KEY1_PRES)                   /* ����KEY1���ñȽ�ֵ-500 */
        {
            pwm_duty_temp -= 500;
            if(pwm_duty_temp <= -MAX_PWM_DUTY/2)
                pwm_duty_temp = -MAX_PWM_DUTY/2;
            if(pwm_duty_temp < 0)                   /* ͨ���ж�������������ת���� */
            {
                g_bldc_motor1.pwm_duty = -pwm_duty_temp;
                g_bldc_motor1.dir = CCW;
            }
            else
            {
                g_bldc_motor1.pwm_duty = pwm_duty_temp;
                g_bldc_motor1.dir = CW;
            }                                                  
            g_bldc_motor1.run_flag = RUN;           /* �������� */
            start_motor1();                         /* ���е�� */
        }
        else if(key == KEY2_PRES)                   /* ����KEY2�رյ�� */
        {
            stop_motor1();                          /* ͣ�� */
            g_bldc_motor1.run_flag = STOP;          /* ���ͣ�� */
            pwm_duty_temp = 0;                      /* ������0 */
            g_bldc_motor1.pwm_duty = 0;
        }
        delay_ms(10);
    }
}
