#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define RED "\033[;31;m"
#define WHITE "\033[;37;m"
#define GREEN "\033[;32;m"
#define LINE_BELOW_TEXT "\033[;4;m"
#define LINE_NOT_BELOW_TEXT "\033[;0;m"

int main(int argc, char *argv[]) {
    FILE *file_txt;
    int num_all_pages;
    char save_as[50];
    char cmd[200];
    char buffer[255];
    if(argc < 2) {
        printf("\n%sUse: %s%s 'Your file pdf' %s\n", WHITE, GREEN, LINE_BELOW_TEXT, LINE_NOT_BELOW_TEXT);
        return 0;
    }
    if (strstr(argv[1], ".pdf") == NULL) {
        printf("%sInvalid coordination%s\n\n", RED, LINE_BELOW_TEXT);
        printf("%sUse: %s%s 'Your file pdf' %s\n", WHITE, GREEN, LINE_BELOW_TEXT, LINE_NOT_BELOW_TEXT);
        return 0;
    }
    FILE *pdf_file = fopen(argv[1], "rb");
    if (pdf_file == NULL) {
        printf("%sError opening file: %s%s\n", RED, argv[1], LINE_BELOW_TEXT);
        return 0;
    }
    strcpy(save_as, argv[1]);
    for (int i = strlen(argv[1]) - 1; i >= 0; i--) {
        if (save_as[i] == '/') {
            strcpy(save_as + i + 1, save_as + i + 1 + 4);
            strcpy(save_as + i + 1 + strlen(save_as + i + 1) - 4, ".txt");
            break;
        }
        if (i == 0) {
            strcpy(save_as, argv[1]);
            strcpy(save_as + strlen(save_as) - 4, ".txt");
        }
    }
    FILE *pdf = popen("pdftotext - -", "w");
    if (!pdf) {
        printf("%sError opening pipe to pdftotext%s\n", RED, LINE_BELOW_TEXT);
        return 0;
    }
    int num_bytes;
    char buf[8192];
    while ((num_bytes = fread(buf, 1, sizeof(buf), pdf_file))) {
        fwrite(buf, 1, num_bytes, pdf);
    }
    if (ferror(pdf_file)) {
        printf("%sError reading from file: %s%s\n", RED, argv[1], LINE_BELOW_TEXT);
        fclose(pdf);
        return 0;
    }
    fclose(pdf);
    sprintf(cmd, "mv -f -v ./-%s %s", save_as, save_as);
    system(cmd);
    fclose(pdf_file);
    printf("\n%sConverting PDF to txt done!%s\n", GREEN, LINE_BELOW_TEXT);
    return 0;
}
