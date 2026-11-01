################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/src/croutine.c \
../freertos/src/event_groups.c \
../freertos/src/heap_4.c \
../freertos/src/list.c \
../freertos/src/port.c \
../freertos/src/queue.c \
../freertos/src/stream_buffer.c \
../freertos/src/tasks.c \
../freertos/src/timers.c 

OBJS += \
./freertos/src/croutine.o \
./freertos/src/event_groups.o \
./freertos/src/heap_4.o \
./freertos/src/list.o \
./freertos/src/port.o \
./freertos/src/queue.o \
./freertos/src/stream_buffer.o \
./freertos/src/tasks.o \
./freertos/src/timers.o 

C_DEPS += \
./freertos/src/croutine.d \
./freertos/src/event_groups.d \
./freertos/src/heap_4.d \
./freertos/src/list.d \
./freertos/src/port.d \
./freertos/src/queue.d \
./freertos/src/stream_buffer.d \
./freertos/src/tasks.d \
./freertos/src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/src/%.o freertos/src/%.su freertos/src/%.cyclo: ../freertos/src/%.c freertos/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../freertos/inc -I../Drivers -I../User/Task -I"E:/My_Project/p1_2/User/Keys" -I"E:/My_Project/p1_2/freertos/src" -I"E:/My_Project/p1_2/User" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-freertos-2f-src

clean-freertos-2f-src:
	-$(RM) ./freertos/src/croutine.cyclo ./freertos/src/croutine.d ./freertos/src/croutine.o ./freertos/src/croutine.su ./freertos/src/event_groups.cyclo ./freertos/src/event_groups.d ./freertos/src/event_groups.o ./freertos/src/event_groups.su ./freertos/src/heap_4.cyclo ./freertos/src/heap_4.d ./freertos/src/heap_4.o ./freertos/src/heap_4.su ./freertos/src/list.cyclo ./freertos/src/list.d ./freertos/src/list.o ./freertos/src/list.su ./freertos/src/port.cyclo ./freertos/src/port.d ./freertos/src/port.o ./freertos/src/port.su ./freertos/src/queue.cyclo ./freertos/src/queue.d ./freertos/src/queue.o ./freertos/src/queue.su ./freertos/src/stream_buffer.cyclo ./freertos/src/stream_buffer.d ./freertos/src/stream_buffer.o ./freertos/src/stream_buffer.su ./freertos/src/tasks.cyclo ./freertos/src/tasks.d ./freertos/src/tasks.o ./freertos/src/tasks.su ./freertos/src/timers.cyclo ./freertos/src/timers.d ./freertos/src/timers.o ./freertos/src/timers.su

.PHONY: clean-freertos-2f-src

