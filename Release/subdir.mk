################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FSM.c \
../GeneralFunc.c \
../MapMaze.c \
../MotorDriver.c \
../Obs.c \
../PinDefined.c \
../USART.c \
../main.c 

OBJS += \
./FSM.o \
./GeneralFunc.o \
./MapMaze.o \
./MotorDriver.o \
./Obs.o \
./PinDefined.o \
./USART.o \
./main.o 

C_DEPS += \
./FSM.d \
./GeneralFunc.d \
./MapMaze.d \
./MotorDriver.d \
./Obs.d \
./PinDefined.d \
./USART.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega2560 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


