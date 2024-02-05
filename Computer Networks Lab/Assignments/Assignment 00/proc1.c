#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void main()
{
	int fd1,fd2;
	int *a,res,n,i;
	mkfifo("./myfifo1",0666);
	fd1=open("./myfifo1",O_WRONLY);
	printf("Enter the number of elements : ");
	scanf("%d",&n);
	getchar();
	write(fd1,&n,sizeof(int));
	printf("\nEnter the array elements :\n");
	a=(int *)malloc(n*sizeof(int));
	//res=(int *)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
	{
		printf("Enter the element a[%d] : ",i);
		scanf("%d",&a[i]);
		write(fd1,&a[i],sizeof(int));
	}
	//write(fd1,a,sizeof(a));

	fd2=open("./myfifo2",O_RDONLY);
	//read(fd2,res,sizeof(res));
	printf("\nThe sorted array is : \n");
	for(i=0;i<n;i++)
	{
		read(fd2,&res,sizeof(int));		
		printf("%d ",res);
	}
	printf("\n");
	close(fd1);
	close(fd2);
}
