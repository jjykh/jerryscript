/* Copyright 2015-2016 Samsung Electronics Co., Ltd.
 * Copyright 2015-2016 University of Szeged.
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

#include "common.h"
#include "ecma-helpers.h"

/** \addtogroup parser Parser
 * @{
 *
 * \addtogroup jsparser JavaScript
 * @{
 *
 * \addtogroup jsparser_utils Utility
 * @{
 */

/**
 * Free literal.
 */
void
util_free_literal (lexer_literal_t *literal_p) /**< literal */
{
  if (literal_p->type == LEXER_IDENT_LITERAL
      || literal_p->type == LEXER_STRING_LITERAL)
  {
    if (!(literal_p->status_flags & LEXER_FLAG_SOURCE_PTR))
    {
      jmem_heap_free_block_size_stored ((void *) literal_p->u.char_p);
    }
  }
  else if ((literal_p->type == LEXER_FUNCTION_LITERAL)
           || (literal_p->type == LEXER_REGEXP_LITERAL))
  {
    ecma_bytecode_deref (literal_p->u.bytecode_p);
  }
} /* util_free_literal */

#ifdef PARSER_DUMP_BYTE_CODE

/**
 * Debug utility to print a character sequence.
 */
static void
util_print_chars (const uint8_t *char_p, /**< character pointer */
                  size_t size) /**< size */
{
  while (size > 0)
  {
    jerry_port_log (JERRY_LOG_LEVEL_DEBUG, "%c", *char_p++);
    size--;
  }
} /* util_print_chars */

/**
 * Debug utility to print a number.
 */
static void
util_print_number (ecma_number_t num_p) /**< number to print */
{
  lit_utf8_byte_t str_buf[ECMA_MAX_CHARS_IN_STRINGIFIED_NUMBER];
  lit_utf8_size_t str_size = ecma_number_to_utf8_string (num_p, str_buf, sizeof (str_buf));
  str_buf[str_size] = 0;
  jerry_port_log (JERRY_LOG_LEVEL_DEBUG, "%s", str_buf);
} /* util_print_number */

/**
 * Print literal.
 */
void
util_print_literal (lexer_literal_t *literal_p) /**< literal */
{
  if (literal_p->type == LEXER_IDENT_LITERAL)
  {
    if (literal_p->status_flags & LEXER_FLAG_VAR)
    {
      jerry_port_log (JERRY_LOG_LEVEL_DEBUG, "var_ident(");
    }
    else
    {
      jerry_port_log (JERRY_LOG_LEVEL_DEBUG, "ident(");
    }
    util_print_chars (literal_p->u.char_p, literal_p->prop.length);
  }
  else if (literal_p->type == LEXER_FUNCTION_LITERAL)
  {
    jerry_port_log (JERRY_LOG_LEVEL_DEBUG, "function");
    return;
  }
  else if (literal_p->type == LEXER_STRING_LITERAL)
  {
    jerry_port_log (JERRY_LOG_LEVEL_DEBUG, "string(");
    util_print_chars (literal_p->u.char_p, literal_p->prop.length);
  }
  else if (literal_p->type == LEXER_NUMBER_LITERAL)
  {
    ecma_string_t *value_p = JMEM_CP_GET_NON_NULL_POINTER (ecma_string_t, literal_p->u.value);

    JERRY_ASSERT (ECMA_STRING_GET_CONTAINER (value_p) == ECMA_STRING_LITERAL_NUMBER);

    jerry_port_log (JERRY_LOG_LEVEL_DEBUG, "number(");
    util_print_number (ecma_get_number_from_value (value_p->u.lit_number));
  }
  else if (literal_p->type == LEXER_REGEXP_LITERAL)
  {
    jerry_port_log (JERRY_LOG_LEVEL_DEBUG, "regexp");
    return;
  }
  else
  {
    jerry_port_log (JERRY_LOG_LEVEL_DEBUG, "unknown");
    return;
  }

  jerry_port_log (JERRY_LOG_LEVEL_DEBUG, ")");
} /* util_print_literal */

#endif /* PARSER_DUMP_BYTE_CODE */

/**
 * @}
 * @}
 * @}
 */
