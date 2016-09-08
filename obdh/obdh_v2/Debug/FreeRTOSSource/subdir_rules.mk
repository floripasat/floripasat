################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
FreeRTOSSource/croutine.obj: ../FreeRTOSSource/croutine.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="/home/elder/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/MemMang" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/CCS/MSP430X/" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/Fsat/" --advice:power=all --define=__MSP430F6659__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOSSource/croutine.d" --obj_directory="FreeRTOSSource" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSSource/event_groups.obj: ../FreeRTOSSource/event_groups.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="/home/elder/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/MemMang" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/CCS/MSP430X/" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/Fsat/" --advice:power=all --define=__MSP430F6659__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOSSource/event_groups.d" --obj_directory="FreeRTOSSource" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSSource/list.obj: ../FreeRTOSSource/list.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="/home/elder/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/MemMang" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/CCS/MSP430X/" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/Fsat/" --advice:power=all --define=__MSP430F6659__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOSSource/list.d" --obj_directory="FreeRTOSSource" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSSource/queue.obj: ../FreeRTOSSource/queue.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="/home/elder/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/MemMang" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/CCS/MSP430X/" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/Fsat/" --advice:power=all --define=__MSP430F6659__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOSSource/queue.d" --obj_directory="FreeRTOSSource" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSSource/tasks.obj: ../FreeRTOSSource/tasks.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="/home/elder/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/MemMang" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/CCS/MSP430X/" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/Fsat/" --advice:power=all --define=__MSP430F6659__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOSSource/tasks.d" --obj_directory="FreeRTOSSource" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

FreeRTOSSource/timers.obj: ../FreeRTOSSource/timers.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="/home/elder/ti/ccsv6/ccs_base/msp430/include" --include_path="/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/include" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/MemMang" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/FreeRTOSSource/portable/CCS/MSP430X/" --include_path="/home/elder/workspace_v6_1_3/obdh_v2/Fsat/" --advice:power=all --define=__MSP430F6659__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOSSource/timers.d" --obj_directory="FreeRTOSSource" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


