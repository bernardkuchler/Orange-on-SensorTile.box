################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Zajem_podatkov-Jakost_gibanja/Projekt/Middlewares/ST/STM32_USB_Device_Library/Class/CDC_MSC/Src/usbd_cdc_msc.c 

OBJS += \
./Middlewares/STM32_USBD_Library/Class/CDC_MSC/usbd_cdc_msc.o 

C_DEPS += \
./Middlewares/STM32_USBD_Library/Class/CDC_MSC/usbd_cdc_msc.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/STM32_USBD_Library/Class/CDC_MSC/usbd_cdc_msc.o: F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Zajem_podatkov-Jakost_gibanja/Projekt/Middlewares/ST/STM32_USB_Device_Library/Class/CDC_MSC/Src/usbd_cdc_msc.c Middlewares/STM32_USBD_Library/Class/CDC_MSC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32L4R9xx -DUSE_HAL_DRIVER -DUSE_USB_FS -DUSE_SENSORTILEBOX -DARM_MATH_CM4 -c -I../../../../Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/DSP/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/SensorTile.box -I../../../../../Drivers/BSP/Components/Common -I../../../../../Drivers/BSP/Components/hts221 -I../../../../../Drivers/BSP/Components/lps22hh -I../../../../../Drivers/BSP/Components/lsm6dsox -I../../../../../Drivers/BSP/Components/lis2mdl -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC_MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../Middlewares/ST/STM32_MotionAC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionEC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionGC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionMC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionTL_Library/Inc -I../../../../../Middlewares/Third_Party/FatFs/src -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Middlewares-2f-STM32_USBD_Library-2f-Class-2f-CDC_MSC

clean-Middlewares-2f-STM32_USBD_Library-2f-Class-2f-CDC_MSC:
	-$(RM) ./Middlewares/STM32_USBD_Library/Class/CDC_MSC/usbd_cdc_msc.cyclo ./Middlewares/STM32_USBD_Library/Class/CDC_MSC/usbd_cdc_msc.d ./Middlewares/STM32_USBD_Library/Class/CDC_MSC/usbd_cdc_msc.o ./Middlewares/STM32_USBD_Library/Class/CDC_MSC/usbd_cdc_msc.su

.PHONY: clean-Middlewares-2f-STM32_USBD_Library-2f-Class-2f-CDC_MSC

