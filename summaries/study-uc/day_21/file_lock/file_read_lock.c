#include <stdio.h>
#include <file_head.h>

int main(int args, char *argv[])
{
	struct flock r_lock;

	printf("get pid:%d\n", getpid());
	//只读打开
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		perror("error tips:");
		return -1;
	}

	//初始化锁的内容
	r_lock.l_type = F_RDLCK; //指定锁的类型
	//指定锁的区域
	r_lock.l_whence = SEEK_SET;
	r_lock.l_len = 128;
	r_lock.l_start = 0;

	//对文件加锁
	int f_lock = fcntl(fd, F_SETLK, &r_lock);
	if(f_lock == -1)
	{
		perror("error tips:");
		return -1;
	}

	printf("fcntl() sucessful...\n");
	getchar(); //方便在两个进程中测试

	//关闭文件描述符,有可能造成锁的丢失
	close(fd);
	return 0;
}
