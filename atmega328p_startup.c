/**
 * FLASH is word(uint16_t) addressable
 * SRAM is half-word addressable(uint8_t)
 * 
 * 
 * .bss: Static uninitialized
 * .common: global uninitialized (we can merge common and bss sections)
 * 		Commons only appear before the linking stage. Commons are what later goes into the bss or data‚ 
 * 		but it's up to the linker to decide where it goes. This allows you to have the same variable defined in 
 * 		different compilation units. As far as I know this is mostly to allow some ancient header files that had int foo; in them instead of extern int foo;
 * 
 * 
*/


/**
 * FLASH:
 * 			<---- x16 ----->
 *          .isr_vector
 *          .text 
 *          .rodata (constant data)
 *          .data (initialized global and static variables)
 *          ...
 *          ...
 *          bootloader
 * 
 * 
 * 
 * SRAM:
 * 			<----x8-------->
 * 			.data (copied from flash)
 * 			.bss 
 * 			heap
 * 			...
 * 			stack
 * 			
*/

#include <stdint.h>
#include <stdlib.h>

int main(void);


// #define SRAM_START 0x0100
// #define SRAM_END 0x08FF
// #define SRAM_SIZE 2048


#define SRAM_START 0x800100
#define SRAM_END 0x8008ff
#define SRAM_END_L 0xff
#define SRAM_END_H 0x08


#define SPH 0x3E
#define SPL 0x3D
#define SREG 0x3F
//const uint32_t RAMEND = SRAM_END;



extern uint16_t __bss_start;
extern uint16_t __bss_end;

extern uint16_t __data_start;
extern uint16_t __data_end;
extern uint16_t __data_load_addr; // addr of data in sram

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

// __attribute__((naked)) void __exit(void)  {
// 	asm volatile("cli");
// 	for(;;);
// }


// B is placed in 000001DC
// bss start:000001DC        // 008001dc 
// bss end:00000296          // 00800296
// data load 00002EF2        // 00002ef2
// data start:00000100       // 00800100
// data end:000001DC         // 008001dc
// B is placed in 000001D


__attribute__((naked)) void __exit(void)  {
	asm volatile("cli");
	for(;;);
}

// overload the copy data funcion from std C library, need the freestanding compile flag
void __do_copy_data(void){
	uint16_t size_data = &__data_end - &__data_start;
    uint16_t *pDst = (uint16_t*)&__data_start; // sram
    //uint32_t *pSrc = (uint32_t*)&_etext; // flash, end of rodata section
    uint16_t *pSrc = (uint16_t*)&__data_load_addr;

    for(uint16_t i =0; i< size_data;i++){
        *pDst++ = *pSrc++;
    }
}

// // overload the clear bss from std C lib
void __do_clear_bss(void){
	uint16_t size_bss = &__bss_end - &__bss_start;
	//ram is 8bit wide
    uint8_t* pDst = (uint8_t*)(&__bss_start);
    for(uint16_t i =0; i< size_bss;i++){
        *pDst++ = 0;
    }
}





void __exit(void);

__attribute__((naked)) void Reset_Handler(void){
	
	// init SREG by writing all zeroes to it. XOR R1, R1 will set R1 to zero
	asm volatile("eor r1,r1");
	asm volatile("out %0, r1"::"M"(SREG):);
	
	
	// load SRAMEND address into r29,r28
	asm volatile("ldi r29, %0"::"M"(SRAM_END_H):);
	asm volatile("ldi r28, %0"::"M"(SRAM_END_L):);
	
	// save the SRAMEND into SPH and SPL to init the SP
	asm volatile("out %0, r28"::"M"(SPL):);
	asm volatile("out %0, r29"::"M"(SPH):);
	asm volatile("sei");		// enable interrupts
	
	__do_copy_data();
	
	__do_clear_bss();

	
	main();
	
	__exit();
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












