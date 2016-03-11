//============================================================================
//============================================================================
// Name        : ax25.cpp
// Author      : fgs
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h> // para usar funcoes de C :)
#include <vector>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
//#include "crctester.c"

using namespace std;

//#define FLAG 01111110
#define BITsMIN 112 // quantidade minima de bit para Address
#define BITsMAX 560 // quantidade maxima de bit para Address
//#define PID {1,1,1,1,0,0,0,0} // No layer 3 protocol implemented
#define NELEMS(x)  (sizeof(x) / sizeof(int))

const unsigned char str[] = {"TEST"};

//const unsigned char string[] = {"123456789"};

/*
* | Flag     | Address      | Control | Info.    | FCS     | Flag     |
* | 01111110 | 112/560 Bits | 8 Bits  | N*8 Bits | 16 Bits | 01111110 |
*
*
*
* | Flag     | Address      | Control | PID    | Info.    | FCS     | Flag     |
* | 01111110 | 112/560 Bits | 8 Bits  | 8 Bits | N*8 Bits | 16 Bits | 01111110 |
*
*/


// internal global values:

unsigned int crcmask;
unsigned int crchighbit;
unsigned int crcinit_direct;
unsigned int crcinit_nondirect;
unsigned int crctab[256];

int bit, crc;


/* ----------------------- CRC parameters (default values are for CRC-CCITT): ----------------------- */

const int order = 16;
const unsigned int polynom = 0x1021;
const int direct = 1;
const unsigned int crcinit = 0xffff;
const unsigned int crcxor = 0x0000;
const int refin = 0;
const int refout = 0;

/* ---------------------------------------------------------------------------------------------- */

int ready = 1;


/* ----------------------------- subroutines ---------------------------------- */

void flipbits (int *a, int nelems){
	int temp, i;

	for (i=0; i<nelems/2; i++){
		temp = a[nelems-1-i];
		a[nelems-1-i] = a[i];
		a[i] = temp;
	}

	/*
	for(i=0; i<nelems; i++){
		cout << a[i];
	}
	cout<<endl;
	*/
}

unsigned int reflect (unsigned int crc, int bitnum) {

	// reflects the lower 'bitnum' bits of 'crc'

	unsigned int i, j=1, crcout=0;

	for (i=(unsigned int)1<<(bitnum-1); i; i>>=1) {
		if (crc & i) crcout|=j;
		j<<= 1;
	}
	return (crcout);
}

void generate_crc_table() {

	// make CRC lookup table used by table algorithms

	int i, j;
	unsigned int bit, crc;

	for (i=0; i<256; i++) {

		crc=(unsigned int)i;
		if (refin) crc=reflect(crc, 8);
		crc<<= order-8;

		for (j=0; j<8; j++) {

			bit = crc & crchighbit;
			crc<<= 1;
			if (bit) crc^= polynom;
		}

		if (refin) crc = reflect(crc, order);
		crc&= crcmask;
		crctab[i]= crc;
	}
}

unsigned int crctablefast (unsigned char* p, unsigned int len) {

	// fast lookup table algorithm without augmented zero bytes, e.g. used in pkzip.
	// only usable with polynom orders of 8, 16, 24 or 32.

	unsigned int crc = crcinit_direct;

	if (refin) crc = reflect(crc, order);

	if (!refin) while (len--) crc = (crc << 8) ^ crctab[ ((crc >> (order-8)) & 0xff) ^ *p++];
	else while (len--) crc = (crc >> 8) ^ crctab[ (crc & 0xff) ^ *p++];

	if (refout^refin) crc = reflect(crc, order);
	crc^= crcxor;
	crc&= crcmask;

	return(crc);
}

int crcParameters(){

	int i;
	// at first, compute constant bit masks for whole CRC and CRC high bit

			crcmask = ((((unsigned int)1<<(order-1))-1)<<1)|1;
			crchighbit = (unsigned int)1<<(order-1);


			// check parameters

			if (order < 1 || order > 32) {
				printf("ERROR, invalid order, it must be between 1..32.\n");
				return(0);
			}

			if (polynom != (polynom & crcmask)) {
				printf("ERROR, invalid polynom.\n");
				return(0);
			}

			if (crcinit != (crcinit & crcmask)) {
				printf("ERROR, invalid crcinit.\n");
				return(0);
			}

			if (crcxor != (crcxor & crcmask)) {
				printf("ERROR, invalid crcxor.\n");
				return(0);
			}


		// generate lookup table

		generate_crc_table();

		if (!direct) {

				crcinit_nondirect = crcinit;
				crc = crcinit;
				for (i=0; i<order; i++) {

					bit = crc & crchighbit;
					crc<<= 1;
					if (bit) crc^= polynom;
				}
				crc&= crcmask;
				crcinit_direct = crc;
			}

			else {

				crcinit_direct = crcinit;
				crc = crcinit;
				for (i=0; i<order; i++) {

					bit = crc & 1;
					if (bit) crc^= polynom;
					crc >>= 1;
					if (bit) crc|= crchighbit;
				}
				crcinit_nondirect = crc;
			}

		return(0);
}

int *decimal2bin(int decimalNumber){

	static int c, k, binary[16];
	//int i;
	for (c = 15; c >= 0; c--){
		k = decimalNumber >> c;

	    if (k & 1){
	    	/*printf("1"); */
	    	binary[c] = 1;
	    }
	    else{
	    	/*printf("0"); */
	    	binary[c] = 0;
	    }
	}
	//cout<<endl;

	flipbits(binary, 16);

	//cout<<"binary: ";
	//  for(i=0; i<16; i++) cout<<binary[i];
	//cout<<endl;

	return binary;

	//return binaryNumber;
}

