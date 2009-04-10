/**
 * swampex, a map processing library
 *
 * Authors: 
 *
 * Daniil Smelov <dn.smelov@gmail.com>
 *
 * Copyright (C) 2006-2009 Daniil Smelov, Slava Baryshnikov
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#ifndef __IMG_DECODER_INCLUDED
#define __IMG_DECODER_INCLUDED

/*--------------------------------------------------------------------------*/
#ifndef UNDER_CE
#include <sys/types.h>
#endif
#include <stdio.h>
#include "map_types.h"
#include <SDL.h>


/*--------------------------------------------------------------------------*/
typedef struct 
{
	SDL_Surface*		image;
} img_stream;

/*--------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

map_stream*	img_open(char* path);
void		img_get_tile(map_stream* s, int scale, int x, int y, unsigned char* data);
int			img_num_scales(map_stream* s);
int			img_num_tiles_per_x(map_stream* s, int scale);
int			img_num_tiles_per_y(map_stream* s, int scale);
int			img_scale_dx(map_stream* s, int scale);
int			img_scale_dy(map_stream* s, int scale);
void		img_close(map_stream*);

#ifdef __cplusplus
};
#endif

#endif
