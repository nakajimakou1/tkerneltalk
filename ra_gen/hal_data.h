/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_sci_b_uart.h"
#include "r_uart_api.h"
#include "r_gpt.h"
#include "r_timer_api.h"
FSP_HEADER
/** UART on SCI Instance. */
extern const uart_instance_t g_uart2;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_b_uart_instance_ctrl_t g_uart2_ctrl;
extern const uart_cfg_t g_uart2_cfg;
extern const sci_b_uart_extended_cfg_t g_uart2_cfg_extend;

#ifndef uart_pc_callback
void uart_pc_callback(uart_callback_args_t *p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t g_uart1;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_b_uart_instance_ctrl_t g_uart1_ctrl;
extern const uart_cfg_t g_uart1_cfg;
extern const sci_b_uart_extended_cfg_t g_uart1_cfg_extend;

#ifndef uart_pc_callback
void uart_pc_callback(uart_callback_args_t *p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t g_uart0;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_b_uart_instance_ctrl_t g_uart0_ctrl;
extern const uart_cfg_t g_uart0_cfg;
extern const sci_b_uart_extended_cfg_t g_uart0_cfg_extend;

#ifndef user_uart_callback
void user_uart_callback(uart_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer_ctrl;
extern const timer_cfg_t g_timer_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
