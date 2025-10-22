################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PARSE/source/Parse_address.c 

OBJS += \
./src/PARSE/source/Parse_address.o 

C_DEPS += \
./src/PARSE/source/Parse_address.d 


# Each subdirectory must supply rules for building sources it contributes
src/PARSE/source/%.o: ../src/PARSE/source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/PARSE/source/Parse_address.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


