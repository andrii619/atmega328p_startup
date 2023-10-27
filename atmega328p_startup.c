


#include <stdint.h>


int main(void);


#define SRAM_START 0x0100
#define SRAM_END 0x08FF
#define SRAM_SIZE 2048



void vector_table(void) __attribute__((naked)) __attribute__((section (".isr_vector")));
//void _exit(void) __attribute__((naked));

void ExternalInt0_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void ExternalInt1_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void PinChangeInt0_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void PinChangeInt1_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void PinChangeInt2_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void Watchdog_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void Timer2_CompA_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void Timer2_CompB_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void Timer2_Overflow_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void Timer1_Capture_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void Timer1_CompA_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void Timer1_CompB_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void Timer1_Overflow_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void Timer0_CompA_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void Timer0_CompB_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void TImer0_Overflow_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void SPI_Complete_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void UsartRx_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void UsartDataRegEmpty_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void UsartTx_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void ADC_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void EEPROM_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void AnalogComparator_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void TWI_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 
void SPM_Handler(void) __attribute__ ((weak, alias("Default_Handler"))); 





// implement reset handler

__attribute__((naked)) void exit(void)  {
	asm volatile("cli");
	for(;;);
}



void Reset_Handler(void){
	
	main();
	
	exit();
}

void Default_Handler(void){
	Reset_Handler();
}





// uint16_t vector_table[] __attribute__((section (".isr_vector"))) = {
// 	(uint16_t)&Reset_Handler,			//0x0000
// 	(uint16_t)&ExternalInt0_Handler,		//0x0002
// 	(uint16_t)&ExternalInt1_Handler,		//0x0004
// 	(uint16_t)&PinChangeInt0_Handler,
// 	(uint16_t)&PinChangeInt1_Handler,
// 	(uint16_t)&PinChangeInt2_Handler,
// 	(uint16_t)&Watchdog_Handler,
// 	(uint16_t)&Timer2_CompA_Handler,
// 	(uint16_t)&Timer2_CompB_Handler,
// 	(uint16_t)&Timer2_Overflow_Handler,
// 	(uint16_t)&Timer1_Capture_Handler,
// 	(uint16_t)&Timer1_CompA_Handler,
// 	(uint16_t)&Timer1_CompB_Handler,
// 	(uint16_t)&Timer1_Overflow_Handler,
// 	(uint16_t)&Timer0_CompA_Handler,
// 	(uint16_t)&Timer0_CompB_Handler,
// 	(uint16_t)&TImer0_Overflow_Handler,
// 	(uint16_t)&SPI_Complete_Handler,
// 	(uint16_t)&UsartRx_Handler,
// 	(uint16_t)&UsartDataRegEmpty_Handler,
// 	(uint16_t)&UsartTx_Handler,
// 	(uint16_t)&ADC_Handler,
// 	(uint16_t)&EEPROM_Handler,
// 	(uint16_t)&AnalogComparator_Handler,
// 	(uint16_t)&TWI_Handler,
// 	(uint16_t)&SPM_Handler,
	
// };

















void vector_table(void){
	//asm volatile("rjmp Reset_Handler");
	asm volatile("jmp Reset_Handler");
	asm volatile("jmp ExternalInt0_Handler");
	asm volatile("jmp ExternalInt1_Handler");
	asm volatile("jmp PinChangeInt0_Handler");
	asm volatile("jmp PinChangeInt1_Handler");
	asm volatile("jmp PinChangeInt2_Handler");
	asm volatile("jmp Watchdog_Handler");
	asm volatile("jmp Timer2_CompA_Handler");
	asm volatile("jmp Timer2_CompB_Handler");
	asm volatile("jmp Timer2_Overflow_Handler");
	asm volatile("jmp Timer1_Capture_Handler");
	asm volatile("jmp Timer1_CompA_Handler");
	asm volatile("jmp Timer1_CompB_Handler");
	asm volatile("jmp Timer1_Overflow_Handler");
	asm volatile("jmp Timer0_CompA_Handler");
	asm volatile("jmp Timer0_CompB_Handler");
	asm volatile("jmp TImer0_Overflow_Handler");
	asm volatile("jmp SPI_Complete_Handler");
	asm volatile("jmp UsartRx_Handler");
	asm volatile("jmp UsartDataRegEmpty_Handler");
	asm volatile("jmp UsartTx_Handler");
	asm volatile("jmp ADC_Handler");
	asm volatile("jmp EEPROM_Handler");
	asm volatile("jmp AnalogComparator_Handler");
	asm volatile("jmp TWI_Handler");
	asm volatile("jmp SPM_Handler");
}












