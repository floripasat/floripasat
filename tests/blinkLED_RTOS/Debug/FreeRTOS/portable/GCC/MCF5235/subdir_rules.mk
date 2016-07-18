################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/portable/GCC/MCF5235/port.obj: ../FreeRTOS/portable/GCC/MCF5235/port.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="/code/sdk/ti/ccsv6/ccs_base/msp430/include" --include_path="/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power=all -g --define=__MSP430F6659__ --diag_wrap=off --display_error_number --diag_warning=225 --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="FreeRTOS/portable/GCC/MCF5235/port.d" --obj_directory="FreeRTOS/portable/GCC/MCF5235" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