void controlField(int *a, int nelems);
void Iframes (int *a, int nelems);
void Sframes (int *a, int nelems);
void Uframes (int *a, int nelems);
void findFlag (int *a, int nelems);
void findAddress(int *a, int nelems);

void initInfo(int *a){
	int i;

	for(i=0; i<(256*8); i++) a[i] = 0;

	//for(i=0; i<256; i++) cout << a[i];
	//cout << endl;
}

void initAddress(int *l, int tam){
	int AddMin = 48;
	int i, tam_temp = AddMin - tam;
	int temp[tam_temp];


	for(i=tam; i<AddMin; i++){
		if ( (i-1)%8 == 0 ) temp[i-tam] = 1;
		else temp[i-tam] = 0;
	}

	flipbits(temp, tam_temp);

	for(i=tam; i<AddMin; i++) l[i] = temp[i-tam];


	/*
	cout<<"Valor de l:  ";
	for (i = 0; i<AddMin; i++)
		cout << l[i];
	cout<<endl;
	*/
}

/* Transforma caracteres em bits invertidos */
void fullAddressDest(int *l, char *c, int tam_c, int tam_c_bits, int *SSID_dest){

	int i, k=0;
	char temp; // lembrar do caracter NULL em c[7]

	/* ASCII em vetor de bits :DDDD */
		//printf("Valor de cd: ");
		for(i=0; i<tam_c; i++){

			l[0] = 0; //printf("0");
			k++;
			temp = c[i];
			while (c[i]) {
				if (c[i] & 1) {l[k] = 1; //printf("1");
				}
				else {l[k] = 0; //printf("0");
				}
				c[i] >>= 1;
				k++;
			}
			/* Digitos contem 6 bits.
			 * Se for, adiciona um bit para deixa-lo com formato padrao de 7 bits
			 */
			if (isdigit(temp)) {l[k] = 0; k++; //printf("0");
			}
		}
		//printf("\n");

		/*
		cout<<"Valor de cd: ";
			for (i = 0; i<tam_c_bits; i++) cout<<l[i];
		cout<<endl;
		*/

		initAddress(l,tam_c_bits);

		// preenche o SSID
		for (i = 48; i<56; i++)	l[i] = SSID_dest[i-48];
}

/* Transforma caracteres em bits invertidos */
void fullAddressSource(int *m, char *c, int tam_c, int tam_c_bits, int *SSID_source){

	int i, k=0;
	char temp; // lembrar do caracter NULL em c[7]

	/* ASCII em vetor de bits :DDDD */
		//printf("Valor de cs: ");
		for(i=0; i<tam_c; i++){

			m[0] = 0; //printf("0");
			k++;
			temp = c[i];
			while (c[i]) {
				if (c[i] & 1) {m[k] = 1; //printf("1");
				}
				else { m[k] = 0; //printf("0");
				}
			c[i] >>= 1;
			k++;
			}
			/* Digitos contem 6 bits.
			 * Se for, adiciona um bit para deixa-lo com formato padrao de 7 bits
			 */
			if (isdigit(temp)) {m[k] = 0; k++; //printf("0");
			}
		}
		//printf("\n");

		initAddress(m,tam_c_bits);

		// preenche o SSID
		for (i = 48; i<56; i++)	m[i] = SSID_source[i-48];
}

void fullInfo(int *infoFIELD, unsigned char *inform, int tam_c, int tam_c_bits){

	int i, k=0;
	char temp;

	/* Inicializa o campo Info com zeros */
		initInfo(infoFIELD);

	/* ASCII em vetor de bits :DDDD */
		//printf("Valor de i: ");
		for(i=0; i<tam_c; i++){

			//infoFIELD[0] = 0; printf("0");
			//k++;
			temp = inform[i];
			while (inform[i]) {
				if (inform[i] & 1) {
					infoFIELD[k] = 1; //printf("1");
				}
				else {
					infoFIELD[k] = 0; //printf("0");
				}
				inform[i] >>= 1;
				k++;
			}
			k++; //printf("0");
			if (isdigit(temp)) {
				infoFIELD[k] = 0; k++; //printf("0");
			}
		}
		//printf("\n");
}

void printDest(int *fr){
	int i, j, cont, temp = 0;
	char destChar[6] = "\0";

	cont = 0;
	for(j = 0; j<6; j++){
		for(i=8+1+cont; i<8+8+cont; i++){
			temp = temp + fr[i]*pow(2,i-1-cont-8);
		}
		destChar[j] = temp;
		cont = i-8;
		//cout<<temp <<endl;
		temp = 0;
	}
	cout<<"Destination: "<<destChar <<endl;
}

void printSource(int *fr){
	int i, j, cont, temp = 0;
	char sourceChar[6] = "\0";

	cont = 0;
	for(j = 0; j<6; j++){
		for(i=64+1+cont; i<64+8+cont; i++){
			temp = temp + fr[i]*pow(2,i-1-cont-64);
		}
		sourceChar[j] = temp;
		cont = i-64;
		//cout<<temp <<endl;
		temp = 0;
	}
	cout<< "Source: " <<sourceChar <<endl;
}

unsigned char *printInfo(int *fr){
	int i, j, cont, temp = 0;
	unsigned char infoChar[256] = "\0";

	cont = 0;
		for(j = 0; j<256; j++){ // verificar jaja
			for(i=136+cont; i<136+8+cont; i++){ // 136 eh o indice que comeca a INFO
				temp = temp + fr[i]*pow(2,i-cont-136); // converte de binario para inteiro
			}
			infoChar[j] = temp; // recebe o ASCII referente ao numero inteiro
			cont = i-136;
			//cout<<j <<endl;
			temp = 0;
			if (infoChar[j] == '\0') break; // se encontrou "\0", conclui-se que nao ha mais informacao
		}
		infoChar[j] = '\0';
		cout<< "Info: " <<infoChar <<endl;
		return infoChar;
}

