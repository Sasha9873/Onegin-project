#include "Onegin.h"

int text_init(struct Text* text)
{
    FILE* file = fopen(text->file_name, "rb");
    if (file == NULL){
        printf("Error: file was not been open!\n");
        return FILE_NOT_OPEN;
    }

    fseek(file, 0L, SEEK_END);
    text->file_size = ftell(file);

    fseek(file, 0L, SEEK_SET);

    text->buffer = (char*)calloc(text->file_size + 1, sizeof(char));
    text->buffer[text->file_size] = '\0';
    int t = fread((void*)text->buffer, sizeof(char), text->file_size, file);
    fflush(stdout);

    printf("%s\n", text->buffer);
    text->n_strings = count_strings(text);
    text->strings = (struct String*)calloc(text->n_strings, sizeof(struct String));

    serarate_to_strings(text);
 /*   printf("sym1 = %c sym2 = %c size = %d\n\n\n", text->strings->start[0], (text->strings->start + 1)[0], sizeof(struct String));

    return EXIT_SUCCESS;*/
}

int get_file_size(size_t* k_bytes, FILE* file)
{
    if (file == NULL){
        printf("Error: file was not been open!\n");
        return FILE_NOT_OPEN;
    }

    int n_lines = 0;

    fseek(file, 0L, SEEK_END);
    *k_bytes = ftell(file);

    fprintf(file, "\0");

    fseek(file, 0L, SEEK_SET);

    fclose(file);

    return EXIT_SUCCESS;
}


int read_from_file(char* buffer, size_t k_bytes, FILE* file)
{
    fread(buffer, sizeof(char), k_bytes + 1, file);

    if (file == NULL){
        printf("Error: file was not been open!\n");
        return FILE_NOT_OPEN;
    }

    return EXIT_SUCCESS;
}


int serarate_to_strings(struct Text* text)
{
    int k_lines = 0, current_position = 0; // strchr || strtok

    while(((text->strings + k_lines)->length = my_getline2(text->buffer + current_position)) != 0 ){

        (text->strings + k_lines)->start = text->buffer + current_position;

        current_position += (text->strings + k_lines)->length;

        printf("len = %d, k_lines = %d pointer = %p, c=%c\n", (text->strings + k_lines)->length, k_lines, (text->strings + k_lines)->start, *((text->strings + k_lines)->start));

        k_lines++;
    }
    for(k_lines = 0; k_lines < 8; k_lines++)
        printf("len8 = %d, pointer = %p, c=%c\n", (text->strings + k_lines)->length, (text->strings + k_lines)->start, *((text->strings + k_lines)->start));
    return 0;
}

int count_strings(struct Text* text)
{
    int index = 0, k_lines = 0;
    for(index = 0; index < text->file_size; index++){
       // printf("in = %d\n", index);
        fflush(stdout);
        printf("%c ", text->buffer[index]);
        if(text->buffer[index] == '\n') {
              k_lines++;
        }
    }
    return k_lines;
}


int my_getline2(char* buffer)
{
    int symbol = 0, length = 0;

    assert(buffer != NULL);

    char* line_end = strchr(buffer, '\n');
    char* file_end = strchr(buffer, '\0');
    if(buffer == file_end)
        return 0;
    printf("  line end=%dp",line_end);
    length = (line_end - buffer)/sizeof(*buffer) + 1;

    printf("\nlen=%d\n",length);
    return length;
}


int sort_file(struct Text* text)
{
    int n_index = 0;
    char* temp = NULL;
    int help = 0;
    int n_sym1 = 0, n_sym2 = 0;
    char sym1 = '\0', sym2 = '\0';
    printf("\nn_lines= %d\n",text->n_strings);

    //void*c;
    //int*b;
    //b = (int*)c;
    printf("sort\n");
    for(int k_iters = 0; k_iters < text->n_strings - 1; k_iters++)
    {
        for(n_index = 0; n_index < text->n_strings - k_iters - 1; n_index++){
                n_sym1 = n_sym2 = 0;
                printf("iters = %d  index = %d\n", k_iters, n_index);
                if(comparator(text->strings + n_index, text->strings + n_index + 1) == 1){
                     temp = (text->strings + n_index)->start;
                    (text->strings + n_index)->start = (text->strings + n_index + 1)->start;
                    (text->strings + n_index + 1)->start = temp;

                    help = (text->strings + n_index)->length;
                    (text->strings + n_index)->length = (text->strings + n_index + 1)->length;
                    (text->strings + n_index + 1)->length = help;
                    printf("2 iters = %d  index = %d str1 = %s str2 = %s\n", k_iters, n_index, (text->strings + n_index)->start, (text->strings + n_index + 1)->start);
                }
                printf("777777\n");
                fflush(stdout);
        }
        char c;
        int u;
        printf("\n");
        for(int y = 0; y < text->n_strings; y++){
            printf("\nstr:");
            for(u = 0; u < (text->strings + y)->length; u++){
                printf("%c", (text->strings + y)->start[u]);
            }

        }
        //printf("str: %s\n\n", (text->strings)->start);
        //printf("48989565656565\n");
    }
    return EXIT_SUCCESS;
}


