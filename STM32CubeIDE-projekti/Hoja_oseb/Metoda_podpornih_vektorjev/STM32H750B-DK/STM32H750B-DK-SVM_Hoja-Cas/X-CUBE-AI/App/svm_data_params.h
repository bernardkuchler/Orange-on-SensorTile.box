/**
  ******************************************************************************
  * @file    svm_data_params.h
  * @author  AST Embedded Analytics Research Platform
  * @date    Wed Jul 12 12:24:12 2023
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

#ifndef SVM_DATA_PARAMS_H
#define SVM_DATA_PARAMS_H
#pragma once

#include "ai_platform.h"

/*
#define AI_SVM_DATA_WEIGHTS_PARAMS \
  (AI_HANDLE_PTR(&ai_svm_data_weights_params[1]))
*/

#define AI_SVM_DATA_CONFIG               (NULL)


#define AI_SVM_DATA_ACTIVATIONS_SIZES \
  { 3004, }
#define AI_SVM_DATA_ACTIVATIONS_SIZE     (3004)
#define AI_SVM_DATA_ACTIVATIONS_COUNT    (1)
#define AI_SVM_DATA_ACTIVATION_1_SIZE    (3004)



#define AI_SVM_DATA_WEIGHTS_SIZES \
  { 52624, }
#define AI_SVM_DATA_WEIGHTS_SIZE         (52624)
#define AI_SVM_DATA_WEIGHTS_COUNT        (1)
#define AI_SVM_DATA_WEIGHT_1_SIZE        (52624)



#define AI_SVM_DATA_ACTIVATIONS_TABLE_GET() \
  (&g_svm_activations_table[1])

extern ai_handle g_svm_activations_table[1 + 2];



#define AI_SVM_DATA_WEIGHTS_TABLE_GET() \
  (&g_svm_weights_table[1])

extern ai_handle g_svm_weights_table[1 + 2];


#endif    /* SVM_DATA_PARAMS_H */
