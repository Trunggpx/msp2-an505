#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>
#include "uart.h"

/*-----------------------------------------------------------*/
/* Idle Task memory (configSUPPORT_STATIC_ALLOCATION = 1) */
static StaticTask_t xIdleTCB;
static StackType_t xIdleStack[ configMINIMAL_STACK_SIZE ];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTCB,
                                    StackType_t  **ppxIdleStack,
                                    StackType_t  *pulIdleStackSize )
{
    *ppxIdleTCB       = &xIdleTCB;
    *ppxIdleStack     = xIdleStack;
    *pulIdleStackSize = configMINIMAL_STACK_SIZE;
}

/* Nếu configUSE_TIMERS == 1 và configSUPPORT_STATIC_ALLOCATION == 1 */
#if ( configUSE_TIMERS == 1 ) && ( configSUPPORT_STATIC_ALLOCATION == 1 )
static StaticTask_t xTimerTaskTCB;
static StackType_t  xTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t  **ppxTimerTaskStackBuffer,
                                     uint32_t     *pulTimerTaskStackSize )
{
    *ppxTimerTaskTCBBuffer   = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = xTimerTaskStack;
    *pulTimerTaskStackSize   = configTIMER_TASK_STACK_DEPTH;
}
#endif

/*-----------------------------------------------------------*/
/* Assert handler */
void vAssertCalled(const char *file, int line)
{
    (void)file;
    (void)line;
    __asm("bkpt 0");
    while(1) { }
}

/* Stack overflow hook (nếu bật) */
void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    char *pcTaskName )
{
    (void)xTask;
    (void)pcTaskName;
    __asm("bkpt 0");
    while(1) { }
}

/* Malloc failed hook (nếu bật) */
void vApplicationMallocFailedHook( void )
{
    __asm("bkpt 0");
    while(1) { }
}

/*-----------------------------------------------------------*/
/* Demo Task: in "Hello from FreeRTOS" qua UART mỗi 1 giây */
static void TaskA(void *p)
{
    (void)p;
    for (;;)
    {
        uart_puts("Hello from FreeRTOS\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/*-----------------------------------------------------------*/
int main(void)
{
    uart_init();

    /* tạo 1 task FreeRTOS */
    BaseType_t r = xTaskCreate(
        TaskA,          /* function */
        "A",            /* name */
        256,            /* stack words */
        NULL,           /* param */
        1,              /* priority */
        NULL            /* handle */
    );

    if (r != pdPASS) {
        /* Nếu fail thì assert */
        vAssertCalled(__FILE__, __LINE__);
    }

    /* start scheduler */
    vTaskStartScheduler();

    /* Nếu tới đây là lỗi (không đủ heap tạo idle/timer task) */
    vAssertCalled(__FILE__, __LINE__);

    while (1) { }
}
