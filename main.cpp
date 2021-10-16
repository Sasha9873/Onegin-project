//указатель на массив структур
#include "Onegin.h"

/**
 * Creates buffer for a file text.
 *
 * @returns 0 if all is normal
 */
 // wchar.h

 // usage
int main(int argc, char** argv) {
    struct Text text;

    text.file_name = "right_file"; // not good

    if (argc > 1)
        text.file_name = argv[1];

    int is_error = 0;
    is_error = text_init(&text);
    /*printf("Number of strings: %d\n", text.n_strings);
    if (is_error == FILE_NOT_OPEN){
        printf("Error: file was not been open!\n");
        return FILE_NOT_OPEN;
    }
    printf("sort\n");
    sort_file(&text);
    printf("6666777\n");*/
    //const char name_produced_file[]=  "sorted_file"; // .sorted
    return 0;
}
