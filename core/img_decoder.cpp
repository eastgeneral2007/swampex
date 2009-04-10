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

#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <string.h>
#include "img_decoder.h"

#include "SDL_image.h"

/*--------------------------------------------------------------------------*/
map_stream* img_open(char* path)
{
	img_stream* s = (img_stream*)malloc(sizeof(img_stream));
	memset(s, 0, sizeof(img_stream));
	
	s->image = IMG_Load(path);
	
	return (map_stream*)s;
}

/*--------------------------------------------------------------------------*/
void img_get_tile(map_stream* stream, int scale, int x, int y, unsigned char* data)
{
	img_stream* s = (img_stream*)stream;

    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif


	SDL_Surface* tile = 
		SDL_CreateRGBSurface(SDL_SWSURFACE, 64, 64, 32,
							rmask, gmask, bmask, amask);
							
	SDL_Rect r = {x * 64, y * 64, 64, 64};
	
	SDL_BlitSurface(s->image, &r, tile, NULL);
	
	memcpy(data, tile->pixels, tile->pitch*tile->h);
	
	SDL_FreeSurface(tile);
}

/*--------------------------------------------------------------------------*/
int	img_num_scales(map_stream* s)
{
	return 1;
}

/*--------------------------------------------------------------------------*/
int	img_num_tiles_per_x(map_stream* stream, int scale)
{
	img_stream* s = (img_stream*)stream;

	int n = s->image->w/64;
	
	if (s->image->w % 64)
		n++;
		
	return n;
}

/*--------------------------------------------------------------------------*/
int	img_num_tiles_per_y(map_stream* stream, int scale)
{
	img_stream* s = (img_stream*)stream;

	int n = s->image->h/64;
	
	if (s->image->h % 64)
		n++;
		
	return n;
}

/*--------------------------------------------------------------------------*/
int	img_scale_dx(map_stream* stream, int scale)
{
	img_stream* s = (img_stream*)stream;

	if (scale == 0)
		return s->image->w;
		
	return 0;
}

/*--------------------------------------------------------------------------*/
int	img_scale_dy(map_stream* stream, int scale)
{
	img_stream* s = (img_stream*)stream;

	if (scale == 0)
		return s->image->h;
		
	return 0;
}

/*--------------------------------------------------------------------------*/
void img_close(map_stream* stream)
{
	img_stream* s = (img_stream*)stream;

	if (s)
	{
		if (s->image)
			SDL_FreeSurface(s->image);
			
		free(s);
	}	
}
