#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void run_scenario_normal_exit() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process: exit secara normal dengan kode 42
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

void run_scenario_signal_exit() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process: menyebabkan segfault (akses ilegal)
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

int main() {
    printf("=== Skenario 1: Exit normal ===\n");
    run_scenario_normal_exit();

    printf("\n=== Skenario 2: Exit karena sinyal ===\n");
    run_scenario_signal_exit();

    return 0;
}
