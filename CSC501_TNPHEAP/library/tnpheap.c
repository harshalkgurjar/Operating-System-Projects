#include <npheap/tnpheap_ioctl.h>
#include <npheap/npheap.h>
#include <npheap.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <signal.h>
#include <malloc.h>
#include <string.h>

struct my_tnpheap
{
    void *mapping;
    void *buffer;
    __u64 version;
    __u64 offset;
    __u64 size;
    struct my_tnpheap *next
};


struct tnpheap_cmd cmd;
struct my_tnpheap *start = NULL;

__u64 tnpheap_get_version(int npheap_dev, int tnpheap_dev, __u64 offset)
{
    __u64 ver; 
    struct tnpheap_cmd vercmd;
    vercmd.offset = offset;
    ver = ioctl(tnpheap_dev,TNPHEAP_IOCTL_GET_VERSION,&vercmd);
    return var;
}



int tnpheap_handler(int sig, siginfo_t *si)
{
    return 0;
}


void *tnpheap_alloc(int npheap_dev, int tnpheap_dev, __u64 offset, __u64 size)
{
    __u64 ver;
    struct my_tnpheap *temp = start;
    while(temp!=NULL)
    {
        if (offset == temp->offset)
	{
            ver = tnpheap_get_version(npheap_dev,tnpheap_dev,offset); 
            printf("Object %lld already there & Current version of the object is %lld\n\n",offset,ver);
	    return temp->buffer;		
	}

	else
	{
	    temp=temp->next;
	}
    }

    printf("Object NOT there, Adding...........\n");
    struct my_tnpheap *temp2 = start;
       
    struct my_tnpheap *new_node = (struct my_tnpheap*)malloc(sizeof(struct my_tnpheap));
    new_node->mapping = (void *)npheap_alloc(npheap_dev,offset,size);
    new_node->buffer = (void *)malloc(size);
    new_node->version = tnpheap_get_version(npheap_dev,tnpheap_dev,offset);
    new_node->offset = offset;
    new_node->size = size;
    new_node->next = NULL;

    if(temp2==NULL)
    {
        printf("first object!!!!!\n");
	start = new_node;
    }
    else
    {
        while(temp2->next!=NULL)
        {
            printf("Appending to list\n");
	    temp2=temp2->next;
        }

        temp2->next = new_node;
    }
    return new_node->buffer;     
}

__u64 tnpheap_start_tx(int npheap_dev, int tnpheap_dev)
{
    return ioctl(tnpheap_dev,TNPHEAP_IOCTL_START_TX,&cmd);
}

int tnpheap_commit(int npheap_dev, int tnpheap_dev)
{
    return 0;
}

