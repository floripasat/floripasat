/*
 * crc.c
 *
 *  Created on: 26 de mai de 2016
 *      Author: mario
 */


unsigned char CRC8(unsigned char *Data, unsigned int n) {
	unsigned char CRC, inbyte, Mix;    // CRC, inbyte e Mix tem 8 bits
	int i, j;
	for (i = 1; i < n - 2 ; i++) {              // contagem dos bytes(de 1 a n-2 para o floripa sat)
		inbyte = Data[i];
		for (j = 0; j < 8; j++) { 			// contagem dos bits de cada byte
			Mix = (CRC ^ inbyte) & 0x01;// Mix eh a divisao (xor) dos bytes da mensagem pelo polinomio crc
			CRC >>= 1;// CRC comeca em 0 e eh shiftado para a direita a cada iteracao
			if (Mix != 0)// se Mix for diferente de zero, o CRC vira o XOR dele mesmo com a mascara de bits 0x8C
				CRC ^= 0x8C;
			inbyte >>= 1;
		}
	}
	return CRC;
}
