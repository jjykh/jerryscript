#include <sys/timeb.h>
#include <windows.h>

#include "jerry-port.h"
#include "jerry-port-win32.h"


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
 * Provide log message to filestream implementation for the engine.
 */
int jerry_port_logmsg (FILE *stream, /**< stream pointer */
                       const char *format, /**< format string */
                       ...) /**< parameters */
{
  va_list args;
  int count;
  va_start (args, format);
  count = vfprintf (stream, format, args);
  va_end (args);
  return count;
} /* jerry_port_logmsg */

/**
 * Provide error message to console implementation for the engine.
 */
int jerry_port_errormsg (const char *format, /**< format string */
                         ...) /**< parameters */
{
  va_list args;
  int count;
  va_start (args, format);
  count = vfprintf (stderr, format, args);
  va_end (args);
  return count;
} /* jerry_port_errormsg */
