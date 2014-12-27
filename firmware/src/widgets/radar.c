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

 Radar by Luis Alves
 Initial version shows home
 Todo: Add waypoints

*********************************************************************/

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "widgets.h"
#include "max7456.h"
#include "mavlink.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

WIDGET_STATE(0, 0, WIDGET_DISABLED);

extern struct mavlink_data mavdata;

#define SCALE1 200.0
#define SCALE2 500.0
#define SCALE3 1000.0

#define XSIZE 21
#define YSIZE 11
#define XCENTER 10
#define YCENTER 5

struct xy {
  unsigned char x, y;
};

static struct xy prev_home;

static void draw(void)
{
  float direction_rad, s;
  unsigned int scale, distance = mavdata.calcs.home_distance;
  char x, y, i;
  char buf[XSIZE];

  if (distance < SCALE1)
    scale = SCALE1;
  else if (distance < SCALE2)
    scale = SCALE2;
  else
    scale = SCALE3;
  
  if (distance > scale)
    distance = scale;

  direction_rad = ToRad(mavdata.calcs.home_direction);
  s = sin(direction_rad) * distance + scale;
  x = (char) ((int) (s * XSIZE)/(scale*2));

  s = cos(direction_rad) * distance + scale;
  y = YSIZE - 1 - ((int) (s * YSIZE)/(scale*2));

  max7456_putc(state.x + XCENTER, state.y + YCENTER, 0x2a);
  max7456_putc(state.x + prev_home.x, state.y + prev_home.y, ' ');
  max7456_putc(state.x + x, state.y + y, 0xb);

  sprintf(buf, "%4d%c", scale, 0xc);
  max7456_puts(state.x, state.y, buf);

  prev_home.x = x;
  prev_home.y = y;
}

WIDGET_DECLARE(radar_widget, RADAR_WIDGET_ID, draw);

