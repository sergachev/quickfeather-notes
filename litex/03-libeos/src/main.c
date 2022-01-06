#include "Fw_global_config.h"
#include "qf_hardwaresetup.h"
#include "s3x_clock.h"
#include "fpga_loader.h"
#include "FreeRTOS.h"
#include "RtosTask.h"
#include "quicklogic_quickfeather_bit.h"


// LiteX BIOS entry point
int main(int i, char **c);


void main_task( void *pParameter )
{
	(void)(pParameter);
	main(0, NULL);
}


void SystemInit(void)
{
	xTaskHandle hMain;
	qf_hardwareSetup();
	load_fpga(sizeof(axFPGABitStream), axFPGABitStream);

	NVIC_SetPriority(Uart_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY);

	S3x_Clk_Enable(S3X_FB_21_CLK); // FPGA clock
	S3x_Clk_Enable(S3X_FB_16_CLK);

	xTaskCreate (main_task, "main", 1024, NULL, (UBaseType_t)(PRIORITY_NORMAL), &hMain);

	vTaskStartScheduler();

	while(1);
}