void egua(int *fr, int indice){
		int cont=0, temp = 0;
		int j,i;
		float egua = 0;

		indice = 0;


		for(j = 0; j<2; j++){ // dois octetos
			for(i=indice+cont; i<indice+8+cont; i++){ // 136 eh o indice que comeca a INFO
				temp = temp + fr[i]*pow(2,i-cont-indice); // converte de binario para inteiro
			}
			egua = temp;
			//cont = i-indice;
			temp = 0;
		}

		// vou chamar uma funcao para 3 pares de octetos do ADC0 ADC1 ADC2

//		ADC_1_2_3_I (fr, indice);



						//egua = egua*cte;


}

void ADC_4_5_6_I(int *fr, int ind){

	int cont=0, temp = 0;
	int i,j,k;
	double I_ADC = 0, V_ADC = 0;
	int ind2 = ind;


	for (k=0; k<3; k++){ // tres pares de octetos
		ind = ind + 8;
		for(j = 0; j<2; j++){ // dois octetos para cada ADC
			for(i=ind; i<ind+8; i++, cont++){ // 136 eh o indice que comeca a INFO
				temp = temp + fr[i]*pow(2,cont); // converte de binario para inteiro
			}
			//ind = ind - 16;
			V_ADC = V_ADC+ temp;
			//cont = i-ind;
			temp = 0;
			ind = 2*k*8 + ind2;
		}
		cont = 0;
		ind = 16*pow(2,k);

		I_ADC = V_ADC*6.1035/(50*25*16.5);
		cout<< "I_ADC_" <<k<<": "<<I_ADC<<endl;

		V_ADC = 0;
	}
}


void ADC_1_2_3_V(int *fr, int ind){

	int cont=0, temp = 0;
	int i,j,k;
	double V_panel = 0, V_ADC = 0;
	int ind2 = ind;
	//indice = 0;


	for (k=0; k<3; k++){ // tres pares de octetos
		ind = ind + 8;
		for(j = 0; j<2; j++){ // dois octetos para cada ADC
			for(i=ind; i<ind+8; i++, cont++){ // 136 eh o indice que comeca a INFO
				temp = temp + fr[i]*pow(2,cont); // converte de binario para inteiro
			}
			//ind = ind - 16;
			V_ADC = V_ADC+ temp;
			//cont = i-ind;
			temp = 0;
			ind = 2*k*8 + ind2;
		}
		cont = 0;
		ind = 16*pow(2,k);

		V_panel = V_ADC*6.1035*193.1/pow(10,6);
		cout<< "V_panel_" <<k<<": "<<V_panel<<endl;

		V_ADC = 0;
	}
}

/****** ADC Voltage Total Data *******/
void ADC_total_V(int *fr, int ind){
	int cont=0, temp=0;
	int i,j;
	double V_ADC_total = 0, V_ADC = 0;
	int ind2 = ind;


	ind = ind + 8;
	for(j = 0; j<2; j++){ // dois octetos para cada ADC
		for(i=ind; i<ind+8; i++, cont++){ // 136 eh o indice que comeca a INFO
			temp = temp + fr[i]*pow(2,cont); // converte de binario para inteiro
		}

		V_ADC = V_ADC+temp;
		temp = 0;
		ind = ind2;
	}

	V_ADC_total = V_ADC*6.1035*4/pow(10,4);
	cout<< "V_ADC_total: "<<V_ADC_total<<endl;
}

/****** MSP430 Temperature Sensor ******/
void MSP_TS (int *fr, int ind){
	int cont=0, temp=0;
	int i,j;
	double TemperSens = 0, V_MSP = 0;
	int ind2 = ind;


	ind = ind + 8;
	for(j = 0; j<2; j++){ // dois octetos para cada ADC
		for(i=ind; i<ind+8; i++, cont++){ // 136 eh o indice que comeca a INFO
			temp = temp + fr[i]*pow(2,cont); // converte de binario para inteiro
		}

		V_MSP = V_MSP+temp;
		temp = 0;
		ind = ind2;
	}

	TemperSens = (V_MSP*6.1035*pow(10,-4) - 0.986)/0.00355;
	cout<< "Temperature Sensor: "<<TemperSens<<" Celsius"<<endl;
}


/******** Average Current **********/
void AVC (int *fr, int ind){
	int cont=0, flag = 0;;
	int i;
	double AVC_I = 0, V_AVC = 0;
	int V_AVC_int[16],V_AVC_MSB[8],V_AVC_LSB[8];

	for(i=ind; i<ind+16; i++) V_AVC_int[i-ind] = fr[i];

	for(i=0; i<8; i++)	V_AVC_MSB[i] = V_AVC_int[i];

	for(i=8; i<16; i++)	V_AVC_LSB[i-8] = V_AVC_int[i];

	flipbits(V_AVC_MSB, 8);
	flipbits(V_AVC_LSB, 8);

	// Colocado na forma original
	for(i=0; i<8; i++) 	V_AVC_int[i] = V_AVC_MSB[i];
	for(i=8; i<16; i++)	V_AVC_int[i] = V_AVC_LSB[i-8];


	//for(i=0; i<16; i++) cout<<V_AVC_int[i];
	//cout<<endl;

	/* Two's Complement */
	if (V_AVC_int[0] == 1){
		i = 15;
		while(i>=0){
			if(V_AVC_int[i] == 1 or flag){
				flag = 1;
				i--;
				V_AVC_int[i] = !V_AVC_int[i];
				i++;
			}
			i--;
		}
	}
	V_AVC_int[0] = 0;


	//for(i=0; i<16; i++) cout<<V_AVC_int[i];
	//cout<<endl;


	flipbits(V_AVC_int, 16); // flip the vector for calculation below

	for(i=0; i<15; i++, cont++){ // the last bit is the parity bit
		V_AVC = V_AVC + V_AVC_int[i]*pow(2,cont); // converte de binario para inteiro
	}

	// cout<< "Average Current: "<<V_AVC<<" Ampere"<<endl;

	AVC_I = V_AVC*1.5625*pow(10,-6)/0.015;
	cout<< "Average Current: "<<AVC_I<<" Ampere"<<endl;
}

