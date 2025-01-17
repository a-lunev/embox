/**
 * @file
 * @brief
 *
 * @author  Anton Kozlov
 * @date    23.05.2014
 */
#include <errno.h>
#include <string.h>
#include <limits.h>

#include <embox/cmd.h>

#include <fs/dvfs.h>
#include <fs/inode.h>
#include <fs/inode_operation.h>
#include <fs/fs_driver.h>
#include <fs/super_block.h>
#include <fs/dir_context.h>
#include <fs/file_desc.h>
#include <fs/file_operation.h>

#define BINFS_NAME "binfs"


extern struct file_operations binfs_fops;

extern int binfs_destroy_inode(struct inode *inode);
struct super_block_operations binfs_sbops = {
	.open_idesc    = dvfs_file_open_idesc,
	.destroy_inode = binfs_destroy_inode,
};

extern int binfs_fill_sb(struct super_block *sb, const char *source);
static const struct fs_driver binfs_driver = {
	.name      = "binfs",
	.fill_sb   = binfs_fill_sb,
};

ARRAY_SPREAD_DECLARE(const struct fs_driver *const, fs_drivers_registry);
ARRAY_SPREAD_ADD(fs_drivers_registry, &binfs_driver);

static struct auto_mount binfs_auto_mount = {
	.mount_path = "/bin",
	.fs_driver  = (struct fs_driver *)&binfs_driver,
};

ARRAY_SPREAD_DECLARE(const struct auto_mount *const, auto_mount_tab);
ARRAY_SPREAD_ADD(auto_mount_tab, &binfs_auto_mount);

