/***********************************************************************************************************************
 * File Name    : uart.c
 * Description  : Contains UART functions definition.
 **********************************************************************************************************************/

#include "common_utils.h"
#include "uart_pc.h"
#include "uart_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup r_sci_uart_pc
 * @{
 **********************************************************************************************************************/

/*
 * Private function declarations
*/
/* uart pc */
/* Temporary buffer to save data from receive buffer for further processing */
static uint8_t g_pc_temp_buffer[MAX_DATA_LENGTH] = {RESET_VALUE};
static uint8_t g_pc_reply_buffer[MAX_DATA_LENGTH] = {"\r"};

/* Counter to update g_temp_buffer index */
static volatile uint8_t g_pc_counter_var = RESET_VALUE;

/* Flag to check whether data is received or not */
static volatile uint8_t g_pc_data_received_flag = false;

/* Flag for user callback */
static volatile uint8_t g_pc_uart_event = RESET_VALUE;

/*****************************************************************************************************************
 *  @brief       UART Example project to demonstrate the functionality
 *  @param[in]   None
 *  @retval      FSP_SUCCESS     Upon success
 *  @retval      Any Other Error code apart from FSP_SUCCESS
 ****************************************************************************************************************/
fsp_err_t uart_pc_com(void)
{
    fsp_err_t err = FSP_SUCCESS;
    while (true)
    {
        if(g_pc_data_received_flag)
        {
            g_pc_data_received_flag  = false;
            uint8_t input_length = RESET_VALUE;

            /* Calculate g_temp_buffer length */
            input_length = ((uint8_t)(strlen((char *) &g_pc_temp_buffer)));

            /* Check if input data length is in limit */
            if (input_length > 0)
            {
                /* send rcv data send to talk board */
                err = uart_print_pc_msg(g_pc_reply_buffer); // rcv data end reply
                if (FSP_SUCCESS != err)
                {
                    APP_PRINT ("\r\n ** UART0 FAILED *uart0_print_user_msg* \r\n");
                    deinit_pc_uart();
                    APP_ERR_TRAP(err);
                }

                err = uart_print_user_msg(g_pc_temp_buffer);// data send to talk board
                if (FSP_SUCCESS != err)
                {
                    APP_PRINT ("\r\n ** UART0 FAILED *uart0_print_user_msg* \r\n");
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
fsp_err_t uart_pc_init(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Initialize UART channel with baud rate 115200 */
#if defined (BOARD_RA6T2_MCK) || defined (BOARD_RA8M1_EK)
    err = R_SCI_B_UART_Open (&g_uart2_ctrl, &g_uart2_cfg);
#else
    err = R_SCI_UART_Open (&g_uart2_ctrl, &g_uart2_cfg);
#endif
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n**  R_SCI2_UART_Open API failed  **\r\n");
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
fsp_err_t uart_print_pc_msg(uint8_t *p_msg)
{
    fsp_err_t err   = FSP_SUCCESS;
    uint8_t msg_len = RESET_VALUE;
    uint32_t local_timeout = (DATA_LENGTH * UINT16_MAX);
    uint8_t *p_temp_ptr = (uint8_t *)p_msg;

    /* Calculate length of message received */
    msg_len = ((uint8_t)(strlen((char *)p_temp_ptr)));

    /* Reset callback capture variable */
    g_pc_uart_event = RESET_VALUE;

    /* Writing to terminal */
#if defined (BOARD_RA6T2_MCK) || defined (BOARD_RA8M1_EK)
    err = R_SCI_B_UART_Write (&g_uart2_ctrl, p_msg, msg_len);
#else
    err = R_SCI_UART_Write (&g_uart2_ctrl, p_msg, msg_len);
#endif

    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n**  R_SCI_UART_Write API Failed  **\r\n");
        return err;
    }

    /* Check for event transfer complete */
    while ((UART_EVENT_TX_COMPLETE != g_pc_uart_event) && (--local_timeout))
    {
        /* Check if any error event occurred */
        if (UART_PC_ERROR_EVENTS == g_pc_uart_event)
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
 *  @brief       Deinitialize SCI UART module
 *  @param[in]   None
 *  @retval      None
 **********************************************************************************************************************/
void deinit_pc_uart(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Close module */
#if defined (BOARD_RA6T2_MCK) || defined (BOARD_RA8M1_EK)
    err =  R_SCI_B_UART_Close (&g_uart2_ctrl);
#else
    err =  R_SCI_UART_Close (&g_uart2_ctrl);
#endif

    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n**  R_SCI_UART_Close API failed  ** \r\n");
    }
}

/*******************************************************************************************************************//**
 *  @brief       Close SCI UART module
 *  @param[in]   None
 *  @retval      None
 **********************************************************************************************************************/
void uart_pc_close(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Close module */
#if defined (BOARD_RA6T2_MCK) || defined (BOARD_RA8M1_EK)
    err =  R_SCI_B_UART_Close (&g_uart2_ctrl);
#else
    err =  R_SCI_UART_Close (&g_uart2_ctrl);
#endif

    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("\r\n**  R_SCI_UART_Close API failed  ** \r\n");
    }
}

/*****************************************************************************************************************
 *  @brief      UART PC callback
 *  @param[in]  p_args
 *  @retval     None
 ****************************************************************************************************************/
void uart_pc_callback(uart_callback_args_t *p_args)
{
    /* Logged the event in global variable */
    g_pc_uart_event = (uint8_t)p_args->event;

    /* Reset g_temp_buffer index if it exceeds than buffer size */
    if(DATA_LENGTH == g_pc_counter_var)
    {
        g_pc_counter_var = RESET_VALUE;
    }

    if(UART_EVENT_RX_CHAR == p_args->event)
    {
        switch (p_args->data)
        {
            /* If Enter is pressed by user, set flag to process the data */
            case CARRIAGE_ASCII:
            {
                g_pc_counter_var = RESET_VALUE;
                g_pc_data_received_flag  = true;
                // rcv data end then send to talk board
                break;
            }
            /* Read all data provided by user until enter button is pressed */
            default:
            {
                g_pc_temp_buffer[g_pc_counter_var++] = (uint8_t ) p_args->data;
                break;
            }
        }
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup r_sci_uart_pc)
 **********************************************************************************************************************/

