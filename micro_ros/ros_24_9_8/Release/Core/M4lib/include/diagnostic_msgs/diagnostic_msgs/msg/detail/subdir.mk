################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__description.c \
../Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__functions.c \
../Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__type_support.c \
../Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__description.c \
../Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__functions.c \
../Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__type_support.c \
../Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__description.c \
../Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__functions.c \
../Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__type_support.c 

OBJS += \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__description.o \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__functions.o \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__type_support.o \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__description.o \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__functions.o \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__type_support.o \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__description.o \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__functions.o \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__type_support.o 

C_DEPS += \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__description.d \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__functions.d \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__type_support.d \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__description.d \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__functions.d \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__type_support.d \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__description.d \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__functions.d \
./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__type_support.d 


# Each subdirectory must supply rules for building sources it contributes
Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/%.o Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/%.su Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/%.cyclo: ../Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/%.c Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-M4lib-2f-include-2f-diagnostic_msgs-2f-diagnostic_msgs-2f-msg-2f-detail

clean-Core-2f-M4lib-2f-include-2f-diagnostic_msgs-2f-diagnostic_msgs-2f-msg-2f-detail:
	-$(RM) ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__description.cyclo ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__description.d ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__description.o ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__description.su ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__functions.cyclo ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__functions.d ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__functions.o ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__functions.su ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__type_support.cyclo ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__type_support.d ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__type_support.o ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_array__type_support.su ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__description.cyclo ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__description.d ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__description.o ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__description.su ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__functions.cyclo ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__functions.d ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__functions.o ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__functions.su ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__type_support.cyclo ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__type_support.d ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__type_support.o ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/diagnostic_status__type_support.su ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__description.cyclo ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__description.d ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__description.o ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__description.su ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__functions.cyclo ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__functions.d ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__functions.o ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__functions.su ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__type_support.cyclo ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__type_support.d ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__type_support.o ./Core/M4lib/include/diagnostic_msgs/diagnostic_msgs/msg/detail/key_value__type_support.su

.PHONY: clean-Core-2f-M4lib-2f-include-2f-diagnostic_msgs-2f-diagnostic_msgs-2f-msg-2f-detail

