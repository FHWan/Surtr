################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/Desktop/4，程序源码/4，程序源码/2，扩展例程/1，FreeRTOS例程/1，FreeRTOS例程/FreeRTOS实验例程22\ FreeRTOS内存管理实验/Drivers/BSP/LCD/lcd.c \
F:/Desktop/4，程序源码/4，程序源码/2，扩展例程/1，FreeRTOS例程/1，FreeRTOS例程/FreeRTOS实验例程22\ FreeRTOS内存管理实验/Drivers/BSP/LCD/lcd_ex.c 

OBJS += \
./Drivers/BSP/LCD/lcd.o \
./Drivers/BSP/LCD/lcd_ex.o 

C_DEPS += \
./Drivers/BSP/LCD/lcd.d \
./Drivers/BSP/LCD/lcd_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/LCD/lcd.o: F:/Desktop/4，程序源码/4，程序源码/2，扩展例程/1，FreeRTOS例程/1，FreeRTOS例程/FreeRTOS实验例程22\ FreeRTOS内存管理实验/Drivers/BSP/LCD/lcd.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\User" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Drivers\RISC_V\Core" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Drivers" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares\FreeRTOS" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares\FreeRTOS\include" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Drivers/BSP/LCD/lcd_ex.o: F:/Desktop/4，程序源码/4，程序源码/2，扩展例程/1，FreeRTOS例程/1，FreeRTOS例程/FreeRTOS实验例程22\ FreeRTOS内存管理实验/Drivers/BSP/LCD/lcd_ex.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\User" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Drivers\RISC_V\Core" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Drivers" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares\FreeRTOS" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares\FreeRTOS\include" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\4，程序源码\4，程序源码\2，扩展例程\1，FreeRTOS例程\1，FreeRTOS例程\FreeRTOS实验例程22 FreeRTOS内存管理实验\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