/******** Temperature Register Value *********/
void TEMP_REG (int *fr, int ind){
	int cont=0, flag=0;
	int i,j;
	double TR = 0, V_TR = 0;
	int V_TR_int[16],V_TR_MSB[8],V_TR_LSB[8];


	for(i=ind; i<ind+16; i++) V_TR_int[i-ind] = fr[i];

	for(i=0; i<8; i++)	V_TR_MSB[i] = V_TR_int[i];

	for(i=8; i<16; i++)	V_TR_LSB[i-8] = V_TR_int[i];

	flipbits(V_TR_MSB, 8);
	flipbits(V_TR_LSB, 8);


		// Colocado na forma original
	for(i=0; i<8; i++) 	V_TR_int[i] = V_TR_MSB[i];
	for(i=8; i<16; i++)	V_TR_int[i] = V_TR_LSB[i-8];

	//for(i=0; i<16; i++) cout<<V_TR_int[i];
	//cout<<endl;


	/* Two's Complement */
	if (V_TR_int[0] == 1){
		i = 15;
		while(i>=0){
			if(V_TR_int[i] == 1 or flag){
				flag = 1;
				i--;
				V_TR_int[i] = !V_TR_int[i];
				i++;
			}
			i--;
		}
	}
	V_TR_int[0] = 0;

	//for(i=0; i<16; i++) cout<<V_TR_int[i];
	//cout<<endl;

		// desloca cinco posicoes para a direita
	for(j=0;j<5;j++){
		for(i=15;i>0;i--) V_TR_int[i] = V_TR_int[i-1];

		V_TR_int[0] = 0;
	}

	//for(i=0; i<16; i++) cout<<V_TR_int[i];
	//cout<<endl;

	flipbits(V_TR_int, 16); // flip the vector for calculation below

	for(i=0; i<15; i++, cont++){
		V_TR = V_TR + V_TR_int[i]*pow(2,cont); // converte de binario para inteiro
	}


	TR = V_TR*0.125;
	cout<< "Temperature Register: "<<TR<<" Celsius"<<endl;
}


/********* Voltage Register Value **********/
void VOLT_REG(int *fr, int ind){

	int cont=0, flag = 0;
	int i,j;
	double V_REG = 0, V_bat;
	int V_REG_int[16],V_REG_MSB[8],V_REG_LSB[8];


	for(i=ind; i<ind+16; i++) V_REG_int[i-ind] = fr[i];

	for(i=0; i<8; i++)	V_REG_MSB[i] = V_REG_int[i];

	for(i=8; i<16; i++)	V_REG_LSB[i-8] = V_REG_int[i];

	flipbits(V_REG_MSB, 8);
	flipbits(V_REG_LSB, 8);

	// Colocado na forma original
	for(i=0; i<8; i++) 	V_REG_int[i] = V_REG_MSB[i];
	for(i=8; i<16; i++)	V_REG_int[i] = V_REG_LSB[i-8];

	//for(i=0; i<16; i++) cout<<V_REG_int[i];
	//cout<<endl;

	/* Two's Complement */
	if (V_REG_int[0] == 1){
		i = 15;
		while(i>=0){
			if(V_REG_int[i] == 1 or flag){
				flag = 1;
				i--;
				V_REG_int[i] = !V_REG_int[i];
				i++;
			}
			i--;
		}
	}
	V_REG_int[0] = 0;

	//for(i=0; i<16; i++) cout<<V_REG_int[i];
	//cout<<endl;


	// desloca cinco posicoes para a direita. Olhar na documentacao
	for(j=0;j<5;j++){
		for(i=15;i>0;i--) V_REG_int[i] = V_REG_int[i-1];

		V_REG_int[0] = 0;
	}

	//for(i=0; i<16; i++) cout<<V_REG_int[i];
	//cout<<endl;

	flipbits(V_REG_int, 16); // flip the vector for calculation below

	for(i=0; i<15; i++, cont++)	V_REG = V_REG + V_REG_int[i]*pow(2,cont); // converte de binario para inteiro


	V_bat = V_REG*4.883*pow(10,-3);
	cout<< "Voltage Register: "<<V_bat<< " V"<<endl;
}

