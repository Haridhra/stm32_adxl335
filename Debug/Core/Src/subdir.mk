################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ADXL335.c \
../Core/Src/main.c \
../Core/Src/millis.c \
../Core/Src/stm32_uart_console.c \
../Core/Src/stm32l4_adc.c \
../Core/Src/stm32wlxx_hal_msp.c \
../Core/Src/stm32wlxx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32wlxx.c 

OBJS += \
./Core/Src/ADXL335.o \
./Core/Src/main.o \
./Core/Src/millis.o \
./Core/Src/stm32_uart_console.o \
./Core/Src/stm32l4_adc.o \
./Core/Src/stm32wlxx_hal_msp.o \
./Core/Src/stm32wlxx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32wlxx.o 

C_DEPS += \
./Core/Src/ADXL335.d \
./Core/Src/main.d \
./Core/Src/millis.d \
./Core/Src/stm32_uart_console.d \
./Core/Src/stm32l4_adc.d \
./Core/Src/stm32wlxx_hal_msp.d \
./Core/Src/stm32wlxx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32wlxx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32WL55xx -c -I../Core/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc -I../Drivers/STM32WLxx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ADXL335.d ./Core/Src/ADXL335.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/millis.d ./Core/Src/millis.o ./Core/Src/stm32_uart_console.d ./Core/Src/stm32_uart_console.o ./Core/Src/stm32l4_adc.d ./Core/Src/stm32l4_adc.o ./Core/Src/stm32wlxx_hal_msp.d ./Core/Src/stm32wlxx_hal_msp.o ./Core/Src/stm32wlxx_it.d ./Core/Src/stm32wlxx_it.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32wlxx.d ./Core/Src/system_stm32wlxx.o

.PHONY: clean-Core-2f-Src

