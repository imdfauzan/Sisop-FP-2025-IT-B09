#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void normal_exit(){
    pid_t pid = fork();

    if (pid==0) {
        printf("[Child] Keluar normal dengan exit code 42.\n");
        exit(42);
    } else if (pid > 0) {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("[Parent] Child keluar normal dengan kode: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("[Parent] Child dihentikan oleh sinyal: %d\n", WTERMSIG(status));
        }
    } else {
        perror("fork");
    }
}

void signal_exit(){
    pid_t pid = fork();

    if (pid==0) {
        printf("[Child] Akan menyebabkan segfault (SIGSEGV)...\n");
        raise(SIGSEGV); // atau *(int *)0 = 0; untuk segfault juga
    } else if (pid > 0) {
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            printf("[Parent] Child keluar normal dengan kode: %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("[Parent] Child dihentikan oleh sinyal: %d (%s)\n",
                   WTERMSIG(status), strsignal(WTERMSIG(status)));
        }
    } else {
        perror("fork");
    }
}

int main(){
    printf("=== Exit normal: ===\n");
    normal_exit();

    printf("\n=== Exit karena sinyal: ===\n");
    signal_exit();

    return 0;
}
