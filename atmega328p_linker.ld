ENTRY(Reset_Handler)


MEMORY{
    FLASH(rx): ORIGIN =0x000000, LENGTH =32K /*0x0000 to 0x3FFF (16 bit word addresses)*/
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
    
    __data_load_addr = LOADADDR(.data);
    __data_load_start = LOADADDR(.data); /*for avrlibc*/
    .data :
    {
    	__data_start = .; /* start of SRAM*/
        *(.data)
        . = ALIGN(4);
        __data_end = .;
    } >SRAM AT> FLASH /*vma is in SRAM and lma(load memory addr ) is in FLASH*/
    .bss : /* uninitialized global data section */
    {
        __bss_start = .;
        *(COMMON)
        *(.bss)
        . = ALIGN(4);
        __bss_end = .;
        __end__ = .;
    }>SRAM AT> SRAM
    
      /DISCARD/ :
    {
        *(.comment)
    }
}
