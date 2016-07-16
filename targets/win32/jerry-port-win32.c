#include <sys/timeb.h>
#include <windows.h>

#include "jerry-port.h"
#include "jerry-port-win32.h"

/**
 * Actual log level
 */
static jerry_log_level_t jerry_log_level = JERRY_LOG_LEVEL_ERROR;

static bool abort_on_fail = false;

/**
 * Sets whether 'abort' should be called instead of 'exit' upon exiting with
 * non-zero exit code in the default implementation of jerry_port_fatal.
 */
void jerry_port_default_set_abort_on_fail (bool flag) /**< new value of 'abort on fail' flag */
{
  abort_on_fail = flag;
} /* jerry_port_default_set_abort_on_fail */

/**
 * Check whether 'abort' should be called instead of 'exit' upon exiting with
 * non-zero exit code in the default implementation of jerry_port_fatal.
 *
 * @return true - if 'abort on fail' flag is set,
 *         false - otherwise.
 */
bool jerry_port_default_is_abort_on_fail ()
{
  return abort_on_fail;
} /* jerry_port_default_is_abort_on_fail */

/**
 * Default implementation of jerry_port_fatal.
 */
void jerry_port_fatal (jerry_fatal_code_t code)
{
  if (code != 0
      && code != ERR_OUT_OF_MEMORY
      && jerry_port_default_is_abort_on_fail ())
  {
    abort ();
  }
  else
  {
    exit (code);
  }
} /* jerry_port_fatal */

/**
 * Default implementation of jerry_port_get_time_zone.
 */
bool jerry_port_get_time_zone (jerry_time_zone_t *tz_p)
{
  struct _timeb tb;
  _ftime64_s(&tb);

  tz_p->offset = tb.timezone;
  tz_p->daylight_saving_time = tb.dstflag;

  return true;
} /* jerry_port_get_time_zone */

/**
 * Default implementation of jerry_port_get_current_time.
 */
double jerry_port_get_current_time ()
{
  struct _timeb tb;
  _ftime64_s(&tb);

  return ((double) tb.time) * 1000.0 + tb.millitm;
} /* jerry_port_get_current_time */




/**
 * Get the log level
 *
 * @return current log level
 */
jerry_log_level_t
jerry_port_default_get_log_level (void)
{
  return jerry_log_level;
} /* jerry_port_default_get_log_level */

/**
 * Set the log level
 */
void
jerry_port_default_set_log_level (jerry_log_level_t level) /**< log level */
{
  jerry_log_level = level;
} /* jerry_port_default_set_log_level */

/**
 * Provide console message implementation for the engine.
 */
void
jerry_port_console (const char *format, /**< format string */
                    ...) /**< parameters */
{
  va_list args;
  va_start (args, format);
  vfprintf (stdout, format, args);
  va_end (args);
} /* jerry_port_console */

/**
 * Provide log message implementation for the engine.
 */
void
jerry_port_log (jerry_log_level_t level, /**< log level */
                const char *format, /**< format string */
                ...)  /**< parameters */
{
  if (level <= jerry_log_level)
  {
    va_list args;
    va_start (args, format);
    vfprintf (stderr, format, args);
    va_end (args);
  }
} /* jerry_port_log */
