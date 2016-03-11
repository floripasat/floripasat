
#include "hal.h"
// Global Variables
char 		  i;									// task counter
void 		  (*ScheduleTasks[TASK_NUMBER])(void);	// store functions pointers tasks to be executed
int 		  ScheduleTaskPeriod[TASK_NUMBER]; 		// store each temporization task
int 		  ActualTaskTiming[TASK_NUMBER]; 		// store how many miliseconds is missing to execute each task
char 		  FlagGenerateByTimerA0Interruption;    // signaling timer0 interruption
volatile char ThereIsTaskInExecution;
int 		  TaskTimeout;							// time-out counter

// I2C DATA
unsigned char TXData;
unsigned char TXByteCtr;
unsigned int  TxFlag;
unsigned char RXData;

//prototypes:
//1-funções  gerais
void ConfigureTimerA0(void);
void SetTimerA0(unsigned int ttimer);
void InicializeTask	(void);
void ExecuteTask	(void);
void I2CReadInit(void);

//2-tarefas a serem executadas
void Task_1(void);
void Task_2(void);
void Task_3(void);
void Task_4(void);

// temporization configuration
void InicializeTask	(void)
{
	ScheduleTasks[TASK_1] = Task_1;
	ScheduleTasks[TASK_2] = Task_2;
	ScheduleTasks[TASK_3] = Task_3;
	ScheduleTasks[TASK_4] = Task_4;

	ScheduleTaskPeriod[TASK_1] = TIME_EXECUTION_TASK_1;
	ScheduleTaskPeriod[TASK_2] = TIME_EXECUTION_TASK_2;
	ScheduleTaskPeriod[TASK_3] = TIME_EXECUTION_TASK_3;
	ScheduleTaskPeriod[TASK_4] = TIME_EXECUTION_TASK_4;

	ActualTaskTiming[TASK_1] = TIME_EXECUTION_TASK_1;
	ActualTaskTiming[TASK_2] = TIME_EXECUTION_TASK_2;
	ActualTaskTiming[TASK_3] = TIME_EXECUTION_TASK_3;
	ActualTaskTiming[TASK_4] = TIME_EXECUTION_TASK_4;

	// no task to be executed now
	ThereIsTaskInExecution = NO;
}

void ConfigureTimerA0(void)
{
	FlagGenerateByTimerA0Interruption = NO;

	CCTL0 = CCIE;                           // CCR0 interrupt enabled
	SetTimerA0(50000);
	TACTL = TASSEL_2 + MC_1 + ID1;                // SMCLK, upmode -  SMCLK = 1 MHz, SMCLK/1 = 1 MHz (1 us)
}

void SetTimerA0(unsigned int ttimer){ CCR0 = ttimer; /*Number of cycles in the timer*/ }

void ExecuteTask (void)
{
	if (i > TASK_NUMBER-1) i = 0;

	// Check null pointer
	if(ScheduleTasks[i] !=0)
	{
		// CHECK TASK TIME AND EXECUTE TASK
		if (ActualTaskTiming[i] == 0)
		{
			ThereIsTaskInExecution = YES;
			TaskTimeout = TIMEOUT_TASK;
			ScheduleTasks[i](); 		// execute task
			ThereIsTaskInExecution = NO;
			ActualTaskTiming[i] = ScheduleTaskPeriod[i]; // reescheduling task
			i = i + 1;
		}
	}
}

int main(void)
{

  i = 0;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output

  P3SEL |= 0x06;                            // Assign I2C pins to USCI_B0
  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;
  UCB0I2CSA = 0x48;                         // Slave Address is 048h
  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
  IE2 |= UCB0TXIE;                          // Enable TX interrupt
  IE2 |= UCB0RXIE;							// Enable RX Interrupt

  TXData = 0x00;                            // Holds TX data

  InicializeTask();
  ConfigureTimerA0();

  // main scheduling looping
  while(1)
  {

	  TXByteCtr = 1;                          // Load TX byte counter

	  __bis_SR_register(GIE);
	  if ((FlagGenerateByTimerA0Interruption == YES))
	  {
		  FlagGenerateByTimerA0Interruption = NO;
		  ExecuteTask();					// SYSTEM TASKS - EACH TASK HAS THEIR OWN "TIME"
	  }

	  TXData++;
  }
}

// TIMER_A0 INTERRUPTION
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0

  if (CCIFG == 1)
  {
	  FlagGenerateByTimerA0Interruption = YES;

	  // INCREASE TASK TIME
	  if (ActualTaskTiming[i] > 0) ActualTaskTiming[i]--;

	  // TIMEOUT ROUTINE
	  if (ThereIsTaskInExecution == YES)
	  {
		  TaskTimeout = TaskTimeout - 1;
	      if ( TaskTimeout == 0 )
	      {
	    	  WDTCTL = 0;  // reset all system
	      }
	  }
  }
}

// I2C INTERRUPTION
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  if(TxFlag){

	  if (TXByteCtr)                            // Check TX byte counter
	  {
		  //UCB0TXBUF = 0x55;                     // Load TX buffer
		  UCB0TXBUF = TXData;
		  TXByteCtr--;                            // Decrement TX byte counter
	  }
	  else
	  {
		  UCB0CTL1 |= UCTXSTP;                    // I2C stop condition
		  IFG2 &= ~UCB0TXIFG;                     // Clear USCI_B0 TX int flag
		  //__bic_SR_register_on_exit(CPUOFF);      // Exit LPM0
	  }
  }
  	  else{
	  RXData = UCB0RXBUF;                       // Get RX data
	  IFG2 &= ~UCB0TXIFG;
  }
}

void Task_1(void)
{ /*todo*/
	P1OUT = 0x01;
	SetTimerA0(65350);
	TxFlag = 1;								// I2C Write

	//UCB0TXBUF = 0x55;                     // Load TX buffer

	while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
	UCB0CTL1 |= UCTR + UCTXSTT;             // I2C TX, start condition

}
void Task_2(void)
{ /*todo*/
	P1OUT = 0x01;
	SetTimerA0(65350);
	TxFlag = 0;								// I2C Read
	I2CReadInit();

	//UCB0TXBUF = 0xFF;

	while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
	UCB0CTL1 &= ~UCTXSTT;					// Clear start condition
	__delay_cycles(50);
	UCB0CTL1 |=UCTXSTT;             // I2C TX, start condition


	//while(1); // for debug timeout
}
void Task_3(void)
{ /*todo*/
	P1OUT = 0x01;
	SetTimerA0(20000);
}
void Task_4(void)
{ /*todo*/
	P1OUT = 0x01;
	SetTimerA0(65350);

}

void I2CReadInit(void)
{
    UCB0CTL1 &= ~UCTR;                      // UCTR=0 => Receive Mode (R/W bit = 1)
    IFG2 &= ~UCB0RXIFG;                     // Clear RXIFG flag
    IE2 &= ~UCB0TXIE;                       // disable Transmit ready interrupt
    IE2 |= UCB0RXIE;                        // enable Receive ready interrupt
}
