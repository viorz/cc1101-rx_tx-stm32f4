#include "App_CC.h"
#include <string.h>

void start_init(void)
{
    HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port,SPI1_NSS_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(Reset_GPIO_Port,Reset_Pin,GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(Reset_GPIO_Port,Reset_Pin,GPIO_PIN_SET);
    
    cc1101_Config();//
    HAL_Delay(10);
    
    HAL_Delay(10);
}

void run_App(void)
{
    char sx1276_TX_Data[256];
    sprintf (sx1276_TX_Data,"%s%s","CC1101","\n");
    uint8_t sx1276_RX_Data[256];
    char TX_Data_UART[256];
    uint16_t length_RX_Data;
    uint16_t length_TX_Data;
    length_TX_Data = strlen(sx1276_TX_Data)+1;

    uint8_t mode_RX_or_TX=0;
    
    switch(mode_RX_or_TX)
    {
        case 0:
            cc1101_EntryTx();
        break;
        case 1:
            cc1101_EntryRx();
        break;  
    }
    
    
    while(1)
    {
        switch(mode_RX_or_TX)
        {
            case 0:
                BLUE_LED_H();
                cc1101_TxPacket((uint8_t*)sx1276_TX_Data, length_TX_Data);
                BLUE_LED_L();
                HAL_Delay(1000);
//                cc1101_Config();
            case 1:
//                if(cc1101_RxPacket(sx1276_RX_Data,&length_RX_Data))
//                {
//                    BLUE_LED_H();
//                    sprintf((char*)TX_Data_UART,"%s%s%s","RX data from LoRa:    ",(char*)sx1276_RX_Data,"\n");
//                    HAL_UART_Transmit(&huart3, (uint8_t*)TX_Data_UART, strlen((char*)TX_Data_UART), 100);
//                }
//                else
                    BLUE_LED_L();
        }
        
    }
}
