#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_node {
    char *data;
    struct s_node *next;
} t_node;

void append(t_node **head, const char *data) {
    t_node *new_node = malloc(sizeof(t_node));
    new_node->data = strdup(data);
    new_node->next = NULL;
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        t_node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void write_to_pipe(int pipe_fd, t_node *head) {
    t_node *current = head;
    while (current) {
        write(pipe_fd, current->data, strlen(current->data));
        write(pipe_fd, "\n", 1);
        current = current->next;
    }
}

int main() {
    t_node *head = NULL;
    append(&head, "Hello");
    append(&head, "from");
    append(&head, "heredoc");

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        execve("/bin/cat", (char *[]){ "cat", NULL }, NULL);
        perror("execve");  // execve() only returns on error
        exit(EXIT_FAILURE);
    } else {        // Parent
        close(pipefd[0]);
        write_to_pipe(pipefd[1], head);
        close(pipefd[1]);  // Close write end of pipe to signal EOF to child.
        wait(NULL);  // Wait for child to terminate
    }

    // Cleanup
    t_node *current = head;
    while (current) {
        t_node *temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }

    return 0;
}
