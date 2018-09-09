################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include RF24/subdir.mk
-include Drivers/subdir.mk
-include CMSIS/EFM32GG/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: RF24_test_STK.axf

# Tool invocations
RF24_test_STK.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C++ Linker'
	arm-none-eabi-g++ -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "RF24_test_STK.ld" --specs=nosys.specs -Xlinker --gc-sections -Xlinker -Map="RF24_test_STK.map" --specs=nano.specs -o RF24_test_STK.axf "./src/main.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_dbg.o" "./emlib/em_dma.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_int.o" "./emlib/em_leuart.o" "./emlib/em_rmu.o" "./emlib/em_rtc.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./RF24/HardwareSPI.o" "./RF24/RF24.o" "./RF24/ustimer.o" "./RF24/utilities.o" "./Drivers/BMP280.o" "./Drivers/i2cspm.o" "./Drivers/rtcdriver.o" "./Drivers/si7013.o" "./Drivers/sleep.o" "./CMSIS/EFM32GG/startup_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: RF24_test_STK.hex'
	arm-none-eabi-objcopy -O ihex "RF24_test_STK.axf" "RF24_test_STK.hex"
	@echo ' '

	@echo 'Building bin file: RF24_test_STK.bin'
	arm-none-eabi-objcopy -O binary "RF24_test_STK.axf" "RF24_test_STK.bin"
	@echo ' '

	@echo 'Building s37 file: RF24_test_STK.s37'
	arm-none-eabi-objcopy -O srec "RF24_test_STK.axf" "RF24_test_STK.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "RF24_test_STK.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) RF24_test_STK.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
