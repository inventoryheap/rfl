/**
 * @file SystemConfig.h
 * @brief  Header file for the system configuration
 * @author Joshua Lafleur (josh.lafleur@outlook.com)
 * @version 0.1
 * @date 2023-01-13
 */

#pragma once

/******************************************************************************
 *                             I N C L U D E S
 ******************************************************************************/
#include "stm32f1xx.h"
#include "ErrorHandler.h"


/******************************************************************************
 *                              D E F I N E S
 ******************************************************************************/

#define USE_FULL_LL_DRIVER
#define SD_NSS2_Port GPIOB
#define SD_NSS2_Pin GPIO_PIN_12
#define SD_SCK2_Port GPIOB
#define SD_SCK2_Pin GPIO_PIN_13
#define SD_MISO2_Port GPIOB
#define SD_MISO2_Pin GPIO_PIN_14
#define SD_MOSI2_Port GPIOB
#define SD_MOSI2_Pin GPIO_PIN_15
