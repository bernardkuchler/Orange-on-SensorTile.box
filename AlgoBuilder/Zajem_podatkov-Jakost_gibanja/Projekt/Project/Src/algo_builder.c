#include "algo_builder.h"

const char Identification_String[] = "ID_STRING:Design.xml,On-line";

float Acceleration_g_1_data[3];
void *Sensor_Hub_1_out;


sDISPLAY_INFO display_info_list[] = {
{INFO_TYPE_GRAPH,1,3,VAR_TYPE_FLOAT,0,"graph|Acceleration|g|1|19|accX|accY|accZ||||0",0},
{0,0,0,0,0,0,0}};


void AB_Init(void)
{
	Sensor_Hub_Init(1, 26, 1, 1);
	Accelero_Init();
	Message_Length = 12;
}

void AB_Handler(void)
{
	Sensor_Hub_Handler(&Sensor_Hub_1_out);
	Accelero_Sensor_GetData(Sensor_Hub_1_out, Acceleration_g_1_data);
	Display_Update(Acceleration_g_1_data, &display_info_list[0]);
}
