################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/BSP/motor/motor.c 

OBJS += \
./Core/BSP/motor/motor.o 

C_DEPS += \
./Core/BSP/motor/motor.d 


# Each subdirectory must supply rules for building sources it contributes
Core/BSP/motor/%.o Core/BSP/motor/%.su Core/BSP/motor/%.cyclo: ../Core/BSP/motor/%.c Core/BSP/motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"F:/SMT32CubeMx/project/ros/Core/M4lib/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/SMT32CubeMx/project/ros/Core/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-BSP-2f-motor

clean-Core-2f-BSP-2f-motor:
	-$(RM) ./Core/BSP/motor/motor.cyclo ./Core/BSP/motor/motor.d ./Core/BSP/motor/motor.o ./Core/BSP/motor/motor.su

.PHONY: clean-Core-2f-BSP-2f-motor

