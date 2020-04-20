#ifndef SPI__H__
#define SPI__H__

void initSPI();
unsigned char spi_io(unsigned char o);
void SPI_write(unsigned short o,unsigned char c);

#endif // SPI__H__