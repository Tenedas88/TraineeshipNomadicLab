################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/USB/MSC/Src/usbd_desc.c \
../src/USB/MSC/Src/usbd_msc.c \
../src/USB/MSC/Src/usbd_msc_F4Flash.c \
../src/USB/MSC/Src/usbd_msc_bot.c \
../src/USB/MSC/Src/usbd_msc_data.c \
../src/USB/MSC/Src/usbd_msc_scsi.c 

OBJS += \
./src/USB/MSC/Src/usbd_desc.o \
./src/USB/MSC/Src/usbd_msc.o \
./src/USB/MSC/Src/usbd_msc_F4Flash.o \
./src/USB/MSC/Src/usbd_msc_bot.o \
./src/USB/MSC/Src/usbd_msc_data.o \
./src/USB/MSC/Src/usbd_msc_scsi.o 

C_DEPS += \
./src/USB/MSC/Src/usbd_desc.d \
./src/USB/MSC/Src/usbd_msc.d \
./src/USB/MSC/Src/usbd_msc_F4Flash.d \
./src/USB/MSC/Src/usbd_msc_bot.d \
./src/USB/MSC/Src/usbd_msc_data.d \
./src/USB/MSC/Src/usbd_msc_scsi.d 


# Each subdirectory must supply rules for building sources it contributes
src/USB/MSC/Src/%.o: ../src/USB/MSC/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/Workspace Gruppo 2/Seminario USB - Doxygen Doc/USB_MSD/src/USB/MSC/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Seminario USB - Doxygen Doc/USB_MSD/src/USB/Core/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


