/*************************************************************************
 *
 *			Terminal configure file
 *
 *	---------------------------------------------------------------------
 *
 *	Examples in Readme.h file.
 *
 ************************************************************************/

#ifndef _TERMIANL_CONFIG_H_
#define _TERMIANL_CONFIG_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>		
	
// strtol, itoa
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_hal.h"

// ****************************** Code keys ********************************

#define _KEY_INIT(c)					((char)c)

#define TERM_KEY_ENTER					(_KEY_INIT(0x0D))		// Enter command symbol
#define TERM_KEY_BACKSPACE				(_KEY_INIT(0x08))		// Delete character before cursor 
#define TERM_KEY_LSHIFT					(_KEY_INIT(0x08))		// Left shift symbol
#define TERM_KEY_ESCAPE					(_KEY_INIT(0xF0))		// Exception execute command symbol
#define TERM_KEY_UP						(_KEY_INIT(0xF1))		// KeyUp symbol
#define TERM_KEY_RIGHT					(_KEY_INIT(0xF2))		// KeyRight symbol
#define TERM_KEY_DOWN					(_KEY_INIT(0xF3))		// KeyDown symbol
#define TERM_KEY_LEFT					(_KEY_INIT(0xF4))		// KeyLeft symbol
#define TERM_KEY_DEL					(_KEY_INIT(0xF5))		// Delete character after cursor position
#define TERM_KEY_HOME					(_KEY_INIT(0xA0))		// Home key
#define TERM_KEY_END					(_KEY_INIT(0xA1))		// End key
#define TERM_KEY_TAB					(_KEY_INIT(0x09))		//
#define TERM_KEY_RESET					'~'						// Reset CPU

// **************************************************************************

// ********************** Terminal Settings *********************************

#define _TERM_VER_				"v1.4"				// Terminal version
#define TERM_SIZE_TASK          (8)				// Max number of commands
#define TERM_CMD_BUF_SIZE		(200)				// Max number of character buffer string command
#define TERM_CMD_LOG_SIZE		(5)				// Max number of loging command
#define TERM_ARGS_BUF_SIZE		(200)				// Max number of arguments in one command
#define TERM_ARG_SIZE			(15)				// Max number character of one arguments
#define CHAR_INTERRUPT			TERM_KEY_ESCAPE 	// Abort execute command key-code symbol
#define STRING_TERM_ENTER		"\n\r"				// String new line
#define STRING_TERM_ARROW		">> "				// String arrow enter
#define RESET_FCN()					NVIC_SystemReset()				// Reset CPU Function

#define TERM_TIMELEFT_EN				(1)			// Calculate time
#define TERM_TX_RX_EN					(1)			// Terminal Printf (without this don,t work)
#define TERM_TX_RX_DEB_EN				(0)			// Addition debug printf
#define TERM_CMD_LOG_EN					(1)			// Command logging
#define TERM_CMD_AUTOCMPLT_EN			(1)			// Command AutoComplete
#define TERM_LR_KEY_EN					(1)			// Move cursor left-rigth
#define TERM_DEFAULT_ALLOC_EN			(1)			// Default Memory Allocate functions
#define TERM_DEFAULT_STRING_EN			(1)			// Default String functions
#define TERM_PRINT_ERROR_EXEC_EN		(1)			// Print error after execute command
#define TERM_PRINT_ERROR_ADD_CMD_EN		(1)			// Print error after added command
#define ECHO_EN							(1)			// Enter echo enable

// **************************************************************************

// ************************* IO Terminal Settings ***************************

#if (TERM_TX_RX_EN == 1)
#include <stdio.h>

#define Terminnal_PutString(string)  printf("%s",(string));
#define Terminal_PutChar(char) LL_USART_TransmitData8(USART1,char);

#define CLI_Printf		COM_Printf
#if (ECHO_EN == 1)
#define CLI_PutChar		Terminal_PutChar
#else	// ECHO_EN != 1
#define CLI_PutChar
#endif	// ECHO_EN == 1

#else	// TERM_TX_RX_EN != 1
#define CLI_Printf
#define CLI_PutChar
#endif	// TERM_TX_RX_EN == 1
// **************************************************************************

// *********************** IO Debug Terminal Settings ***********************

#if (TERM_TX_RX_DEB_EN == 1)
#define CLI_DPrintf		printf
#else	// TERM_TX_RX_DEB_EN != 1
#define CLI_DPrintf
#endif	// TERM_TX_RX_DEB_EN == 1

// **************************************************************************

// ************************ Time calculate Settings *************************

#if (TERM_TIMELEFT_EN == 1)

	// yout implementation
#define Get_SystemTick HAL_GetTick

#define CLI_GetUs()					((float)Get_SystemTick() * 10)	// System time in us
#define CLI_GetFastUs()				(Get_SystemTick << 3)			// System time in us (not exact)
#define CLI_GetFastMs()				(Get_SystemTick >> 7)			// System time in ms (not exact)
#define CLI_CounterReset()			{Get_SystemTick = 0;}

#else	// TERM_TIMELEFT_EN != 1

#define CLI_GetUs()					(0)			// System time in us
#define CLI_GetFastUs()				(0)			// System time in us (not exact)
#define CLI_GetFastMs()				(0)			// System time in ms (not exact)
#define CLI_CounterReset()			{}

#endif	// TERM_TIMELEFT_EN == 1

// **************************************************************************

// ********************** memory allocate functions *************************

#if (TERM_DEFAULT_ALLOC_EN == 1)

#define cli_malloc		malloc
#define cli_free		free
#else
#define cli_malloc		// your implementation
#define cli_free		// your implementation
#endif

// **************************************************************************

// *************************** string functions *****************************

#if (TERM_DEFAULT_STRING_EN == 1)
#include <string.h>
#define cli_memcpy		memcpy
#else
#define cli_memcpy		// your implementation
#endif

// **************************************************************************

#endif // _TERMIANL_CONFIG_H_
