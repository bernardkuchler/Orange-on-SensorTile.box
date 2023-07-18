#include "algo_builder.h"

int32_t DummyNodeInt[1];
const char Identification_String[] = "ID_STRING:Design.xml,On-line";

float Acceleration_g_1_data[3];
int32_t FSM_MLC_1_mlc_output[1];
void *Sensor_Hub_1_out;


sDISPLAY_INFO display_info_list[] = {
{INFO_TYPE_GRAPH,1,3,VAR_TYPE_FLOAT,0,"graph|Acceleration|g|4|19|accX|accY|accZ||||0",0},
{INFO_TYPE_INT32,2,1,VAR_TYPE_INT32,12,"int32|klasifikacijski razred|klasifikacijski razred|||||||||||||||",0},
{0,0,0,0,0,0,0}};


void AB_Init(void)
{
	Sensor_Hub_Init(0, 104, 1, 1);
	Accelero_Init();
	FSM_MLC_Init(0, 1);
	Message_Length = 16;
}

void AB_Handler(void)
{
	Sensor_Hub_Handler(&Sensor_Hub_1_out);
	Accelero_Sensor_GetData(Sensor_Hub_1_out, Acceleration_g_1_data);
	FSM_MLC_GetData(Sensor_Hub_1_out, DummyNodeInt, FSM_MLC_1_mlc_output, 0, 1);
	Display_Update(Acceleration_g_1_data, &display_info_list[0]);
	Display_Update(FSM_MLC_1_mlc_output, &display_info_list[1]);
}
