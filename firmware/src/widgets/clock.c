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
#include "timer.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif


WIDGET_STATE(0, 0, WIDGET_DISABLED);

extern struct mavlink_data mavdata;

static void draw(void)
{
  struct datetime *t = get_time();
  char buf[10];
  sprintf(buf, "%2d:%02d:%02d", t->h, t->m, t->s);
  max7456_putsxy(state.x, state.y, buf);
}

WIDGET_DECLARE(clock_widget, "Clock", CLOCK_WIDGET_ID, draw);

