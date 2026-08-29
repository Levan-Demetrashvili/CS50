#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;
const int BLOCK_SIZE = 512;

FILE *create_jpeg_file(BYTE buffer[], int count);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover [forensic image]\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "rb");
    if (card == NULL)
    {
        printf("Could not open forensic image for reading\n");
        return 1;
    }

    const int SIGNATURE[] = {0xff, 0xd8, 0xff};
    BYTE image_buffer[BLOCK_SIZE];
    FILE *f = NULL;
    int image_count = 0;
    int writing = 0;

    while (fread(image_buffer, sizeof(BYTE), BLOCK_SIZE, card) != 0)
    {

        if (image_buffer[0] == SIGNATURE[0] && image_buffer[1] == SIGNATURE[1] &&
            image_buffer[2] == SIGNATURE[2] && image_buffer[3] >= 224 && image_buffer[3] <= 239)
        {
            // Close last file, open new JPEG file and write image_buffer to it
            if (f != NULL)
            {
                fclose(f);
            }
            f = create_jpeg_file(image_buffer, image_count);
            image_count++;
            writing = 1;
        }
        else if (writing)
        {
            // add the next block
            fwrite(image_buffer, sizeof(BYTE), BLOCK_SIZE, f);
        }
    }

    fclose(f);
    fclose(card);
    return 0;
}

FILE *create_jpeg_file(BYTE buffer[], int count)
{
    char *filename = malloc(sizeof(char) * 8);
    if (filename == NULL)
    {
        printf("Cannot continue the execution of program");
        exit(1);
    }

    sprintf(filename, "%03d.jpg", count);

    FILE *jpeg_file = fopen(filename, "wb");
    free(filename);

    if (jpeg_file == NULL)
    {
        printf("Cannot continue the execution of program");
        exit(1);
    }

    fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, jpeg_file);
    return jpeg_file;
}
