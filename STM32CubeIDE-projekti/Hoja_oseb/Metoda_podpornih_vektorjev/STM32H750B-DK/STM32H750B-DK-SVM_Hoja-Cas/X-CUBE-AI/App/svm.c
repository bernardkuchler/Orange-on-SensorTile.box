/**
  ******************************************************************************
  * @file    svm.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Wed Jul 12 12:24:12 2023
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


#include "svm.h"
#include "svm_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_svm
 
#undef AI_SVM_MODEL_SIGNATURE
#define AI_SVM_MODEL_SIGNATURE     "9f90a327dbae70ba81969339dfb28f75"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Wed Jul 12 12:24:12 2023"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_SVM_N_BATCHES
#define AI_SVM_N_BATCHES         (1)

static ai_ptr g_svm_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_svm_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  label_rho_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  label_scratch0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 729, AI_STATIC)
/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  label_classlabels_ints_array, AI_ARRAY_FORMAT_U8,
  NULL, NULL, 5, AI_STATIC)
/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  label_vectors_per_class_array, AI_ARRAY_FORMAT_U8,
  NULL, NULL, 5, AI_STATIC)
/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  label_prob_a_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  float_input_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 16, AI_STATIC)
/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  label_output0_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1, AI_STATIC)
/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  label_prob_b_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10, AI_STATIC)
/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  label_output1_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 5, AI_STATIC)
/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  output_probability_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 10, AI_STATIC)
/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  output_probability_classlabels_ints_array, AI_ARRAY_FORMAT_U8,
  NULL, NULL, 5, AI_STATIC)
/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  output_label_output_array, AI_ARRAY_FORMAT_S32|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 1, AI_STATIC)
/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  label_coefficients_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 2624, AI_STATIC)
/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  label_support_vectors_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10496, AI_STATIC)
/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  label_rho, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 10), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &label_rho_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  label_scratch0, AI_STATIC,
  1, 0x0,
  AI_SHAPE_INIT(4, 1, 729, 1, 1), AI_STRIDE_INIT(4, 4, 4, 2916, 2916),
  1, &label_scratch0_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  label_classlabels_ints, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 5), AI_STRIDE_INIT(4, 1, 1, 5, 5),
  1, &label_classlabels_ints_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  label_vectors_per_class, AI_STATIC,
  3, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 5), AI_STRIDE_INIT(4, 1, 1, 5, 5),
  1, &label_vectors_per_class_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  label_prob_a, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 10), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &label_prob_a_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  float_input_output, AI_STATIC,
  5, 0x0,
  AI_SHAPE_INIT(4, 1, 16, 1, 1), AI_STRIDE_INIT(4, 4, 4, 64, 64),
  1, &float_input_output_array, NULL)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  label_output0, AI_STATIC,
  6, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &label_output0_array, NULL)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  label_prob_b, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 10), AI_STRIDE_INIT(4, 4, 4, 40, 40),
  1, &label_prob_b_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  label_output1, AI_STATIC,
  8, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &label_output1_array, NULL)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  output_probability_output, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 5, 1), AI_STRIDE_INIT(4, 4, 4, 8, 40),
  1, &output_probability_output_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  output_probability_classlabels_ints, AI_STATIC,
  10, 0x0,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 1, 1, 5, 5),
  1, &output_probability_classlabels_ints_array, NULL)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  output_label_output, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 1), AI_STRIDE_INIT(4, 4, 4, 4, 4),
  1, &output_label_output_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  label_coefficients, AI_STATIC,
  12, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 2624), AI_STRIDE_INIT(4, 4, 4, 10496, 10496),
  1, &label_coefficients_array, NULL)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  label_support_vectors, AI_STATIC,
  13, 0x0,
  AI_SHAPE_INIT(4, 1, 1, 1, 10496), AI_STRIDE_INIT(4, 4, 4, 41984, 41984),
  1, &label_support_vectors_array, NULL)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  output_label_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &label_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_label_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  output_label_layer, 2,
  CAST_TYPE, 0x0, NULL,
  cast, forward_cast,
  &output_label_chain,
  NULL, &output_label_layer, AI_STATIC, 
  .to_format = AI_ARRAY_FORMAT_S32, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  output_probability_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &label_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_probability_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &output_probability_classlabels_ints),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  output_probability_layer, 4,
  ZIPMAP_TYPE, 0x0, NULL,
  zipmap, forward_zipmap,
  &output_probability_chain,
  NULL, &output_label_layer, AI_STATIC, 
  .has_classlabels_int = 1, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  label_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &float_input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &label_output0, &label_output1),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 7, &label_coefficients, &label_support_vectors, &label_rho, &label_classlabels_ints, &label_vectors_per_class, &label_prob_a, &label_prob_b),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &label_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  label_layer, 1,
  SVC_TYPE, 0x0, NULL,
  svc, forward_svc,
  &label_chain,
  NULL, &output_probability_layer, AI_STATIC, 
  .kernel_type = AI_SVC_KERNEL_POLYNOMIAL, 
  .gamma = 0.0625, 
  .coef0 = 1.0, 
  .degree = 3.0, 
  .proba_support = 1, 
  .has_classlabels_int = 1, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 52624, 1, 1),
    52624, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 3004, 1, 1),
    3004, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_SVM_IN_NUM, &float_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_SVM_OUT_NUM, &output_label_output, &output_probability_output),
  &label_layer, 0, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 52624, 1, 1),
      52624, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 3004, 1, 1),
      3004, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_SVM_IN_NUM, &float_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_SVM_OUT_NUM, &output_label_output, &output_probability_output),
  &label_layer, 0, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/


/******************************************************************************/
AI_DECLARE_STATIC
ai_bool svm_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_svm_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    float_input_output_array.data = AI_PTR(g_svm_activations_map[0] + 0);
    float_input_output_array.data_start = AI_PTR(g_svm_activations_map[0] + 0);
    
    label_scratch0_array.data = AI_PTR(g_svm_activations_map[0] + 64);
    label_scratch0_array.data_start = AI_PTR(g_svm_activations_map[0] + 64);
    
    label_output0_array.data = AI_PTR(g_svm_activations_map[0] + 2980);
    label_output0_array.data_start = AI_PTR(g_svm_activations_map[0] + 2980);
    
    label_output1_array.data = AI_PTR(g_svm_activations_map[0] + 2984);
    label_output1_array.data_start = AI_PTR(g_svm_activations_map[0] + 2984);
    
    output_probability_output_array.data = AI_PTR(g_svm_activations_map[0] + 0);
    output_probability_output_array.data_start = AI_PTR(g_svm_activations_map[0] + 0);
    
    output_label_output_array.data = AI_PTR(g_svm_activations_map[0] + 40);
    output_label_output_array.data_start = AI_PTR(g_svm_activations_map[0] + 40);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool svm_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_svm_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    label_rho_array.format |= AI_FMT_FLAG_CONST;
    label_rho_array.data = AI_PTR(g_svm_weights_map[0] + 0);
    label_rho_array.data_start = AI_PTR(g_svm_weights_map[0] + 0);
    
    label_classlabels_ints_array.format |= AI_FMT_FLAG_CONST;
    label_classlabels_ints_array.data = AI_PTR(g_svm_weights_map[0] + 40);
    label_classlabels_ints_array.data_start = AI_PTR(g_svm_weights_map[0] + 40);
    
    label_vectors_per_class_array.format |= AI_FMT_FLAG_CONST;
    label_vectors_per_class_array.data = AI_PTR(g_svm_weights_map[0] + 48);
    label_vectors_per_class_array.data_start = AI_PTR(g_svm_weights_map[0] + 48);
    
    label_prob_a_array.format |= AI_FMT_FLAG_CONST;
    label_prob_a_array.data = AI_PTR(g_svm_weights_map[0] + 56);
    label_prob_a_array.data_start = AI_PTR(g_svm_weights_map[0] + 56);
    
    label_prob_b_array.format |= AI_FMT_FLAG_CONST;
    label_prob_b_array.data = AI_PTR(g_svm_weights_map[0] + 96);
    label_prob_b_array.data_start = AI_PTR(g_svm_weights_map[0] + 96);
    
    output_probability_classlabels_ints_array.format |= AI_FMT_FLAG_CONST;
    output_probability_classlabels_ints_array.data = AI_PTR(g_svm_weights_map[0] + 136);
    output_probability_classlabels_ints_array.data_start = AI_PTR(g_svm_weights_map[0] + 136);
    
    label_coefficients_array.format |= AI_FMT_FLAG_CONST;
    label_coefficients_array.data = AI_PTR(g_svm_weights_map[0] + 144);
    label_coefficients_array.data_start = AI_PTR(g_svm_weights_map[0] + 144);
    
    label_support_vectors_array.format |= AI_FMT_FLAG_CONST;
    label_support_vectors_array.data = AI_PTR(g_svm_weights_map[0] + 10640);
    label_support_vectors_array.data_start = AI_PTR(g_svm_weights_map[0] + 10640);
    
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/


AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_svm_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_SVM_MODEL_NAME,
      .model_signature   = AI_SVM_MODEL_SIGNATURE,
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
      
      .n_macc            = 31490,
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
ai_bool ai_svm_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_SVM_MODEL_NAME,
      .model_signature   = AI_SVM_MODEL_SIGNATURE,
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
      
      .n_macc            = 31490,
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
ai_error ai_svm_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_svm_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_error ai_svm_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
    ai_error err;
    ai_network_params params;

    err = ai_svm_create(network, AI_SVM_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE)
        return err;
    if (ai_svm_data_params_get(&params) != true) {
        err = ai_svm_get_error(*network);
        return err;
    }
#if defined(AI_SVM_DATA_ACTIVATIONS_COUNT)
    if (activations) {
        /* set the addresses of the activations buffers */
        for (int idx=0;idx<params.map_activations.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
    }
#endif
#if defined(AI_SVM_DATA_WEIGHTS_COUNT)
    if (weights) {
        /* set the addresses of the weight buffers */
        for (int idx=0;idx<params.map_weights.size;idx++)
            AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
    }
#endif
    if (ai_svm_init(*network, &params) != true) {
        err = ai_svm_get_error(*network);
    }
    return err;
}

AI_API_ENTRY
ai_buffer* ai_svm_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_buffer* ai_svm_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    ((ai_network *)network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}

AI_API_ENTRY
ai_handle ai_svm_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_svm_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if (!net_ctx) return false;

  ai_bool ok = true;
  ok &= svm_configure_weights(net_ctx, params);
  ok &= svm_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_svm_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_svm_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_SVM_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