void CURRENT_REG (int *fr, int ind){
	int cont=0, flag = 0;;
	int i;
	double V_CR = 0, I_bat = 0;
	int V_CR_int[16],V_CR_MSB[8],V_CR_LSB[8];

	for(i=ind; i<ind+16; i++) V_CR_int[i-ind] = fr[i];

	for(i=0; i<8; i++)	V_CR_MSB[i] = V_CR_int[i];

	for(i=8; i<16; i++)	V_CR_LSB[i-8] = V_CR_int[i];

	flipbits(V_CR_MSB, 8);
	flipbits(V_CR_LSB, 8);

	for(i=0; i<8; i++) 	V_CR_int[i] = V_CR_MSB[i];
	for(i=8; i<16; i++)	V_CR_int[i] = V_CR_LSB[i-8];

	//for(i=0; i<16; i++) cout<<V_CR_int[i];
	//cout<<endl;


	/* Two's Complement */
	if (V_CR_int[0] == 1){
		i = 15;
		while(i>=0){
			if(V_CR_int[i] == 1 or flag){
				flag = 1;
				i--;
				V_CR_int[i] = !V_CR_int[i];
				i++;
			}
			i--;
		}
	}
	V_CR_int[0] = 0;

	//for(i=0; i<16; i++) cout<<V_CR_int[i];
	//cout<<endl;

	flipbits(V_CR_int, 16); // flip the vector for calculation below

	for(i=0; i<15; i++, cont++){ // the last bit is the parity bit
		V_CR = V_CR + V_CR_int[i]*pow(2,cont); // converte de binario para inteiro
	}

	I_bat = V_CR*1.5625*pow(10,-6)/0.015;
	cout<< "Current Register: "<<I_bat<<" Ampere"<<endl;
}

void ACCUM_CURRENT (int *fr, int ind){
	int cont=0, temp=0;
	int i,j;
	double Q_bat = 0, V_ACR = 0;
	int ind2 = ind;


	ind = ind + 8;
	for(j = 0; j<2; j++){ // dois octetos para cada Register
		for(i=ind; i<ind+8; i++, cont++){ // 136 eh o indice que comeca a INFO
			temp = temp + fr[i]*pow(2,cont); // converte de binario para inteiro
		}

		V_ACR = V_ACR+temp;
		temp = 0;
		ind = ind2;
	}

	Q_bat = V_ACR*6.25*pow(10,-6)/0.015;
	cout<< "Accumulated Current: "<<Q_bat<<" Ampere hour"<<endl;
}


/****** Voltage Regulator Status *******/
void VR_STATUS (int *fr, int ind){
	int cont=0;
	int i;
	double V_status = 0;


	for(i=ind; i<ind+8; i++, cont++){ // ind eh o indice que comeca o Voltage Regulator Status
		V_status = V_status + fr[i]*pow(2,cont); // convercao de binario para inteiro
	}


	cout<< "Voltage Regulator Status: "<<V_status<<endl;
}



void RTD(int *fr, int ind){

	int cont=0, temp = 0;
	int i,j,k;
	double T_RTD, V_RTD, V_ADC_RTD = 0;
	int ind2;
	int fr_cp[21*8];

	// copia para outro vetor, pois eh mais facil tratar um vetor comecando com indice "0"
	for(i=ind; i<ind+21*8; i++)
		fr_cp[i-ind] = fr[i];

	ind = 0;
	ind2 = ind + 8;

	for (k=0; k<4; k++){ // tres pares de octetos
		ind = ind + 16;
		for(j = 0; j<3; j++){ // tres octetos para cada RTD
			for(i=ind; i<ind+8; i++, cont++){ // ind eh o indice que comeca a INFO
				temp = temp + fr_cp[i]*pow(2,cont); // converte de binario para inteiro
			}
			//ind = ind - 16;
			V_ADC_RTD = V_ADC_RTD + temp;
			//cont = i-ind;
			temp = 0;
			ind = 2*k*8 + ind2*(k+1) - (j*8);
		}
		cont = 0;
		ind = 16*pow(2,k) + 8;

		V_RTD = V_ADC_RTD/(2.048*pow(2,24));

		T_RTD = (1000*33 - 898*V_RTD - 1000*V_RTD)/(3.85*V_RTD - 3.85*33);
		cout<<"V_ADC_RTD_" <<k+1<<": "<<V_ADC_RTD<<endl;

		//cout<<"TEMPERATURE_RTD_" <<k+1<<": "<<T_RTD<<" Celsius"<<endl;

		V_ADC_RTD = 0;
	}
}

static unsigned char * checkCRC(int fr[]){
	int i, j, cont, temp = 0;
	unsigned char CRC_Char[16] = "\0";

	//unsigned char ar[16] = {0,1,0,1,0,1,0,0, 0,1,0,0,0,1,0,1};

	// 192 eh o indice que comeca o FCS
	cont = 0;
	for(j=0; j<2; j++){ // numero de octetos a ser contato
		for(i=192+8+cont-1; i>=192+cont; i--){
			temp = temp + fr[i]*pow(2,-i-1+8+cont+192); // converte binario para inteiro
		}
		CRC_Char[j] = temp; // recebe o ASCII referente ao inteiro recebido
		cont = i+8+1-192; // cont  = 0 e 8
		//printf("Cont: %d\n", cont);
		temp = 0;
	}

		//printf("CRC: \n");
		//for(i=0;i<2;i++) printf("%c", CRC_Char[i]);
		//printf("\n");
		//printf("%s",CRC_Char);
		//cout<< "CRC: "<< CRC_Char<<endl;

		return CRC_Char;
}

