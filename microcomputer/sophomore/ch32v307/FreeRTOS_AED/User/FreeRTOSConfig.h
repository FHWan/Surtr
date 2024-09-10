#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

#define configMTIME_BASE_ADDRESS 	            0
#define configMTIMECMP_BASE_ADDRESS             0

/* 基础配置项 */
#define configUSE_PREEMPTION			        1                               /* 1: 抢占式调度器, 0: 协程式调度器, 无默认需定义 */
#define configUSE_IDLE_HOOK				        0                               /* 1: 使能/关闭空闲任务钩子函数, 无默认需定义  */
#define configUSE_TICK_HOOK				        0                               /* 1: 使能/关闭系统时钟节拍中断钩子函数, 无默认需定义 */
#define configCPU_CLOCK_HZ				        SystemCoreClock                 /* 定义CPU主频, 单位: Hz, 无默认需定义 */
#define configTICK_RATE_HZ				        1000                            /* 定义系统时钟节拍频率, 单位: Hz, 无默认需定义 */
#define configMAX_PRIORITIES			        15                              /* 定义最大优先级数, 最大优先级=configMAX_PRIORITIES-1, 无默认需定义 */
#define configMINIMAL_STACK_SIZE		        128                             /* 定义空闲任务的栈空间大小, 单位: Word, 无默认需定义 */
#define configSUPPORT_STATIC_ALLOCATION         0                               /* 1: 支持静态申请内存, 默认: 0 */
#define configSUPPORT_DYNAMIC_ALLOCATION        1                               /* 1: 支持动态申请内存, 默认: 1 */
#define configTOTAL_HEAP_SIZE			        ((size_t)(10 * 1024))           /* FreeRTOS堆中可用的RAM总量, 单位: Byte, 无默认需定义 */
#define configMAX_TASK_NAME_LEN			        16                              /* 定义任务名最大字符数, 默认: 16 */
#define configUSE_TRACE_FACILITY		        1                               /* 1: 使能可视化跟踪调试, 默认: 0 */
#define configUSE_STATS_FORMATTING_FUNCTIONS    1                               /* configUSE_TRACE_FACILITY为1时，会编译vTaskList()和vTaskGetRunTimeStats()函数, 默认: 0 */
#define configUSE_16_BIT_TICKS			        0                               /* 1: 定义系统时钟节拍计数器的数据类型为16位无符号数, 无默认需定义 */
#define configIDLE_SHOULD_YIELD			        1                               /* 1: 使能在抢占式调度下,同优先级的任务能抢占空闲任务, 默认: 1 */
#define configUSE_TASK_NOTIFICATIONS            1                               /* 1: 使能任务间直接的消息传递,包括信号量、事件标志组和消息邮箱, 默认: 1 */
#define configTASK_NOTIFICATION_ARRAY_ENTRIES   1                               /* 定义任务通知数组的大小, 默认: 1 */
#define configUSE_MUTEXES				        1                               /* 1: 使能互斥信号量, 默认: 0 */
#define configQUEUE_REGISTRY_SIZE		        8                               /* 定义可以注册的信号量和消息队列的个数, 默认: 0 */
#define configUSE_QUEUE_SETS                    1                               /* 1: 使能队列集, 默认: 0 */
#define configCHECK_FOR_STACK_OVERFLOW	        0                               /* 1: 使能栈溢出检测方法1, 2: 使能栈溢出检测方法2, 默认: 0 */
#define configUSE_RECURSIVE_MUTEXES		        1                               /* 1: 使能递归互斥信号量, 默认: 0 */
#define configUSE_MALLOC_FAILED_HOOK	        0                               /* 1: 使能动态内存申请失败钩子函数, 默认: 0 */
#define configUSE_APPLICATION_TASK_TAG	        0
#define configUSE_COUNTING_SEMAPHORES	        1                               /* 1: 使能计数信号量, 默认: 0 */
#define configGENERATE_RUN_TIME_STATS	        0                               /* 1: 使能任务运行时间统计功能, 默认: 0 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0                               /* 1: 使用硬件计算下一个要运行的任务, 0: 使用软件算法计算下一个要运行的任务, 默认: 0 */

/* 协程相关定义 */
#define configUSE_CO_ROUTINES 			        0
#define configMAX_CO_ROUTINE_PRIORITIES         2

/* 软件定时器相关定义 */
#define configUSE_TIMERS				        1
#define configTIMER_TASK_PRIORITY		        (configMAX_PRIORITIES - 1)
#define configTIMER_QUEUE_LENGTH		        5
#define configTIMER_TASK_STACK_DEPTH	        (configMINIMAL_STACK_SIZE * 2)

/* 可选函数, 1: 使能 */
#define INCLUDE_vTaskPrioritySet			    1
#define INCLUDE_uxTaskPriorityGet			    1
#define INCLUDE_vTaskDelete					    1
#define INCLUDE_vTaskCleanUpResources		    1
#define INCLUDE_vTaskSuspend				    1
#define INCLUDE_vTaskDelayUntil				    1
#define INCLUDE_vTaskDelay					    1
#define INCLUDE_eTaskGetState				    1
#define INCLUDE_xTimerPendFunctionCall		    1
#define INCLUDE_xTaskAbortDelay				    1
#define INCLUDE_xTaskGetHandle				    1
#define INCLUDE_xSemaphoreGetMutexHolder	    1
#define INCLUDE_xTaskResumeFromISR              1

/* 断言 */
#define configASSERT( x ) if( ( x ) == 0 ) { taskDISABLE_INTERRUPTS(); printf("err at line %d of file \"%s\". \r\n ",__LINE__,__FILE__); while(1); }

/* 映射printf函数 */
#define configPRINT_STRING( pcString )  printf( pcString )

#endif
