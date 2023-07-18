################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/Third_Party/FatFs/src/diskio.c \
F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/Third_Party/FatFs/src/ff.c \
F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c 

OBJS += \
./Middlewares/FatFs/Core/diskio.o \
./Middlewares/FatFs/Core/ff.o \
./Middlewares/FatFs/Core/ff_gen_drv.o 

C_DEPS += \
./Middlewares/FatFs/Core/diskio.d \
./Middlewares/FatFs/Core/ff.d \
./Middlewares/FatFs/Core/ff_gen_drv.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/Core/diskio.o: F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/Third_Party/FatFs/src/diskio.c Middlewares/FatFs/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32L4R9xx -DUSE_HAL_DRIVER -DUSE_USB_FS -DUSE_SENSORTILEBOX -DARM_MATH_CM4 -c -I../../../../Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/DSP/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/SensorTile.box -I../../../../../Drivers/BSP/Components/Common -I../../../../../Drivers/BSP/Components/hts221 -I../../../../../Drivers/BSP/Components/lps22hh -I../../../../../Drivers/BSP/Components/lsm6dsox -I../../../../../Drivers/BSP/Components/lis2mdl -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC_MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../Middlewares/ST/STM32_MotionAC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionEC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionGC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionMC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionTL_Library/Inc -I../../../../../Middlewares/Third_Party/FatFs/src -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Middlewares/FatFs/Core/ff.o: F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/Third_Party/FatFs/src/ff.c Middlewares/FatFs/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32L4R9xx -DUSE_HAL_DRIVER -DUSE_USB_FS -DUSE_SENSORTILEBOX -DARM_MATH_CM4 -c -I../../../../Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/DSP/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/SensorTile.box -I../../../../../Drivers/BSP/Components/Common -I../../../../../Drivers/BSP/Components/hts221 -I../../../../../Drivers/BSP/Components/lps22hh -I../../../../../Drivers/BSP/Components/lsm6dsox -I../../../../../Drivers/BSP/Components/lis2mdl -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC_MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../Middlewares/ST/STM32_MotionAC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionEC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionGC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionMC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionTL_Library/Inc -I../../../../../Middlewares/Third_Party/FatFs/src -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
Middlewares/FatFs/Core/ff_gen_drv.o: F:/FRI_novSSD/Diploma/Diploma-GitHub/AlgoBuilder/Klasifikacijsko_drevo-Jakost_gibanja/projekt/Middlewares/Third_Party/FatFs/src/ff_gen_drv.c Middlewares/FatFs/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DSTM32L4R9xx -DUSE_HAL_DRIVER -DUSE_USB_FS -DUSE_SENSORTILEBOX -DARM_MATH_CM4 -c -I../../../../Inc -I../../../../../Drivers/CMSIS/Include -I../../../../../Drivers/CMSIS/DSP/Include -I../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../Drivers/BSP/SensorTile.box -I../../../../../Drivers/BSP/Components/Common -I../../../../../Drivers/BSP/Components/hts221 -I../../../../../Drivers/BSP/Components/lps22hh -I../../../../../Drivers/BSP/Components/lsm6dsox -I../../../../../Drivers/BSP/Components/lis2mdl -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC_MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Class/MSC/Inc -I../../../../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../../../../Middlewares/ST/STM32_MotionAC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionAW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionEC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionFX_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionGC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionID_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionMC_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPM_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionPW_Library/Inc -I../../../../../Middlewares/ST/STM32_MotionTL_Library/Inc -I../../../../../Middlewares/Third_Party/FatFs/src -O3 -ffunction-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Middlewares-2f-FatFs-2f-Core

clean-Middlewares-2f-FatFs-2f-Core:
	-$(RM) ./Middlewares/FatFs/Core/diskio.cyclo ./Middlewares/FatFs/Core/diskio.d ./Middlewares/FatFs/Core/diskio.o ./Middlewares/FatFs/Core/diskio.su ./Middlewares/FatFs/Core/ff.cyclo ./Middlewares/FatFs/Core/ff.d ./Middlewares/FatFs/Core/ff.o ./Middlewares/FatFs/Core/ff.su ./Middlewares/FatFs/Core/ff_gen_drv.cyclo ./Middlewares/FatFs/Core/ff_gen_drv.d ./Middlewares/FatFs/Core/ff_gen_drv.o ./Middlewares/FatFs/Core/ff_gen_drv.su

.PHONY: clean-Middlewares-2f-FatFs-2f-Core

