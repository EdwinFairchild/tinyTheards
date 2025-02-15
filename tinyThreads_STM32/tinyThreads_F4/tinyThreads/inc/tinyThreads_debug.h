#ifndef CFG_TINYTHREADS_DEBUG_H
#define CFG_TINYTHREADS_DEBUG_H

#include "tinyThreads_config.h"
#include "tinyThreads_error.h"
#include "tinyThreads_port.h"

// TODO: Makes the assumption user has retargeted printf to UART
// provide a print wrapper via tinyThreads_port.h
// clang-format off
// Debug macro definition
#if defined(CFG_TINYTHREADS_DEBUG) && (CFG_TINYTHREADS_DEBUG == 1)
#define debug(err)                                                         \
    if (err != TINYTHREADS_OK)                                             \
    {                                                                      \
        printf("!!! err @ %s: %s !!!\r\n", __func__, errorToString(err));  \
        if (CFG_TINYTHREADS_DEBUG_HALT_ON_ERROR)                           \
        {                                                                  \
            TT_ASM_BREAKPOINT();                                           \
        }                                                                  \
    }
// clang-format on
__STATIC_FORCEINLINE void port_dbg_signal_1_assert(void)
{
    // set GPIOC pin 9 high using registers
    GPIOC->BSRR = GPIO_BSRR_BS_9;
}

__STATIC_FORCEINLINE void port_dbg_signal_1_deassert(void)
{
    // set GPIOC pin 9 low using registers
    // do a nop to make sure the signal is low
    // GPIOC->BSRR = GPIO_BSRR_BR_9; // not sure BSRR wants to be called twice to work
    GPIOC->ODR &= ~GPIO_ODR_OD9;
}

__STATIC_FORCEINLINE void port_dbg_signal_2_assert(void)
{
    // set GPIOC pin 9 high using registers
    GPIOC->BSRR = GPIO_BSRR_BS_8;
}

__STATIC_FORCEINLINE void port_dbg_signal_2_deassert(void)
{
    // set GPIOC pin 9 low using registers
    GPIOC->BSRR = GPIO_BSRR_BR_8;
}
#else
#define debug(err)                   ((void)0)
#define port_dbg_signal_1_assert()   ((void)0)
#define port_dbg_signal_1_deassert() ((void)0)
#define port_dbg_signal_2_assert()   ((void)0)
#define port_dbg_signal_2_deassert() ((void)0)
#endif

#endif // CFG_TINYTHREADS_DEBUG_H
