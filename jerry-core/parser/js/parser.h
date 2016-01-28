/* Copyright 2014-2016 Samsung Electronics Co., Ltd.
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

#ifndef PARSER_H
#define PARSER_H

#include "jerry-api.h"
#include "byte-code.h"

/** \addtogroup parser Parser
 * @{
 *
 * \addtogroup jsparser ECMAScript
 * @{
 *
 * \addtogroup jsparser_parser Parser
 * @{
 */

/**
 * Parser completion status
 */
typedef enum
{
  JSP_STATUS_OK,             /**< parse finished successfully, no early errors occured */
  JSP_STATUS_SYNTAX_ERROR,   /**< SyntaxError early error occured */
  JSP_STATUS_REFERENCE_ERROR /**< ReferenceError early error occured */
} jsp_status_t;

extern void parser_set_show_instrs (int);

extern jsp_status_t parser_parse_script (const jerry_api_char_t *, size_t,
                                         ecma_compiled_code_t **);
extern jsp_status_t parser_parse_eval (const jerry_api_char_t *, size_t, bool,
                                       ecma_compiled_code_t **);

/**
 * @}
 * @}
 * @}
 */

#endif /* !PARSER_H */
