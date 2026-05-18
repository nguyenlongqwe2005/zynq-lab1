/*
 * LED_test.c - Lab 1 HW/SW Codesign
 * Muc tieu: Dieu khien 8 LED tren ZedBoard nhap nhay giua 2 trang thai.
 *
 * Trang thai A: 11000011 (0xC3) - 4 LED ngoai cung sang.
 * Trang thai B: 00111100 (0x3C) - 4 LED giua sang.
 *
 * Vitis 2024.1 SDT flow: dung XPAR_XGPIO_0_BASEADDR thay cho DEVICE_ID cu.
 */

#include "xparameters.h"
#include "xgpio.h"
#include "xil_printf.h"

#define GPIO_BASEADDR     XPAR_XGPIO_0_BASEADDR
#define LED_CHANNEL       1
#define LED_DELAY         5000000

XGpio Gpio;

int main(void)
{
    int status;
    int led_data;

    xil_printf("=== Lab 1: LED Test on Zynq-7000 ===\r\n");

    /* Khoi tao driver AXI GPIO (SDT flow - dung BASEADDR) */
    status = XGpio_Initialize(&Gpio, GPIO_BASEADDR);
    if (status != XST_SUCCESS) {
        xil_printf("GPIO Initialization Failed.\r\n");
        return XST_FAILURE;
    }

    /* Cau hinh huong: 8 bit cua Channel 1 deu la OUTPUT (bit=0 -> output) */
    XGpio_SetDataDirection(&Gpio, LED_CHANNEL, 0x00);

    xil_printf("GPIO initialized. Starting LED blink...\r\n");

    /* Vong lap chinh: nhap nhay giua 2 trang thai */
    while (1) {
        /* Trang thai A: 0xC3 = 11000011 */
        led_data = 0xC3;
        XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, led_data);
        for (volatile int i = 0; i < LED_DELAY; i++);

        /* Trang thai B: 0x3C = 00111100 */
        led_data = 0x3C;
        XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, led_data);
        for (volatile int i = 0; i < LED_DELAY; i++);
    }

    return XST_SUCCESS;
}
