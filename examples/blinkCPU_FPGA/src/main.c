#include "Fw_global_config.h" // This defines application specific characteristics
#include "qf_hardwaresetup.h" // hardware init (clk / GPIOs)

#include "eoss3_hal_gpio.h"   // GPIO driver
#include "fpga_loader.h"     // API for loading FPGA
#include "blinkFPGA_bit.h"   // FPGA bitstream to load into FPGA

#include "s3x_clock.h"

void Delay(uint32_t nCount) {
	volatile uint32_t count = nCount;
	for (; count != 0; count--) __asm__("nop");
}

int main(void) {
    qf_hardwareSetup();

	S3x_Clk_Disable(S3X_FB_21_CLK);
	S3x_Clk_Disable(S3X_FB_16_CLK);

	load_fpga(sizeof(axFPGABitStream),axFPGABitStream);     // Load bitstrem into FPGA
	S3x_Clk_Enable(S3X_FB_21_CLK);                          // Start FPGA clock
	S3x_Clk_Enable(S3X_FB_16_CLK);
      
    while(1) {
		HAL_GPIO_Write(6, 1);
		Delay(0x3fFFFF);
		HAL_GPIO_Write(6, 0);
		Delay(0x3fFFFF);
	}
}

//needed for startup_EOSS3b.s asm file
void SystemInit(void) {}