int comparator(const void* str1, const void* str2)
{
    printf("comp555\n");
    struct String* string1 = (struct String*) str1;
    struct String* string2 = (struct String*) str2;
    int n_sym1 = 0, n_sym2 = 0;
    char sym1 = '\0', sym2 = '\0';
    printf("string = %p %s str2 = %s\n", string1->start, string1->start, string2->start);
    sym1 = string1->start[0];
    sym2 = string2->start[0];

    //while(n_sym1 <= (text->strings + n_index)->length && n_sym2 <= (text->strings + n_index + 1)->length){
    while(sym1 != '\n' && sym2 != '\n'){

        while(isalnum(sym1) == 0){ // ctype.h
            n_sym1++;
            sym1 = string1->start[n_sym1];
        }

        while(isalnum(sym2) == 0){
            n_sym2++;
            sym2 = string2->start[n_sym2];
        }
        //printf("sym1 = %c sym2 = %c\n", sym1, sym2);
        //fflush(stdout);
        if (sym1 > sym2)
            return 1;

        else if (sym1 == sym2){
            n_sym1++;
            n_sym2++;
        }
        else{
            //printf("<\n");
            //fflush(stdout);
            return -1;
        }


        sym1 = string1->start[n_sym1];
        sym2 = string2->start[n_sym2];
    }

    return 0;
}

/*int write_new_file(struct Text* text, const char* name)
{
    printf("55\n");
    printf("%s\n",name);

    FILE* new_file = fopen(name, "w");
    if (new_file == NULL) {
        printf("Error opening file\n");
    }
    printf("%p\n",new_file);
    fflush(stdout);

    if (new_file == NULL){
        printf("Error: file was not been open!\n");
        return FILE_NOT_OPEN;
    }

    fprintf(new_file, "sorted file:\n\n");
    printf("88378\n");

    for(int n_lines = 0; n_lines < text->n_strings; n_lines++)
        for(int num = 0; num < (text->strings + n_lines)->length; num++)
            fprintf(new_file, "%c", *((text->strings + n_lines)->start + num));

    fclose(new_file);
    printf("55");
    return EXIT_SUCCESS;
}*/

/*int reverse_sort_file(struct Text* text) // void* index
{
    int n_index = 0;
    char* temp = NULL;
    int help = 0;
    int n_sym1 = 0, n_sym2 = 0;
    char sym1 = '\0', sym2 = '\0';
    printf("\nn_lines= %d\n",text->n_strings);

    //void*c;
    //int*b;
    //b = (int*)c;
    printf("sort\n");
    for(int k_iters = 0; k_iters < text->n_strings - 1; k_iters++)
    {
        for(n_index = 0; n_index < text->n_strings - k_iters - 1; n_index++){
                n_sym1 = (text->strings + n_index)->length -2;
                n_sym2 = (text->strings + n_index + 1)->length -2;
                printf("iters = %d  index = %d\n", k_iters, n_index);
                if(comparator_reverse(text, n_index) == 1){
                    temp = (text->strings + n_index)->start;
                    (text->strings + n_index)->start = (text->strings + n_index + 1)->start;
                    (text->strings + n_index + 1)->start = temp;

                    help = (text->strings + n_index)->length;
                    (text->strings + n_index)->length = (text->strings + n_index + 1)->length;
                    (text->strings + n_index + 1)->length = help;
                    printf("iters = %d  index = %d %s %s\n", k_iters, n_index, (text->strings + n_index)->start, (text->strings + n_index + 1)->start);
                }

        }printf("999999");
    }printf("777777");
    return EXIT_SUCCESS;
}

int comparator_reverse(const void* str1, const void* str2)
{
    printf("comp555\n");
    int n_sym1 = 0, n_sym2 = 0;
    char sym1 = '\0', sym2 = '\0';

    str1 = (int*)str1;
    srt2 = (int*)str2;

    sym1 = str[0];
    sym2 = str[0];

    while(sym1 != '\n' && sym2 != '\n'){
        while(isalnum(sym1) == 0){
            n_sym1++;
            sym1 = str1[n_sym1];
        }

        while(isalnum(sym2) == 0){
            n_sym2++;
                sym2 = str2[n_sym1];
        }

        if (sym1 > sym2)
            return 1;

        else if (sym1 == sym2){
            n_sym1++;
            n_sym2++;
        }
        else
            return -1;

        sym1 = str1[n_sym1];
        sym2 = str2[n_sym2];
    }
    return 0;
}*/

