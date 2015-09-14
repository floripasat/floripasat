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


// CRC parameters (default values are for CRC-CCITT):

const int order = 16;
const unsigned int polynom = 0x1021;
const int direct = 1;
const unsigned int crcinit = 0xffff;
const unsigned int crcxor = 0x0000;
const int refin = 0;
const int refout = 0;


int ready = 1;

// subroutines

void flipbits (int *a, int nelems);

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

	for(i=0; i<256; i++) a[i] = 0;

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

/* Transforma caracteres em bits e os inverte */
void fullAddressDest(int *l, char *c, int tam_c, int tam_c_bits, int *SSID_dest){

	int i, k=0, j;
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

		for (j = 48; j<56; j++)	l[j] = SSID_dest[j-48];
}

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

			if (isdigit(temp)) {m[k] = 0; k++; //printf("0");
			}
		}
		//printf("\n");

		initAddress(m,tam_c_bits);

		for (i = 48; i<56; i++)	m[i] = SSID_source[i-48];
}

void fullInfo(int *infoFIELD, unsigned char *inform, int tam_c, int tam_c_bits){

	int i, k=0;
	char temp;

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
	char destChar[6] = "\n";

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
	char sourceChar[6] = "\n";

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
	unsigned char infoChar[256] = "\n";

	cont = 0;
		for(j = 0; j<256; j++){
			for(i=136+cont; i<136+8+cont; i++){
				temp = temp + fr[i]*pow(2,i-cont-136);
			}
			infoChar[j] = temp;
			cont = i-136;
			//cout<<j <<endl;
			temp = 0;
			if (infoChar[j] == 00000000) break; // se encontrou "\n", conclui-se que nao ha mais informacao
		}
		cout<< "Info: " <<infoChar <<endl;
		return infoChar;
}

unsigned char * checkCRC(int *fr){
	int i, j, cont, temp = 0;
	unsigned char CRC_Char[16] = "\n";

	//unsigned char ar[16] = {0,1,0,1,0,1,0,0, 0,1,0,0,0,1,0,1};

	cont = 0;
		for(j=0; j<2; j++){ // numero de octetos a ser contato
			for(i=192+8+cont-1; i>=192+cont; i--){
				temp = temp + fr[i]*pow(2,-i-1+8+cont+192);
			}
			CRC_Char[j] = temp;
			cont = i+8+1-192;
			//cout<<j <<endl;
			temp = 0;
		}

		for(i=0;i<2;i++) printf("%c", CRC_Char[i]);
		printf("\n");
		//printf("%s",CRC_Char);
		return CRC_Char;
}

