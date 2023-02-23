/**
 * @file SystemManager.c
 * @brief  System Manager of the reflow oven
 * @author Joshua Lafleur (josh.lafleur@outlook.com)
 * @version 0.1
 * @date 2023-01-13
 */

/******************************************************************************
 *                             I N C L U D E S
 ******************************************************************************/

#include "ErrorHandler.h"
#include "SystemConfig.h"
#include "HW_spi.h"

//user includes
#include "../PID/include/PID.h"
#include "../SSD1306/include/ssd1306.h"


/******************************************************************************
 *                       P U B L I C  F U N C T I O N S
 ******************************************************************************/

/**
 * @brief  Main function of the reflow oven
 *
 * @retval none
 */
int main(void){
    
    HAL_Init();
    HW_SPI_Init();    
    HW_SPI_Transmit8(spi2, 5);

    return 0;
}

/**
 * @brief  Error handler of the reflow oven
 */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
        //while(1) will lock up the processor until reset
    }
}

