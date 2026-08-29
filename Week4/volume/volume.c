// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t HEADER_BYTE;
typedef int16_t SAMPLE_BYTES;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    int bytes_count = 0;
    HEADER_BYTE h;
    SAMPLE_BYTES s;

    while (bytes_count < 44)
    {
        fread(&h, sizeof(h), 1, input);
        fwrite(&h, sizeof(h), 1, output);
        bytes_count++;
    }

    while (fread(&s, sizeof(s), 1, input) != 0)
    {
        s *= factor;
        fwrite(&s, sizeof(s), 1, output);
    }

    // TODO: Read samples from input file and write updated data to output file

    // Close files
    fclose(input);
    fclose(output);
}
