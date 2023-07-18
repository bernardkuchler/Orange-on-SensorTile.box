################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FATFS/Target/bsp_driver_sdram.c \
../FATFS/Target/sdram_diskio.c 

OBJS += \
./FATFS/Target/bsp_driver_sdram.o \
./FATFS/Target/sdram_diskio.o 

C_DEPS += \
./FATFS/Target/bsp_driver_sdram.d \
./FATFS/Target/sdram_diskio.d 


# Each subdirectory must supply rules for building sources it contributes
FATFS/Target/%.o FATFS/Target/%.su FATFS/Target/%.cyclo: ../FATFS/Target/%.c FATFS/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../X-CUBE-AI/App -I../X-CUBE-AI -I../X-CUBE-AI/Target -I../Middlewares/ST/AI/Inc -I../Drivers/BSP/Components/mt25tl01g -I../Drivers/BSP/STM32H750B-DK -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FATFS-2f-Target

clean-FATFS-2f-Target:
	-$(RM) ./FATFS/Target/bsp_driver_sdram.cyclo ./FATFS/Target/bsp_driver_sdram.d ./FATFS/Target/bsp_driver_sdram.o ./FATFS/Target/bsp_driver_sdram.su ./FATFS/Target/sdram_diskio.cyclo ./FATFS/Target/sdram_diskio.d ./FATFS/Target/sdram_diskio.o ./FATFS/Target/sdram_diskio.su

.PHONY: clean-FATFS-2f-Target

