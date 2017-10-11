################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c 

OBJS += \
./src/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.o 

C_DEPS += \
./src/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.d 


# Each subdirectory must supply rules for building sources it contributes
src/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.o: /home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-FreeRTOS-USB-HID/src/USB/Core/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-FreeRTOS-USB-HID/src/USB/HID/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-FreeRTOS-USB-HID/src/FreeRTOS-USB-HID-Lib/Inc" -I"/home/davide/Desktop/STM32ToolChain/Workspace Arm/STM32F4-FreeRTOS-USB-HID/include" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


