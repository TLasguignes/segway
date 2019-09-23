################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Device/ST/STM32F30x/Source/Templates/system_stm32f30x.c 

OBJS += \
./Libraries/CMSIS/Device/ST/STM32F30x/Source/Templates/system_stm32f30x.o 

C_DEPS += \
./Libraries/CMSIS/Device/ST/STM32F30x/Source/Templates/system_stm32f30x.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/CMSIS/Device/ST/STM32F30x/Source/Templates/system_stm32f30x.o: /home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Device/ST/STM32F30x/Source/Templates/system_stm32f30x.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F30 -DUSE_STDPERIPH_DRIVER -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Device/ST/STM32F30x/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/STM32F30x_StdPeriph_Driver/inc" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Libraries/CMSIS/Device/ST/STM32F30x/Source/Templates/system_stm32f30x.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

