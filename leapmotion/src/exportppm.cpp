/* THIS IS NOT MINE! */
#include <cstring>
#include <stdio.h>
#include "exportppm.h"

size_t ppm_save(struct ppm_image &img, const std::string &filename) {
	FILE *outfile = fopen(filename.c_str(), "w");
	if (outfile == NULL)
		return (size_t)NULL;
	size_t n = 0;
	n += fprintf(outfile, "P6\n# THIS IS A COMMENT\n%d %d\n%d\n", 
		     img.width/3, img.height, 0xFF);
	n += fwrite(img.data,
		    sizeof(unsigned char),
		    img.size*3,
		    outfile );
	fclose(outfile);
	return n;
}
