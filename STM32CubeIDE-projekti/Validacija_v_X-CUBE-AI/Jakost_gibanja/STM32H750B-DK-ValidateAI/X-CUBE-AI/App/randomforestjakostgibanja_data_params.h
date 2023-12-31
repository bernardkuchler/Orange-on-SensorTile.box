/**
  ******************************************************************************
  * @file    randomforestjakostgibanja_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    Thu Jun  1 14:09:10 2023
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#ifndef RANDOMFORESTJAKOSTGIBANJA_DATA_PARAMS_H
#define RANDOMFORESTJAKOSTGIBANJA_DATA_PARAMS_H
#pragma once

#include "ai_platform.h"

/*
#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_randomforestjakostgibanja_data_weights_params[1]))
*/

#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_CONFIG               (NULL)


#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_ACTIVATIONS_SIZES \
  { 40, }
#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_ACTIVATIONS_SIZE     (40)
#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_ACTIVATIONS_COUNT    (1)
#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_ACTIVATION_1_SIZE    (40)



#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_WEIGHTS_SIZES \
  { 5284, }
#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_WEIGHTS_SIZE         (5284)
#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_WEIGHTS_COUNT        (1)
#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_WEIGHT_1_SIZE        (5284)



#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_randomforestjakostgibanja_activations_table[1])

extern ai_handle g_randomforestjakostgibanja_activations_table[1 + 2];



#define AI_RANDOMFORESTJAKOSTGIBANJA_DATA_WEIGHTS_TABLE_GET() \
  (&g_randomforestjakostgibanja_weights_table[1])

extern ai_handle g_randomforestjakostgibanja_weights_table[1 + 2];


#endif    /* RANDOMFORESTJAKOSTGIBANJA_DATA_PARAMS_H */
