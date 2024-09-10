################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__description.c \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__functions.c \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__type_support.c \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__description.c \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__functions.c \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__type_support.c \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__description.c \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__functions.c \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__type_support.c \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__description.c \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__functions.c \
../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__type_support.c 

OBJS += \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__description.o \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__functions.o \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__type_support.o \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__description.o \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__functions.o \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__type_support.o \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__description.o \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__functions.o \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__type_support.o \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__description.o \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__functions.o \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__type_support.o 

C_DEPS += \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__description.d \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__functions.d \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__type_support.d \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__description.d \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__functions.d \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__type_support.d \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__description.d \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__functions.d \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__type_support.d \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__description.d \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__functions.d \
./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__type_support.d 


# Each subdirectory must supply rules for building sources it contributes
Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/%.o Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/%.su Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/%.cyclo: ../Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/%.c Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-M4lib-2f-include-2f-shape_msgs-2f-shape_msgs-2f-msg-2f-detail

clean-Core-2f-M4lib-2f-include-2f-shape_msgs-2f-shape_msgs-2f-msg-2f-detail:
	-$(RM) ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__description.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__description.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__description.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__description.su ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__functions.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__functions.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__functions.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__functions.su ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__type_support.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__type_support.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__type_support.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh__type_support.su ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__description.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__description.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__description.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__description.su ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__functions.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__functions.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__functions.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__functions.su ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__type_support.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__type_support.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__type_support.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/mesh_triangle__type_support.su ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__description.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__description.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__description.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__description.su ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__functions.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__functions.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__functions.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__functions.su ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__type_support.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__type_support.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__type_support.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/plane__type_support.su ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__description.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__description.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__description.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__description.su ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__functions.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__functions.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__functions.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__functions.su ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__type_support.cyclo ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__type_support.d ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__type_support.o ./Core/M4lib/include/shape_msgs/shape_msgs/msg/detail/solid_primitive__type_support.su

.PHONY: clean-Core-2f-M4lib-2f-include-2f-shape_msgs-2f-shape_msgs-2f-msg-2f-detail

