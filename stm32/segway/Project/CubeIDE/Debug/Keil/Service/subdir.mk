################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service/Accelerometre.c \
/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service/Fonctions.c \
/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service/Gyroscope.c \
/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service/Init.c 

OBJS += \
./Keil/Service/Accelerometre.o \
./Keil/Service/Fonctions.o \
./Keil/Service/Gyroscope.o \
./Keil/Service/Init.o 

C_DEPS += \
./Keil/Service/Accelerometre.d \
./Keil/Service/Fonctions.d \
./Keil/Service/Gyroscope.d \
./Keil/Service/Init.d 


# Each subdirectory must supply rules for building sources it contributes
Keil/Service/Accelerometre.o: /home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service/Accelerometre.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F30 -DUSE_STDPERIPH_DRIVER -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Device/ST/STM32F30x/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/STM32F30x_StdPeriph_Driver/inc" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Keil/Service/Accelerometre.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Keil/Service/Fonctions.o: /home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service/Fonctions.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F30 -DUSE_STDPERIPH_DRIVER -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Device/ST/STM32F30x/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/STM32F30x_StdPeriph_Driver/inc" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Keil/Service/Fonctions.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Keil/Service/Gyroscope.o: /home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service/Gyroscope.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F30 -DUSE_STDPERIPH_DRIVER -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Device/ST/STM32F30x/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/STM32F30x_StdPeriph_Driver/inc" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Keil/Service/Gyroscope.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Keil/Service/Init.o: /home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service/Init.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32F30 -DUSE_STDPERIPH_DRIVER -DSTM32F303VCTx -DSTM32 -DSTM32F3 -DSTM32F3DISCOVERY -DDEBUG -c -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/CMSIS/Device/ST/STM32F30x/Include" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/STM32F30x_StdPeriph_Driver/inc" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Libraries/Utilities/STM32F3_Discovery" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil" -I"/home/dimercur/Documents/Travail/git/segway/stm32/segway/Project/Keil/Service" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Keil/Service/Init.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

