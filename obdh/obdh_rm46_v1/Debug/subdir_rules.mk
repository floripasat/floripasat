################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 -me -O3 --opt_for_speed=5 --include_path="/home/elder/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="/code/floripasat/obdh/obdh_rm46_v1/Library" --include_path="/code/floripasat/obdh/obdh_rm46_v1/FreeRTOS/portable/CCS/ARM_Cortex-R4" --include_path="/code/floripasat/obdh/obdh_rm46_v1/FreeRTOS/portable/MemMang" --include_path="/code/floripasat/obdh/obdh_rm46_v1" --include_path="/code/floripasat/obdh/obdh_rm46_v1/FreeRTOS/include" --include_path="/code/floripasat/obdh/obdh_rm46_v1/FreeRTOS" -g --display_error_number --diag_warning=225 --abi=eabi --enum_type=packed --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

reg_test.obj: ../reg_test.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 -me -O3 --opt_for_speed=5 --include_path="/home/elder/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="/code/floripasat/obdh/obdh_rm46_v1/Library" --include_path="/code/floripasat/obdh/obdh_rm46_v1/FreeRTOS/portable/CCS/ARM_Cortex-R4" --include_path="/code/floripasat/obdh/obdh_rm46_v1/FreeRTOS/portable/MemMang" --include_path="/code/floripasat/obdh/obdh_rm46_v1" --include_path="/code/floripasat/obdh/obdh_rm46_v1/FreeRTOS/include" --include_path="/code/floripasat/obdh/obdh_rm46_v1/FreeRTOS" -g --display_error_number --diag_warning=225 --abi=eabi --enum_type=packed --preproc_with_compile --preproc_dependency="reg_test.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


