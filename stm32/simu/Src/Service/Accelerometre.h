/**
  ******************************************************************************
  * @file    Accelerometre.h
  * @author  INSA Toulouse
  * @version V1.0
  * @date    13-Juin-2017
	* @brief   Header for Accelerometre.c
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ACCELEROMETRE_H
#define __ACCELEROMETRE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f3_discovery_lsm303dlhc.h"

/* Private define ------------------------------------------------------------*/
#define LSM_Acc_Sensitivity_2g     (float)     1.0f            /*!< accelerometer sensitivity with 2 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_4g     (float)     0.5f            /*!< accelerometer sensitivity with 4 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_8g     (float)     0.25f           /*!< accelerometer sensitivity with 8 g full scale [LSB/mg] */
#define LSM_Acc_Sensitivity_16g    (float)     0.0834f         /*!< accelerometer sensitivity with 12 g full scale [LSB/mg]*/
#define LSM_Acc_Sensitivity  LSM_Acc_Sensitivity_2g;					 /*!< On a choisi sensitivité de 2 g full scale [LSB/mg]     */

/* Exported functions ------------------------------------------------------- */
void Acc_read(float* pfData);
void Acc_config(void);
uint32_t Acc_TIMEOUT_UserCallback(void);

#endif /* __ACCELEROMETRE_H */

/************************ (C) COPYRIGHT INSA TOULOUSE ************************/
