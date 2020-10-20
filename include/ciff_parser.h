#ifndef NATIVE_CIFF_PARSER_H
#define NATIVE_CIFF_PARSER_H

#define MAGIC_SIZE 4
#define HEADERSIZE_SIZE 8
#define CONTENTSIZE_SIZE 8
#define WIDTH_SIZE 8
#define HEIGHT_SIZE 8

typedef struct {
    char magic[MAGIC_SIZE];
    unsigned long long header_size;
    unsigned long long content_size;
    unsigned long long width;
    unsigned long long height;

    char *caption;

    unsigned long long tag_count;
    char **tags;

    unsigned char *pixels;
} CIFF;

void ciff_free(CIFF *ciff);
CIFF* ciff_parse(const unsigned char *buffer, unsigned long long size);
void ciff_to_bmp(const CIFF *ciff, unsigned char **bmp, unsigned long long *file_size);

#endif //NATIVE_CIFF_PARSER_H
