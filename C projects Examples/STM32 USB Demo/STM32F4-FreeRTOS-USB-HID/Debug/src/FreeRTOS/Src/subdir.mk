################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FreeRTOS/Src/cmsis_os.c \
../src/FreeRTOS/Src/croutine.c \
../src/FreeRTOS/Src/event_groups.c \
../src/FreeRTOS/Src/list.c \
../src/FreeRTOS/Src/port.c \
../src/FreeRTOS/Src/queue.c \
../src/FreeRTOS/Src/tasks.c \
../src/FreeRTOS/Src/timers.c 

OBJS += \
./src/FreeRTOS/Src/cmsis_os.o \
./src/FreeRTOS/Src/croutine.o \
./src/FreeRTOS/Src/event_groups.o \
./src/FreeRTOS/Src/list.o \
./src/FreeRTOS/Src/port.o \
./src/FreeRTOS/Src/queue.o \
./src/FreeRTOS/Src/tasks.o \
./src/FreeRTOS/Src/timers.o 

C_DEPS += \
./src/FreeRTOS/Src/cmsis_os.d \
./src/FreeRTOS/Src/croutine.d \
./src/FreeRTOS/Src/event_groups.d \
./src/FreeRTOS/Src/list.d \
./src/FreeRTOS/Src/port.d \
./src/FreeRTOS/Src/queue.d \
./src/FreeRTOS/Src/tasks.d \
./src/FreeRTOS/Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
src/FreeRTOS/Src/%.o: ../src/FreeRTOS/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-FreeRTOS-USB-HID/src/FreeRTOS/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


