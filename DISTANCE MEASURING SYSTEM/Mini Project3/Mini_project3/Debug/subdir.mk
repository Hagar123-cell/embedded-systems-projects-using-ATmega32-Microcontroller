################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../AUTO_SPEED_CONTROLLER.c \
../DC_MOTOR.c \
../GPIO.c \
../LCD.c \
../PWM.c \
../TEMP_SENSOR.c 

OBJS += \
./ADC.o \
./AUTO_SPEED_CONTROLLER.o \
./DC_MOTOR.o \
./GPIO.o \
./LCD.o \
./PWM.o \
./TEMP_SENSOR.o 

C_DEPS += \
./ADC.d \
./AUTO_SPEED_CONTROLLER.d \
./DC_MOTOR.d \
./GPIO.d \
./LCD.d \
./PWM.d \
./TEMP_SENSOR.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


