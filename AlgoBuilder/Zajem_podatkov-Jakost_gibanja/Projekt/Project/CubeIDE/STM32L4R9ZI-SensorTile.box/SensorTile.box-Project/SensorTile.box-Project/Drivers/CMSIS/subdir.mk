################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Zajem_podatkov-Jakost_gibanja/Projekt/Project/Src/system_stm32l4xx.c 

OBJS += \
./Drivers/CMSIS/system_stm32l4xx.o 

C_DEPS += \
./Drivers/CMSIS/system_stm32l4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32l4xx.o: F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Zajem_podatkov-Jakost_gibanja/Projekt/Project/Src/system_stm32l4xx.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32L4R9xx -DUSE_HAL_DRIVER -DUSE_USB_FS -DUSE_SENSORTILEBOX -DARM_MATH_CM4 -c -I../../../../Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/DSP/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/SensorTile.box -I../../../../../Drivers/BSP/Components/Common -I../../../../../Drivers/BSP/Components/hts221 -I../../../../../Drivers/BSP/Components/lps22hh -I../../../../../Drivers/BSP/Components/lsm6dsox -I../../../../../Drivers/BSP/Components/lis2mdl -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC_MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../Middlewares/ST/STM32_MotionAC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionEC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionGC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionMC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionTL_Library/Inc -I../../../../../Middlewares/Third_Party/FatFs/src -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS

clean-Drivers-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/system_stm32l4xx.cyclo ./Drivers/CMSIS/system_stm32l4xx.d ./Drivers/CMSIS/system_stm32l4xx.o ./Drivers/CMSIS/system_stm32l4xx.su

.PHONY: clean-Drivers-2f-CMSIS

