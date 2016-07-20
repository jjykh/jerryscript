/* Copyright 2014-2016 Samsung Electronics Co., Ltd.
 * Copyright 2016 University of Szeged.
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

/**
 * Implementation of exit with specified status code.
 */

#include "jrt.h"
#include "jrt-libc-includes.h"

#define JERRY_INTERNAL
#include "jerry-internal.h"

/*
 * Exit with specified status code.
 *
 * If !JERRY_NDEBUG and code != 0, print status code with description
 * and call assertion fail handler.
 */
void __noreturn
jerry_fatal (jerry_fatal_code_t code) /**< status code */
{
#ifndef JERRY_NDEBUG
  jerry_port_log (JERRY_LOG_LEVEL_ERROR, "Error: ");

  switch (code)
  {
    case ERR_OUT_OF_MEMORY:
    {
      jerry_port_log (JERRY_LOG_LEVEL_ERROR, "ERR_OUT_OF_MEMORY\n");
      break;
    }
    case ERR_SYSCALL:
    {
      /* print nothing as it may invoke syscall recursively */
      break;
    }
    case ERR_REF_COUNT_LIMIT:
    {
      jerry_port_log (JERRY_LOG_LEVEL_ERROR, "ERR_REF_COUNT_LIMIT\n");
      break;
    }
    case ERR_UNIMPLEMENTED_CASE:
    {
      jerry_port_log (JERRY_LOG_LEVEL_ERROR, "ERR_UNIMPLEMENTED_CASE\n");
      break;
    }
    case ERR_FAILED_INTERNAL_ASSERTION:
    {
      jerry_port_log (JERRY_LOG_LEVEL_ERROR, "ERR_FAILED_INTERNAL_ASSERTION\n");
      break;
    }
  }
#endif /* !JERRY_NDEBUG */

  jerry_port_fatal (code);

  /* to make compiler happy for some RTOS: 'control reaches end of non-void function' */
  while (true)
  {
  }
} /* jerry_fatal */

/**
 * Handle failed assertion
 */
void __noreturn
jerry_assert_fail (const char *assertion, /**< assertion condition string */
                   const char *file, /**< file name */
                   const char *function, /**< function name */
                   const uint32_t line) /**< line */
{
#ifndef JERRY_NDEBUG
  jerry_port_log (JERRY_LOG_LEVEL_ERROR,
                  "ICE: Assertion '%s' failed at %s(%s):%lu.\n",
                  assertion,
                  file,
                  function,
                  (unsigned long) line);
#else /* JERRY_NDEBUG */
  (void) assertion;
  (void) file;
  (void) function;
  (void) line;
#endif /* !JERRY_NDEBUG */

  jerry_fatal (ERR_FAILED_INTERNAL_ASSERTION);
} /* jerry_assert_fail */

/**
 * Handle execution of control path that should be unreachable
 */
void __noreturn
jerry_unreachable (const char *comment, /**< comment to unreachable mark if exists,
                                             NULL - otherwise */
                   const char *file, /**< file name */
                   const char *function, /**< function name */
                   const uint32_t line) /**< line */
{
#ifndef JERRY_NDEBUG
  jerry_port_log (JERRY_LOG_LEVEL_ERROR,
                  "ICE: Unreachable control path at %s(%s):%lu was executed",
                  file,
                  function,
                  (unsigned long) line);
#else /* JERRY_NDEBUG */
  (void) file;
  (void) function;
  (void) line;
#endif /* !JERRY_NDEBUG */

  if (comment != NULL)
  {
    jerry_port_log (JERRY_LOG_LEVEL_ERROR, "(%s)", comment);
  }

  jerry_port_log (JERRY_LOG_LEVEL_ERROR, ".\n");

  jerry_fatal (ERR_FAILED_INTERNAL_ASSERTION);
} /* jerry_unreachable */

/**
 * Handle unimplemented case execution
 */
void __noreturn
jerry_unimplemented (const char *comment, /**< comment to unimplemented mark if exists,
                                               NULL - otherwise */
                     const char *file, /**< file name */
                     const char *function, /**< function name */
                     const uint32_t line) /**< line */
{
#ifndef JERRY_NDEBUG
  jerry_port_log (JERRY_LOG_LEVEL_ERROR,
                  "SORRY: Unimplemented case at %s(%s):%lu was executed",
                  file,
                  function,
                  (unsigned long) line);
#else /* JERRY_NDEBUG */
  (void) file;
  (void) function;
  (void) line;
#endif /* !JERRY_NDEBUG */

  if (comment != NULL)
  {
    jerry_port_log (JERRY_LOG_LEVEL_ERROR, "(%s)", comment);
  }

  jerry_port_log (JERRY_LOG_LEVEL_ERROR, ".\n");

  jerry_fatal (ERR_UNIMPLEMENTED_CASE);
} /* jerry_unimplemented */
