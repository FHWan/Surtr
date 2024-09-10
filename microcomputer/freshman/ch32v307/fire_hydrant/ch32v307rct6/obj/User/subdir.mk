################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/EC20.c \
../User/IIC.c \
../User/MPU6050.c \
../User/RC522.c \
../User/SPI.c \
../User/adc.c \
../User/beep.c \
../User/ch32v30x_it.c \
../User/gpio.c \
../User/lcd.c \
../User/main.c \
../User/system_ch32v30x.c \
../User/timer.c \
../User/usart.c 

OBJS += \
./User/EC20.o \
./User/IIC.o \
./User/MPU6050.o \
./User/RC522.o \
./User/SPI.o \
./User/adc.o \
./User/beep.o \
./User/ch32v30x_it.o \
./User/gpio.o \
./User/lcd.o \
./User/main.o \
./User/system_ch32v30x.o \
./User/timer.o \
./User/usart.o 

C_DEPS += \
./User/EC20.d \
./User/IIC.d \
./User/MPU6050.d \
./User/RC522.d \
./User/SPI.d \
./User/adc.d \
./User/beep.d \
./User/ch32v30x_it.d \
./User/gpio.d \
./User/lcd.d \
./User/main.d \
./User/system_ch32v30x.d \
./User/timer.d \
./User/usart.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\stm32\teamproject\2023大一下项目范海炜\3.消防栓\雪龙（请先下载MRS）ch32v307rct6\Debug" -I"F:\stm32\teamproject\2023大一下项目范海炜\3.消防栓\雪龙（请先下载MRS）ch32v307rct6\Core" -I"F:\stm32\teamproject\2023大一下项目范海炜\3.消防栓\雪龙（请先下载MRS）ch32v307rct6\User" -I"F:\stm32\teamproject\2023大一下项目范海炜\3.消防栓\雪龙（请先下载MRS）ch32v307rct6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