/*int reverse_sort_file(struct index_size* index, int n_lines)
{
    int n_index = 0;
    int n_sym1 = 0, n_sym2 = 0;
    char* temp = NULL;
    int help = 0;
    char sym1 = '\0', sym2 = '\0';
    //printf("\nn_lines= %d\n",n_lines);
    for(int k_iters = 0; k_iters < n_lines - 1; k_iters++)
    {
        //("\nk_index= %d\n",n_index);
        //printf("k_iters= %d\n",k_iters);

        for(n_index = 0; n_index < n_lines - k_iters -1; n_index++){
            n_sym1 = (index + n_index)->length - 2;
            n_sym2 = (index + n_index + 1)->length - 2;
            //printf("2%c %c\n",*((index + n_index)->pointer_start), *((index + n_index + 1)->pointer_start));
            //printf("\nidex=%d\n",n_index);
            while(n_sym1 >= 0 && n_sym2 >= 0){
                sym1 = *((index + n_index) -> start + n_sym1);
                sym2 = *((index + n_index + 1) -> start + n_sym2);

                //printf("sym1=%c sym2=%c\n",sym1,sym2);

                while(isalnum(sym1) == 0){
                    n_sym--;
                    sym1 = *((index + n_index) -> start + n_symbols1);
                }

                while(isalnum(sym2) == 0){
                    n_sym--;
                    sym2 = *((index + n_index + 1) -> start + n_symbols2);
                }

                //printf("sym1=%c sym2=%c\n",sym1,sym2);
                if (sym1 > sym2)
                {
                    //printf("1!!!!!!%c %c\n",*((index + n_index)->pointer_start), *((index + n_index + 1)->pointer_start));
                    temp = (index + n_index)->start;
                    (index + n_index)->start = (index + n_index + 1)->start;
                    (index + n_index + 1)->start = temp;

                    help = (index + n_index)->length;
                    (index + n_index)->length = (index + n_index + 1)->length;
                    (index + n_index + 1)->length = help;

                    break;

                }
                else if (sym1 == sym2){
                    n_sym--;
                    n_sym2--;
                    //printf("!!!!!2%c %c  %d %d\n",*((index + n_index)->pointer_start), *((index + n_index + 1)->pointer_start),n_symbols1,n_symbols2);
                }
                else
                    break;
            };
        }
        //for(int i = 0; i < n_lines; i++)
            //printf("%c\n", *((index + i)->pointer_start));
    }

    return EXIT_SUCCESS;
}

void swap(struct String* lhs, struct String* rhs) {
    struct String tmp = *lhs;
}
int compare_strings(const void* lhs, const void* rhs) {
    // type
    swap(lhs, rhs);
}
int add_to_new_file(struct Text* text, const char* name)
{
    FILE* new_file = fopen(name, "a");
    if (new_file == NULL){
        printf("Error: file was not been open!\n");
        return FILE_NOT_OPEN;
    }

    fprintf(new_file, "\n\nreverse sorted file:\n\n");

    for(int n_lines = 0; n_lines < text->n_strings; n_lines++)
        for(int num = 0; num < (text->strings + n_lines)->length; num++)
            fprintf(new_file, "%c", *((text->strings + n_lines)->start + num));

    fprintf(new_file, "\n\noriginal file:\n\n%s", text->buffer);

    fclose(new_file);
    return EXIT_SUCCESS;
}
*/
