/***************************************************************
 * This confidential and  proprietary  software may be used only
 * as authorised  by  a licensing  agreement  from  ARM  Limited
 *
 *             (C) COPYRIGHT 2013-2015 ARM Limited
 *                      ALL RIGHTS RESERVED
 *
 *  The entire notice above must be reproduced on all authorised
 *  copies and copies  may only be made to the  extent permitted
 *  by a licensing agreement from ARM Limited.
 *
 ***************************************************************/
#ifndef __SVC_EXPORTS_H__
#define __SVC_EXPORTS_H__

/* maximum depth of nested context switches
 * this includes both IRQn and secure gateways, as they use the same state stack
 * for their context switches */
#define UVISOR_SVC_CONTEXT_MAX_DEPTH 0x10

/* SVC takes a 8bit immediate, which is split as follows:
 *    bit 7 to bit UVISOR_SVC_CUSTOM_BITS: hardcoded table
 *    bit UVISOR_SVC_CUSTOM_BITS - 1 to bit 0: custom table
 * in addition, if the hardcoded table is used, the lower bits
 *    bit UVISOR_SVC_CUSTOM_BITS - 1 to bit 0
 * are used to pass the number of arguments of the SVC call (up to 4) */
#define UVISOR_SVC_CUSTOM_BITS     4
#define UVISOR_SVC_FIXED_BITS      (8 - UVISOR_SVC_CUSTOM_BITS)
#define UVISOR_SVC_CUSTOM_MSK      ((uint8_t) (0xFF >> UVISOR_SVC_FIXED_BITS))
#define UVISOR_SVC_FIXED_MSK       ((uint8_t) ~UVISOR_SVC_CUSTOM_MSK)
#define UVISOR_SVC_CUSTOM_TABLE(x) ((uint8_t)  (x) &  UVISOR_SVC_CUSTOM_MSK)
#define UVISOR_SVC_FIXED_TABLE(x)  ((uint8_t) ((x) << UVISOR_SVC_CUSTOM_BITS)  \
                                                   &  UVISOR_SVC_FIXED_MSK)

/* SVC immediate values for custom table */
#define UVISOR_SVC_ID_ISR_SET        UVISOR_SVC_CUSTOM_TABLE(0)
#define UVISOR_SVC_ID_ISR_GET        UVISOR_SVC_CUSTOM_TABLE(1)
#define UVISOR_SVC_ID_IRQ_ENABLE     UVISOR_SVC_CUSTOM_TABLE(2)
#define UVISOR_SVC_ID_IRQ_DISABLE    UVISOR_SVC_CUSTOM_TABLE(3)
#define UVISOR_SVC_ID_IRQ_PEND_CLR   UVISOR_SVC_CUSTOM_TABLE(4)
#define UVISOR_SVC_ID_IRQ_PEND_SET   UVISOR_SVC_CUSTOM_TABLE(5)
#define UVISOR_SVC_ID_IRQ_PEND_GET   UVISOR_SVC_CUSTOM_TABLE(6)
#define UVISOR_SVC_ID_IRQ_PRIO_SET   UVISOR_SVC_CUSTOM_TABLE(7)
#define UVISOR_SVC_ID_IRQ_PRIO_GET   UVISOR_SVC_CUSTOM_TABLE(8)
#define UVISOR_SVC_ID_BENCHMARK_CFG  UVISOR_SVC_CUSTOM_TABLE(9)
#define UVISOR_SVC_ID_BENCHMARK_RST  UVISOR_SVC_CUSTOM_TABLE(10)
#define UVISOR_SVC_ID_BENCHMARK_STOP UVISOR_SVC_CUSTOM_TABLE(11)
#define UVISOR_SVC_ID_HALT_USER_ERR  UVISOR_SVC_CUSTOM_TABLE(12)

/* SVC immediate values for hardcoded table (call from unprivileged) */
#define UVISOR_SVC_ID_UNVIC_OUT      UVISOR_SVC_FIXED_TABLE(1)
#define UVISOR_SVC_ID_CX_IN          UVISOR_SVC_FIXED_TABLE(2)
#define UVISOR_SVC_ID_CX_OUT         UVISOR_SVC_FIXED_TABLE(3)

/* SVC immediate values for hardcoded table (call from privileged) */
#define UVISOR_SVC_ID_UNVIC_IN       UVISOR_SVC_FIXED_TABLE(1)

/* unprivileged code uses a secure gateway to switch context */
#define UVISOR_SVC_ID_SECURE_GATEWAY(args)                                     \
    ((UVISOR_SVC_ID_CX_IN) | (UVISOR_SVC_CUSTOM_TABLE(args)))

#endif/*__SVC_EXPORTS_H__*/