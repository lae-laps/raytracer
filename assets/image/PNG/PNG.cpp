#include <stdio.h>
#include <stdlib.h>

#include "PNG.hpp"
#include "../../global.hpp"

int PNG::write(const std::string path) const {
	return 0;
}


void PNG::set_pos(const int, const int, const val n[]) const {
}
void PNG::set_pos(const int, const int, const unsigned int n[]) const {
}
void PNG::set_pos(const int, const int, const int, const val) const {
}
void PNG::set_pos(const int, const int, const int, const unsigned int) const {
}


/*

#include <png.h>

Function that works with libpng

int PNG::write(const std::string path) const {

	// structures

	//png_byte color_type;
	//png_byte bit_depth;
	png_bytep *row_pointers = NULL;

	// test image
	
	for (unsigned int i = 0; i < height; i++) {
		for (unsigned int j = 0; j < width; j++) {
				row_pointers[i][j] = i * j;
			}   
	}

	// write

	//int y;

	FILE *fp = fopen(path.c_str(), "wb");
	if (!fp) return 1;

	png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png) return 1;

	png_infop info = png_create_info_struct(png);
	if (!info) return 1;

	if (setjmp(png_jmpbuf(png))) return 1;

	png_init_io(png, fp);

	// Output is 8bit depth, RGBA format.

	png_set_IHDR(
		png,
		info,
		width, height,
		8,
		PNG_COLOR_TYPE_RGB,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
	);
	png_write_info(png, info);

	// To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
	// Use png_set_filler().
	png_set_filler(png, 0, PNG_FILLER_AFTER);

	if (!row_pointers) return 1;

	png_write_image(png, row_pointers);
	png_write_end(png, NULL);
	
	for (unsigned int y = 0; y < height; y++) {
		free(row_pointers[y]);
	}

	free(row_pointers);

	fclose(fp);

	png_destroy_write_struct(&png, &info);

	return 0;
}
*/
