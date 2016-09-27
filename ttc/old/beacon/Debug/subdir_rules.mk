################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
bsp.obj: ../bsp.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="/code/sdk/ti/ccsv6/ccs_base/msp430/include" --include_path="/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power=all -g --define=__MSP430F6659__ --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="bsp.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

cc112x_spi.obj: ../cc112x_spi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="/code/sdk/ti/ccsv6/ccs_base/msp430/include" --include_path="/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power=all -g --define=__MSP430F6659__ --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="cc112x_spi.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

hal_spi_rf_floripasat.obj: ../hal_spi_rf_floripasat.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="/code/sdk/ti/ccsv6/ccs_base/msp430/include" --include_path="/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power=all -g --define=__MSP430F6659__ --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="hal_spi_rf_floripasat.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

io_pin_int.obj: ../io_pin_int.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="/code/sdk/ti/ccsv6/ccs_base/msp430/include" --include_path="/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power=all -g --define=__MSP430F6659__ --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="io_pin_int.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="/code/sdk/ti/ccsv6/ccs_base/msp430/include" --include_path="/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power=all -g --define=__MSP430F6659__ --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '

watchdog.obj: ../watchdog.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="/code/sdk/ti/ccsv6/ccs_base/msp430/include" --include_path="/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --advice:power=all -g --define=__MSP430F6659__ --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="watchdog.d" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


