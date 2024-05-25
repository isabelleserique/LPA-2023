#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct zip_file_hdr {
    int signature;
    short version;
    short flags;
    short compression;
    short mod_time;
    short mod_date;
    int crc;
    int compressed_size;
    int uncompressed_size;
    short name_length;
    short extra_field_length;
} __attribute__ ((packed));

void main(int argc, char *argv[]) {

    int info = 1;
    FILE *zip_file = fopen(argv[1], "rb");
    struct zip_file_hdr *file_hdr = malloc(sizeof(struct zip_file_hdr));

    while ((feof(zip_file) == false)){
        fread(file_hdr, sizeof(struct zip_file_hdr), 1, zip_file);
        if(file_hdr->signature == 0x04034b50) {
            char *arquivo = malloc(file_hdr->name_length + 1);

            fread(arquivo, file_hdr->name_length, 1, zip_file);
            strcat(arquivo, "\0");
            printf("Arquivo %d\n", info);
            printf(" --> Nome do Arquivo: %s\n", arquivo); 
            printf(" --> Tamanho Compactado: %d\n", file_hdr->compressed_size);
            printf(" --> Tamanho Descompactado: %d\n", file_hdr->uncompressed_size);  

            info++;
            free(arquivo);

            fseek(zip_file, file_hdr->extra_field_length + file_hdr->compressed_size, SEEK_CUR);           
        } else {
            break;
        }
    }   
    free(file_hdr);
    fclose(zip_file);
}   