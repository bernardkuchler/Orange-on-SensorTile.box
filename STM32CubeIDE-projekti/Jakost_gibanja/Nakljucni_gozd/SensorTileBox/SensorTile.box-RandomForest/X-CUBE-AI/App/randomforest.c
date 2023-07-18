/**
  ******************************************************************************
  * @file    randomforest.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue Jul 11 18:26:21 2023
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "randomforest.h"
#include "randomforest_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_randomforest
 
#undef AI_RANDOMFOREST_MODEL_SIGNATURE
#define AI_RANDOMFOREST_MODEL_SIGNATURE     "f92f7cbd75ca2c0823ec460dfea94401"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Tue Jul 11 18:26:21 2023"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_RANDOMFOREST_N_BATCHES
#define AI_RANDOMFOREST_N_BATCHES         (1)

static ai_ptr g_randomforest_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_randomforest_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  label_output0_array, AI_ARRAY_FORMAT_S32|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 1, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  label_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  label_class_nodeids_array, AI_ARRAY_FORMAT_U16,
  NULL, NULL, 90, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  output_probability_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 6, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  label_branch_mode_array, AI_ARRAY_FORMAT_U8,
  NULL, NULL, 6, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  label_nb_class_by_estimator_array, AI_ARRAY_FORMAT_U16,
  NULL, NULL, 6, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  label_nodes_featureids_array, AI_ARRAY_FORMAT_U8,
  NULL, NULL, 54, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  label_classlabels_int64s_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 3, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  label_nodes_values_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 54, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  label_base_values_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 3, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  label_nodes_truenodeids_array, AI_ARRAY_FORMAT_U16,
  NULL, NULL, 54, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  label_class_ids_array, AI_ARRAY_FORMAT_U16,
  NULL, NULL, 90, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  output_probability_classlabels_ints_array, AI_ARRAY_FORMAT_U8,
  NULL, NULL, 3, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  label_nodes_falsenodeids_array, AI_ARRAY_FORMAT_U16,
  NULL, NULL, 54, AI_STATIC)
/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  label_class_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 90, AI_STATIC)
/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  float_input_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 1, AI_STATIC)
/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  label_nb_node_by_estimator_array, AI_ARRAY_FORMAT_U16,
  NULL, NULL, 6, AI_STATIC)
/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  label_output0, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &label_output0_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  label_output1, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &label_output1_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  label_class_nodeids, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 90, 1, 1), AI_STRIDE_INIT(4, 2, 2, 180, 180),
  1, &label_class_nodeids_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  output_probability_output, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 3, 1), AI_STRIDE_INIT(4, 4, 4, 8, 24),
  1, &output_probability_output_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  label_branch_mode, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 6, 1, 1), AI_STRIDE_INIT(4, 1, 1, 6, 6),
  1, &label_branch_mode_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  label_nb_class_by_estimator, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 6, 1, 1), AI_STRIDE_INIT(4, 2, 2, 12, 12),
  1, &label_nb_class_by_estimator_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  label_nodes_featureids, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 54, 1, 1), AI_STRIDE_INIT(4, 1, 1, 54, 54),
  1, &label_nodes_featureids_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  label_classlabels_int64s, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &label_classlabels_int64s_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  label_nodes_values, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 54, 1, 1), AI_STRIDE_INIT(4, 4, 4, 216, 216),
  1, &label_nodes_values_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  label_base_values, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &label_base_values_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  label_nodes_truenodeids, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 54, 1, 1), AI_STRIDE_INIT(4, 2, 2, 108, 108),
  1, &label_nodes_truenodeids_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  label_class_ids, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 90, 1, 1), AI_STRIDE_INIT(4, 2, 2, 180, 180),
  1, &label_class_ids_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  output_probability_classlabels_ints, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 1, 1, 3, 3),
  1, &output_probability_classlabels_ints_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  label_nodes_falsenodeids, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 54, 1, 1), AI_STRIDE_INIT(4, 2, 2, 108, 108),
  1, &label_nodes_falsenodeids_array, NULL)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  label_class_weights, AI_STATIC,
  14, 0x0,
  AI_SHAPE_INIT(4, 1, 90, 1, 1), AI_STRIDE_INIT(4, 4, 4, 360, 360),
  1, &label_class_weights_array, NULL)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  float_input_output, AI_STATIC,
  15, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &float_input_output_array, NULL)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  label_nb_node_by_estimator, AI_STATIC,
  16, 0x0,
  AI_SHAPE_INIT(4, 1, 6, 1, 1), AI_STRIDE_INIT(4, 2, 2, 12, 12),
  1, &label_nb_node_by_estimator_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  output_probability_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &label_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_probability_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_probability_classlabels_ints),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  output_probability_layer, 3,
  ZIPMAP_TYPE, 0x0, NULL,
  zipmap, forward_zipmap,
  &output_probability_chain,
  NULL, &output_probability_layer, AI_STATIC, 
  .has_classlabels_int = 1, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  label_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &float_input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &label_output0, &label_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 12, &label_branch_mode, &label_nodes_featureids, &label_nodes_values, &label_nodes_truenodeids, &label_nodes_falsenodeids, &label_class_weights, &label_nb_node_by_estimator, &label_class_nodeids, &label_nb_class_by_estimator, &label_classlabels_int64s, &label_base_values, &label_class_ids),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  label_layer, 1,
  TREE_ENSEMBLE_CLASSIFIER_TYPE, 0x0, NULL,
  tree_ensemble_classifier, forward_tree_ensemble_classifier,
  &label_chain,
  NULL, &output_probability_layer, AI_STATIC, 
  .nl_func = NULL, 
  .all_weights_are_positive = 1, 
  .nodes_values_scale = 1.0, 
  .nodes_values_offset = 0, 
  .class_weights_scale = 1.0, 
  .class_weights_offset = 0, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1268, 1, 1),
    1268, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 40, 1, 1),
    40, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_RANDOMFOREST_IN_NUM, &float_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_RANDOMFOREST_OUT_NUM, &label_output0, &output_probability_output),
  &label_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1268, 1, 1),
      1268, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 40, 1, 1),
      40, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_RANDOMFOREST_IN_NUM, &float_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_RANDOMFOREST_OUT_NUM, &label_output0, &output_probability_output),
  &label_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool randomforest_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_randomforest_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    float_input_output_array.data = AI_PTR(g_randomforest_activations_map[0] + 20);
    float_input_output_array.data_start = AI_PTR(g_randomforest_activations_map[0] + 20);
    
    label_output0_array.data = AI_PTR(g_randomforest_activations_map[0] + 24);
    label_output0_array.data_start = AI_PTR(g_randomforest_activations_map[0] + 24);
    
    label_output1_array.data = AI_PTR(g_randomforest_activations_map[0] + 28);
    label_output1_array.data_start = AI_PTR(g_randomforest_activations_map[0] + 28);
    
    output_probability_output_array.data = AI_PTR(g_randomforest_activations_map[0] + 0);
    output_probability_output_array.data_start = AI_PTR(g_randomforest_activations_map[0] + 0);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool randomforest_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_randomforest_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    label_class_nodeids_array.format |= AI_FMT_FLAG_CONST;
    label_class_nodeids_array.data = AI_PTR(g_randomforest_weights_map[0] + 0);
    label_class_nodeids_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 0);
    
    label_branch_mode_array.format |= AI_FMT_FLAG_CONST;
    label_branch_mode_array.data = AI_PTR(g_randomforest_weights_map[0] + 180);
    label_branch_mode_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 180);
    
    label_nb_class_by_estimator_array.format |= AI_FMT_FLAG_CONST;
    label_nb_class_by_estimator_array.data = AI_PTR(g_randomforest_weights_map[0] + 188);
    label_nb_class_by_estimator_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 188);
    
    label_nodes_featureids_array.format |= AI_FMT_FLAG_CONST;
    label_nodes_featureids_array.data = AI_PTR(g_randomforest_weights_map[0] + 200);
    label_nodes_featureids_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 200);
    
    label_classlabels_int64s_array.format |= AI_FMT_FLAG_CONST;
    label_classlabels_int64s_array.data = AI_PTR(g_randomforest_weights_map[0] + 256);
    label_classlabels_int64s_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 256);
    
    label_nodes_values_array.format |= AI_FMT_FLAG_CONST;
    label_nodes_values_array.data = AI_PTR(g_randomforest_weights_map[0] + 268);
    label_nodes_values_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 268);
    
    label_base_values_array.format |= AI_FMT_FLAG_CONST;
    label_base_values_array.data = AI_PTR(g_randomforest_weights_map[0] + 484);
    label_base_values_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 484);
    
    label_nodes_truenodeids_array.format |= AI_FMT_FLAG_CONST;
    label_nodes_truenodeids_array.data = AI_PTR(g_randomforest_weights_map[0] + 496);
    label_nodes_truenodeids_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 496);
    
    label_class_ids_array.format |= AI_FMT_FLAG_CONST;
    label_class_ids_array.data = AI_PTR(g_randomforest_weights_map[0] + 604);
    label_class_ids_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 604);
    
    output_probability_classlabels_ints_array.format |= AI_FMT_FLAG_CONST;
    output_probability_classlabels_ints_array.data = AI_PTR(g_randomforest_weights_map[0] + 784);
    output_probability_classlabels_ints_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 784);
    
    label_nodes_falsenodeids_array.format |= AI_FMT_FLAG_CONST;
    label_nodes_falsenodeids_array.data = AI_PTR(g_randomforest_weights_map[0] + 788);
    label_nodes_falsenodeids_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 788);
    
    label_class_weights_array.format |= AI_FMT_FLAG_CONST;
    label_class_weights_array.data = AI_PTR(g_randomforest_weights_map[0] + 896);
    label_class_weights_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 896);
    
    label_nb_node_by_estimator_array.format |= AI_FMT_FLAG_CONST;
    label_nb_node_by_estimator_array.data = AI_PTR(g_randomforest_weights_map[0] + 1256);
    label_nb_node_by_estimator_array.data_start = AI_PTR(g_randomforest_weights_map[0] + 1256);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_randomforest_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_RANDOMFOREST_MODEL_NAME,
      .model_signature   = AI_RANDOMFOREST_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 48,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_bool ai_randomforest_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_RANDOMFOREST_MODEL_NAME,
      .model_signature   = AI_RANDOMFOREST_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 48,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}

AI_API_ENTRY
ai_error ai_randomforest_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_randomforest_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_randomforest_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_randomforest_create(network, AI_RANDOMFOREST_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_randomforest_data_params_get(&params) != true) {
        err = ai_randomforest_get_error(*network);
        return err;
    }
#if defined(AI_RANDOMFOREST_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_RANDOMFOREST_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_randomforest_init(*network, &params) != true) {
        err = ai_randomforest_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_randomforest_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_randomforest_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_randomforest_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_randomforest_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= randomforest_configure_weights(net_ctx, params);
  ok &= randomforest_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_randomforest_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_randomforest_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_RANDOMFOREST_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

