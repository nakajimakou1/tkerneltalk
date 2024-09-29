/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = sci_b_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [1] = sci_b_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [2] = sci_b_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [3] = sci_b_uart_eri_isr, /* SCI0 ERI (Receive error) */
            [4] = sci_b_uart_rxi_isr, /* SCI1 RXI (Receive data full) */
            [5] = sci_b_uart_txi_isr, /* SCI1 TXI (Transmit data empty) */
            [6] = sci_b_uart_tei_isr, /* SCI1 TEI (Transmit end) */
            [7] = sci_b_uart_eri_isr, /* SCI1 ERI (Receive error) */
            [8] = sci_b_uart_rxi_isr, /* SCI2 RXI (Receive data full) */
            [9] = sci_b_uart_txi_isr, /* SCI2 TXI (Transmit data empty) */
            [10] = sci_b_uart_tei_isr, /* SCI2 TEI (Transmit end) */
            [11] = sci_b_uart_eri_isr, /* SCI2 ERI (Receive error) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_VECT_ENUM(EVENT_SCI0_RXI,GROUP0), /* SCI0 RXI (Receive data full) */
            [1] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TXI,GROUP1), /* SCI0 TXI (Transmit data empty) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_SCI0_TEI,GROUP2), /* SCI0 TEI (Transmit end) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_SCI0_ERI,GROUP3), /* SCI0 ERI (Receive error) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_SCI1_RXI,GROUP4), /* SCI1 RXI (Receive data full) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_SCI1_TXI,GROUP5), /* SCI1 TXI (Transmit data empty) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_SCI1_TEI,GROUP6), /* SCI1 TEI (Transmit end) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_SCI1_ERI,GROUP7), /* SCI1 ERI (Receive error) */
            [8] = BSP_PRV_VECT_ENUM(EVENT_SCI2_RXI,GROUP0), /* SCI2 RXI (Receive data full) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_SCI2_TXI,GROUP1), /* SCI2 TXI (Transmit data empty) */
            [10] = BSP_PRV_VECT_ENUM(EVENT_SCI2_TEI,GROUP2), /* SCI2 TEI (Transmit end) */
            [11] = BSP_PRV_VECT_ENUM(EVENT_SCI2_ERI,GROUP3), /* SCI2 ERI (Receive error) */
        };
        #endif
        #endif
