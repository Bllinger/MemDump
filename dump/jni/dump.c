#include <string.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <android/log.h>

#define LOG    "Blinger Say:"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__) 
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__) 
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__) 
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__) 
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__) 

int findAddr(char *libname,uint32_t *libAddrStart,int *libSize);

void startDump(char * libname)
{
	uint32_t libAddrStart;
	int libSize;
	FILE *fd;
	char lib_path[1024];
	void *buf;

	sprintf(lib_path, "/data/data/dump.so");
	if (findAddr(libname,&libAddrStart,&libSize) < 0)
	{
		/* code */
		LOGE("findAddr failue");
		exit(-1);
	}
	LOGD("libAddrStart = %x  libSize = %d lib_path = %s",libAddrStart,libSize,lib_path);
	buf = (void *)libAddrStart;

	if ((fd = fopen(lib_path, "wb+")) < 0)
	{
		/* code */
		LOGE("create file failue");
		goto _error;

	}

	if ((fwrite(buf,1, libSize, fd)) != libSize)
	{
		/* code */
		LOGE("write data failue");
		goto _error;

	}

	fclose(fd);
	LOGD("dump success!");
	return;

  _error:
  	LOGE("_error");
  	fclose(fd);
}

int findAddr(char *libname,uint32_t *libAddrStart,int *libSize)
{
	char buf[1024],*temp;
	int pid,count = 0;
	FILE *fp;
	uint32_t libAddrEnd;

	pid = getpid();

	sprintf(buf, "/proc/%d/maps", pid);

	if ((fp = fopen(buf, "r")) == NULL)
	{
		/* code */
		LOGE("open %s failue", buf);

		return -1;
	}

	while(fgets(buf, sizeof(buf), fp))
	{
		if ((strstr(buf, libname)))
		{
			/* code */
			count++;
			if (count == 1)
			{
				/* code */
				temp = strtok(buf, "-");
				*libAddrStart = strtoul(temp, NULL, 16);
				continue;
			}else if(count == 3){
				temp = strtok(buf, "-");
				temp = strtok(NULL, " ");
				libAddrEnd = strtoul(temp, NULL, 16);
				break;
			}
		}
		
	}
	*libSize = libAddrEnd - *libAddrStart;
	LOGD("libAddrStart = 0x%x  libAddrEnd = 0x%x  libSize = %d",*libAddrStart,libAddrEnd,*libSize);
	fclose(fp);
	return 0;
}