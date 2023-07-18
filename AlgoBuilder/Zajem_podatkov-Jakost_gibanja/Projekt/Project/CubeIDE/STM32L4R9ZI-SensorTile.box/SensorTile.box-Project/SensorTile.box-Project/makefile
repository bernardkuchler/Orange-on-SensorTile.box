################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/STM32_USBD_Library/Core/subdir.mk
-include Middlewares/STM32_USBD_Library/Class/MSC/subdir.mk
-include Middlewares/STM32_USBD_Library/Class/CDC_MSC/subdir.mk
-include Middlewares/STM32_USBD_Library/Class/CDC/subdir.mk
-include Middlewares/FatFs/Options/subdir.mk
-include Middlewares/FatFs/Core/subdir.mk
-include Example/User/subdir.mk
-include Example/SW4STM32/subdir.mk
-include Example/AlgoBuilder/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/SensorTile.box/subdir.mk
-include Drivers/BSP/Components/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := SensorTile.box-Project
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SensorTile.box-Project.elf \

MAP_FILES += \
SensorTile.box-Project.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SensorTile.box-Project.list \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: SensorTile.box-Project.elf secondary-outputs

# Tool invocations
SensorTile.box-Project.elf SensorTile.box-Project.map: $(OBJS) $(USER_OBJS) ../LinkerScript.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "SensorTile.box-Project.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"../LinkerScript.ld" -Wl,-Map="SensorTile.box-Project.map" -Wl,--gc-sections -static -L../../../../../Middlewares/ST/STM32_MotionAC_Library/Lib -L../../../../../Middlewares/ST/STM32_MotionAW_Library/Lib -L../../../../../Middlewares/ST/STM32_MotionEC_Library/Lib -L../../../../../Middlewares/ST/STM32_MotionFX_Library/Lib -L../../../../../Middlewares/ST/STM32_MotionGC_Library/Lib -L../../../../../Middlewares/ST/STM32_MotionID_Library/Lib -L../../../../../Middlewares/ST/STM32_MotionMC_Library/Lib -L../../../../../Middlewares/ST/STM32_MotionPM_Library/Lib -L../../../../../Middlewares/ST/STM32_MotionPW_Library/Lib -L../../../../../Middlewares/ST/STM32_MotionTL_Library/Lib -L../../../../../Drivers/CMSIS/Lib/GCC  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SensorTile.box-Project.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SensorTile.box-Project.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SensorTile.box-Project.elf SensorTile.box-Project.list SensorTile.box-Project.map default.size.stdout
	-@echo ' '

post-build:
	arm-none-eabi-objcopy -O binary "SensorTile.box-Project.elf" "SensorTile.box-Project.bin"
	arm-none-eabi-objcopy -O ihex "SensorTile.box-Project.elf" "SensorTile.box-Project.hex"
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified post-build

-include ../makefile.targets
