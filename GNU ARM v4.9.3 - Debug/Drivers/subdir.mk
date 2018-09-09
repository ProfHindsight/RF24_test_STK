################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/i2cspm.c \
../Drivers/rtcdriver.c \
../Drivers/si7013.c \
../Drivers/sleep.c 

CPP_SRCS += \
../Drivers/BMP280.cpp 

OBJS += \
./Drivers/BMP280.o \
./Drivers/i2cspm.o \
./Drivers/rtcdriver.o \
./Drivers/si7013.o \
./Drivers/sleep.o 

C_DEPS += \
./Drivers/i2cspm.d \
./Drivers/rtcdriver.d \
./Drivers/si7013.d \
./Drivers/sleep.d 

CPP_DEPS += \
./Drivers/BMP280.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BMP280.o: ../Drivers/BMP280.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb '-DEFM32GG990F1024=1' -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\RF24" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\Drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -Os -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"Drivers/BMP280.d" -MT"Drivers/BMP280.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/i2cspm.o: ../Drivers/i2cspm.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -std=c99 '-DEFM32GG990F1024=1' -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\RF24" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\Drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -Os -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"Drivers/i2cspm.d" -MT"Drivers/i2cspm.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/rtcdriver.o: ../Drivers/rtcdriver.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -std=c99 '-DEFM32GG990F1024=1' -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\RF24" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\Drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -Os -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"Drivers/rtcdriver.d" -MT"Drivers/rtcdriver.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/si7013.o: ../Drivers/si7013.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -std=c99 '-DEFM32GG990F1024=1' -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\RF24" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\Drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -Os -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"Drivers/si7013.d" -MT"Drivers/si7013.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/sleep.o: ../Drivers/sleep.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -std=c99 '-DEFM32GG990F1024=1' -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/CMSIS/Include" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\RF24" -I"C:\Users\Colton\SimplicityStudio\v4_workspace\RF24_test_STK\Drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/bsp" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/emlib/inc" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//hardware/kit/common/drivers" -I"T:/SiliconLabs/SimplicityStudio/v4/developer/sdks/exx32/v5.0.0.0//platform/Device/SiliconLabs/EFM32GG/Include" -Os -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"Drivers/sleep.d" -MT"Drivers/sleep.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


