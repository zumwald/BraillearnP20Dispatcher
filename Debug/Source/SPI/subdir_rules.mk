################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Source/SPI/SPI.obj: ../Source/SPI/SPI.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"E:/ti/ccsv5/tools/compiler/arm_5.0.1/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 -g --include_path="E:/ti/ccsv5/tools/compiler/arm_5.0.1/include" --include_path="E:/StellarisWorkspace/Braillearn_P20Dispatcher/Source/SPI" --include_path="E:/StellarisWorkspace/Braillearn_P20Dispatcher/Source/UART" --include_path="E:/StellarisWorkspace/Braillearn_P20Dispatcher/Source/Control" --include_path="E:/StellarisWorkspace/Braillearn_P20Dispatcher/Source/Key" --include_path="E:/StellarisWorkspace/Braillearn_P20Dispatcher" --include_path="E:/StellarisWare" --gcc --define=ccs="ccs" --define=PART_LM4F120H5QR --define=TARGET_IS_BLIZZARD_RA1 --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="Source/SPI/SPI.pp" --obj_directory="Source/SPI" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


