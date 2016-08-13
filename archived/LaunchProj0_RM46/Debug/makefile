################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /code/sdk/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./source/dabort.obj" \
"./source/esm.obj" \
"./source/gio.obj" \
"./source/notification.obj" \
"./source/pinmux.obj" \
"./source/sys_core.obj" \
"./source/sys_dma.obj" \
"./source/sys_intvecs.obj" \
"./source/sys_main.obj" \
"./source/sys_mpu.obj" \
"./source/sys_pcr.obj" \
"./source/sys_phantom.obj" \
"./source/sys_pmm.obj" \
"./source/sys_pmu.obj" \
"./source/sys_selftest.obj" \
"./source/sys_startup.obj" \
"./source/sys_vim.obj" \
"./source/system.obj" \
"../source/sys_link.cmd" \
$(GEN_CMDS__FLAG) \
-lrtsv7R4_T_le_v3D16_eabi.lib \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include source/subdir_vars.mk
-include source/subdir_rules.mk
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
LaunchProj0_RM46.out \

EXE_OUTPUTS__QUOTED += \
"LaunchProj0_RM46.out" \

BIN_OUTPUTS += \
LaunchProj0_RM46.hex \

BIN_OUTPUTS__QUOTED += \
"LaunchProj0_RM46.hex" \


# All Target
all: LaunchProj0_RM46.out

# Tool invocations
LaunchProj0_RM46.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi -me -g --display_error_number --diag_warning=225 --diag_wrap=off --enum_type=packed -z -m"LaunchProj0_RM46.map" --heap_size=0x800 --stack_size=0x800 -i"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/lib" -i"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="LaunchProj0_RM46_linkInfo.xml" --rom_model -o "LaunchProj0_RM46.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

LaunchProj0_RM46.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"/code/sdk/ti/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armhex"  -o "LaunchProj0_RM46.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "source/esm.d" "source/gio.d" "source/notification.d" "source/pinmux.d" "source/sys_dma.d" "source/sys_main.d" "source/sys_pcr.d" "source/sys_phantom.d" "source/sys_pmm.d" "source/sys_selftest.d" "source/sys_startup.d" "source/sys_vim.d" "source/system.d" 
	-$(RM) "source/dabort.obj" "source/esm.obj" "source/gio.obj" "source/notification.obj" "source/pinmux.obj" "source/sys_core.obj" "source/sys_dma.obj" "source/sys_intvecs.obj" "source/sys_main.obj" "source/sys_mpu.obj" "source/sys_pcr.obj" "source/sys_phantom.obj" "source/sys_pmm.obj" "source/sys_pmu.obj" "source/sys_selftest.obj" "source/sys_startup.obj" "source/sys_vim.obj" "source/system.obj" 
	-$(RM) "source/dabort.d" "source/sys_core.d" "source/sys_intvecs.d" "source/sys_mpu.d" "source/sys_pmu.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

