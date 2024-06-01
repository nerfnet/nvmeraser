#pragma once

#define R_IDENTIFY_BUFF 0x1000

#define NVME_NAMESPACE_COUNT_OFFSET 0x204
#define NVME_IDENTIFY 0x06

int nvme_wipe(int fd);
int is_nvme_device(const char* device_path);  