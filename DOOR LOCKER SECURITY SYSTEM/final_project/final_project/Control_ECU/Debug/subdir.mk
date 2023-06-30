################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DC_MOTOR.c \
../GPIO.c \
../Timer.c \
../buzzer.c \
../external_eeprom.c \
../i2c.c \
../main.c \
../uart.c 

OBJS += \
./DC_MOTOR.o \
./GPIO.o \
./Timer.o \
./buzzer.o \
./external_eeprom.o \
./i2c.o \
./main.o \
./uart.o 

C_DEPS += \
./DC_MOTOR.d \
./GPIO.d \
./Timer.d \
./buzzer.d \
./external_eeprom.d \
./i2c.d \
./main.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


