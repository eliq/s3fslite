#include <string>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "fileinfo.h"

Fileinfo::Fileinfo(std::string path, unsigned uid, unsigned gid,
        mode_t mode, time_t mtime, size_t size)
{
    set(path, uid, gid, mode, mtime, size);
}

Fileinfo::Fileinfo(std::string path, struct stat *info) {
    set(path, info->st_uid, info->st_gid, info->st_mode, info->st_mtime,
            info->st_size);
}

void Fileinfo::set(std::string path, unsigned uid, unsigned gid,
    mode_t mode, time_t mtime, size_t size)
{
    this->path = path;
    this->uid = uid;
    this->gid = gid;
    this->mode = mode;
    this->mtime = mtime;
    this->size = size;
}

void Fileinfo::toStat(struct stat *info) {
    memset(info, 0, sizeof(struct stat));
    info->st_nlink = 1;
    info->st_uid = uid;
    info->st_gid = gid;
    info->st_mode = mode;
    info->st_mtime = mtime;
    info->st_ctime = mtime;
    info->st_atime = mtime;
    info->st_size = size;
    if (S_ISREG(mode))
        info->st_blocks = info->st_size / 512 + 1;
}

