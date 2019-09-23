################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery.c \
/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_l3gd20.c \
/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_lsm303dlhc.c 

OBJS += \
./Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery.o \
./Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_l3gd20.o \
./Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_lsm303dlhc.o 

C_DEPS += \
./Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery.d \
./Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_l3gd20.d \
./Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_lsm303dlhc.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery.o: /home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F30 -DUSE_STDPERIPH_DRIVER -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Device/ST/STM32F30x/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/STM32F30x_StdPeriph_Driver/inc" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_l3gd20.o: /home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_l3gd20.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F30 -DUSE_STDPERIPH_DRIVER -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Device/ST/STM32F30x/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/STM32F30x_StdPeriph_Driver/inc" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_l3gd20.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_lsm303dlhc.o: /home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_lsm303dlhc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F30 -DUSE_STDPERIPH_DRIVER -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Device/ST/STM32F30x/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/STM32F30x_StdPeriph_Driver/inc" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/Utilities/STM32F3_Discovery/stm32f3_discovery_lsm303dlhc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

