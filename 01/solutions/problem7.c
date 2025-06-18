#include<unistd.h>
int main() {
    while (1) {
        char buf[1];
        int r = read(0, buf, 1);
        if (!r || r == -1)
            break;
        write(1, buf, 1);
    }
    return 0;
}