int main() {

	//int a [] = {0,1,1,1,1,1,1,0,  1,0,0,1,  0,1,1,1,1,1,1,0};
	static int dest_bits[56], source_bits[56];


	int adc1[] = {1,1,1,1,0,0,0,0, 1,1,1,1,1,1,1,1,
				  0,0,0,0,0,0,0,1, 0,1,1,0,0,0,0,0,
				  0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,
				  1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
				  1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0};

	int rtd[] = {1,1,1,1,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,1,
				 0,1,1,0,0,0,0,0, 0,0,0,0,0,0,0,1, 0,0,0,0,0,0,0,0,
				 0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0,
				 0,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0, 1,0,0,0,0,0,0,0};


	//ADC_4_5_6_I(adc1, 16);
	//ADC_1_2_3_V(adc1, 0);
	//ADC_total_V(adc1, 0);
	//MSP_TS(adc1, 0);
	//AVC(adc1, 16);
	//TEMP_REG(adc1, 16);
	//VOLT_REG(adc1, 0);
	//CURRENT_REG(adc1,16);
	//VR_STATUS(adc1, 8);
	RTD(rtd, 0);


	int flag[8] = {0,1,1,1,1,1,1,0}; // Default value to FLAG
	int control[8] = {0,0,1,1,1,1,1,0}; // initial value to Control Field
	int pid[8] = {1,1,1,1,0,0,0,0}; // No layer 3 protocol implemented
	static int frame[2208]; // (256 de INFO + 20 do resto)*8
	int infoRecepTam = 0;

	static int infoField[256*8]; // The I field defaults to a length of 256 octets --- INFO ---

	static unsigned char info[] = {"TEST"}; // example
	static unsigned char *infoCRC;
	unsigned char *infoRecep;
	static unsigned char *testCRC = NULL;
	//info[4] = 0x8c;
	//info[5] = 0xca;
	//info[6] = 00000000;

	int contBits = 0;


	/* ---------------------------------------------------- */
	FILE *fp;

	int tam_dest, tam_dest_bits, tam_source, tam_source_bits, tam_info, tam_info_bits;
	static unsigned int CRC;
	int i,j;
	static int *binCRC;

	/* ------------------------ Example --------------------------------- */

	char destination[] = "1B0"; // Example of DESTINATION address
	int SSID_dest[8] = {0,1,1,0, 0,0,0,0}; // SSID DESTINATION
	int C_bit_dest = 0; // indica que tem mais enderecos
    	SSID_dest[0] = C_bit_dest; // set the bit "C" from DESTINATION

	char source[] = "01B"; // Example of SOURCE address
	int SSID_source[8] = {1,1,1,0, 0,0,0,1}; // SSID SOURCE
	int C_bit_source = 1; // indica que eh o ultimo octeto do campo Address
		SSID_source[0] = C_bit_source; // set the bit "C" from SOURCE


	tam_dest = (sizeof(destination)/sizeof(destination[0]))-1; // number of characters without the NULL
	tam_dest_bits = tam_dest*8; // length of DESTINATION in 8 bits

	tam_source = (sizeof(source)/sizeof(source[0]))-1; // number of characters without the NULL
	tam_source_bits = tam_source*8; // length of SOURCE in 8 bits



	/*******************************************\ Functions /*********************************************/

	/* Invert the SSID DESTINATION */
	flipbits(SSID_dest, 8);

	/* Invert the SSID SOURCE */
	flipbits(SSID_source, 8);

	/* Invert the CONTROL octet  */
	flipbits(control, 8);

	/* Invert the PID */
	flipbits(pid, 8);


	/****************************************************\ Field DESTINATION /****************************************************/

	/* Preenche o endereco de destino (invertido) em bits e seu SSID em dest_bits*/
	fullAddressDest(dest_bits, destination, tam_dest, tam_dest_bits, SSID_dest);

	/*
	cout<<"Valor de dest_bits:  ";
	for (i = 0; i<56; i++) cout<<dest_bits[i];
	cout<<endl;
	*/

	/****************************************************************************************************************************/



	/*****************************************************\ Field SOURCE /******************************************************/

	/* Preenche o endereco de origem (invertido) em bits e o seu SSID em source_bits*/
	fullAddressSource(source_bits, source, tam_source, tam_source_bits, SSID_source);

	/*
	cout<<"Valor de source_bits:  ";
		for (i = 0; i<56; i++) cout << source_bits[i];
	cout<<endl;
	*/

	/**************************************************************************************************************************/



	/*****************************************************\ Field INFO /****************************************************/

	/* Faz o calculo do tamanho da informacao em bits */
	tam_info = (sizeof(info)/sizeof(info[0]))-1;
	tam_info_bits = tam_info*8;

	/* Preenche a informacao no campo Info */
	fullInfo(infoField, info, tam_info, tam_info_bits); // converte cada caracter ASCII --> 8bit

/*	printf("info field: ");
	for(i=0; i<(50); i++) printf("%d", infoField[i]);
	printf("\n"); */

	/*********************************************************************************************************************/


	/*******************************************************\ Field FCS /******************************************************/

		/* CRC calculation based on CRC-CCITT */
		crcParameters();
		CRC = crctablefast(info, strlen((const char*)info));

		printf("crc table fast: 0x%x\n", CRC);

		/* Converte o CRC de decimal para binario em um vetor de 16 bits */
		binCRC = decimal2bin(CRC);

		/*
		cout<<"binary: ";
		for(i=0; i<16; i++){
			cout<<*binCRC;
			binCRC = binCRC+1;
		}
		binCRC = binCRC-16;
		cout<<endl;
		*/

		/***********************************************************************************************************************/



	/**************************************************\ Make the Frame /*************************************************/
	/* Preenche a flag incial*/
	for (i=0; i<8; i++)	frame[i] = flag[i];

	/* Preenche o destino e SSID */
	for (j=8; j<64; j++) frame[j] = dest_bits[j-8];

	/* Preenche a origem e SSID */
	for (j=64; j<120; j++) frame[j] = source_bits[j-64];

	/* Preenche o Control Field */
	for(j=120; j<128; j++) frame[j] = control[j-120];

	/* Preenche o PID */
	for(j=128; j<136; j++) frame[j] = pid[j-128];

	/* Preenche a informacao */
	for(j=136; j<2184; j++) frame[j] = infoField[j-136];

	/* Preenche o FCS */
	for(j=2184; j<2200; j++) {
		frame[j] = *binCRC;
		binCRC = binCRC+1;
	}

	/* Preenche a flag final */
	for (j=2200; j<2208; j++)	frame[j] = flag[j-2200];


	/* Imprime o frame */
	cout<< "Vf:  ";
	for(i=392; i<408; i++) cout<<frame[i];
	cout<<endl;

	/*********************************************************************************************************************/






	/**************************************************\ Write to File /*************************************************/

	if((fp = fopen("frame.txt","w")) == NULL){
		printf("O arquivo nao pode ser aberto.\n");
		exit(1);
	}

	i=0;
	do{
		fprintf(fp, "%d",frame[i]);
		//putc(frame[i],fp);
		i++;
	}while(i<2208);

	fclose(fp);

	/*********************************************************************************************************************/



	/**************************************************\ Read from File /*************************************************/

	if((fp = fopen("frame.txt","r")) == NULL){
		printf("O arquivo nao pode ser aberto.\n");
		exit(1);
	}

	char ch;
	int frameRecep[2208];

	ch = getc(fp); /* Le "0"s e "1"s em ASCII */
	i=0;

	while(ch!=EOF){
		//printf("%c",ch); /* show on screen o que esta no aquivo em ASCII*/

		if (ch == '0')	frameRecep[i] = 0; /* Preenche "0"s e "1"s em vetor de inteiros */
		else if (ch == '1') frameRecep[i] = 1;

		i++;
		ch = getc(fp); /* Le "0"s e "1"s em ASCII */
	}

	fclose(fp);
//	printf("\n");

	/* mostra na tela o vetor de bits recebidos do arquivo */
	//for(i=0;i<2208;i++)	printf("%d",frameRecep[i]); /* show on screen */
	//printf("\n");

	/***********************************************************************************************************************/




	//flipbits(b, sizeof(b)/sizeof(b[0]));
	//cout <<"B: "<< b << endl;

	//findFlag(a, tam_a);
	//findAddress(b, 16);

	static int fr[] ={
/* Flag */			0,1,1,1,1,1,1,0,
/* Destination */	0,0,1,0,0,1,0,1,  0,1,0,1,0,0,0,1,  0,1,0,1,1,0,0,1,  0,1,1,1,1,0,0,1,  0,1,1,0,0,1,1,0,  0,1,1,0,0,1,1,0,
/* SSID */			0,0,0,0,1,1,1,1,
/* Source */		0,0,1,1,1,0,0,1,  0,1,1,1,0,1,1,0,  0,0,0,1,1,0,0,1,  0,1,0,1,0,0,0,1,  0,1,0,1,1,0,0,1,  0,0,1,1,1,0,0,1,
/* SSID */          1,0,0,0,0,1,1,0,
/* Control */		0,1,1,1,1,1,0,0,
/* PID */ 			0,0,0,0,1,1,1,1,
/* Info */			0,0,1,0,1,0,1,0, 1,0,1,0,0,0,1,0, 1,1,0,0,1,0,1,0, 0,0,1,0,1,0,1,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
/* FCS */		   //0,1,0,1,0,1,0,0, 0,1,0,0,0,1,0,1};
					1,0,0,0,1,1,0,0, 1,1,0,0,1,0,1,0,
/* Flag */			0,1,1,1,1,1,1,0};

	printf("\n************************************\\ Decoding example /*************************************\n");

	printDest(fr);
	printSource(fr);

	// recebe a INFO decodificada ja em ASCII e mostra da tela
	infoRecep = printInfo(fr);
	//cout<<strlen((char*)infoRecep)<<endl;

	// recebe o FSC decodificado em ASCII
	infoCRC = checkCRC(fr);
	//cout<<strlen((const char*)infoRecep)<<endl;

	testCRC = infoRecep; // apontam para o mesmo endereco

	for(i=0; infoRecep[i]; i++, infoRecepTam++); // outra forma de contar o tamanho do vetor
	//cout<<"tam: "<<infoRecepTam<<endl;

	//for(i=0; i<infoRecepTam; i++) testCRC[i] = infoRecep[i];

	//testCRC[4] = 0;

	//testCRC = testCRC-1;


	for(i=0; i<infoRecepTam;i++) testCRC[i] = infoRecep[i]; // talvez sem necessidade, so foi criado pra dar compatibilidade com a funcao crctablefast();
	for(i= infoRecepTam; i<infoRecepTam+2;i++) testCRC[i] = infoCRC[i-infoRecepTam]; // INFO+CRC para testar se o CRC eh valido
	//cout<<"i: "<< i<<endl;
	testCRC[infoRecepTam+2] = '\0';

	//cout<<testCRC<<endl;


	/* Verifica se o FCS field esta correto */

	/* Verificar no site http://www.zorc.breitbandkatze.de/crc.html */

	// unsigned int crctablefast (unsigned char* p, unsigned int len);
	if (!crctablefast(testCRC, strlen((const char*)testCRC)))
			cout<<"Test CRC is correct!" << endl;
	//cout<<"Test CRC:"<< (int)crctablefast((unsigned char *)testCRC, strlen((const char*)testCRC)) << endl;


	//initInfo(a);

	return 0;
}


