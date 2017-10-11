################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/_initialize_hardware.c \
../src/_write.c \
../src/main.c \
../src/stm32f4_discovery.c \
../src/stm32f4_discovery_accelerometer.c \
../src/stm32f4xx_it.c 

OBJS += \
./src/_initialize_hardware.o \
./src/_write.o \
./src/main.o \
./src/stm32f4_discovery.o \
./src/stm32f4_discovery_accelerometer.o \
./src/stm32f4xx_it.o 

C_DEPS += \
./src/_initialize_hardware.d \
./src/_write.d \
./src/main.d \
./src/stm32f4_discovery.d \
./src/stm32f4_discovery_accelerometer.d \
./src/stm32f4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-HID/src/USB/Core/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-HID/src/USB/HID/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-HID/src/Accelerometer/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


