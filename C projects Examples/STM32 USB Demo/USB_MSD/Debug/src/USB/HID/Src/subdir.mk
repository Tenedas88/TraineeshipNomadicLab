################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/USB/HID/Src/usbd_hid.c 

OBJS += \
./src/USB/HID/Src/usbd_hid.o 

C_DEPS += \
./src/USB/HID/Src/usbd_hid.d 


# Each subdirectory must supply rules for building sources it contributes
src/USB/HID/Src/%.o: ../src/USB/HID/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/andrea/Desktop/Embedded/Embedded_Cworkspace/USB_HID_PROVA/src/USB/Core/Inc" -I"/home/andrea/Desktop/Embedded/Embedded_Cworkspace/USB_HID_PROVA/src/USB/HID/Inc" -I"/home/andrea/Desktop/Embedded/Embedded_Cworkspace/USB_HID_PROVA/src/Accellerometro/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


