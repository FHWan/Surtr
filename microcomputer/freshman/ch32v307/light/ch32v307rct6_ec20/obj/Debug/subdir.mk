################################################################################
# MRS Version: {"version":"1.8.5","date":"2023/05/22"}
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/%.o: ../Debug/%.c
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"F:\stm32\teamproject\2023��һ����Ŀ�����\2.·��\ѩ������������MRS��ch32v307rct6ʵ��ec20\Debug" -I"F:\stm32\teamproject\2023��һ����Ŀ�����\2.·��\ѩ������������MRS��ch32v307rct6ʵ��ec20\Core" -I"F:\stm32\teamproject\2023��һ����Ŀ�����\2.·��\ѩ������������MRS��ch32v307rct6ʵ��ec20\User" -I"F:\stm32\teamproject\2023��һ����Ŀ�����\2.·��\ѩ������������MRS��ch32v307rct6ʵ��ec20\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

