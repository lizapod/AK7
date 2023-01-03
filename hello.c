#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>

MODULE_AUTHOR("Podvoiska Eliza <elizapodvoiska@gmail.com>");
MODULE_DESCRIPTION("Lab7");
MODULE_LICENSE("Dual BSD/GPL");

static uint myparam = 1;

struct my_data {
	struct list_head list;
	ktime_t ktime;
};

LIST_HEAD(my_list);

module_param(myparam, uint, 0644);
MODULE_PARM_DESC(myparam, "An unsigned integer, specifies how many times to write \"Hello, world \"");
static int __init hello_init(void)
{
	uint i;
	if (myparam == 0 || (myparam > 5 && myparam <= 10)) { printk(KERN_WARNING "Warning: myparam is 0 or between 5 and 10 !\n");
	} else {
		BUG_ON(myparam > 10);
	}
	
	for (i = 0; i < myparam; i++) {
		struct my_data *new = 0;
		new->ktime = ktime_get();
		list_add_tail(&new->list, &my_list);
		printk(KERN_INFO "Hello, world!\n");
	}
	return 0;
}

static void __exit hello_exit(void)
{
	struct my_data *md, *tmp;
	list_for_each_entry_safe(md, tmp, &my_list, list) {
		printk(KERN_INFO "Time: %lld\n", md->ktime);
		list_del(&md->list);
		kfree(md);
	}
}

module_init(hello_init);
module_exit(hello_exit);
