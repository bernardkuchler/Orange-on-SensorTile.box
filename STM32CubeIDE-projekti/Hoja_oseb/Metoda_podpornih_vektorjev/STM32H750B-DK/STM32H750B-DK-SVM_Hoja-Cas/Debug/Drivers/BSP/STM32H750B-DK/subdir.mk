################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32H750B-DK/stm32h750b_discovery_qspi.c 

OBJS += \
./Drivers/BSP/STM32H750B-DK/stm32h750b_discovery_qspi.o 

C_DEPS += \
./Drivers/BSP/STM32H750B-DK/stm32h750b_discovery_qspi.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32H750B-DK/%.o Drivers/BSP/STM32H750B-DK/%.su Drivers/BSP/STM32H750B-DK/%.cyclo: ../Drivers/BSP/STM32H750B-DK/%.c Drivers/BSP/STM32H750B-DK/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../X-CUBE-AI/App -I../X-CUBE-AI -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/AI/Inc -I../Drivers/BSP/Components/mt25tl01g -I../Drivers/BSP/STM32H750B-DK -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32H750B-2d-DK

clean-Drivers-2f-BSP-2f-STM32H750B-2d-DK:
	-$(RM) ./Drivers/BSP/STM32H750B-DK/stm32h750b_discovery_qspi.cyclo ./Drivers/BSP/STM32H750B-DK/stm32h750b_discovery_qspi.d ./Drivers/BSP/STM32H750B-DK/stm32h750b_discovery_qspi.o ./Drivers/BSP/STM32H750B-DK/stm32h750b_discovery_qspi.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32H750B-2d-DK

