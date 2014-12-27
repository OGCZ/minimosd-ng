/*******************************************************************

MinimOSD-ng
Copyright (C) 2014  Luis Alves

This file is part of MinimOSD-ng.

MinimOSD-ng is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

MinimOSD-ng is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MinimOSD-ng.  If not, see <http://www.gnu.org/licenses/>.

*********************************************************************/

#include "config.h"
#include <stdio.h>
#include <string.h>
#include "widgets.h"
#include "max7456.h"
#include "mavlink.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

static struct widget_state state;

extern struct mavlink_data mavdata;
extern struct minimosd_ng_config config;

static char draw(void)
{
  unsigned int distance = mavdata.calcs.home_distance;
  char u = 'm';

  if (config.units & LENGTH_UNITS_IMPERIAL) {
    distance = (unsigned int) ((float) distance * M2FEET);
    if (distance > 20000) {
      distance /= MILE2FEET;
      u = MAX7456_FONT_MILES;
    } else {
      u = 'f';
    }
  } else {
    if (distance > 10000) {
      distance /= 1000;
      u = MAX7456_FONT_KM;
    }
  }
  max7456_printf(state.x, state.y, "%c%4d%c",
    MAX7456_FONT_HOME, distance, u);
  return 1;
}

WIDGET_DECLARE(homedistance_widget, HOMEDISTANCE_WIDGET_ID, draw);

