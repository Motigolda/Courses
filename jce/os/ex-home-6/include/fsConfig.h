#ifndef FS_CONFIG_H
#define FS_CONFIG_H

#ifndef DISK_SIZE
#define DISK_SIZE (256)
#endif

#ifndef DISK_PATH
#define DISK_PATH "DISK_SIM_FILE.txt"
#endif

#ifndef DISK_SIM_FILE
#define DISK_SIM_FILE DISK_PATH
#endif

#define SUCCESS (1)

#define ERROR_OPERATION_FAILED (-1)

#define BLOCK_SIZE_UNDEFINED (-1)

#define ERROR_FD_NOT_EXISTS (-1)

#define ERROR_FILE_NOT_FOUND (-1)

#define ERROR_FILE_IS_FULL (-1)

#define ERROR_DISK_IS_FULL (-1)

#define ERROR_BUFFER_LARGER_THAN_BLOCK_SIZE (-1)

#define ERROR_BLOCK_NOT_IN_USE (-1)

#define ERROR_FD_NOT_EXISTS (-1)

#define ERROR_NOT_ENOUGH_FREE_SPACE (-1)

#define ERROR_NULL_BUFFER (-1)

#define ERROR_LEN_ZERO (-1)

#define ERROR_LEN_TOO_BIG (-1)

#define NOT_DEFINED (-1)

#define NOT_INITIALIZED (-1)

#define ERROR_INVALID_BLOCK_INDEX (-1)

#endif