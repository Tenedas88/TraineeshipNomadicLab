################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/list.c \
/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/timers.c 

OBJS += \
./src/FreeRTOS/Source/croutine.o \
./src/FreeRTOS/Source/event_groups.o \
./src/FreeRTOS/Source/list.o \
./src/FreeRTOS/Source/queue.o \
./src/FreeRTOS/Source/tasks.o \
./src/FreeRTOS/Source/timers.o 

C_DEPS += \
./src/FreeRTOS/Source/croutine.d \
./src/FreeRTOS/Source/event_groups.d \
./src/FreeRTOS/Source/list.d \
./src/FreeRTOS/Source/queue.d \
./src/FreeRTOS/Source/tasks.d \
./src/FreeRTOS/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
src/FreeRTOS/Source/croutine.o: /home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/EventLogger/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/fat/inc" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/Sys_Timer/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/Core/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/MSC/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FreeRTOS/Source/event_groups.o: /home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/EventLogger/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/fat/inc" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/Sys_Timer/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/Core/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/MSC/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FreeRTOS/Source/list.o: /home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/list.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/EventLogger/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/fat/inc" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/Sys_Timer/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/Core/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/MSC/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FreeRTOS/Source/queue.o: /home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/queue.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/EventLogger/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/fat/inc" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/Sys_Timer/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/Core/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/MSC/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FreeRTOS/Source/tasks.o: /home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/EventLogger/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/fat/inc" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/Sys_Timer/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/Core/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/MSC/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/FreeRTOS/Source/timers.o: /home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/timers.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_ITM -DSTM32F407xx -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/EventLogger/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/fat/inc" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/home/davide/Desktop/Boards/F4/STM32Cube_FW_F4_V1.5.0/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/Sys_Timer/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/Core/Inc" -I"/home/davide/Desktop/Workspace Gruppo 2/Progetto Finale/EventLogger_FreeRTOS_Flash/src/usb/MSC/Inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


