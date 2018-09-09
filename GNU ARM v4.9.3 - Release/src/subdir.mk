################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main.cpp 

OBJS += \
./src/main.o 

CPP_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/main.o: ../src/main.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C++ Compiler'
	arm-none-eabi-g++ -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32GG990F1024=1' -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\RF24" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\Drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/EFM32GG_STK3700/config" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -MMD -MP -MF"src/main.d" -MT"src/main.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


