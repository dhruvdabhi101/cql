#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/_types/_ssize_t.h>
#define true 1

typedef struct {
    size_t input_lenght;
    size_t buffer_lenght;
    char* buffer;
} InputBuffer;

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer-> input_lenght = 0;
    input_buffer-> buffer_lenght = 0;

    return input_buffer;
}

void print_prompt() {
    printf("db> ");
}

ssize_t getline(char** lineptr, size_t *n, FILE *stream);

void read_input(InputBuffer* input_buffer) {
    ssize_t bytes_read =
        getline(&(input_buffer->buffer), &(input_buffer->buffer_lenght), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }


    //Ignoring Trailing Newlines
    input_buffer->input_lenght = bytes_read - 1;
    input_buffer->buffer[bytes_read-1] = 0;

}
void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}



int main(int argc, char *argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while(true) {
        print_prompt();
        read_input(input_buffer);

        if(strcmp(input_buffer->buffer, ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {


            printf("Unrecognized Command \033[0;31m ':%s'\033[0m .\n", input_buffer->buffer);
        }
    }
}
