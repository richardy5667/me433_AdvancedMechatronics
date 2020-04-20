#include<xc.h>           // processor SFR definitions
#include"spi.h"
#include<sys/attribs.h>  // __ISR macro
// initialize SPI1
void initSPI() {
    // Pin B14 has to be SCK1
    // Turn of analog pins
    ANSELA=0;
    // Make an output pin for CS
    TRISAbits.TRISA0=0;
    LATAbits.LATA0=1;
    // Set SDO1 (Pin A1)
    RPA1Rbits.RPA1R=0b0011;
    // Set SDI1 (Pin B5)
    SDI1Rbits.SDI1R=0b0001;

    // setup SPI1
    SPI1CON = 0; // turn off the spi module and reset it
    SPI1BUF; // clear the rx buffer by reading from it
    SPI1BRG = 1; // 1000 for 24kHz, 1 for 24MHz; // baud rate to 10 MHz [SPI1BRG = (48000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0; // clear the overflow bit
    SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)
    SPI1CONbits.MSTEN = 1; // master operation
    SPI1CONbits.ON = 1; // turn on spi 
}



unsigned char spi_io(unsigned char o){
    SPI1BUF=o;
    while(!SPI1STATbits.SPIRBF){
        ;
    }
    return SPI1BUF;
}

void SPI_write(unsigned short o,unsigned char c){
    o=o|(c<<15);
    o=o|(0b111<<12);
    LATAbits.LATA0=0;
    spi_io(o>>8);
    spi_io(o);
    LATAbits.LATA0=1;
}