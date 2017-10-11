################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/_initialize_hardware.c \
../src/_write.c \
../src/main.c \
../src/stm32f4_discovery.c \
../src/stm32f4_discovery_audio.c \
../src/stm32f4xx_it.c 

OBJS += \
./src/_initialize_hardware.o \
./src/_write.o \
./src/main.o \
./src/stm32f4_discovery.o \
./src/stm32f4_discovery_audio.o \
./src/stm32f4xx_it.o 

C_DEPS += \
./src/_initialize_hardware.d \
./src/_write.d \
./src/main.d \
./src/stm32f4_discovery.d \
./src/stm32f4_discovery_audio.d \
./src/stm32f4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-AUDIO-SPEAKER/include" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-AUDIO-SPEAKER/system/include" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-AUDIO-SPEAKER/system/include/cmsis" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-AUDIO-SPEAKER/system/include/stm32f4-hal" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-AUDIO-SPEAKER/src/USB/Audio/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-AUDIO-SPEAKER/src/USB/Core/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-AUDIO-SPEAKER/src/Audio Jack/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-AUDIO-SPEAKER/src/PDM" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


