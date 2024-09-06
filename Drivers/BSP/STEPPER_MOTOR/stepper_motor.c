/**
 ****************************************************************************************************
 * @file        stepper_motor.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-14
 * @brief       ������� ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� F407���������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211014
 * ��һ�η���
 *
 ****************************************************************************************************
 */
 
#include "./BSP/STEPPER_MOTOR/stepper_motor.h"
#include "./BSP/TIMER/atim.h"

/**
 * @brief       ��ʼ������������IO��, ��ʹ��ʱ��
 * @param       arr: �Զ���װֵ
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void stepper_init(uint16_t arr, uint16_t psc)
{
    GPIO_InitTypeDef gpio_init_struct;

    STEPPER_DIR1_GPIO_CLK_ENABLE();                                 /* DIR1ʱ��ʹ�� */
    STEPPER_DIR2_GPIO_CLK_ENABLE();                                 /* DIR2ʱ��ʹ�� */
    STEPPER_DIR3_GPIO_CLK_ENABLE();                                 /* DIR3ʱ��ʹ�� */
    STEPPER_DIR4_GPIO_CLK_ENABLE();                                 /* DIR4ʱ��ʹ�� */
            
    STEPPER_EN1_GPIO_CLK_ENABLE();                                  /* EN1ʱ��ʹ�� */
    STEPPER_EN2_GPIO_CLK_ENABLE();                                  /* EN2ʱ��ʹ�� */
    STEPPER_EN3_GPIO_CLK_ENABLE();                                  /* EN3ʱ��ʹ�� */
    STEPPER_EN4_GPIO_CLK_ENABLE();                                  /* EN4ʱ��ʹ�� */
    

    gpio_init_struct.Pin = STEPPER_DIR1_GPIO_PIN;                   /* DIR1���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                    /* ������� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;                          /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;                   /* ���� */
    HAL_GPIO_Init(STEPPER_DIR1_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��DIR1���� */

    gpio_init_struct.Pin = STEPPER_DIR2_GPIO_PIN;                   /* DIR2���� */
    HAL_GPIO_Init(STEPPER_DIR2_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��DIR2���� */

    gpio_init_struct.Pin = STEPPER_DIR3_GPIO_PIN;                   /* DIR3���� */
    HAL_GPIO_Init(STEPPER_DIR3_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��DIR3���� */

    gpio_init_struct.Pin = STEPPER_DIR4_GPIO_PIN;                   /* DIR4���� */
    HAL_GPIO_Init(STEPPER_DIR4_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��DIR4���� */
    
    /*   �ѻ����ų�ʼ��   */
    
    gpio_init_struct.Pin = STEPPER_EN1_GPIO_PIN;                    /* EN1���� */
    HAL_GPIO_Init(STEPPER_EN1_GPIO_PORT, &gpio_init_struct);        /* ��ʼ��EN1���� */
    
    gpio_init_struct.Pin = STEPPER_EN2_GPIO_PIN;                    /* EN2���� */
    HAL_GPIO_Init(STEPPER_EN2_GPIO_PORT, &gpio_init_struct);        /* ��ʼ��EN2���� */
    
    gpio_init_struct.Pin = STEPPER_EN3_GPIO_PIN;                    /* EN3���� */
    HAL_GPIO_Init(STEPPER_EN3_GPIO_PORT, &gpio_init_struct);        /* ��ʼ��EN3���� */
    
    gpio_init_struct.Pin = STEPPER_EN4_GPIO_PIN;                    /* EN4���� */
    HAL_GPIO_Init(STEPPER_EN4_GPIO_PORT, &gpio_init_struct);        /* ��ʼ��EN4���� */
    
    atim_timx_oc_chy_init(arr, psc);   /* ��ʼ��PUL���ţ��Լ�����ģʽ�� */
}

/**
 * @brief       �����������
 * @param       motor_num: ��������ӿ����
 * @retval      ��
 */
void stepper_star(uint8_t motor_num)
{
    switch(motor_num)
    {
        case STEPPER_MOTOR_1 :
        {
            HAL_TIM_PWM_Start(&g_atimx_handle, ATIM_TIMX_PWM_CH1);     /* ������ӦPWMͨ�� */
            break;
        }
        case STEPPER_MOTOR_2 :
        {
            HAL_TIM_PWM_Start(&g_atimx_handle, ATIM_TIMX_PWM_CH2);     /* ������ӦPWMͨ�� */
            break;
        }
        case STEPPER_MOTOR_3 :
        {
            HAL_TIM_PWM_Start(&g_atimx_handle, ATIM_TIMX_PWM_CH3);     /* ������ӦPWMͨ�� */
            break;  
        }
        case STEPPER_MOTOR_4 :
        {
            HAL_TIM_PWM_Start(&g_atimx_handle, ATIM_TIMX_PWM_CH4);     /* ������ӦPWMͨ�� */
            break;
        }
        default : break;
    }
}

/**
 * @brief       �رղ������
 * @param       motor_num: ��������ӿ����
 * @retval      ��
 */
void stepper_stop(uint8_t motor_num)
{
    switch(motor_num)
    {
        case STEPPER_MOTOR_1 :
        {
            HAL_TIM_PWM_Stop(&g_atimx_handle, ATIM_TIMX_PWM_CH1);     /* �رն�ӦPWMͨ�� */
            break;
        }
        case STEPPER_MOTOR_2 :
        {
            HAL_TIM_PWM_Stop(&g_atimx_handle, ATIM_TIMX_PWM_CH2);     /* �رն�ӦPWMͨ�� */
            break;
        }
        case STEPPER_MOTOR_3 :
        {
            HAL_TIM_PWM_Stop(&g_atimx_handle, ATIM_TIMX_PWM_CH3);     /* �رն�ӦPWMͨ�� */
            break;  
        }
        case STEPPER_MOTOR_4 :
        {
            HAL_TIM_PWM_Stop(&g_atimx_handle, ATIM_TIMX_PWM_CH4);     /* �رն�ӦPWMͨ�� */
            break;
        }
        default : break;
    }
}


