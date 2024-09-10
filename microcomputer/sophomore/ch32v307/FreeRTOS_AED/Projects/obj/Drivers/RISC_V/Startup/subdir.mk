################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Drivers/RISC_V/Startup/startup_ch32v30x_D8C.S 

OBJS += \
./Drivers/RISC_V/Startup/startup_ch32v30x_D8C.o 

S_UPPER_DEPS += \
./Drivers/RISC_V/Startup/startup_ch32v30x_D8C.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/RISC_V/Startup/startup_ch32v30x_D8C.o: F:/Desktop/AED/yinjian/ch32v307/FreeRTOS_AED/Drivers/RISC_V/Startup/startup_ch32v30x_D8C.S
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -x assembler-with-cpp -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\include" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -I"F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Middlewares\FreeRTOS\portable\MemMang" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

