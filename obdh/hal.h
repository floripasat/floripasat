#ifndef __HAL_H__
#define __HAL_H__

//------------------------------------------------
// basic definitions
#define BYTE unsigned char
#define WORD unsigned int
#define BOOL bool
#define TRUE 1
#define FALSE 0
//------------------------------------------------
// logger definitions
#define OP_RD  192 // 0b0110_0000 -- read opcode
#define OP_WR  160 // 0b1010_0000 -- write opcode

//------------------------------------------------
// scheduler definitions
#define YES                    1
#define NO                     0

#define TASK_0                 0
#define TASK_1                 1
#define TASK_2                 2
#define TASK_3                 3

#define TASK_NUMBER            4  // number of tasks

#define EXECUTION_TASK_0  2  //
#define EXECUTION_TASK_1  1  //
#define EXECUTION_TASK_2  2  //
#define EXECUTION_TASK_3  3  //

#define TIMEOUT_TASK           4  //

//-------------------------------------------------
// microntroller
#include <msp430g2553.h>

#endif
