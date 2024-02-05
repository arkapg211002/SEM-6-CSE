#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

void swap(int a[],int l,int m)
{
	int temp=a[l];
	a[l]=a[m];
	a[m]=temp;
}

void quick(int a[],int l,int r)
{
	int i,last,left=l,right=r;
	if(left>=right) return;
	last=left;
	swap(a,left,(left+right)/2);
	for(i=left+1;i<=right;i++)
	{
		if(a[left]>a[i]) swap(a,++last,i);	
	}
	swap(a,last,left);
	quick(a,left,last-1);
	quick(a,last+1,right);
}

void main()
{
	int fd1,fd2;
	int *a,n,i,j,temp;
	mkfifo("./myfifo2",0666);
	fd1=open("./myfifo1",O_RDONLY);
	read(fd1,&n,sizeof(int));
	printf("The size of the array is : %d\n",n);
	a=(int *)malloc(n*sizeof(int));
	//read(fd1,a,sizeof(a));
	printf("The array elements are : \n");
	for(i=0;i<n;i++)
	{
		read(fd1,&a[i],sizeof(int));
		printf("%d ",a[i]);
	}
	printf("\n");
	
	quick(a,0,n-1);
	/*
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	
	}
	*/
	
	fd2=open("./myfifo2",O_WRONLY);
	//write(fd2,a,sizeof(a));
	for(i=n-1;i>=0;i--)
	{
		write(fd2,&a[i],sizeof(int));
	}
	close(fd1);
	close(fd2);
}
