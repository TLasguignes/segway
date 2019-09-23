################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Libraries/Utilities/STM32F3_Discovery/subdir.mk
-include Libraries/STM32F30x_StdPeriph_Driver/src/subdir.mk
-include Libraries/CMSIS/Device/ST/STM32F30x/Source/Templates/subdir.mk
-include Keil/Service/subdir.mk
-include Keil/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
segway.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
segway.list \


# All Target
all: segway.elf secondary-outputs

# Tool invocations
segway.elf: $(OBJS) $(USER_OBJS) /home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/CubeIDE/STM32F303VCTX_FLASH.ld
	arm-none-eabi-gcc -o "segway.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/CubeIDE/STM32F303VCTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="segway.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

segway.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "segway.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
