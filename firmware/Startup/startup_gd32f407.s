;/****************************************************************************
; startup_gd32f407.s — GD32F407VE bare-metal startup for Keil ARMCC5 (legacy)
;****************************************************************************/
                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Size      EQU     0x00001000
Stack_Mem       SPACE   Stack_Size
__initial_sp

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
Heap_Size       EQU     0x00000800
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

; Vector table
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp
                DCD     Reset_Handler
                DCD     NMI_Handler
                DCD     HardFault_Handler
                DCD     MemManage_Handler
                DCD     BusFault_Handler
                DCD     UsageFault_Handler
                DCD     0
                DCD     0
                DCD     0
                DCD     0
                DCD     SVC_Handler
                DCD     DebugMon_Handler
                DCD     0
                DCD     PendSV_Handler
                DCD     SysTick_Handler
                ; IRQs 0..66 → Default_Handler; 67 = USBFS
                REPT    67
                DCD     Default_Handler
                ENDR
                DCD     USBFS_IRQHandler
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

Default_Handler PROC
                EXPORT  Default_Handler           [WEAK]
                B       .
                ENDP

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP
USBFS_IRQHandler PROC
                EXPORT  USBFS_IRQHandler          [WEAK]
                B       .
                ENDP

                ALIGN
                EXPORT  __user_initial_stackheap
__user_initial_stackheap
                LDR     R0, =Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, =(Heap_Mem + Heap_Size)
                LDR     R3, =Stack_Mem
                BX      LR

                ALIGN
                END
