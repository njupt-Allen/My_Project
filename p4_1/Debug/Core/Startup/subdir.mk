################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f103rctx.s 

OBJS += \
./Core/Startup/startup_stm32f103rctx.o 

S_DEPS += \
./Core/Startup/startup_stm32f103rctx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG -c -I"E:/My_Project/p4_1/freertos/inc" -I"E:/My_Project/p4_1/Core/Inc" -I"E:/My_Project/p4_1/User/Task" -I"E:/My_Project/p4_1/Drivers" -I"E:/My_Project/p4_1/User/Keys" -I"E:/My_Project/p4_1/freertos/src" -I"E:/My_Project/p4_1/User" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f103rctx.d ./Core/Startup/startup_stm32f103rctx.o

.PHONY: clean-Core-2f-Startup

