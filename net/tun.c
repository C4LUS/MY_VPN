#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <stdbool.h>
#include <linux/if_tun.h>

#define IFNAMSIZ 16

int main() {
    int tun_fd = open("/dev/net/tun", O_RDWR);

    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
    strcpy(ifr.ifr_name, "tun0");
    ioctl(tun_fd, TUNSETIFF, (void *)&ifr);

    while (true) {
        char buffer[1056];
        int nread = read(tun_fd, buffer, sizeof(buffer));
        printf("Read %d bytes from device %s\n",nread ,ifr.ifr_name);
    }
    close(tun_fd);
    return 0;
}