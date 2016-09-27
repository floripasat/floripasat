################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./bsp.obj" \
"./cc112x_spi.obj" \
"./hal_spi_rf_floripasat.obj" \
"./io_pin_int.obj" \
"./main.obj" \
"./watchdog.obj" \
"../lnk_msp430f6659.cmd" \
$(GEN_CMDS__FLAG) \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
beacon.out \

EXE_OUTPUTS__QUOTED += \
"beacon.out" \

BIN_OUTPUTS += \
beacon.hex \

BIN_OUTPUTS__QUOTED += \
"beacon.hex" \


# All Target
all: beacon.out

# Tool invocations
beacon.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --advice:power=all -g --define=__MSP430F6659__ --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=minimal -z -m"beacon.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"/code/sdk/ti/ccsv6/ccs_base/msp430/include" -i"/code/sdk/ti/ccsv6/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/lib" -i"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/include" --reread_libs --warn_sections --diag_wrap=off --display_error_number --xml_link_info="beacon_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "beacon.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

beacon.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-msp430_15.12.1.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "beacon.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "bsp.d" "cc112x_spi.d" "hal_spi_rf_floripasat.d" "io_pin_int.d" "main.d" "watchdog.d" 
	-$(RM) "bsp.obj" "cc112x_spi.obj" "hal_spi_rf_floripasat.obj" "io_pin_int.obj" "main.obj" "watchdog.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

