#ifndef EXPORTPPM_H
#define EXPORTPPM_H

#include <string>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

struct ppm_image {
	int width;
	int height;
	const unsigned char *data;
	int size;
};

size_t ppm_save(struct ppm_image &img, const std::string &filename);

#endif
