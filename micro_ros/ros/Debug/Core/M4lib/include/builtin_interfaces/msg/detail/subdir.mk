################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/M4lib/include/builtin_interfaces/msg/detail/duration__description.c \
../Core/M4lib/include/builtin_interfaces/msg/detail/duration__functions.c \
../Core/M4lib/include/builtin_interfaces/msg/detail/duration__type_support.c \
../Core/M4lib/include/builtin_interfaces/msg/detail/time__description.c \
../Core/M4lib/include/builtin_interfaces/msg/detail/time__functions.c \
../Core/M4lib/include/builtin_interfaces/msg/detail/time__type_support.c 

OBJS += \
./Core/M4lib/include/builtin_interfaces/msg/detail/duration__description.o \
./Core/M4lib/include/builtin_interfaces/msg/detail/duration__functions.o \
./Core/M4lib/include/builtin_interfaces/msg/detail/duration__type_support.o \
./Core/M4lib/include/builtin_interfaces/msg/detail/time__description.o \
./Core/M4lib/include/builtin_interfaces/msg/detail/time__functions.o \
./Core/M4lib/include/builtin_interfaces/msg/detail/time__type_support.o 

C_DEPS += \
./Core/M4lib/include/builtin_interfaces/msg/detail/duration__description.d \
./Core/M4lib/include/builtin_interfaces/msg/detail/duration__functions.d \
./Core/M4lib/include/builtin_interfaces/msg/detail/duration__type_support.d \
./Core/M4lib/include/builtin_interfaces/msg/detail/time__description.d \
./Core/M4lib/include/builtin_interfaces/msg/detail/time__functions.d \
./Core/M4lib/include/builtin_interfaces/msg/detail/time__type_support.d 


# Each subdirectory must supply rules for building sources it contributes
Core/M4lib/include/builtin_interfaces/msg/detail/%.o Core/M4lib/include/builtin_interfaces/msg/detail/%.su Core/M4lib/include/builtin_interfaces/msg/detail/%.cyclo: ../Core/M4lib/include/builtin_interfaces/msg/detail/%.c Core/M4lib/include/builtin_interfaces/msg/detail/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"F:/SMT32CubeMx/project/ros/Core/M4lib/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/SMT32CubeMx/project/ros/Core/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-M4lib-2f-include-2f-builtin_interfaces-2f-msg-2f-detail

clean-Core-2f-M4lib-2f-include-2f-builtin_interfaces-2f-msg-2f-detail:
	-$(RM) ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__description.cyclo ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__description.d ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__description.o ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__description.su ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__functions.cyclo ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__functions.d ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__functions.o ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__functions.su ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__type_support.cyclo ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__type_support.d ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__type_support.o ./Core/M4lib/include/builtin_interfaces/msg/detail/duration__type_support.su ./Core/M4lib/include/builtin_interfaces/msg/detail/time__description.cyclo ./Core/M4lib/include/builtin_interfaces/msg/detail/time__description.d ./Core/M4lib/include/builtin_interfaces/msg/detail/time__description.o ./Core/M4lib/include/builtin_interfaces/msg/detail/time__description.su ./Core/M4lib/include/builtin_interfaces/msg/detail/time__functions.cyclo ./Core/M4lib/include/builtin_interfaces/msg/detail/time__functions.d ./Core/M4lib/include/builtin_interfaces/msg/detail/time__functions.o ./Core/M4lib/include/builtin_interfaces/msg/detail/time__functions.su ./Core/M4lib/include/builtin_interfaces/msg/detail/time__type_support.cyclo ./Core/M4lib/include/builtin_interfaces/msg/detail/time__type_support.d ./Core/M4lib/include/builtin_interfaces/msg/detail/time__type_support.o ./Core/M4lib/include/builtin_interfaces/msg/detail/time__type_support.su

.PHONY: clean-Core-2f-M4lib-2f-include-2f-builtin_interfaces-2f-msg-2f-detail

