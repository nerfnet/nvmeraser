#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include "nvme.h"

int main(int argc, char** argv) {
	DIR *dev_dir;
	struct dirent *entry;
	
	dev_dir = opendir("/dev");
	
	if(!dev_dir) {
		perror("opening /dev failed");
		return 1;
	}
	
	char current_device[256];
	while((entry = readdir(dev_dir)) != NULL) {
		if(is_nvme_device(entry->d_name)) {
			snprintf(current_device, 256, "%s/%s", dev_path, entry->d_name);
			
			int fd = open(current_device, O_RDWR);
			if(fd == -1) {
				perror("device open failure"); //ok..
				continue;
			}
			
			printf("Wiping: %s\n", current_device);
			if(nvme_wipe(fd) == 0) {
				printf("Disk wiped: %s\n\n", current_device);
			}
			
			close(fd);
		}
	}
	
	closedir(dev_dir);
	return 0;
}