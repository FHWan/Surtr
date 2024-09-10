################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/core_riscv.c 

OBJS += \
./Core/core_riscv.o 

C_DEPS += \
./Core/core_riscv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/%.o: ../Core/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\stm32\teamproject\2023大一下项目范海炜\3.消防栓\雪龙（请先下载MRS）ch32v307rct6\Debug" -I"F:\stm32\teamproject\2023大一下项目范海炜\3.消防栓\雪龙（请先下载MRS）ch32v307rct6\Core" -I"F:\stm32\teamproject\2023大一下项目范海炜\3.消防栓\雪龙（请先下载MRS）ch32v307rct6\User" -I"F:\stm32\teamproject\2023大一下项目范海炜\3.消防栓\雪龙（请先下载MRS）ch32v307rct6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

