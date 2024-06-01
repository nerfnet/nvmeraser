#include "nvme.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/nvme_ioctl.h>

void wipe_ns(int ns) {
	// TODO 
}

int nvme_wipe(int fd) {
	char id_buff[R_IDENTITY_BUFF];
	struct nvme_admin_cmd nvme_cmd = {0};
	
	nvme_cmd.opcode = NVME_IDENTIFY;
	nvme_cmd.nsid = 0;
	nvme_cmd.data = id_buff;
	nvme_cmd.data_len = R_IDENTITY_BUFF;	
	nvme_cmd.cdw10 = 1;
	
	int r = ioctl(fd, NVME_IOCTL_ADMIN_CMD, &nvme_cmd);
	
	if(r != 0) {
		perror("ioctl op failed");
		return 1;
	}
	
	int* ns = (int*)(id_buff + NVME_NAMESPACE_COUNT_OFFSET);
	printf("Max namespaces: %i\n", *ns);
	
	for(int i = 0; i < *ns; i++) {
		wipe_ns(i);
	}
	return 0;
}

int is_nvme_device(const char *dev_path) {
	return strstr(dev_path, "nvme") != NULL;
}
