#ifndef __SX1276_H__
#define __SX1276_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"



#define NSS_L() HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port,SPI1_NSS_Pin,GPIO_PIN_RESET);
#define NSS_H() HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port,SPI1_NSS_Pin,GPIO_PIN_SET);
#define Get_NIRQ()					HAL_GPIO_ReadPin(DIO0_GPIO_Port,DIO0_Pin)//(PD_IDR & 0x04) == 0x04//PD2

#define Frequency       (uint32_t)915000000 //915 MHz
#define F_XOSC         (uint32_t)32000000   //32 MHz
#define Frf             (uint32_t)14991360  //(Frequency*2^19)/F_XOSC
#define Frequency_reg   ((Frf>>16)&0xFF),((Frf>>8)&0xFF),(Frf&0xFF)

void cc1101_Config(void);
void cc1101_EntryTx(void);
void cc1101_EntryRx(void);
void cc1101_TxPacket(uint8_t *TX_Data, uint16_t length_Data);
uint8_t cc1101_RxPacket(uint8_t *RX_Data, uint16_t* length_Data);




// ---------------------------------------------------
// Command Strobes
// ---------------------------------------------------
#define	SRES	0x30    //Reset chip
#define	SFSTXON	0x31    //Enable and calibrate frequency synthesizer
#define	SXOFF	0x32    //Turn off crystal oscillator
#define	SCAL	0x33    //Calibrate frequency synthesizer and turn it off
#define	SRX	    0x34    //Enable RX
#define	STX	    0x35    //Enable TX
#define	SIDLE	0x36    //Exit RX / TX
#define	SWOR	0x38    //RX polling sequence 
#define	SPWD	0x39    //Comand sleep
#define	SFRX	0x3A    //Flush the RX FIFO buffer
#define	SFTX	0x3B    //Flush the TX FIFO buffer
#define	SWORRST	0x3C    //Reset real time clock
#define	SNOP	0x3D    //No operation


// ---------------------------------------------------
// Packet sniffer stttings for CC1101
//#define @RN@ @<<@0x@AH@ @<<@ //@Rd@
// ---------------------------------------------------
#define IOCFG2         0x00      //GDO2 Output Pin Configuration
#define IOCFG1         0x01      //GDO1 Output Pin Configuration
#define IOCFG0         0x02      //GDO0 Output Pin Configuration
#define FIFOTHR        0x03      //RX FIFO and TX FIFO Thresholds
#define SYNC1          0x04      //Sync Word, High Byte
#define SYNC0          0x05      //Sync Word, Low Byte
#define PKTLEN         0x06      //Packet Length
#define PKTCTRL1       0x07      //Packet Automation Control
#define PKTCTRL0       0x08      //Packet Automation Control
#define ADDR           0x09      //Device Address
#define CHANNR         0x0A      //Channel Number
#define FSCTRL1        0x0B      //Frequency Synthesizer Control
#define FSCTRL0        0x0C      //Frequency Synthesizer Control
#define FREQ2          0x0D      //Frequency Control Word, High Byte
#define FREQ1          0x0E      //Frequency Control Word, Middle Byte
#define FREQ0          0x0F      //Frequency Control Word, Low Byte
#define MDMCFG4        0x10      //Modem Configuration
#define MDMCFG3        0x11      //Modem Configuration
#define MDMCFG2        0x12      //Modem Configuration
#define MDMCFG1        0x13      //Modem Configuration
#define MDMCFG0        0x14      //Modem Configuration
#define DEVIATN        0x15      //Modem Deviation Setting
#define MCSM2          0x16      //Main Radio Control State Machine Configuration
#define MCSM1          0x17      //Main Radio Control State Machine Configuration
#define MCSM0          0x18      //Main Radio Control State Machine Configuration
#define FOCCFG         0x19      //Frequency Offset Compensation Configuration
#define BSCFG          0x1A      //Bit Synchronization Configuration
#define AGCCTRL2       0x1B      //AGC Control
#define AGCCTRL1       0x1C      //AGC Control
#define AGCCTRL0       0x1D      //AGC Control
#define WOREVT1        0x1E      //High Byte Event0 Timeout
#define WOREVT0        0x1F      //Low Byte Event0 Timeout
#define WORCTRL        0x20      //Wake On Radio Control
#define FREND1         0x21      //Front End RX Configuration
#define FREND0         0x22      //Front End TX Configuration
#define FSCAL3         0x23      //Frequency Synthesizer Calibration
#define FSCAL2         0x24      //Frequency Synthesizer Calibration
#define FSCAL1         0x25      //Frequency Synthesizer Calibration
#define FSCAL0         0x26      //Frequency Synthesizer Calibration
#define RCCTRL1        0x27      //RC Oscillator Configuration
#define RCCTRL0        0x28      //RC Oscillator Configuration
#define FSTEST         0x29      //Frequency Synthesizer Calibration Control
#define PTEST          0x2A      //Production Test
#define AGCTEST        0x2B      //AGC Test
#define TEST2          0x2C      //Various Test Settings
#define TEST1          0x2D      //Various Test Settings
#define TEST0          0x2E      //Various Test Settings
#define PARTNUM        0x30      //Chip ID
#define VERSION        0x31      //Chip ID
#define FREQEST        0x32      //Frequency Offset Estimate from Demodulator
#define LQI            0x33      //Demodulator Estimate for Link Quality
#define RSSI           0x34      //Received Signal Strength Indication
#define MARCSTATE      0x35      //Main Radio Control State Machine State
#define WORTIME1       0x36      //High Byte of WOR Time
#define WORTIME0       0x37      //Low Byte of WOR Time
#define PKTSTATUS      0x38      //Current GDOx Status and Packet Status
#define VCO_VC_DAC     0x39      //Current Setting from PLL Calibration Module
#define TXBYTES        0x3A      //Underflow and Number of Bytes
#define RXBYTES        0x3B      //Overflow and Number of Bytes
#define RCCTRL1_STATUS 0x3C      //Last RC Oscillator Calibration Result
#define RCCTRL0_STATUS 0x3D      //Last RC Oscillator Calibration Result
#define PATABLE        0x3E      //PATABLE Access
#define DATA_FIFO      0x3F      //FIFO Access for TX or RX



#endif
