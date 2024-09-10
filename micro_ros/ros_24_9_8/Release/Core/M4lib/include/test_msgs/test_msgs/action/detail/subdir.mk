################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__description.c \
../Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__functions.c \
../Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__type_support.c \
../Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__description.c \
../Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__functions.c \
../Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__type_support.c 

OBJS += \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__description.o \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__functions.o \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__type_support.o \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__description.o \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__functions.o \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__type_support.o 

C_DEPS += \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__description.d \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__functions.d \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__type_support.d \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__description.d \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__functions.d \
./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__type_support.d 


# Each subdirectory must supply rules for building sources it contributes
Core/M4lib/include/test_msgs/test_msgs/action/detail/%.o Core/M4lib/include/test_msgs/test_msgs/action/detail/%.su Core/M4lib/include/test_msgs/test_msgs/action/detail/%.cyclo: ../Core/M4lib/include/test_msgs/test_msgs/action/detail/%.c Core/M4lib/include/test_msgs/test_msgs/action/detail/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-M4lib-2f-include-2f-test_msgs-2f-test_msgs-2f-action-2f-detail

clean-Core-2f-M4lib-2f-include-2f-test_msgs-2f-test_msgs-2f-action-2f-detail:
	-$(RM) ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__description.cyclo ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__description.d ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__description.o ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__description.su ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__functions.cyclo ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__functions.d ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__functions.o ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__functions.su ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__type_support.cyclo ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__type_support.d ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__type_support.o ./Core/M4lib/include/test_msgs/test_msgs/action/detail/fibonacci__type_support.su ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__description.cyclo ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__description.d ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__description.o ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__description.su ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__functions.cyclo ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__functions.d ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__functions.o ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__functions.su ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__type_support.cyclo ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__type_support.d ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__type_support.o ./Core/M4lib/include/test_msgs/test_msgs/action/detail/nested_message__type_support.su

.PHONY: clean-Core-2f-M4lib-2f-include-2f-test_msgs-2f-test_msgs-2f-action-2f-detail

