#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fds[2];
    char buffer[100];

    if (pipe(fds) == -1) {  // Pipe oluştur
        perror("Pipe oluşturulamadı");
        return 1;
    }

    if (fork() == 0) {  // Çocuk process
        close(fds[0]);  // Okuma ucunu kapat
        write(fds[1], "Merhaba Pipe!", 13);
        close(fds[1]);  // Yazma ucunu kapat
    } else {  // Ebeveyn process
        close(fds[1]);  // Yazma ucunu kapat
        read(fds[0], buffer, 100);
        printf("Gelen veri: %s\n", buffer);
        close(fds[0]);  // Okuma ucunu kapat
    }

    return 0;
}