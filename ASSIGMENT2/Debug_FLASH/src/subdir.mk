################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/UART_DRIVER.c \
../src/clock_and_modes.c \
../src/main.c 

OBJS += \
./src/UART_DRIVER.o \
./src/clock_and_modes.o \
./src/main.o 

C_DEPS += \
./src/UART_DRIVER.d \
./src/clock_and_modes.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/UART_DRIVER.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


