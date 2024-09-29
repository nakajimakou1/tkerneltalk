/***********************************************************************************************************************
 * File Name    : uart_pc.h
 * Description  : Contains function declaration of uart_pc.c and Macros.
 **********************************************************************************************************************/

#ifndef UART_PC_H_
#define UART_PC_H_

#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_sci_b_uart.h"
#include "r_uart_api.h"

/* Macro definition */
#define CARRIAGE_ASCII            (13u)     /* Carriage return */
#define ZERO_ASCII                (48u)     /* ASCII value of zero */
#define NINE_ASCII                (57u)     /* ASCII value for nine */
#define DATA_LENGTH               (4u)      /* Expected Input Data length */
#define MAX_RCVLENGTH             (8u)
#define UART_PC_ERROR_EVENTS      ( UART_EVENT_BREAK_DETECT | \
                                    UART_EVENT_ERR_OVERFLOW | \
                                    UART_EVENT_ERR_FRAMING  | \
                                    UART_EVENT_ERR_PARITY)    /* UART Error event bits mapped in registers */

/* Function declaration */
fsp_err_t uart_pc_com(void);
fsp_err_t uart_print_pc_msg(uint8_t *p_msg);
fsp_err_t uart_pc_init(void);
void uart_pc_close(void);
void deinit_pc_uart(void);

/** UART on SCI Instance. */
extern const uart_instance_t g_pc_uart;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_b_uart_instance_ctrl_t g_pc_uart_ctrl;
extern const uart_cfg_t g_pc_uart_cfg;
extern const sci_b_uart_extended_cfg_t g_pc_uart_cfg_extend;

#ifndef uart_pc_callback
void uart_pc_callback(uart_callback_args_t *p_args);
#endif

fsp_err_t uart2_com(void);
fsp_err_t uart2_print_msg(uint8_t *p_msg);
fsp_err_t uart2_init(void);
void uart2_close(void);
void deinit_uart2(void);

/** UART on SCI Instance. */
extern const uart_instance_t g_uart2;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_b_uart_instance_ctrl_t g_uart2_ctrl;
extern const uart_cfg_t g_uart2_cfg;
extern const sci_b_uart_extended_cfg_t g_uart2_cfg_extend;

#ifndef uart2_callback
void uart2_callback(uart_callback_args_t *p_args);
#endif

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif

#endif /* UART_PC_H_ */
