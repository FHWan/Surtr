################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Infrared.obj: ../Infrared.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/MSP/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/MSP/workspace/gpio_ex1_outputHi" --include_path="D:/MSP/workspace/gpio_ex1_outputHi/driverlib/MSP430F5xx_6xx" --include_path="D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="none" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="Infrared.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Motor.obj: ../Motor.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/MSP/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/MSP/workspace/gpio_ex1_outputHi" --include_path="D:/MSP/workspace/gpio_ex1_outputHi/driverlib/MSP430F5xx_6xx" --include_path="D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="none" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="Motor.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

PID.obj: ../PID.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/MSP/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/MSP/workspace/gpio_ex1_outputHi" --include_path="D:/MSP/workspace/gpio_ex1_outputHi/driverlib/MSP430F5xx_6xx" --include_path="D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="none" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="PID.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

UART.obj: ../UART.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/MSP/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/MSP/workspace/gpio_ex1_outputHi" --include_path="D:/MSP/workspace/gpio_ex1_outputHi/driverlib/MSP430F5xx_6xx" --include_path="D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="none" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="UART.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

gpio_ex1_outputHi.obj: ../gpio_ex1_outputHi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/MSP/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/MSP/workspace/gpio_ex1_outputHi" --include_path="D:/MSP/workspace/gpio_ex1_outputHi/driverlib/MSP430F5xx_6xx" --include_path="D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="none" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="gpio_ex1_outputHi.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

oled.obj: ../oled.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="D:/MSP/ccs/ccsv8/ccs_base/msp430/include" --include_path="D:/MSP/workspace/gpio_ex1_outputHi" --include_path="D:/MSP/workspace/gpio_ex1_outputHi/driverlib/MSP430F5xx_6xx" --include_path="D:/MSP/ccs/ccsv8/tools/compiler/ti-cgt-msp430_18.1.1.LTS/include" --advice:power="none" --define=__MSP430F5529__ --define=DEPRECATED -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="oled.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


