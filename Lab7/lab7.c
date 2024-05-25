#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>

struct chunk {
    int length;
    char type[4];
} __attribute__ ((packed));

struct chunk_IHDR {
    int width;
    int height;
    char bit_depth;
    char colour_type;
    char compression_method;
    char filter_method;
    char interlace_method;
} __attribute__ ((packed));

void main(int argc, char *argv[]) {
    int i_chunk = 1;
    struct chunk *chunk = malloc(sizeof(struct chunk));
    struct chunk_IHDR *chunk_ihdr = malloc(sizeof(struct chunk_IHDR));
    FILE *png_file = fopen(argv[1], "rb");
    fseek(png_file, 8, SEEK_CUR);

    while ((feof(png_file) == false)){
        printf("Lendo chunk %d\n", i_chunk);
        fread(chunk, sizeof(struct chunk), 1, png_file); 
        printf(" --> Tamanho: %d\n", ntohl(chunk->length));
        printf(" --> Tipo:  %.4s\n", chunk->type);

        if(strcmp(chunk->type, "IHDR") == 0) {
            fread(chunk_ihdr, sizeof(struct chunk_IHDR), 1, png_file); 
            printf("    --> Largura: %d\n", ntohl(chunk_ihdr->width));
            printf("    --> Altura:  %d\n", ntohl(chunk_ihdr->height));
            fseek(png_file, 4, SEEK_CUR);
        }
        else if(strcmp(chunk->type, "IEND") == 0) {  break;  }
        else {  fseek(png_file, ntohl(chunk->length)+4, SEEK_CUR);  }

        i_chunk++;
    }   
    free(chunk);
    free(chunk_ihdr);
    fclose(png_file);
}   