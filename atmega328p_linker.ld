ENTRY(Reset_Handler)


MEMORY{
    FLASH(rx): ORIGIN =0x000000, LENGTH =32K
    SRAM(rwx): ORIGIN =0x800100, LENGTH =2K
    EEPROM(r): ORIGIN =0x808100, LENGTH =1K 
}


SECTIONS {
    
    .text : /* code section */
    {
        *(.isr_vector)
        *(.text)
        . = ALIGN(4);
    }>FLASH AT> FLASH
    
    .rodata : /* read only constants. stored in flash and copied to ram */
    {
        *(.rodata)
        . = ALIGN(4);
    }>FLASH AT> FLASH 
    
    .data :
    {
    	__data_start = .; /* start of SRAM*/
        *(.data)
        . = ALIGN(4);
    } >SRAM AT> FLASH
    .bss : /* uninitialized global data section */
    {
        __bss_start__ = .;
        *(.bss)
        . = ALIGN(4);
        __end__ = .; /*for semihosting*/
    }>SRAM AT> SRAM
    
      /DISCARD/ :
    {
        *(.comment)
    }
}
