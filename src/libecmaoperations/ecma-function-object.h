/* Copyright 2014 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ECMA_FUNCTION_OBJECT_H
#define ECMA_FUNCTION_OBJECT_H

#include "ecma-globals.h"
#include "interpreter.h"

/** \addtogroup ecma ---TODO---
 * @{
 * 
 * \addtogroup ecmafunctionobject ECMA Function object related routines
 * @{
 */

extern bool ecma_op_is_callable( ecma_value_t value);

extern ecma_object_t*
ecma_op_create_function_object( const ecma_char_t* formal_parameter_list_p[],
                                size_t formal_parameters_number,
                                ecma_object_t *scope_p,
                                bool is_strict,
                                interp_bytecode_idx first_opcode_idx);

extern ecma_object_t* ecma_op_get_throw_type_error( void);

extern ecma_completion_value_t ecma_op_function_call( ecma_object_t *func_obj_p,
                                                      ecma_value_t this_arg_value,
                                                      ecma_value_t* arguments_list_p,
                                                      size_t arguments_list_len);

/**
 * @}
 * @}
 */

#endif /* !ECMA_FUNCTION_OBJECT_H */
