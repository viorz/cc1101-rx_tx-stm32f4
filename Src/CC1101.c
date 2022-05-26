#include "CC1101.h"

/*// Address Config = No address check 
// Base Frequency = 432.999817 
// CRC Autoflush = false 
// CRC Enable = true 
// Carrier Frequency = 432.999817 
// Channel Number = 0 
// Channel Spacing = 199.951172 
// Data Format = Normal mode 
// Data Rate = 1.19948 
// Deviation = 5.157471 
// Device Address = 0 
// Manchester Enable = false 
// Modulated = true 
// Modulation Format = GFSK 
// PA Ramping = false 
// Packet Length = 255 
// Packet Length Mode = Variable packet length mode. Packet length configured by the first byte after sync word 
// Preamble Count = 4 
// RX Filter BW = 58.035714 
// Sync Word Qualifier Mode = 30/32 sync word bits detected 
// TX Power = 0 
// Whitening = false 
// Rf settings for CC1101*/
uint8_t rfSettings[] = {
    0x29,  // IOCFG2              GDO2 Output Pin Configuration
    0x2E,  // IOCFG1              GDO1 Output Pin Configuration
    0x06,  // IOCFG0              GDO0 Output Pin Configuration
    0x47,  // FIFOTHR             RX FIFO and TX FIFO Thresholds
    0xD3,  // SYNC1               Sync Word, High Byte
    0x91,  // SYNC0               Sync Word, Low Byte
    0xFF,  // PKTLEN              Packet Length
    0x04,  // PKTCTRL1            Packet Automation Control
    0x05,  // PKTCTRL0            Packet Automation Control
    0x00,  // ADDR                Device Address
    0x00,  // CHANNR              Channel Number
    0x06,  // FSCTRL1             Frequency Synthesizer Control
    0x00,  // FSCTRL0             Frequency Synthesizer Control
    0x10,  // FREQ2               Frequency Control Word, High Byte
    0xA7,  // FREQ1               Frequency Control Word, Middle Byte
    0x62,  // FREQ0               Frequency Control Word, Low Byte
    0xF5,  // MDMCFG4             Modem Configuration
    0x83,  // MDMCFG3             Modem Configuration
    0x13,  // MDMCFG2             Modem Configuration
    0x22,  // MDMCFG1             Modem Configuration
    0xF8,  // MDMCFG0             Modem Configuration
    0x15,  // DEVIATN             Modem Deviation Setting
    0x07,  // MCSM2               Main Radio Control State Machine Configuration
    0x30,  // MCSM1               Main Radio Control State Machine Configuration
    0x18,  // MCSM0               Main Radio Control State Machine Configuration
    0x16,  // FOCCFG              Frequency Offset Compensation Configuration
    0x6C,  // BSCFG               Bit Synchronization Configuration
    0x03,  // AGCCTRL2            AGC Control
    0x40,  // AGCCTRL1            AGC Control
    0x91,  // AGCCTRL0            AGC Control
    0x87,  // WOREVT1             High Byte Event0 Timeout
    0x6B,  // WOREVT0             Low Byte Event0 Timeout
    0xFB,  // WORCTRL             Wake On Radio Control
    0x56,  // FREND1              Front End RX Configuration
    0x10,  // FREND0              Front End TX Configuration
    0xE9,  // FSCAL3              Frequency Synthesizer Calibration
    0x2A,  // FSCAL2              Frequency Synthesizer Calibration
    0x00,  // FSCAL1              Frequency Synthesizer Calibration
    0x1F,  // FSCAL0              Frequency Synthesizer Calibration
    0x41,  // RCCTRL1             RC Oscillator Configuration
    0x00,  // RCCTRL0             RC Oscillator Configuration
    0x59,  // FSTEST              Frequency Synthesizer Calibration Control
    0x7F,  // PTEST               Production Test
    0x3F,  // AGCTEST             AGC Test
    0x81,  // TEST2               Various Test Settings
    0x35,  // TEST1               Various Test Settings
    0x09,  // TEST0               Various Test Settings
    0x00,  // PARTNUM             Chip ID
    0x04   // VERSION             Chip ID
};


