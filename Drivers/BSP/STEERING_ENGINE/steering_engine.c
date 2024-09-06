/**
 ****************************************************************************************************
 * @file        steering_engine.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-14
 * @brief       �����������������PWMģʽ�� ����
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
#include "./BSP/STEERING_ENGINE/steering_engine.h"
#include "./BSP/TIMER/atim.h"

/***************************************************************************************************/
extern TIM_HandleTypeDef g_atimx_pwm_chy_handle;      /* ��ʱ��x��� */

/**
 * @brief       ����Ƕ�ת��ʱ��װ��ֵ
 * @param       angle:�Ƕ�
 * @retval      ��ʱ��װ��ֵ
 */
uint16_t angle_to_tim_val(float angle)
{
    uint16_t ret;
    if((angle < 0)||(angle > 180))
    {
        ret = 0;
    }
    else
    {
        ret = 1500 + (int)((float)((angle - 90.0) * 100 / 9));      /* 0�� -- 500��45�� -- 1000��90�� -- 1500��135�� -- 2000��180�� -- 2500 */
        if((ret < 500)||(ret > 2500))
        {
            ret = 0;
        }
    }
    return ret;
}

/**
 * @brief       ����Ƕ��趨
 * @param       id:�����Ŷ�Ӧ����Ľӿڣ�1~3; angle:�Ƕ�
 * @retval      0:�ɹ�
 */
uint8_t servo_angle_set(uint8_t id,float angle)
{
    uint16_t val;
    switch(id)
    {
        case 1:
            val = angle_to_tim_val(angle);  /* �õ��Ƕ�ת���ıȽ�ֵ */
            if(val != 0)
            {
                __HAL_TIM_SetCompare(&g_atimx_pwm_chy_handle,TIM_CHANNEL_1,val);    /* ���ñȽ�ֵ */
            }
            break;
        case 2:
            val = angle_to_tim_val(angle);
            if(val != 0)
            {
                __HAL_TIM_SetCompare(&g_atimx_pwm_chy_handle,TIM_CHANNEL_2,val);
            }
            break;
        case 3:
            val = angle_to_tim_val(angle);
            if(val != 0)
            {
                __HAL_TIM_SetCompare(&g_atimx_pwm_chy_handle,TIM_CHANNEL_3,val);
            }
            break;
        default:
            break;
    }
    return 0;
}
