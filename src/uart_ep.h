/***********************************************************************************************************************
 * File Name    : uart_ep.h
 * Description  : Contains function declaration of uart_ep.c and Macros.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/

#ifndef UART_EP_H_
#define UART_EP_H_

/* Macro definition */
#define CARRIAGE_ASCII            (13u)     /* Carriage return */
#define ZERO_ASCII                (48u)     /* ASCII value of zero */
#define NINE_ASCII                (57u)     /* ASCII value for nine */
#define DATA_LENGTH               (4u)      /* Expected Input Data length */
#define MAX_DATA_LENGTH           (255u)    /* Max Input Data length */
#define UART_ERROR_EVENTS         (UART_EVENT_BREAK_DETECT | UART_EVENT_ERR_OVERFLOW | UART_EVENT_ERR_FRAMING | \
                                    UART_EVENT_ERR_PARITY)    /* UART Error event bits mapped in registers */

/* Function declaration */
fsp_err_t uart_ep_voice(void);
fsp_err_t uart_print_user_msg(uint8_t *p_msg);
fsp_err_t uart_initialize(void);
void deinit_uart(void);

#ifndef user_uart_callback
void user_uart_callback(uart_callback_args_t *p_args);
#endif

#endif /* UART_EP_H_ */
