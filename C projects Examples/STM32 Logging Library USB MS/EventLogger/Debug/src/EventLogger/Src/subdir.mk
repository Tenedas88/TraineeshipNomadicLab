################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/EventLogger/Src/EventLogger.c \
../src/EventLogger/Src/EventLogger_conf.c 

OBJS += \
./src/EventLogger/Src/EventLogger.o \
./src/EventLogger/Src/EventLogger_conf.o 

C_DEPS += \
./src/EventLogger/Src/EventLogger.d \
./src/EventLogger/Src/EventLogger_conf.d 


# Each subdirectory must supply rules for building sources it contributes
src/EventLogger/Src/%.o: ../src/EventLogger/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/EventLogger/src/EventLogger/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/EventLogger/src/fat/inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/EventLogger/src/usb/Core/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/EventLogger/src/usb/MSC/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/EventLogger/src/Sys_Timer/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


