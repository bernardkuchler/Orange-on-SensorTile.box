################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c 

OBJS += \
./Middlewares/STM32_USBD_Library/Core/usbd_core.o \
./Middlewares/STM32_USBD_Library/Core/usbd_ctlreq.o \
./Middlewares/STM32_USBD_Library/Core/usbd_ioreq.o 

C_DEPS += \
./Middlewares/STM32_USBD_Library/Core/usbd_core.d \
./Middlewares/STM32_USBD_Library/Core/usbd_ctlreq.d \
./Middlewares/STM32_USBD_Library/Core/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/STM32_USBD_Library/Core/usbd_core.o: F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c Middlewares/STM32_USBD_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32L4R9xx -DUSE_HAL_DRIVER -DUSE_USB_FS -DUSE_SENSORTILEBOX -DARM_MATH_CM4 -c -I../../../../Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/DSP/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/SensorTile.box -I../../../../../Drivers/BSP/Components/Common -I../../../../../Drivers/BSP/Components/hts221 -I../../../../../Drivers/BSP/Components/lps22hh -I../../../../../Drivers/BSP/Components/lsm6dsox -I../../../../../Drivers/BSP/Components/lis2mdl -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC_MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../Middlewares/ST/STM32_MotionAC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionEC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionGC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionMC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionTL_Library/Inc -I../../../../../Middlewares/Third_Party/FatFs/src -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Middlewares/STM32_USBD_Library/Core/usbd_ctlreq.o: F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c Middlewares/STM32_USBD_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32L4R9xx -DUSE_HAL_DRIVER -DUSE_USB_FS -DUSE_SENSORTILEBOX -DARM_MATH_CM4 -c -I../../../../Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/DSP/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/SensorTile.box -I../../../../../Drivers/BSP/Components/Common -I../../../../../Drivers/BSP/Components/hts221 -I../../../../../Drivers/BSP/Components/lps22hh -I../../../../../Drivers/BSP/Components/lsm6dsox -I../../../../../Drivers/BSP/Components/lis2mdl -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC_MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../Middlewares/ST/STM32_MotionAC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionEC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionGC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionMC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionTL_Library/Inc -I../../../../../Middlewares/Third_Party/FatFs/src -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Middlewares/STM32_USBD_Library/Core/usbd_ioreq.o: F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c Middlewares/STM32_USBD_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32L4R9xx -DUSE_HAL_DRIVER -DUSE_USB_FS -DUSE_SENSORTILEBOX -DARM_MATH_CM4 -c -I../../../../Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/DSP/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/SensorTile.box -I../../../../../Drivers/BSP/Components/Common -I../../../../../Drivers/BSP/Components/hts221 -I../../../../../Drivers/BSP/Components/lps22hh -I../../../../../Drivers/BSP/Components/lsm6dsox -I../../../../../Drivers/BSP/Components/lis2mdl -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC_MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../Middlewares/ST/STM32_MotionAC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionEC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionGC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionMC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionTL_Library/Inc -I../../../../../Middlewares/Third_Party/FatFs/src -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Middlewares-2f-STM32_USBD_Library-2f-Core

clean-Middlewares-2f-STM32_USBD_Library-2f-Core:
	-$(RM) ./Middlewares/STM32_USBD_Library/Core/usbd_core.cyclo ./Middlewares/STM32_USBD_Library/Core/usbd_core.d ./Middlewares/STM32_USBD_Library/Core/usbd_core.o ./Middlewares/STM32_USBD_Library/Core/usbd_core.su ./Middlewares/STM32_USBD_Library/Core/usbd_ctlreq.cyclo ./Middlewares/STM32_USBD_Library/Core/usbd_ctlreq.d ./Middlewares/STM32_USBD_Library/Core/usbd_ctlreq.o ./Middlewares/STM32_USBD_Library/Core/usbd_ctlreq.su ./Middlewares/STM32_USBD_Library/Core/usbd_ioreq.cyclo ./Middlewares/STM32_USBD_Library/Core/usbd_ioreq.d ./Middlewares/STM32_USBD_Library/Core/usbd_ioreq.o ./Middlewares/STM32_USBD_Library/Core/usbd_ioreq.su

.PHONY: clean-Middlewares-2f-STM32_USBD_Library-2f-Core

