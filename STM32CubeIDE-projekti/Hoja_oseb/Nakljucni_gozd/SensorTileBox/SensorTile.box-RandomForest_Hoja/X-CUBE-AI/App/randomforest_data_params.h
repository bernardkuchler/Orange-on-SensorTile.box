/**
  ******************************************************************************
  * @file    randomforest_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue Jul 11 20:11:36 2023
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

#ifndef RANDOMFOREST_DATA_PARAMS_H
#define RANDOMFOREST_DATA_PARAMS_H
#pragma once

#include "ai_platform.h"

/*
#define AI_RANDOMFOREST_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_randomforest_data_weights_params[1]))
*/

#define AI_RANDOMFOREST_DATA_CONFIG               (NULL)


#define AI_RANDOMFOREST_DATA_ACTIVATIONS_SIZES \
  { 88, }
#define AI_RANDOMFOREST_DATA_ACTIVATIONS_SIZE     (88)
#define AI_RANDOMFOREST_DATA_ACTIVATIONS_COUNT    (1)
#define AI_RANDOMFOREST_DATA_ACTIVATION_1_SIZE    (88)



#define AI_RANDOMFOREST_DATA_WEIGHTS_SIZES \
  { 80496, }
#define AI_RANDOMFOREST_DATA_WEIGHTS_SIZE         (80496)
#define AI_RANDOMFOREST_DATA_WEIGHTS_COUNT        (1)
#define AI_RANDOMFOREST_DATA_WEIGHT_1_SIZE        (80496)



#define AI_RANDOMFOREST_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_randomforest_activations_table[1])

extern ai_handle g_randomforest_activations_table[1 + 2];



#define AI_RANDOMFOREST_DATA_WEIGHTS_TABLE_GET() \
  (&g_randomforest_weights_table[1])

extern ai_handle g_randomforest_weights_table[1 + 2];


#endif    /* RANDOMFOREST_DATA_PARAMS_H */
