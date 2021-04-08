#include "ti_fee.h"
/* USER CODE END */

/* Include Files */
#include "sys_common.h"
/* USER CODE BEGIN (1) */


uint16 u16JobResult,Status;
Std_ReturnType oResult=E_OK;
unsigned char read_data[100]={0};

uint8 SpecialRamBlock[100]={1,2,3,4,5,7,7,4,4};

unsigned char pattern;
uint16 u16writecounter;

unsigned int  FeeVirtualSectorNumber;
unsigned char VsState, u8EEPIndex;
unsigned char u8VirtualSector;
uint8 Test_Recovery;
uint8 Test_Cancel;

void delay(void)
{
    unsigned int dummycnt=0x0000FFU;
    do
    {
        dummycnt--;
    }
    while(dummycnt>0);
}
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
    unsigned int BlockNumber;
    unsigned int BlockOffset, Length;
    unsigned char *Read_Ptr=read_data;

    //unsigned int loop;

    /* Initialize RAM array.*/
    //for(loop=0;loop<100;loop++)SpecialRamBlock[loop] = loop;
    SpecialRamBlock[0]=2;
    SpecialRamBlock[1]=2;
    SpecialRamBlock[2]=2;
    SpecialRamBlock[3]=3;
    SpecialRamBlock[4]=3;
    SpecialRamBlock[5]=1;
    SpecialRamBlock[6]=1;
    /* Initialize FEE. This will create Virtual sectors, initialize global variables etc.*/

    TI_Fee_Init();
    do
    {
        TI_Fee_MainFunction();
        delay();
        Status=TI_Fee_GetStatus(0 );
    }
    while(Status!= IDLE);
  //TI_Fee_Format(0xA5A5A5A5U);
//    do
//    {
//        TI_Fee_MainFunction();
//        delay();
//        Status=TI_Fee_GetStatus(0 );
//    }
//    while(Status!= IDLE);
    BlockOffset = 0;
    Length = 0xFFFF;


    //TI_Fee_EraseImmediateBlock(0x1);
    /* Write the block into EEP Asynchronously. Block size is configured in ti_fee_cfg.c file. Default Block size is
       8 bytes */
    BlockNumber=0x1;

    TI_Fee_Format(0xA5A5A5A5U);
    do
    {
        TI_Fee_MainFunction();
        delay();
        Status=TI_Fee_GetStatus(0 );
    }
    while(Status!= IDLE);

    TI_Fee_Init();
    do
    {
        TI_Fee_MainFunction();
        delay();
        Status=TI_Fee_GetStatus(0 );
    }
    while(Status!= IDLE);
    BlockNumber=0x1;
    TI_Fee_WriteAsync(BlockNumber, &SpecialRamBlock[0]);
    do
    {
        TI_Fee_MainFunction();
        delay();
        Status=TI_Fee_GetStatus(0);
    }
    while(Status!=IDLE);
//    BlockNumber=0x1;
    TI_Fee_WriteAsync(BlockNumber, &SpecialRamBlock[0]);
//    do
//    {
//        TI_Fee_MainFunction();
//        delay();
//        Status=TI_Fee_GetStatus(0);
//    }
//    while(Status!=IDLE);
//
//    /* Write the block into EEP Synchronously. Write will not happen since data is same. */


    /* Read the block with unknown length */
     BlockOffset = 0;
     Length = 0xFFFF;
     oResult=TI_Fee_Read(0x1,BlockOffset,Read_Ptr,Length);
     do
     {
         TI_Fee_MainFunction();
         delay();
         Status=TI_Fee_GetStatus(0);
     }
    while(Status!=IDLE);

    /* Invalidate a written block  */
//    TI_Fee_InvalidateBlock(BlockNumber);
//    do
//    {
//        TI_Fee_MainFunction();
//        delay();
//        Status=TI_Fee_GetStatus(0);
//    }
//    while(Status!=IDLE);

    /* Format bank 7 */
    //TI_Fee_Format(0xA5A5A5A5U);

    while(1){}
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