uint8_t SPIcomand(const uint8_t data)
{
    uint8_t Temp_RX[1];
    uint8_t Temp_TX[1];
    Temp_TX[0]=data;
    NSS_L();
    HAL_SPI_TransmitReceive(&hspi1, Temp_TX, Temp_RX, 1, 10);
    NSS_H();
    return Temp_RX[0];
}
uint8_t SPIWrite(const uint8_t reg, const uint8_t data)
{
    uint8_t Temp_RX[2];
    uint8_t Temp_TX[2];
    Temp_TX[0]=reg;
    Temp_TX[1]=data;
    NSS_L();
//    HAL_SPI_Transmit(&hspi1,Temp,2,10);
    HAL_SPI_TransmitReceive(&hspi1, Temp_TX, Temp_RX, 2, 10);
    NSS_H();
    return Temp_RX[0];
}
uint8_t SPIWriteFIFO(uint8_t reg, uint8_t *data, uint16_t length)
{
    uint8_t Temp_RX[1];
    uint8_t Temp_TX[1];
    Temp_TX[0]=reg|0x40;
    NSS_L();
//    HAL_SPI_Transmit(&hspi1,Temp,1,10);
    HAL_SPI_TransmitReceive(&hspi1, Temp_TX, Temp_RX, 1, 10);
    HAL_SPI_Transmit(&hspi1,data,length,100);
    NSS_H();
    return Temp_RX[0];
}
uint8_t SPIRead(const uint8_t reg, uint8_t *data)
{
    uint8_t Temp_TX[1];
    uint8_t Temp_RX[1];
    Temp_TX[0]=reg|0x80;
    NSS_L();
    HAL_SPI_TransmitReceive(&hspi1, Temp_TX, Temp_RX, 1, 10);
    HAL_SPI_Receive(&hspi1,data,1,10);
    NSS_H();
    return Temp_RX[0];
}
void SPIReadFIFO(uint8_t reg, uint8_t *data, uint16_t length)
{
    uint8_t Temp[1];
    Temp[0]=reg|0xC0;   //Set burst bit and R/W bit
    NSS_L();
    HAL_SPI_Transmit(&hspi1,Temp,1,10);
    HAL_SPI_Receive(&hspi1,data,length,100);
    NSS_H();
}

/*---------------------*/
void cc1101_Config(void)
{
    uint8_t temp=0;
    temp = SPIcomand(SRES);
//    temp = SPIWriteFIFO(IOCFG2, TXSettings, sizeof(TXSettings));
}

/*---------------------*/
void cc1101_EntryRx(void)
{
    uint8_t temp=0;
    temp = SPIWriteFIFO(IOCFG2, rfSettings, sizeof(rfSettings));
//    uint8_t addr;
//    
////    sx1276_Config();

//    SPIWrite(LR_REG_PADAC,0x84);            //Normal and Rx
//    SPIWrite(LR_RegHopPeriod,0xFF);         //RegHopPeriod NO FHSS
//    SPIWrite(LR_REG_DIOMAPPING1,0x01);      //DIO0=00, DIO1=00, DIO2=00, DIO3=01

//    SPIWrite(LR_RegIrqFlagsMask,0x3F);      //Open RxDone interrupt & Timeout
//    SPIWrite(LR_RegIrqFlags,0xFF);
//    SPIWrite(0x30,1<<7);
//    SPIWrite(LR_RegPayloadLength,21);       //RegPayloadLength  21byte(this register must difine when the data long of one byte in SF is 6)

//    addr = SPIRead(LR_RegFifoRxBaseAddr);   //Read RxBaseAddr
//    SPIWrite(LR_RegFifoAddrPtr,addr);       //RxBaseAddr -> FiFoAddrPtrЎЎ
//    SPIWrite(LR_RegOpMode,0x85);            //Continuous Rx Mode//Low Frequency Mode/*0x8d*/
//    uint32_t tickstart = HAL_GetTick();
//    while(1)
//    {
//        if((SPIRead(LR_RegModemStat)&0x04)==0x04)   //Rx-on going RegModemStat
//            break;
//        if((HAL_GetTick()-tickstart)>=3)
//            return;                         //over time for error
//    }
//    return;
}

