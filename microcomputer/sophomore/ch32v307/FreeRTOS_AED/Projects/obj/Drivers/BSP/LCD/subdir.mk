################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/Desktop/4������Դ��/4������Դ��/2����չ����/1��FreeRTOS����/1��FreeRTOS����/FreeRTOSʵ������22\ FreeRTOS�ڴ����ʵ��/Drivers/BSP/LCD/lcd.c \
F:/Desktop/4������Դ��/4������Դ��/2����չ����/1��FreeRTOS����/1��FreeRTOS����/FreeRTOSʵ������22\ FreeRTOS�ڴ����ʵ��/Drivers/BSP/LCD/lcd_ex.c 

OBJS += \
./Drivers/BSP/LCD/lcd.o \
./Drivers/BSP/LCD/lcd_ex.o 

C_DEPS += \
./Drivers/BSP/LCD/lcd.d \
./Drivers/BSP/LCD/lcd_ex.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/LCD/lcd.o: F:/Desktop/4������Դ��/4������Դ��/2����չ����/1��FreeRTOS����/1��FreeRTOS����/FreeRTOSʵ������22\ FreeRTOS�ڴ����ʵ��/Drivers/BSP/LCD/lcd.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\User" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Drivers\RISC_V\Core" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Drivers" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares\FreeRTOS" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares\FreeRTOS\include" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
Drivers/BSP/LCD/lcd_ex.o: F:/Desktop/4������Դ��/4������Դ��/2����չ����/1��FreeRTOS����/1��FreeRTOS����/FreeRTOSʵ������22\ FreeRTOS�ڴ����ʵ��/Drivers/BSP/LCD/lcd_ex.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\User" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Drivers\RISC_V\Core" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Drivers" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Drivers\CH32V30x_Driver\inc" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares\FreeRTOS" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares\FreeRTOS\include" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares\FreeRTOS\portable\GCC\RISC-V" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares\FreeRTOS\portable\MemMang" -I"F:\Desktop\4������Դ��\4������Դ��\2����չ����\1��FreeRTOS����\1��FreeRTOS����\FreeRTOSʵ������22 FreeRTOS�ڴ����ʵ��\Middlewares\FreeRTOS\portable\GCC\RISC-V\chip_specific_extensions\RV32I_PFIC_no_extensions" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

