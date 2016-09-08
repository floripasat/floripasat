################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./FreeRTOSSource/croutine.obj" \
"./FreeRTOSSource/event_groups.obj" \
"./FreeRTOSSource/list.obj" \
"./FreeRTOSSource/queue.obj" \
"./FreeRTOSSource/tasks.obj" \
"./FreeRTOSSource/timers.obj" \
"./FreeRTOSSource/portable/CCS/MSP430X/port.obj" \
"./FreeRTOSSource/portable/CCS/MSP430X/portext.obj" \
"./FreeRTOSSource/portable/MemMang/heap_1.obj" \
"./Fsat/fsat_tasks.obj" \
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
-include FreeRTOSSource/subdir_vars.mk
-include FreeRTOSSource/portable/CCS/MSP430X/subdir_vars.mk
-include FreeRTOSSource/portable/MemMang/subdir_vars.mk
-include Fsat/subdir_vars.mk
-include subdir_rules.mk
-include FreeRTOSSource/subdir_rules.mk
-include FreeRTOSSource/portable/CCS/MSP430X/subdir_rules.mk
-include FreeRTOSSource/portable/MemMang/subdir_rules.mk
-include Fsat/subdir_rules.mk
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
obdh_v2.out \

EXE_OUTPUTS__QUOTED += \
"obdh_v2.out" \

BIN_OUTPUTS += \
obdh_v2.hex \

BIN_OUTPUTS__QUOTED += \
"obdh_v2.hex" \


# All Target
all: obdh_v2.out

# Tool invocations
obdh_v2.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --advice:power=all --define=__MSP430F6659__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 -z -m"obdh_v2.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"/home/elder/ti/ccsv6/ccs_base/msp430/include" -i"/home/elder/ti/ccsv6/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/lib" -i"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="obdh_v2_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "obdh_v2.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

obdh_v2.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"/home/elder/ti/ccsv6/tools/compiler/ti-cgt-msp430_16.6.0.STS/bin/hex430" --memwidth=8 --romwidth=8 -o "obdh_v2.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main.d" "FreeRTOSSource/croutine.d" "FreeRTOSSource/event_groups.d" "FreeRTOSSource/list.d" "FreeRTOSSource/queue.d" "FreeRTOSSource/tasks.d" "FreeRTOSSource/timers.d" "FreeRTOSSource/portable/CCS/MSP430X/port.d" "FreeRTOSSource/portable/MemMang/heap_1.d" "Fsat/fsat_tasks.d" 
	-$(RM) "main.obj" "FreeRTOSSource/croutine.obj" "FreeRTOSSource/event_groups.obj" "FreeRTOSSource/list.obj" "FreeRTOSSource/queue.obj" "FreeRTOSSource/tasks.obj" "FreeRTOSSource/timers.obj" "FreeRTOSSource/portable/CCS/MSP430X/port.obj" "FreeRTOSSource/portable/CCS/MSP430X/portext.obj" "FreeRTOSSource/portable/MemMang/heap_1.obj" "Fsat/fsat_tasks.obj" 
	-$(RM) "FreeRTOSSource/portable/CCS/MSP430X/portext.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

