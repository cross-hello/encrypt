#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define SIZE (1024*1024)
void xor(char * con, int num, const char *key)
{
	 const int key_num=strlen(key);
	static int key_num_ro=0;
	
	int i;
	for(i=0; i<num; i++)
	{
	   con[i]=con[i] ^ key[key_num_ro++];
	   if(key_num_ro==key_num)
    	key_num_ro=0;
    }
}
int main(int argc, char ** argv)
{
   if(argc<3)
   {printf("用法： 要加密的程序  密文. \n ");
   return 0;
   }
    
	FILE *file=fopen(argv[1],"rb");
	if(file==NULL)
	{
		printf("无法找到 %s\n",argv[1]);
		return 0;
	}
	
	char * name=malloc(strlen(argv[1])+4);
	strcpy(name,"-u-");
	strcat(name,argv[1]);
	FILE *ency_file=fopen(name,"ab");
	free(name);
 
 	char * memory=(char *) malloc(SIZE*sizeof(char));
	
	fseeko64(file,0L,SEEK_END);
	_off64_t times=ftello64(file)/SIZE;
	long times_remain=ftello64(file)%SIZE;
	fseeko64(file,0L,SEEK_SET);
	 
	 long ti=time(0);
	int i;
	for(i=0;i<times;i++)
	{
		fread(memory,SIZE,1,file);
		xor(memory,SIZE,argv[2]);
		fwrite(memory,SIZE,1,ency_file);
	}
	if(times_remain)
	{
		fread(memory,times_remain,1,file);
		xor(memory,times_remain,argv[2]);
		fwrite(memory,times_remain,1,ency_file);
	}
	ti=time(0)-ti;
	printf("Using time %ldmin %lds \n",ti/60,ti%60);
	
	free(memory);
	fclose(ency_file);
	fclose(file);
	
	
	
	
return 0;
}

