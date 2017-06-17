
#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#include <asm/uaccess.h>

#define DRIVER_NAME "DVDD"

MODULE_LICENSE("GPL");

/* variable declarations */
static int major;
static char message[256] = {0};
static short msg_size;
static struct class* ebbchar_class = NULL;
static struct device* ebbchar_device = NULL;

/* function declarations */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

/* file operations structure */
static struct file_operations vuln_dev_driver_fops =
{
    .open       = device_open,
    .read       = device_read,
    .write      = device_write,
    .release    = device_release,
};

static int dvdd_init(void)
{
    printk(KERN_ALERT "Damn Vulnerable Device Driver loaded!\n");

    major = register_chrdev(0, DRIVER_NAME, &vuln_dev_driver_fops);
    if (major < 0) {
        printk(KERN_ALERT "Failed to register a major number for us!\n");
        return major;
    }
    ebbchar_class = class_create(THIS_MODULE, "ebb");
    if (IS_ERR(ebbchar_class)) {
        unregister_chrdev(major, DRIVER_NAME);
        printk(KERN_ALERT "Failed to register device class!\n");
        return PTR_ERR(ebbchar_class);
    }
    ebbchar_device = device_create(ebbchar_class, 0,
                                MKDEV(major, 0), 0, DRIVER_NAME);
    if (IS_ERR(ebbchar_device)) {
        class_destroy(ebbchar_class);
        unregister_chrdev(major, DRIVER_NAME);
        printk(KERN_ALERT "Failed to create device!\n");
        return PTR_ERR(ebbchar_device);
    }
    printk(KERN_INFO "Damn Vulnerable Device Driver created.\n");
    return 0;
}

static void dvdd_exit(void)
{
    device_destroy(ebbchar_class, MKDEV(major, 0));
    class_unregister(ebbchar_class);
    class_destroy(ebbchar_class);
    unregister_chrdev(major, DRIVER_NAME);
    printk(KERN_INFO "Damn Vulnerable Device Driver has been removed!\n");
}

static int device_open(struct inode *inode_ptr, struct file *file_ptr)
{
    printk(KERN_INFO "Damn Vulnerable Device opened!\n");
    return 0;
}

static ssize_t device_read(struct file *file_ptr, char *buffer, size_t len,
        loff_t *offset)
{
    int errc;
    
    errc = copy_to_user(buffer, message, msg_size);
    if (!errc) {
        printk(KERN_INFO "Damn Vulnerable Device Driver: %d chars sent to the user\n", msg_size);
        return (msg_size=0);
    } else {
        printk(KERN_INFO "Damn Vulnerable Device Driver: Failed to send data to the user\n");
        return -EFAULT;
    }
}

static ssize_t device_write(struct file *file_ptr, const char *buff, size_t len,
        loff_t *offset)
{
    if (strlen(buff) < 256 && strlen(buff) == len) {
        msg_size = len;
        printk(KERN_INFO "Damn Vulnerable Device Driver: User-input\
                passed security check!\n");
        sprintf(message, buff, len);
        printk(KERN_INFO "Damn Vulnerable Device Driver: Data successfully\
                copied from user to device.\n");
        printk(KERN_INFO "\t%s->%s\n", buff, message);
        return len;
    } else {
        return 0;
    }
}

static int device_release(struct inode *inode_ptr, struct file *file_ptr)
{
    printk(KERN_INFO "Damn Vulnerable Device Driver Closed\n");
    printk(KERN_INFO "Do not forget to remove the driver!\n");
    return 0;
}

module_init(dvdd_init);
module_exit(dvdd_exit);

