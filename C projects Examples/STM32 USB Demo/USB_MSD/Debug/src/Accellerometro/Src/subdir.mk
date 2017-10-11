################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Accellerometro/Src/lis302dl.c \
../src/Accellerometro/Src/lis3dsh.c 

OBJS += \
./src/Accellerometro/Src/lis302dl.o \
./src/Accellerometro/Src/lis3dsh.o 

C_DEPS += \
./src/Accellerometro/Src/lis302dl.d \
./src/Accellerometro/Src/lis3dsh.d 


# Each subdirectory must supply rules for building sources it contributes
src/Accellerometro/Src/%.o: ../src/Accellerometro/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/andrea/Desktop/Embedded/Embedded_Cworkspace/USB_HID_PROVA/src/USB/Core/Inc" -I"/home/andrea/Desktop/Embedded/Embedded_Cworkspace/USB_HID_PROVA/src/USB/HID/Inc" -I"/home/andrea/Desktop/Embedded/Embedded_Cworkspace/USB_HID_PROVA/src/Accellerometro/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


