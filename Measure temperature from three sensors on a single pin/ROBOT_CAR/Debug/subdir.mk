################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../adc.c \
../dc_motor.c \
../lcd.c \
../lm35_sensor.c \
../main.c \
../twi.c \
../uart.c 

OBJS += \
./adc.o \
./dc_motor.o \
./lcd.o \
./lm35_sensor.o \
./main.o \
./twi.o \
./uart.o 

C_DEPS += \
./adc.d \
./dc_motor.d \
./lcd.d \
./lm35_sensor.d \
./main.d \
./twi.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


