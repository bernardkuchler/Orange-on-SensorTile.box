/**
  ******************************************************************************
  * @file    randomforest_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Tue Jul 11 18:26:21 2023
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

#include "randomforest_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_randomforest_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_randomforest_weights_array_u64[159] = {
  0x4000100010001U, 0x5000500040004U, 0x7000700070005U, 0x1000800080008U,
  0x4000400010001U, 0x5000500050004U, 0x8000700070007U, 0x1000100080008U,
  0x4000400040001U, 0x7000500050005U, 0x8000800070007U, 0x1000100010008U,
  0x5000400040004U, 0x7000700050005U, 0x8000800080007U, 0x4000100010001U,
  0x5000500040004U, 0x7000700070005U, 0x1000800080008U, 0x4000400010001U,
  0x5000500050004U, 0x8000700070007U, 0x101010100080008U, 0xf000f00000101U,
  0xf000f000f000fU, 0x0U, 0x0U, 0x0U,
  0x0U, 0x0U, 0x0U, 0x0U,
  0x100000000U, 0x398c25c200000002U, 0x3dbb4ba000000000U, 0x3d3ab1d5U,
  0x3df3b4b300000000U, 0x0U, 0x389c2295U, 0x3d81aec43db99c71U,
  0x0U, 0x3e2ffeb1U, 0x389c229500000000U, 0x3e0081d900000000U,
  0x3d4409b9U, 0x3e2ffeb100000000U, 0x0U, 0x389be27aU,
  0x3d4409b93dbc0744U, 0x0U, 0x3ded55a9U, 0x398c25c200000000U,
  0x3dbb4ba000000000U, 0x3d4409b9U, 0x3e2d73b200000000U, 0x0U,
  0x392854c5U, 0x3d3ab1d53dbb4ba0U, 0x0U, 0x3e2d73b2U,
  0x0U, 0x0U, 0x4000300000001U, 0x700000000U,
  0x3000000010000U, 0x7000000000004U, 0x100000000U, 0x40003U,
  0x1000000000007U, 0x400030000U, 0x70000U, 0x4000300000001U,
  0x700000000U, 0x3000000010000U, 0x7000000000004U, 0x1000000000000U,
  0x2000100000002U, 0x200010000U, 0x1000000020001U, 0x2000100000002U,
  0x200010000U, 0x1000000020001U, 0x2000100000002U, 0x200010000U,
  0x1000000020001U, 0x2000100000002U, 0x200010000U, 0x1000000020001U,
  0x2000100000002U, 0x200010000U, 0x1000000020001U, 0x2000100000002U,
  0x200010000U, 0x1000000020001U, 0x2000100000002U, 0x200010000U,
  0x1000000020001U, 0x2000100000002U, 0x200020100U, 0x50006U,
  0x2000000000008U, 0x500060000U, 0x80000U, 0x5000600000002U,
  0x800000000U, 0x6000000020000U, 0x8000000000005U, 0x200000000U,
  0x50006U, 0x2000000000008U, 0x500060000U, 0x80000U,
  0x3e2aaaabU, 0x0U, 0x3e2aaaabU, 0x3e06186200000000U,
  0x3d124925U, 0x3de38e393d638e39U, 0x0U, 0x3e2aaaab3e2aaaabU,
  0x0U, 0x3e2aaaab00000000U, 0x0U, 0x3d0888893e088889U,
  0x3d430c3100000000U, 0x3df3cf3dU, 0x3e2aaaab00000000U, 0x3e2aaaabU,
  0x0U, 0x3e2aaaabU, 0x3e10690700000000U, 0x3cd20d21U,
  0x3e04bda13d17b426U, 0x0U, 0x3e2aaaab3e2aaaabU, 0x0U,
  0x3e2aaaab00000000U, 0x0U, 0x3d638e393de38e39U, 0x3d2aaaab00000000U,
  0x3e000000U, 0x3e2aaaab00000000U, 0x3e2aaaabU, 0x0U,
  0x3e2aaaabU, 0x3dc30c3100000000U, 0x3d924925U, 0x3e0000003d2aaaabU,
  0x0U, 0x3e2aaaab3e2aaaabU, 0x0U, 0x3e2aaaab00000000U,
  0x0U, 0x3d9b26ca3dba2e8cU, 0x3d430c3100000000U, 0x3df3cf3dU,
  0x3e2aaaab00000000U, 0x9000900090009U, 0x90009U,
};


ai_handle g_randomforest_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_randomforest_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