void controlField(int *a, int nelems){
	int i;

	//for(i=0; i<nelems; i++)
		if(a[nelems-1] == 0)
			Iframes(a, nelems);
		else if(a[nelems-1] == 1 and a[nelems-2] == 0)
			Sframes(a, nelems);
		else
			Uframes(a, nelems);
}

void Iframes (int *a, int nelems){
	int n_s[3], n_r[3], i;
	int P = 0;

	flipbits(a, nelems);

	P = a[4]; //faz algo aqui dependendo do valor de P

	for (i=1; i<=3; i++) // pode ter mais 3 bits
		n_s[i] = a[i];

	for (i=5; i<=7; i++) // pode ter mais que 3 bits
		n_r[i] = a[i];

}

void Sframes (int *a, int nelems){
	int n_r[3], P, i;
	//int numElems = 8;

	flipbits(a, nelems);

	P = a[4];
	for (i=5; i<=7; i++) n_r[i] = a[i];

	if (a[2] == 0 and a[3] == 0){ // Se RR (Receive Ready), System Ready To Receive.
		ready = 1;
		P = 1;

	}

	if (a[2] == 0 and a[3] == 1){ // Se RNR (Receive Not Ready), TNC Buffer Full.
		ready = 0;
	}

	if (a[2] == 1 and a[3] == 0){ // Se REJ (Reject Frame), Out of Sequence or Duplicate.
		P = 1;
	}

	if (a[2] == 1 and a[3] == 1){ // Se SREJ (Selective Reject), Request single frame repeat.

	}
}

