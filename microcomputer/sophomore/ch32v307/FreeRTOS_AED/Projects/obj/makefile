################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Middlewares/MALLOC/subdir.mk
-include Middlewares/FreeRTOS/portable/MemMang/subdir.mk
-include Middlewares/FreeRTOS/portable/GCC/RISC-V/subdir.mk
-include Middlewares/FreeRTOS/subdir.mk
-include Drivers/SYSTEM/usart/subdir.mk
-include Drivers/SYSTEM/sys/subdir.mk
-include Drivers/SYSTEM/delay/subdir.mk
-include Drivers/RISC_V/Startup/subdir.mk
-include Drivers/RISC_V/Core/subdir.mk
-include Drivers/CH32V30x_Driver/src/subdir.mk
-include Drivers/BSP/servo/subdir.mk
-include Drivers/BSP/adc/subdir.mk
-include Drivers/BSP/MPU6050/subdir.mk
-include Drivers/BSP/EC20/subdir.mk
-include Drivers/BSP/BEEPLED/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
FreeAED.hex \

SECONDARY_LIST += \
FreeAED.lst \

SECONDARY_SIZE += \
FreeAED.siz \


# 所有目标
all: FreeAED.elf secondary-outputs

# 工具调用
FreeAED.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "F:\Desktop\AED\yinjian\ch32v307\FreeRTOS_AED\Projects\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"FreeAED.map" --specs=nano.specs -u _printf_float -u _scanf_float --specs=nosys.specs  -o "FreeAED.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lprintfloat
	@	@
FreeAED.hex: FreeAED.elf
	@	riscv-none-embed-objcopy -O ihex "FreeAED.elf"  "FreeAED.hex"
	@	@
FreeAED.lst: FreeAED.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "FreeAED.elf" > "FreeAED.lst"
	@	@
FreeAED.siz: FreeAED.elf
	@	riscv-none-embed-size --format=berkeley "FreeAED.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) FreeAED.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
