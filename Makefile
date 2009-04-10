.NOTABS=yes

locals = -I./core -I./libs/cross/libgeotrans/src -I./libs/cross/ezxml -I./libs/cross/sdlgfx -I./libs/cross/ul -I./libs/cross/sdlimage
addons = -I/usr/include/libpng -I/usr/include -I/usr/include/SDL

defs = -DEZXML_NOMMAP=1

cc	= gcc
cpp	= g++
includes= -I/usr/include $(locals) $(ficl) $(addons)
cflags	= -g -O0 $(includes) $(defs) 
ldflags = -lpng -lSDL 

sources = ./demos/mapview \
	./libs/cross/sdlimage/IMG_bmp \
	./libs/cross/sdlimage/IMG \
	./libs/cross/sdlimage/IMG_gif \
	./libs/cross/sdlimage/IMG_jpg \
	./libs/cross/sdlimage/IMG_lbm \
	./libs/cross/sdlimage/IMG_pcx \
	./libs/cross/sdlimage/IMG_png \
	./libs/cross/sdlimage/IMG_pnm \
	./libs/cross/sdlimage/IMG_tga \
	./libs/cross/sdlimage/IMG_tif \
	./libs/cross/sdlimage/IMG_xcf \
	./libs/cross/sdlimage/IMG_xpm \
	./libs/cross/sdlimage/IMG_xv \
	./libs/cross/sdlimage/IMG_xxx \
	./libs/cross/libgeotrans/src/albers \
	./libs/cross/libgeotrans/src/azeq \
	./libs/cross/libgeotrans/src/bng \
	./libs/cross/libgeotrans/src/bonne \
	./libs/cross/libgeotrans/src/cassini \
	./libs/cross/libgeotrans/src/cyleqa \
	./libs/cross/libgeotrans/src/eckert4 \
	./libs/cross/libgeotrans/src/eckert6 \
	./libs/cross/libgeotrans/src/eqdcyl \
	./libs/cross/libgeotrans/src/gars \
	./libs/cross/libgeotrans/src/geocent \
	./libs/cross/libgeotrans/src/georef \
	./libs/cross/libgeotrans/src/gnomonic \
	./libs/cross/libgeotrans/src/grinten \
	./libs/cross/libgeotrans/src/lambert_1 \
	./libs/cross/libgeotrans/src/lambert_2 \
	./libs/cross/libgeotrans/src/loccart \
	./libs/cross/libgeotrans/src/mercator \
	./libs/cross/libgeotrans/src/mgrs \
	./libs/cross/libgeotrans/src/miller \
	./libs/cross/libgeotrans/src/mollweid \
	./libs/cross/libgeotrans/src/neys \
	./libs/cross/libgeotrans/src/nzmg \
	./libs/cross/libgeotrans/src/omerc \
	./libs/cross/libgeotrans/src/orthogr \
	./libs/cross/libgeotrans/src/polarst \
	./libs/cross/libgeotrans/src/polycon \
	./libs/cross/libgeotrans/src/sinusoid \
	./libs/cross/libgeotrans/src/stereogr \
	./libs/cross/libgeotrans/src/tranmerc \
	./libs/cross/libgeotrans/src/trcyleqa \
	./libs/cross/libgeotrans/src/ups \
	./libs/cross/libgeotrans/src/usng \
	./libs/cross/libgeotrans/src/utm \
	./libs/cross/ezxml/ezxml \
	./libs/cross/ul/ulClock \
	./libs/cross/ul/ul \
	./libs/cross/ul/ulError \
	./libs/cross/ul/ulLinkedList \
	./libs/cross/ul/ulList \
	./libs/cross/ul/ulRTTI \
	./core/file_collection \
	./core/ozf_decoder \
	./core/img_decoder \
	./core/map_loader \
	./core/map_projection \
	./core/gauss \
	./core/map_container \
	./core/map_index \
	./core/map_filters \
	./core/map_datums \
	./core/map_render \
	./core/qsort \
	./core/log_stream \
	./libs/cross/sdlgfx/SDL_framerate \
	./libs/cross/sdlgfx/SDL_gfxBlitFunc \
	./libs/cross/sdlgfx/SDL_gfxPrimitives \
	./libs/cross/sdlgfx/SDL_imageFilter \
	./libs/cross/sdlgfx/SDL_rotozoom 

objects = {$(sources)}.o

target = ./demos/swampex

$(target): $(objects)
	$(cpp) $(ldflags)  -o $@ $(objects)


%.o: %.cpp
	$(cpp) $(cflags) -c $< -o $@

%.o: %.c
	$(cc) $(cflags) -c $< -o $@

clean:
    rm -f $(objects) $(target)
