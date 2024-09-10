################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Drivers/RISC_V/Core/core_riscv.c 

OBJS += \
./Drivers/RISC_V/Core/core_riscv.o 

C_DEPS += \
./Drivers/RISC_V/Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/RISC_V/Core/core_riscv.o: F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Drivers/RISC_V/Core/core_riscv.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\User" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\RISC_V\Core" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\include" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

