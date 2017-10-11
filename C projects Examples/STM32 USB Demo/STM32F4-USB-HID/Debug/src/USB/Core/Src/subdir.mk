################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/USB/Core/Src/usbd_conf.c \
../src/USB/Core/Src/usbd_core.c \
../src/USB/Core/Src/usbd_ctlreq.c \
../src/USB/Core/Src/usbd_ioreq.c 

OBJS += \
./src/USB/Core/Src/usbd_conf.o \
./src/USB/Core/Src/usbd_core.o \
./src/USB/Core/Src/usbd_ctlreq.o \
./src/USB/Core/Src/usbd_ioreq.o 

C_DEPS += \
./src/USB/Core/Src/usbd_conf.d \
./src/USB/Core/Src/usbd_core.d \
./src/USB/Core/Src/usbd_ctlreq.d \
./src/USB/Core/Src/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
src/USB/Core/Src/%.o: ../src/USB/Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-HID/src/USB/Core/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-HID/src/USB/HID/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-USB-HID/src/Accelerometer/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


