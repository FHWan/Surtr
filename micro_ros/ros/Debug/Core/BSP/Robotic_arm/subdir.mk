################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/BSP/Robotic_arm/robotic_arm.c 

OBJS += \
./Core/BSP/Robotic_arm/robotic_arm.o 

C_DEPS += \
./Core/BSP/Robotic_arm/robotic_arm.d 


# Each subdirectory must supply rules for building sources it contributes
Core/BSP/Robotic_arm/%.o Core/BSP/Robotic_arm/%.su Core/BSP/Robotic_arm/%.cyclo: ../Core/BSP/Robotic_arm/%.c Core/BSP/Robotic_arm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"F:/SMT32CubeMx/project/ros/Core/M4lib/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/SMT32CubeMx/project/ros/Core/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-BSP-2f-Robotic_arm

clean-Core-2f-BSP-2f-Robotic_arm:
	-$(RM) ./Core/BSP/Robotic_arm/robotic_arm.cyclo ./Core/BSP/Robotic_arm/robotic_arm.d ./Core/BSP/Robotic_arm/robotic_arm.o ./Core/BSP/Robotic_arm/robotic_arm.su

.PHONY: clean-Core-2f-BSP-2f-Robotic_arm