void Uframes (int *a, int nelems){


	flipbits(a, nelems);

	if (a[2] == 1 and a[3] == 1 and a[5] == 1 and a[6] == 1 and a[7] == 0){ // SABME (Set Async Balanced Mode) -- Connect Request Extended (modulo 128)
		//
		// Information fields are not allowed
	}

	if (a[2] == 1 and a[3] == 1 and a[5] == 1 and a[6] == 0 and a[7] == 0){ // SABM (Set Async Balanced Mode) -- Connect Request
		// envia de volta um UA frame o mais cedo possivel
		// Information fields are not allowed
	}

	if (a[2] == 0 and a[3] == 0 and a[5] == 0 and a[6] == 1 and a[7] == 0){ // DISC (Disconnect request)
		// envia de volta um UA frame o mais cedo possivel
		// An information field is not permitted in	a DISC command frame.
		// P/F bit set to “1”.
	}

	if (a[2] == 1 and a[3] == 1 and a[5] == 0 and a[6] == 0 and a[7] == 0){ // DM (Disconnect Mode) - System Busy or Disconnected.
		//
		//The DM response does not have an information field.
	}

	if (a[2] == 0 and a[3] == 0 and a[5] == 1 and a[6] == 1 and a[7] == 0){ // UA (Unnumbered Acknowledge)
		// Responde um UA frame se SABM(E) or DISC command foi recebido
		// Information fields are not permitted in a UA frame.
	}

	if (a[2] == 1 and a[3] == 0 and a[5] == 0 and a[6] == 0 and a[7] == 1){ // FRMR (Frame Reject)
		// information field
	}

	if (a[2] == 0 and a[3] == 0 and a[5] == 0 and a[6] == 0 and a[7] == 0){ // UI (Unnumbered Information)
		// contains PID and information fields
		// if P = 1, it must response a DM frame when in the disconnected state, or an RR (or RNR, if appropriate) frame in the information transfer state.
	}

	if (a[2] == 1 and a[3] == 1 and a[5] == 1 and a[6] == 0 and a[7] == 1){ // XID (Exchange Identification) - Negotiate features.
		// information field is optional
		// The information elements start with a Format Identifier (FI) octet. The second octet is the Group Identifier (GI). The third and forth octets form the Group Length (GL).
		// FI = 82x; GI = 80x;
		// returns an XID response unless a UA response to a mode setting command is awaiting transmission,	or a FRMR condition exists.
	}

	if (a[2] == 0 and a[3] == 0 and a[5] == 1 and a[6] == 1 and a[7] == 1){ // TEST
		//
		// information field is optional
	}
}

void findFlag (int *a, int nelems){
	int i, flag[8] = {0,1,1,1,1,1,1,0};
	int bit_Flag_status = 0;

	for (i=0; i<8; i++){
		if (a[i] == flag[i]){
			bit_Flag_status = 1;
			//if (bit_Flag_status) cout << "Start frame" << endl;
		}
		else {
			bit_Flag_status = 0;
			cout << "Start Flag not found." << endl;
			break;
		}
	}

	// cout << "tamanho de a:" << nelems << endl;
	if (bit_Flag_status) cout << "Start frame." << endl;

	bit_Flag_status = 0;

	for (i=0; i<8; i++){
		if (a[nelems-1-i] == flag[i]) bit_Flag_status = 1;
		else {
			bit_Flag_status = 0;
			cout << "Final Flag not found." << endl;
			break;
		}
	}

	if (bit_Flag_status) cout << "End frame." << endl;
}

void findAddress(int *a, int nelems){

	int i,j;
	int v[8]; // forma um octeto com 8 bits
	int C_dest = a[47]; // Receive the Command/Response bit of SSID destination
						// Bit position added the Flag
	int C_source = a[119]; // Receive the Command/Response bit of SSID source
						   // Bit position added the Flag

	/* Because all frames are considered to be either commands or responses,
	 * a device always has one of the bits set to “1” and the other bit set to “0”.
	 */

	if (C_dest == 1 and C_source == 0){
		// is a command
	}
	else if(C_dest == 0 and C_source == 1){
		// is a response
	}

	for(j=0; j<nelems; j=j+8){
		for(i=j; i<j+8; i++)
			v[i-j] = a[i];

		flipbits(v, 8);

		if (v[0] == 1)
			cout << "Fim do campo Address." <<endl; // Encontrou o ultimo octeto do campo Address
	}
}
