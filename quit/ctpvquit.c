#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        fprintf(stderr, "id not given\n");
        return EXIT_FAILURE;
    }

    char* id_s = argv[1];

    execlp("ctpv", "ctpv", "-e", id_s, NULL);
    perror("execlp");
    return EXIT_FAILURE;
}
