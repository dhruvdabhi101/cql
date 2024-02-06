#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_ssize_t.h>
#define true 1

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum { PREPARE_SUCESS, PREPARE_UNRECOGNZED_STATEMENT } PrepareResult;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;

typedef struct {
  StatementType type;
} Statement;

typedef struct {
  size_t input_lenght;
  size_t buffer_lenght;
  char *buffer;
} InputBuffer;

InputBuffer *new_input_buffer() {
  InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->input_lenght = 0;
  input_buffer->buffer_lenght = 0;

  return input_buffer;
}

void print_prompt() { printf("db> "); }

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

void read_input(InputBuffer *input_buffer) {
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_lenght), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignoring Trailing Newlines
  input_buffer->input_lenght = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}
void close_input_buffer(InputBuffer *input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

MetaCommandResult do_meta_command(InputBuffer *input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

PrepareResult prepare_statement(InputBuffer *input_buffer,
                                Statement *statement) {
  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    return PREPARE_SUCESS;
  }
  if (strcmp(input_buffer->buffer, "select") == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCESS;
  }
  return PREPARE_UNRECOGNZED_STATEMENT;
}

void execute_statement(Statement *statement) {
  switch (statement->type) {
  case (STATEMENT_INSERT):
    printf("This is where we will do insert");
    break;
  case (STATEMENT_SELECT):
    printf("This is where we will do select");
    break;
  }
}

int main(int argc, char *argv[]) {
  InputBuffer *input_buffer = new_input_buffer();
  while (true) {
    print_prompt();
    read_input(input_buffer);
    if (input_buffer->buffer[0] == '.') {
      switch (do_meta_command(input_buffer)) {
      case (META_COMMAND_SUCCESS):
        continue;
      case (META_COMMAND_UNRECOGNIZED_COMMAND):
        printf("Unrecognized Command \033[0;31m ':%s'\033[0m .\n",
               input_buffer->buffer);
        continue;
      }
    }
    Statement statement;
    switch (prepare_statement(input_buffer, &statement)) {
    case (PREPARE_SUCESS):
      break;
    case (PREPARE_UNRECOGNZED_STATEMENT):
      printf("Unrecognized Command \033[0;31m ':%s'\033[0m .\n",
             input_buffer->buffer);
      continue;
    }
    execute_statement(&statement);
  }
}

/**
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    } else {


        printf("Unrecognized Command \033[0;31m ':%s'\033[0m .\n",
input_buffer->buffer);
    }
**/
