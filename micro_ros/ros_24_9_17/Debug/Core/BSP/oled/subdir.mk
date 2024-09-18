################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/BSP/oled/oled.c \
../Core/BSP/oled/oledfont.c 

OBJS += \
./Core/BSP/oled/oled.o \
./Core/BSP/oled/oledfont.o 

C_DEPS += \
./Core/BSP/oled/oled.d \
./Core/BSP/oled/oledfont.d 


# Each subdirectory must supply rules for building sources it contributes
Core/BSP/oled/%.o Core/BSP/oled/%.su Core/BSP/oled/%.cyclo: ../Core/BSP/oled/%.c Core/BSP/oled/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"F:/SMT32CubeMx/project/ros/Core/M4lib/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/SMT32CubeMx/project/ros/Core/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-BSP-2f-oled

clean-Core-2f-BSP-2f-oled:
	-$(RM) ./Core/BSP/oled/oled.cyclo ./Core/BSP/oled/oled.d ./Core/BSP/oled/oled.o ./Core/BSP/oled/oled.su ./Core/BSP/oled/oledfont.cyclo ./Core/BSP/oled/oledfont.d ./Core/BSP/oled/oledfont.o ./Core/BSP/oled/oledfont.su

.PHONY: clean-Core-2f-BSP-2f-oled

