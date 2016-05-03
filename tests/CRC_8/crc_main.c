
// Fun��o CRC- Cyclic Redundance Check - Floripasat  //

#include <msp430.h> 
unsigned char CRC8(volatile unsigned char *Data, unsigned int n);  // fun��o que calcula o CRC de 8 bits
unsigned char CRC8_return; 										   // resposta CRC para frame de 35 bytes

volatile unsigned char frame[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };

void main(void) {
	WDTCTL = WDTPW | WDTHOLD;								      // Stop watchdog timer
	while (1) {
		CRC8_return = CRC8(frame, sizeof frame);   				  // atribui valor de retorno ao CRC e chama a fun��o CRC8
			}

}

unsigned char CRC8(volatile unsigned char *Data, unsigned int n)
{
	unsigned char CRC = 0, inbyte, Mix;    // CRC, inbyte e Mix t�m 8 bits
	int i, j;
	for (i = 0; i < n; i++)               // contagem dos bytes
	{
		inbyte = Data[i];

		for (j = 0; j < 8; j++)     	  // contagem dos bits de cada byte
		{
			Mix = (CRC ^ inbyte) & 0x01;  // Mix � a divis�o (xor) dos bytes da mensagem pelo polin�mio crc
			CRC >>= 1;                    // desloca CRC em um bit

			if (Mix!=0)                   // � feito um xor do CRC atual com o polin�mio CRC original, que nesse caso � 0x8C
				CRC ^= 0x8C;

			inbyte >>= 1;
		}
	}

	return CRC;
}

