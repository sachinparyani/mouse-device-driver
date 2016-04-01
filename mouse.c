#include<linux/module.h>
#include<linux/string.h>
#include<linux/fs.h>
#include<asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Device Driver Demo");
MODULE_AUTHOR("sachin");

static char msg[100]={0};
static short readPos=0;
static int times=0;

static int dev_open(struct inode *,struct file *);
static int dev_rls(struct inode *,struct file *);
static ssize_t dev_read(struct file *,char *, size_t,loff_t *);
static  ssize_t dev_write(struct file *,const char *,size_t,loff_t *);
struct file* file_open(const char* path, int flags, int rights) {
    struct file* filp = NULL;
    mm_segment_t oldfs;
    int err = 0;

    oldfs = get_fs();
    set_fs(get_ds());
    filp = filp_open(path, flags, rights);
    set_fs(oldfs);
    if(IS_ERR(filp)) {
        err = PTR_ERR(filp);
        return NULL;
    }
    return filp;
}

int file_read(struct file* file, unsigned long long offset, unsigned char* data, unsigned int size) {
    mm_segment_t oldfs;
    int ret;

    oldfs = get_fs();
    set_fs(get_ds());

    ret = vfs_read(file, data, size, &offset);

    set_fs(oldfs);
    return ret;
}   

static struct file_operations fops =
{
    .read = dev_read,
    .open = dev_open,
    .write= dev_write,
    .release= dev_rls,
};
int init_module(void)
{
         int t = register_chrdev(90,"ourDev",&fops);
      if(t<0) printk(KERN_ALERT "device registration failed .. \n");
      else printk(KERN_ALERT "device registered.. \n");
      return t;
}

void cleanup_module(void)
{
        unregister_chrdev(90,"ourDev");
}
static int dev_open(struct inode *inod,struct file *fil)
{
         times++;
         printk(KERN_ALERT "device opened %d times\n",times);
         return 0;
}

static ssize_t dev_read(struct file *filp, char *buff,size_t len,loff_t *off)
{
       /*short count =0;
       while(len && (msg[readPos]!=0))
       {
             copy_to_user(buff,msg+readPos,1);
             buff++;
             count++;
             len--;
             readPos++;
       }
       return count;
       */
       struct file *f;
       short count=0;
       f = file_open("/dev/input/mice",0, 0);
       if(f == NULL){
        	printk(KERN_ALERT "filp_open error!!.\n");
        	count =0;
        	return count;
        	}
       else 
       {	
       	    //printk(KERN_ALERT "filp_open error!!.\n");
       		count = file_read(f,0,buff,1);
       		//f->f_op->read(f, buff, 1, &f->f_pos);
       		return count;
       }
       
       
}

static ssize_t dev_write(struct file *filp,const char *buff,size_t len,loff_t *off)
{
    short ind = len-1;
    short count=0;
    memset(msg,0,100);
    readPos=0;
    while(len>0)
    {
         copy_from_user(msg+count,buff+ind,1);
         ind--;
         count++;
         len--;
    }
     return count;
}


static int dev_rls(struct inode *inod,struct file *fil)
{
     printk(KERN_ALERT "device closed\n");
return 0;
}   











