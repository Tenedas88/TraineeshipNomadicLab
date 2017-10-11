################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/usb/Core/Src/usbh_conf.c \
../src/usb/Core/Src/usbh_core.c \
../src/usb/Core/Src/usbh_ctlreq.c \
../src/usb/Core/Src/usbh_ioreq.c \
../src/usb/Core/Src/usbh_pipes.c 

OBJS += \
./src/usb/Core/Src/usbh_conf.o \
./src/usb/Core/Src/usbh_core.o \
./src/usb/Core/Src/usbh_ctlreq.o \
./src/usb/Core/Src/usbh_ioreq.o \
./src/usb/Core/Src/usbh_pipes.o 

C_DEPS += \
./src/usb/Core/Src/usbh_conf.d \
./src/usb/Core/Src/usbh_core.d \
./src/usb/Core/Src/usbh_ctlreq.d \
./src/usb/Core/Src/usbh_ioreq.d \
./src/usb/Core/Src/usbh_pipes.d 


# Each subdirectory must supply rules for building sources it contributes
src/usb/Core/Src/%.o: ../src/usb/Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS/src/EventLogger/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS/src/fat/inc" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS/src/Sys_Timer/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS/src/usb/Core/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS/src/usb/MSC/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


