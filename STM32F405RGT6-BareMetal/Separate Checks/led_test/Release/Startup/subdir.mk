################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f405rgtx.s 

OBJS += \
./Startup/startup_stm32f405rgtx.o 

S_DEPS += \
./Startup/startup_stm32f405rgtx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -DSTM32F405xx -c -I/home/last_knight/Projects/MicroJAS/STM32F405RGT6-BareMetal/chip_headers/CMSIS/Include -I/home/last_knight/Projects/MicroJAS/STM32F405RGT6-BareMetal/chip_headers/CMSIS/Device/ST/STM32F4xx/Include -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f405rgtx.d ./Startup/startup_stm32f405rgtx.o

.PHONY: clean-Startup