/*---------------------*/
void cc1101_EntryTx(void)
{
    uint8_t temp=0;
    temp = SPIcomand(SIDLE);
    temp = SPIcomand(SFTX);
    temp = SPIcomand(SFSTXON);
    temp = SPIWriteFIFO(IOCFG2, rfSettings, sizeof(rfSettings));
////    cc1101_Config();
//    
//    uint8_t addr,temp;
//    
//    SPIWrite(LR_REG_PADAC,0x87);            //Tx for 20dBm
//    SPIWrite(LR_RegHopPeriod,0x00);         //RegHopPeriod NO FHSS
//    SPIWrite(LR_REG_DIOMAPPING1,0x41);      //DIO0=01, DIO1=00, DIO2=00, DIO3=01

//    SPIWrite(LR_RegIrqFlags,0xFF);          //LoRaClearIrq
//    SPIWrite(LR_RegIrqFlagsMask,0xF7);      //Open TxDone interrupt
//    SPIWrite(LR_RegPayloadLength,21);       //RegPayloadLength  21byte

//    addr = SPIRead(LR_RegFifoTxBaseAddr);   //RegFiFoTxBaseAddr
//    SPIWrite(LR_RegFifoAddrPtr,addr);       //RegFifoAddrPtr
//    uint32_t tickstart = HAL_GetTick();
//    while(1)
//    {
//        temp=SPIRead(LR_RegPayloadLength);
//        if(temp==21)
//        {
//            break;
//        }
//        if((HAL_GetTick()-tickstart)>=3)
//            return;                         //over time for error
//    }
//    return;
}

/*---------------------*/
void cc1101_TxPacket(uint8_t *TX_Data, uint16_t length_Data)
{
    uint8_t temp=0;
    uint8_t Chip_Status_Byte=0;
    Chip_Status_Byte = SPIWriteFIFO(DATA_FIFO, TX_Data, length_Data);
    Chip_Status_Byte = SPIcomand(STX);
	uint32_t tickstart = HAL_GetTick();
    while(1)
	{
		if(Get_NIRQ())                      //Packet send over
		{
            while(Get_NIRQ())
            {
                if((HAL_GetTick()-tickstart)>=1000)
                    break;                  //over time for error
            }
            SPIcomand(SFTX);

			break;
		}
        else
        {
            if((HAL_GetTick()-tickstart)>=1000)
                break;                      //over time for error
        }
	}
    Chip_Status_Byte = SPIRead(RCCTRL0_STATUS, &temp);
    Chip_Status_Byte = SPIRead(RCCTRL1_STATUS, &temp);
}

/*---------------------*/
uint8_t cc1101_RxPacket(uint8_t *RX_Data, uint16_t* length_Data)
{
    uint8_t i;
    uint8_t addr;
    uint8_t temp=0;
    uint8_t Chip_Status_Byte=0;

    if(Get_NIRQ())
    {
    for(i=0;i<32;i++)
      RX_Data[i] = 0x00;

//    addr = SPIRead(LR_RegFifoRxCurrentaddr);    //last packet addr
//    SPIWrite(LR_RegFifoAddrPtr,addr);           //RxBaseAddr -> FiFoAddrPtr
    Chip_Status_Byte = SPIRead(RXBYTES, &temp);    //Number for received bytes
    SPIReadFIFO(DATA_FIFO, RX_Data, temp);
    *length_Data = temp;

//    SPIWrite(LR_RegIrqFlags,0xFF);
//    SPIWrite(LR_RegIrqFlags,0xFF);
    SPIcomand(SFRX);
    }
    else
        return 0;
    return 1;
}



