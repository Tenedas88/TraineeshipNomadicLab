################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fat/src/diskio.c \
../src/fat/src/ff.c \
../src/fat/src/ff_gen_drv.c \
../src/fat/src/file_operations.c \
../src/fat/src/usbh_diskio.c 

OBJS += \
./src/fat/src/diskio.o \
./src/fat/src/ff.o \
./src/fat/src/ff_gen_drv.o \
./src/fat/src/file_operations.o \
./src/fat/src/usbh_diskio.o 

C_DEPS += \
./src/fat/src/diskio.d \
./src/fat/src/ff.d \
./src/fat/src/ff_gen_drv.d \
./src/fat/src/file_operations.d \
./src/fat/src/usbh_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
src/fat/src/%.o: ../src/fat/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/EventLogger/src/EventLogger/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/EventLogger/src/fat/inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/EventLogger/src/usb/Core/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/EventLogger/src/usb/MSC/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/EventLogger/src/Sys_Timer/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


