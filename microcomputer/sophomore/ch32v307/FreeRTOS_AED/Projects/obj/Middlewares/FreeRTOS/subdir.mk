################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/croutine.c \
F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/event_groups.c \
F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/list.c \
F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/queue.c \
F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/stream_buffer.c \
F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/tasks.c \
F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/timers.c 

OBJS += \
./Middlewares/FreeRTOS/croutine.o \
./Middlewares/FreeRTOS/event_groups.o \
./Middlewares/FreeRTOS/list.o \
./Middlewares/FreeRTOS/queue.o \
./Middlewares/FreeRTOS/stream_buffer.o \
./Middlewares/FreeRTOS/tasks.o \
./Middlewares/FreeRTOS/timers.o 

C_DEPS += \
./Middlewares/FreeRTOS/croutine.d \
./Middlewares/FreeRTOS/event_groups.d \
./Middlewares/FreeRTOS/list.d \
./Middlewares/FreeRTOS/queue.d \
./Middlewares/FreeRTOS/stream_buffer.d \
./Middlewares/FreeRTOS/tasks.d \
./Middlewares/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/croutine.o: F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/croutine.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\User" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\RISC_V\Core" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\include" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/event_groups.o: F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/event_groups.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\User" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\RISC_V\Core" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\include" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/list.o: F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/list.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\User" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\RISC_V\Core" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\include" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/queue.o: F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/queue.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\User" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\RISC_V\Core" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\include" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/stream_buffer.o: F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/stream_buffer.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\User" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\RISC_V\Core" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\include" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/tasks.o: F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/tasks.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\User" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\RISC_V\Core" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\include" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Middlewares/FreeRTOS/timers.o: F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Middlewares/FreeRTOS/timers.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\User" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\RISC_V\Core" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\include" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

