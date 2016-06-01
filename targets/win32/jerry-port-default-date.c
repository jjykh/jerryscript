/* Copyright 2016 Samsung Electronics Co., Ltd.
 * Copyright 2016 University of Szeged
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

#include <sys/timeb.h>
#include <windows.h>

#include "jerry-port.h"
#include "jerry-port-default.h"

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
