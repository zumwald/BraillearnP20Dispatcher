################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Source/Control/Control.obj: ../Source/Control/Control.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"E:/ti/ccsv5/tools/compiler/arm_5.0.1/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 -g --include_path="E:/ti/ccsv5/tools/compiler/arm_5.0.1/include" --include_path="E:/StellarisWorkspace/Braillearn/Source/UART" --include_path="E:/StellarisWorkspace/Braillearn/Source/Control" --include_path="E:/StellarisWorkspace/Braillearn/Source/Key" --include_path="E:/StellarisWorkspace/Braillearn" --include_path="E:/StellarisWare" --gcc --define=ccs="ccs" --define=PART_LM4F120H5QR --define=TARGET_IS_BLIZZARD_RA1 --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="Source/Control/Control.pp" --obj_directory="Source/Control" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


