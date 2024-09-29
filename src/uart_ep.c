/***********************************************************************************************************************
 * File Name    : uart.c
 * Description  : Contains UART functions definition.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* Copyright (c) 2020 - 2024 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
***********************************************************************************************************************/
/*  */

#include "common_utils.h"
#include "uart_ep.h"
#include "uart_pc.h"
#include "timer_pwm.h"

/*******************************************************************************************************************//**
 * @addtogroup r_sci_uart_ep
 * @{
 **********************************************************************************************************************/

/*
 * Private function declarations
 */

/*
 * Private global variables
 */
/* Temporary buffer to save data from receive buffer for further processing */
static uint8_t g_temp_buffer[DATA_LENGTH] = {RESET_VALUE};

/* Counter to update g_temp_buffer index */
static volatile uint8_t g_counter_var = RESET_VALUE;

/* Flag to check whether data is received or not */
static volatile uint8_t g_data_received_flag = false;

/* Flag for user callback */
static volatile uint8_t g_uart_event = RESET_VALUE;

/*****************************************************************************************************************
 *  @brief       UART Example project to demonstrate the functionality
 *  @param[in]   None
 *  @retval      FSP_SUCCESS     Upon success
 *  @retval      Any Other Error code apart from FSP_SUCCESS
 ****************************************************************************************************************/
fsp_err_t uart_ep_voice(void)
{
    fsp_err_t err = FSP_SUCCESS;

    while (true)
    {
        if(g_data_received_flag)
        {
            g_data_received_flag  = false;
            uint8_t input_length = RESET_VALUE;

            /* Calculate g_temp_buffer length */
            input_length = ((uint8_t)(strlen((char *) &g_temp_buffer)));

            /* Check if input data length is in limit */
            if (((uint8_t)input_length > 0) && (g_temp_buffer[0] == CARRIAGE_ASCII))
            {
                err = uart_print_user_msg(g_temp_buffer);// reply
                if (FSP_SUCCESS != err)
                {
                    APP_PRINT ("\r\n ** UART0 FAILED *uart0_print_user_msg* \r\n");
                    timer_gpt_deinit();
                    deinit_pc_uart();
                    APP_ERR_TRAP(err);
                }
            }
        } 
    }
}

/*******************************************************************************************************************//**
 * @brief       Initialize  UART.
 * @param[in]   None
 * @retval      FSP_SUCCESS         Upon successful open and start of timer
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful open
 ***********************************************************************************************************************/
fsp_err_t uart_initialize(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Initialize UART channel with baud rate 115200 */
#if defined (BOARD_RA6T2_MCK) || defined (BOARD_RA8M1_EK)
    err = R_SCI_B_UART_Open (&g_uart0_ctrl, &g_uart0_cfg);
#else
    err = R_SCI_UART_Open (&g_uart0_ctrl, &g_uart0_cfg);
#endif
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n**  R_SCI_UART_Open API failed  **\r\n");
    }
    return err;
}

/*****************************************************************************************************************
 *  @brief       print user message to terminal
 *  @param[in]   p_msg
 *  @retval      FSP_SUCCESS                Upon success
 *  @retval      FSP_ERR_TRANSFER_ABORTED   Upon event failure
 *  @retval      Any Other Error code apart from FSP_SUCCESS,  Unsuccessful write operation
 ****************************************************************************************************************/
fsp_err_t uart_print_user_msg(uint8_t *p_msg)
{
    fsp_err_t err   = FSP_SUCCESS;
    uint8_t msg_len = RESET_VALUE;
    uint32_t local_timeout = (DATA_LENGTH * UINT16_MAX);
    uint8_t *p_temp_ptr = (uint8_t *)p_msg;

    /* Calculate length of message received */
    msg_len = ((uint8_t)(strlen((char *)p_temp_ptr)));

    /* Reset callback capture variable */
    g_uart_event = RESET_VALUE;

    /* Writing to terminal */
#if defined (BOARD_RA6T2_MCK) || defined (BOARD_RA8M1_EK)
    err = R_SCI_B_UART_Write (&g_uart0_ctrl, p_msg, msg_len);
#else
    err = R_SCI_UART_Write (&g_uart0_ctrl, p_msg, msg_len);
#endif

    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n**  R_SCI_UART_Write API Failed  **\r\n");
        return err;
    }

    /* Check for event transfer complete */
    while ((UART_EVENT_TX_COMPLETE != g_uart_event) && (--local_timeout))
    {
        /* Check if any error event occurred */
        if (UART_ERROR_EVENTS == g_uart_event)
        {
            APP_ERR_PRINT ("\r\n**  UART Error Event Received  **\r\n");
            return FSP_ERR_TRANSFER_ABORTED;
        }
    }
    if(RESET_VALUE == local_timeout)
    {
        err = FSP_ERR_TIMEOUT;
    }
    return err;
}

/*******************************************************************************************************************//**
 *  @brief      Deinitialize SCI UART module
 *  @param[in]  None
 *  @retval     None
 **********************************************************************************************************************/
void deinit_uart(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Close module */
#if defined (BOARD_RA6T2_MCK) || defined (BOARD_RA8M1_EK)
    err =  R_SCI_B_UART_Close (&g_uart0_ctrl);
#else
    err =  R_SCI_UART_Close (&g_uart0_ctrl);
#endif

    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n**  R_SCI_UART_Close API failed  ** \r\n");
    }
}

/*****************************************************************************************************************
 *  @brief      UART user callback
 *  @param[in]  p_args
 *  @retval     None
 ****************************************************************************************************************/
void user_uart_callback(uart_callback_args_t *p_args)
{
    /* Logged the event in global variable */
    g_uart_event = (uint8_t)p_args->event;

    /* Reset g_temp_buffer index if it exceeds than buffer size */
    if(DATA_LENGTH == g_counter_var)
    {
        g_counter_var = RESET_VALUE;
    }

    if(UART_EVENT_RX_CHAR == p_args->event)
    {
        switch (p_args->data)
        {
            /* If Enter is pressed by user, set flag to process the data */
            case CARRIAGE_ASCII:
            {
                g_counter_var = RESET_VALUE;
                g_data_received_flag  = true;
                break;
            }
            /* Read all data provided by user until enter button is pressed */
            default:
            {
                g_temp_buffer[g_counter_var++] = (uint8_t ) p_args->data;
                break;
            }
        }
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup r_sci_uart_ep)
 **********************************************************************************************************************/
