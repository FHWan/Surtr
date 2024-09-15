################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/extra_sources/microros_transports/subdir.mk
-include Core/extra_sources/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Core/M4lib/include/visualization_msgs/srv/detail/subdir.mk
-include Core/M4lib/include/visualization_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/unique_identifier_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/type_description_interfaces/srv/detail/subdir.mk
-include Core/M4lib/include/type_description_interfaces/msg/detail/subdir.mk
-include Core/M4lib/include/trajectory_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/test_msgs/srv/detail/subdir.mk
-include Core/M4lib/include/test_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/test_msgs/action/detail/subdir.mk
-include Core/M4lib/include/stereo_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/std_srvs/srv/detail/subdir.mk
-include Core/M4lib/include/std_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/statistics_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/shape_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/service_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/sensor_msgs/srv/detail/subdir.mk
-include Core/M4lib/include/sensor_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/rosgraph_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/rcl_interfaces/srv/detail/subdir.mk
-include Core/M4lib/include/rcl_interfaces/msg/detail/subdir.mk
-include Core/M4lib/include/nav_msgs/srv/detail/subdir.mk
-include Core/M4lib/include/nav_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/micro_ros_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/lifecycle_msgs/srv/detail/subdir.mk
-include Core/M4lib/include/lifecycle_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/geometry_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/example_interfaces/srv/detail/subdir.mk
-include Core/M4lib/include/example_interfaces/msg/detail/subdir.mk
-include Core/M4lib/include/example_interfaces/action/detail/subdir.mk
-include Core/M4lib/include/diagnostic_msgs/srv/detail/subdir.mk
-include Core/M4lib/include/diagnostic_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/composition_interfaces/srv/detail/subdir.mk
-include Core/M4lib/include/builtin_interfaces/msg/detail/subdir.mk
-include Core/M4lib/include/actionlib_msgs/msg/detail/subdir.mk
-include Core/M4lib/include/action_msgs/srv/detail/subdir.mk
-include Core/M4lib/include/action_msgs/msg/detail/subdir.mk
-include Core/BSP/oled/subdir.mk
-include Core/BSP/motor/subdir.mk
-include Core/BSP/encoder/subdir.mk
-include Core/BSP/Robotic_arm/subdir.mk
-include Core/BSP/Kinematics/subdir.mk
-include Core/BSP/JY61P/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := ros
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ros.elf \

MAP_FILES += \
ros.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ros.list \

OBJCOPY_HEX += \
ros.hex \

OBJCOPY_BIN += \
ros.bin \


# All Target
all: main-build

# Main-build Target
main-build: ros.elf secondary-outputs

# Tool invocations
ros.elf ros.map: $(OBJS) $(USER_OBJS) F:\SMT32CubeMx\project\ros\STM32F407ZGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "ros.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"F:\SMT32CubeMx\project\ros\STM32F407ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ros.map" -Wl,--gc-sections -static -L"F:\SMT32CubeMx\project\ros\Core\M4lib" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ros.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ros.list"
	@echo 'Finished building: $@'
	@echo ' '

ros.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "ros.hex"
	@echo 'Finished building: $@'
	@echo ' '

ros.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ros.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout ros.bin ros.elf ros.hex ros.list ros.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
