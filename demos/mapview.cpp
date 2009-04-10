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

#include "map_loader.h"
#include "map_container.h"
#include "map_index.h"
#include "map_datums.h"

#include "map_render.h"

#include <SDL.h>

#include "log_stream.h"

static int pen_x, pen_y, delta_x, delta_y, pressed = 0;

/*--------------------------------------------------------------------------*/
void clear_view(SDL_Surface* view)
{
	if(SDL_MUSTLOCK(view))
		SDL_LockSurface(view);

	int colors[] = {0xFFD4D4D4, 0xFFFFFFFF};
		
	int rects_per_x = view->w/16 + 1;
	int rects_per_y = view->h/16 + 1;
	
	int color_index = 0;
		
	for (int i = 0; i < rects_per_y; i++)
	{
		color_index = i & 1;
		for (int j = 0; j < rects_per_x; j++)
		{
			SDL_Rect rect;
		
			rect.x = j * 16;
			rect.y = i * 16;
			rect.w = 16;
			rect.h = 16;
			
			SDL_FillRect(view, &rect, colors[color_index]);
			
			color_index ^= 1;
		}
	}
		

	if(SDL_MUSTLOCK(view))
		SDL_UnlockSurface(view);
}

/*--------------------------------------------------------------------------*/
#ifdef UNDER_CE
#include <windows.h>
int _tmain(int argc, _TCHAR* argv[])
#else
int main( int argc, char *argv[] ) 
#endif
{
#ifndef UNDER_CE
	logstream_to(stdout);
#else
	FILE* fp = fopen("stdout.txt", "wt");
	logstream_to(fp);
#endif	

#ifndef WIN32
	mapdatums_init("./datums.xml");
	map_index* collection = new map_index("/home/dannie/shared/maps");
#else
#ifndef UNDER_CE
	mapdatums_init(".\\datums.xml");
	map_index* collection = new map_index("E:\\maps");
#else
	mapdatums_init("\\SDMMC\\datums.xml");
	map_index* collection = new map_index("\\SDMMC\\maps");
#endif

#endif

    if (SDL_Init (SDL_INIT_VIDEO) < 0) 
	{
	    fprintf (stderr, "Video initialization failed: %s", SDL_GetError());
		SDL_Quit();
	}    

	int w, h, bpp;
#ifdef UNDER_CE	
	w = 240, h = 240, bpp = 16;
#else
	w = 800, h = 600, bpp = 32;
#endif	

    SDL_Surface* screen = SDL_SetVideoMode(w, h, bpp, SDL_SWSURFACE | SDL_DOUBLEBUF);
	map_render* render = new map_render(collection, w, h);
	
	double lat = 60.680287;
	double lon = 30.005125;
	
	render->center_set(lat, lon);
	
    int done = 0;
    SDL_Event event;


    while (!done) 
	{
	    while (SDL_PollEvent(&event)) 
		{
		    switch (event.type) 
			{
				case SDL_KEYDOWN:
				{
					 switch( event.key.keysym.sym )
					 {
						case SDLK_LEFT:
							render->map_prev();
							break;
						case SDLK_RIGHT:
							render->map_next();
							break;
						
						case SDLK_UP:
							render->zoom_up();
						break;

						case SDLK_DOWN:
							render->zoom_down();
						break;

						case SDLK_RETURN:
							done = 1;
						break;
										
						default:
							break;
					}
				} break;
				
				case SDL_MOUSEMOTION:
				{
					if(pressed)
					{
						int x = event.motion.x;
						int y = event.motion.y;
					
						delta_x = -(pen_x - x);
						delta_y = -(pen_y - y);
						
						clear_view(screen);
					}
				} break;
			
				case SDL_MOUSEBUTTONDOWN:
				{
					pen_x = event.motion.x;
					pen_y = event.motion.y;
					
					pressed = 1;
					delta_x = 0;
					delta_y = 0;
				} break;
			
				case SDL_MOUSEBUTTONUP:
				{
					pen_x = event.motion.x;
					pen_y = event.motion.y;

					render->scroll_by(-delta_x, -delta_y);

					pressed = 0;
					delta_x = 0;
					delta_y = 0;
					
				} break;
				
				
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
		}

		render->center_get(&lat, &lon);
		
		char title[128];
		double zoom = render->zoom_get();
		
		sprintf(title, "lat: %f lon: %f, zoom: %3.2f", lat, lon, (zoom * 100));
		SDL_WM_SetCaption(title, title);

		SDL_Rect src, dst;
		render->rect(&src);
		render->rect(&dst);
		
		dst.x += delta_x;
		dst.y += delta_y;

		if (src.w != screen->w || src.h != screen->h)
		{
			clear_view(screen);
		}
		
        SDL_BlitSurface (render->surface(), &src, screen, &dst);

		SDL_Rect central = { screen->w / 2 - 1, screen->h / 2 - 8, 2, 16}; 
		SDL_FillRect(screen, &central, 0x00FF0000);
		
		central.x = screen->w / 2 - 8;
		central.y = screen->h / 2 - 1;
		central.w = 16;
		central.h = 2;
		SDL_FillRect(screen, &central, 0x00FF0000);

        SDL_Flip(screen);
	}

	delete render;		
	delete collection;
	mapdatums_done();
	
    SDL_Quit ();

#ifdef UNDER_CE
	fclose(fp);
#endif


    return 0;
}