int main() {

	int a [] = {0,1,1,1,1,1,1,0,  1,0,0,1,  0,1,1,1,1,1,1,0};
	static int d[56], m[56];
	int pid[8] = {1,1,1,1,0,0,0,0}; // No layer 3 protocol implemented
	int flag[8] = {0,1,1,1,1,1,1,0};
	int control[8] = {0,0,1,1,1,1,1,0}; // Valor inicial para Control Field
	static int frame[416];
	int infoRecepTam = 0;

	static int infoField[256];

	static unsigned char info[] = {"TEST"};
	static unsigned char *infoCRC;
	unsigned char *infoRecep;
	unsigned char *testCRC = NULL;
	//info[4] = 0x8c;
	//info[5] = 0xca;
	//info[6] = 00000000;

	int contBits = 0;


	/* ---------------------------------------------------- */
	FILE *fp;

	int tam_dest, tam_dest_bits, tam_source, tam_source_bits, tam_info, tam_info_bits;
	unsigned int CRC;
	int i,j;
	static int *binCRC;

	char destination[] = "1B0"; // Endereco de destino
	int SSID_dest[8] = {0,1,1,0,0,0,0,0}; // SSID de destino
	int C_bit_dest = 0; // indica que tem mais enderecos

	SSID_dest[0] = C_bit_dest; // seta o bit "C" do destino

	char source[] = "01B"; // Endereco de origem
	int SSID_source[8] = {1,1,1,0,0,0,0,1}; // SSID de origem
	int C_bit_source = 1; // indica que eh o ultimo octeto do campo Address

	SSID_source[0] = C_bit_source; // seta o bit "C" da origem

	tam_dest = (sizeof(destination)/sizeof(destination[0]))-1; // tamanho em do destino caracteres
	tam_dest_bits = tam_dest*8; // tamanho da mensagem do destino em 8 bits

	tam_source = (sizeof(source)/sizeof(source[0]))-1; // tamanho em da origem caracteres
	tam_source_bits = tam_source*8; // tamanho da mensagem da origem em 8 bits

	/* Inverte SSID do destino */
	flipbits(SSID_dest, 8);

	/* Inverte SSID da origem */
	flipbits(SSID_source, 8);

	/* Inverte o octeto de controle */
	flipbits(control, 8);

	/* Inverte o PID */
	flipbits(pid, 8);

	/* Preenche o endereco de destino (invertido) em bits e o seu SSID */
	fullAddressDest(d, destination, tam_dest, tam_dest_bits, SSID_dest);

	/*
	cout<<"Valor de d:  ";
	for (i = 0; i<56; i++) cout<<d[i];
	cout<<endl;
	*/

	/* Preenche o endereco de origem (invertido) em bits e o seu SSID */
	fullAddressSource(m, source, tam_source, tam_source_bits, SSID_source);

	/*
	cout<<"Valor de m:  ";
		for (i = 0; i<56; i++) cout << m[i];
	cout<<endl;
	*/


	/****************************************************\ Field FCS /****************************************************/

	/* Calculo do CRC */
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

	/*********************************************************************************************************************/



	/****************************************************\ Field Info /****************************************************/

	/* Faz o calculo do tamanho da innformacao em bits */
	tam_info = (sizeof(info)/sizeof(info[0]))-1;
	tam_info_bits = tam_info*8;

	/* Inicializa o campo Info com zeros */
	initInfo(infoField);

	/* Preenche a informacao no campo Info */
	fullInfo(infoField, info, tam_info, tam_info_bits); // converte de ASCII --> 8bit

	printf("info field: ");
	for(i=0; i<50; i++) printf("%d", infoField[i]);
	printf("\n");

	/*********************************************************************************************************************/



	/**************************************************\ Make the Frame /*************************************************/
	/* Preenche a flag incial*/
	for (i=0; i<8; i++)	frame[i] = flag[i];

	/* Preenche o destino e SSID */
	for (j=8; j<64; j++) frame[j] = d[j-8];

	/* Preenche a origem e SSID */
	for (j=64; j<120; j++) frame[j] = m[j-64];

	/* Preenche o Control Field */
	for(j=120; j<128; j++) frame[j] = control[j-120];

	/* Preenche o PID */
	for(j=128; j<136; j++) frame[j] = pid[j-128];

	/* Preenche a informacao */
	for(j=136; j<392; j++) frame[j] = infoField[j-136];

	/* Preenche o FCS */
	for(j=392; j<408; j++) {
		frame[j] = *binCRC;
		binCRC = binCRC+1;
	}

	/* Preenche a flag final */
	for (j=408; j<416; j++)	frame[j] = flag[j-408];


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
	}while(i<416);

	fclose(fp);

	/*********************************************************************************************************************/

	/**************************************************\ Read from File /*************************************************/

	if((fp = fopen("frame.txt","r")) == NULL){
		printf("O arquivo nao pode ser aberto.\n");
		exit(1);
	}

	char ch;
	int frameRecep[416];

	ch = getc(fp); /* Le "0"s e "1"s em ASCII */
	i=0;

	while(ch!=EOF){
		printf("%c",ch); /* imprime na tela*/

		if (ch == '0')	frameRecep[i] = 0; /* Preenche "0"s e "1"s em vetor de inteiros */
		else if (ch == '1') frameRecep[i] = 1;

		i++;
		ch = getc(fp); /* Le "0"s e "1"s em ASCII */
	}

	fclose(fp);
	printf("\n");

	for(i=0;i<416;i++)	printf("%d",frameRecep[i]); /* imprime na tela*/
	printf("\n");

	/*********************************************************************************************************************/




	//flipbits(b, sizeof(b)/sizeof(b[0]));
	//cout <<"B: "<< b << endl;

	//findFlag(a, tam_a);
	//findAddress(b, 16);

	static int fr[] ={
/* Flag */			0,1,1,1,1,1,1,0,
/* Destination */	0,0,1,0,0,1,0,1,  0,1,0,1,0,0,0,1,  0,1,0,1,1,0,0,1,  0,1,1,1,1,0,0,1, 0,1,1,0,0,1,1,0, 0,1,1,0,0,1,1,0,
/* SSID */			0,0,0,0,1,1,1,1,
/* Source */		0,0,1,1,1,0,0,1,  0,1,1,1,0,1,1,0,  0,0,0,1,1,0,0,1,  0,1,0,1,0,0,0,1, 0,1,0,1,1,0,0,1, 0,0,1,1,1,0,0,1,
/* SSID */          1,0,0,0,0,1,1,0,
/* Control */		0,1,1,1,1,1,0,0,
/* PID */ 			0,0,0,0,1,1,1,1,
/* Info */			0,0,1,0,1,0,1,0, 1,0,1,0,0,0,1,0, 1,1,0,0,1,0,1,0, 0,0,1,0,1,0,1,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
/* FCS */		   //0,1,0,1,0,1,0,0, 0,1,0,0,0,1,0,1};
					1,0,0,0,1,1,0,0, 1,1,0,0,1,0,1,0,
/* Flag */			0,1,1,1,1,1,1,0};

	printDest(fr);
	printSource(fr);
	infoRecep = printInfo(fr);
	//cout<<strlen((char*)infoRecep)<<endl;
	infoCRC = checkCRC(fr);
	//cout<<strlen((const char*)infoRecep)<<endl;

	testCRC = infoRecep;

	for(i=0; infoRecep[i]; i++, infoRecepTam++);
	//cout<<"tam: "<<infoRecepTam<<endl;

	//for(i=0; i<infoRecepTam; i++) testCRC[i] = infoRecep[i];

	//testCRC[4] = 0;

	//testCRC = testCRC-1;


	for(i=0; i<infoRecepTam;i++) testCRC[i] = infoRecep[i];
	for(i= infoRecepTam; i<6;i++) testCRC[i] = infoCRC[i-infoRecepTam];
	testCRC[6] = 0;

	//for(i=0; i<4 ;i++)	testCRC[i] = infoRecep[i];

	//for(i=4; i<6 ;i++)	testCRC[i] = infoCRC[i-4];

	cout<<testCRC<<endl;

	/* Verifica se o FCS field esta correto */
	if (!(int)crctablefast((unsigned char *)testCRC, strlen((const char*)testCRC)))
			cout<<"Test CRC is correct!" << endl;
	//cout<<"Test CRC:"<< (int)crctablefast((unsigned char *)testCRC, strlen((const char*)testCRC)) << endl;


	initInfo(a);

	return 0;
}

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
