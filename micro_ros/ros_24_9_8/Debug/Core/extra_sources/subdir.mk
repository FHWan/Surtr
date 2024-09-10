################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/extra_sources/custom_memory_manager.c \
../Core/extra_sources/microros_allocators.c \
../Core/extra_sources/microros_time.c 

OBJS += \
./Core/extra_sources/custom_memory_manager.o \
./Core/extra_sources/microros_allocators.o \
./Core/extra_sources/microros_time.o 

C_DEPS += \
./Core/extra_sources/custom_memory_manager.d \
./Core/extra_sources/microros_allocators.d \
./Core/extra_sources/microros_time.d 


# Each subdirectory must supply rules for building sources it contributes
Core/extra_sources/%.o Core/extra_sources/%.su Core/extra_sources/%.cyclo: ../Core/extra_sources/%.c Core/extra_sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"F:/SMT32CubeMx/project/ros/Core/M4lib/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/SMT32CubeMx/project/ros/Core/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-extra_sources

clean-Core-2f-extra_sources:
	-$(RM) ./Core/extra_sources/custom_memory_manager.cyclo ./Core/extra_sources/custom_memory_manager.d ./Core/extra_sources/custom_memory_manager.o ./Core/extra_sources/custom_memory_manager.su ./Core/extra_sources/microros_allocators.cyclo ./Core/extra_sources/microros_allocators.d ./Core/extra_sources/microros_allocators.o ./Core/extra_sources/microros_allocators.su ./Core/extra_sources/microros_time.cyclo ./Core/extra_sources/microros_time.d ./Core/extra_sources/microros_time.o ./Core/extra_sources/microros_time.su

.PHONY: clean-Core-2f-extra_sources

