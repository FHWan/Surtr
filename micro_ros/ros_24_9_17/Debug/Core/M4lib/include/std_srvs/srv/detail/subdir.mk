################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/M4lib/include/std_srvs/srv/detail/empty__description.c \
../Core/M4lib/include/std_srvs/srv/detail/empty__functions.c \
../Core/M4lib/include/std_srvs/srv/detail/empty__type_support.c \
../Core/M4lib/include/std_srvs/srv/detail/set_bool__description.c \
../Core/M4lib/include/std_srvs/srv/detail/set_bool__functions.c \
../Core/M4lib/include/std_srvs/srv/detail/set_bool__type_support.c \
../Core/M4lib/include/std_srvs/srv/detail/trigger__description.c \
../Core/M4lib/include/std_srvs/srv/detail/trigger__functions.c \
../Core/M4lib/include/std_srvs/srv/detail/trigger__type_support.c 

OBJS += \
./Core/M4lib/include/std_srvs/srv/detail/empty__description.o \
./Core/M4lib/include/std_srvs/srv/detail/empty__functions.o \
./Core/M4lib/include/std_srvs/srv/detail/empty__type_support.o \
./Core/M4lib/include/std_srvs/srv/detail/set_bool__description.o \
./Core/M4lib/include/std_srvs/srv/detail/set_bool__functions.o \
./Core/M4lib/include/std_srvs/srv/detail/set_bool__type_support.o \
./Core/M4lib/include/std_srvs/srv/detail/trigger__description.o \
./Core/M4lib/include/std_srvs/srv/detail/trigger__functions.o \
./Core/M4lib/include/std_srvs/srv/detail/trigger__type_support.o 

C_DEPS += \
./Core/M4lib/include/std_srvs/srv/detail/empty__description.d \
./Core/M4lib/include/std_srvs/srv/detail/empty__functions.d \
./Core/M4lib/include/std_srvs/srv/detail/empty__type_support.d \
./Core/M4lib/include/std_srvs/srv/detail/set_bool__description.d \
./Core/M4lib/include/std_srvs/srv/detail/set_bool__functions.d \
./Core/M4lib/include/std_srvs/srv/detail/set_bool__type_support.d \
./Core/M4lib/include/std_srvs/srv/detail/trigger__description.d \
./Core/M4lib/include/std_srvs/srv/detail/trigger__functions.d \
./Core/M4lib/include/std_srvs/srv/detail/trigger__type_support.d 


# Each subdirectory must supply rules for building sources it contributes
Core/M4lib/include/std_srvs/srv/detail/%.o Core/M4lib/include/std_srvs/srv/detail/%.su Core/M4lib/include/std_srvs/srv/detail/%.cyclo: ../Core/M4lib/include/std_srvs/srv/detail/%.c Core/M4lib/include/std_srvs/srv/detail/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"F:/SMT32CubeMx/project/ros/Core/M4lib/include" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"F:/SMT32CubeMx/project/ros/Core/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-M4lib-2f-include-2f-std_srvs-2f-srv-2f-detail

clean-Core-2f-M4lib-2f-include-2f-std_srvs-2f-srv-2f-detail:
	-$(RM) ./Core/M4lib/include/std_srvs/srv/detail/empty__description.cyclo ./Core/M4lib/include/std_srvs/srv/detail/empty__description.d ./Core/M4lib/include/std_srvs/srv/detail/empty__description.o ./Core/M4lib/include/std_srvs/srv/detail/empty__description.su ./Core/M4lib/include/std_srvs/srv/detail/empty__functions.cyclo ./Core/M4lib/include/std_srvs/srv/detail/empty__functions.d ./Core/M4lib/include/std_srvs/srv/detail/empty__functions.o ./Core/M4lib/include/std_srvs/srv/detail/empty__functions.su ./Core/M4lib/include/std_srvs/srv/detail/empty__type_support.cyclo ./Core/M4lib/include/std_srvs/srv/detail/empty__type_support.d ./Core/M4lib/include/std_srvs/srv/detail/empty__type_support.o ./Core/M4lib/include/std_srvs/srv/detail/empty__type_support.su ./Core/M4lib/include/std_srvs/srv/detail/set_bool__description.cyclo ./Core/M4lib/include/std_srvs/srv/detail/set_bool__description.d ./Core/M4lib/include/std_srvs/srv/detail/set_bool__description.o ./Core/M4lib/include/std_srvs/srv/detail/set_bool__description.su ./Core/M4lib/include/std_srvs/srv/detail/set_bool__functions.cyclo ./Core/M4lib/include/std_srvs/srv/detail/set_bool__functions.d ./Core/M4lib/include/std_srvs/srv/detail/set_bool__functions.o ./Core/M4lib/include/std_srvs/srv/detail/set_bool__functions.su ./Core/M4lib/include/std_srvs/srv/detail/set_bool__type_support.cyclo ./Core/M4lib/include/std_srvs/srv/detail/set_bool__type_support.d ./Core/M4lib/include/std_srvs/srv/detail/set_bool__type_support.o ./Core/M4lib/include/std_srvs/srv/detail/set_bool__type_support.su ./Core/M4lib/include/std_srvs/srv/detail/trigger__description.cyclo ./Core/M4lib/include/std_srvs/srv/detail/trigger__description.d ./Core/M4lib/include/std_srvs/srv/detail/trigger__description.o ./Core/M4lib/include/std_srvs/srv/detail/trigger__description.su ./Core/M4lib/include/std_srvs/srv/detail/trigger__functions.cyclo ./Core/M4lib/include/std_srvs/srv/detail/trigger__functions.d ./Core/M4lib/include/std_srvs/srv/detail/trigger__functions.o ./Core/M4lib/include/std_srvs/srv/detail/trigger__functions.su ./Core/M4lib/include/std_srvs/srv/detail/trigger__type_support.cyclo ./Core/M4lib/include/std_srvs/srv/detail/trigger__type_support.d ./Core/M4lib/include/std_srvs/srv/detail/trigger__type_support.o ./Core/M4lib/include/std_srvs/srv/detail/trigger__type_support.su

.PHONY: clean-Core-2f-M4lib-2f-include-2f-std_srvs-2f-srv-2f-detail

