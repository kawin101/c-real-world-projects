#include <stdio.h>
#include <string.h>

void compress(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    FILE *out = fopen(output_file, "w");

    if (!in || !out) {
        perror("File error");
        return;
    }

    char current, previous;
    int count = 1;

    previous = fgetc(in); // read the first character
    if (previous == EOF) {
        fclose(in);
        fclose(out);
        return;
    }

    while ((current = fgetc(in)) != EOF) {
        if (current == previous) {
            count++;
        } else {
            fprintf(out, "%c%d", previous, count);
            previous = current;
            count = 1;
        }
    }
    fprintf(out, "%c%d", previous, count);
    
    fclose(in);
    fclose(out);
    printf("Compression complete! File saved as %s\n", output_file);
}

void decompress(const char *input_file, const char *output_file) {
    FILE *in = fopen(input_file, "r");
    FILE *out = fopen(output_file, "w");

    if (!in || !out) {
        perror("File error");
        return;
    }

    char ch;
    int count;

    while (fscanf(in, "%c%d", &ch, &count) == 2) {
        for (int i = 0; i < count; i++) {
            fputc(ch, out);
        }
    }

    fclose(in);
    fclose(out);
    printf("Decompression complete! File saved as %s\n", output_file);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <c/d> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    if (argv[1][0] == 'c') {
        compress(argv[2], argv[3]);
    } else if (argv[1][0] == 'd') {
        decompress(argv[2], argv[3]);
    } else {
        printf("Invalid mode! Use 'c' for compression and 'd' for decompress.\n");
        return 1;
    }

    return 0;
}