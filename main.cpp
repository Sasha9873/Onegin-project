//указатель на массив структур
#include "Onegin.h"
//#include "right_changing_file.cpp"
//#include "Onegin_functions.cpp"


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
    is_error = text_init(&text); // inside text struct
    if (is_error == FILE_NOT_OPEN){
        printf("Error: file was not been open!\n");
        return FILE_NOT_OPEN;
    }
    printf("sort\n");
    sort_file(&text);
    printf("6666\n");
    const char name_produced_file[]=  "sorted_file"; // .sorted

    //write_new_file(&text, name_produced_file);

    //reverse_sort_file(&text);//index[0], n_strings);

    //add_to_new_file(text, name_produced_file);

    /*text_print(&text, stream);
    text_destroy(&text);*/

}
/*
int main(int argc, char** argv) // main.cpp
{
    struct String* strings = (struct String*) calloc(n_string, sizeof(struct String)); // text_init
    struct index_size index[MAXSTRINGS]; // naming
    // 1) read file in buffer
    // 2) calloc for strings array

    FILE* file = NULL;

    const char* name_right_file = "right_file";
    if (argc > 1)
        name_right_file = argv[1];//"right_file";

    int is_error = 0;
    size_t k_bytes = 0;

    file = fopen(name_right_file, "r");
    is_error = get_file_size(&k_bytes, file);

    if (is_error == FILE_NOT_OPEN){
        printf("Error: file was not been open!\n");
        return FILE_NOT_OPEN;
    }

    char* buffer = (char*)calloc(k_bytes + 1, sizeof(char));

    if((is_error = read_from_file(buffer, k_bytes, file)) != EXIT_SUCCESS){
        printf("Error: something is wrong with file reading!\n");
        return EXIT_FAILURE;
    }
    //printf("k_bytes=%d,buffer=%p \n", k_bytes, buffer);

    int n_strings = serarate_to_strings(&index[0], buffer, MAXSTRINGS);

    //printf("\n\n");
    for(int n_lines = 0; n_lines < n_strings; n_lines++)
        for(int num = 0; num < index[n_lines].length; num++)
            printf("%c", *(index[n_lines].start + num));

    //printf("7%c\n",*((index)->pointer_start));
    sort_file(&index[0], n_strings);
    //printf("\n\n");
    for(int n_lines = 0; n_lines < n_strings; n_lines++)
        for(int num = 0; num < index[n_lines].length; num++)
            printf("%c", *(index[n_lines].start + num));

    const char name_produced_file[]=  "sorted_file";
    write_new_file(&index[0], n_strings, name_produced_file);

    reverse_sort_file(&index[0], n_strings);
    for(int n_lines = 0; n_lines < n_strings; n_lines++)
        for(int num = 0; num < index[n_lines].length; num++)
            printf("%c", *(index[n_lines].start + num));

    add_to_new_file(&index[0], n_strings, buffer, name_produced_file);

    free(buffer);

    fclose(file);

    return EXIT_SUCCESS;
}


*/
