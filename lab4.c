#include <stdio.h>
#include <stdlib.h>

#ifndef ERROR_OCCUR
#define ERROR_OCCUR 1
#endif // ERROR_OCCUR
#ifndef DISK_MAX_POS
#define DISK_MAX_POS 999
#endif

typedef struct displayArray{
    int *sequences;
    int totalMovement;
}display;

size_t find_in_array(int array[], size_t j, int target){
    for(size_t i=0;i!=j;++i){
        if(array[i]==target) return i;
    }
    return 0;
}

void swap(int* a, int* b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void max_heapify(int arr[], size_t start, size_t end) {
    size_t dad = start;
    size_t son = dad * 2 + 1;
    while (son <= end) {
        if (son + 1 <= end && arr[son] < arr[son + 1])
            son++;
        if (arr[dad] > arr[son])
            return;
        else {
            swap(&arr[dad], &arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void sort(int a[], size_t len){
    long long i;
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(a, i, len - 1);
    for (i = len - 1; i > 0; i--) {
        swap(&a[0], &a[i]);
        max_heapify(a, 0, i - 1);
    }
}

display* scan_alg(int initPos, int *io, size_t size){
    int *ioRequests = (int*)malloc(size * sizeof(int));
    for(size_t i=0;i!=size;++i){
        ioRequests[i]=io[i];
    }
    sort(ioRequests, size);
    size_t indexOfInitPos = find_in_array(ioRequests, size, initPos);
    if(ioRequests[indexOfInitPos]!=initPos){
        exit(1);
    }
    int j = 1;
    long long endAt = -1;
    if(size-indexOfInitPos>indexOfInitPos){
        j = -1;
        endAt = size;
    }
    display *output = (display*)malloc(sizeof(display));
    output->sequences = (int*)malloc(sizeof(int)*size);
    output->totalMovement = 0;
    int pre = 0;
    size_t k = 0;
    for(long long i=indexOfInitPos;i!=endAt;i+=j){
        if(i == size){
            i = indexOfInitPos-1;
            j = -1;
            output->totalMovement += DISK_MAX_POS - pre;
            pre = DISK_MAX_POS;
        } else if(i == -1){
            i = indexOfInitPos+1;
            j = 1;
            output->totalMovement += pre;
            pre = 0;
        }
        output->sequences[k] = ioRequests[i];
        ++k;
        output->totalMovement += abs(ioRequests[i] - pre);
        pre = ioRequests[i];
    }
    for(size_t i=0;i!=size;++i){
        printf("%d\t",output->sequences[i]);
    }
    printf("\n\n");
    return output;
}

display* c_scan_alg(int initPos, int *io, size_t size){
    int *ioRequests = (int*)malloc(size * sizeof(int));
    for(size_t i=0;i!=size;++i){
        ioRequests[i]=io[i];
    }
    sort(ioRequests, size);
    size_t indexOfInitPos = find_in_array(ioRequests, size, initPos);
    if(ioRequests[indexOfInitPos]!=initPos){
        exit(1);
    }
    int j = 1;
    if(size-indexOfInitPos>indexOfInitPos){
        j = -1;
    }
    display *output = (display*)malloc(sizeof(display));
    output->sequences = (int*)malloc(sizeof(int)*size);
    output->totalMovement = 0;
    int pre = 0;
    size_t k = 0;
    for(long long i=indexOfInitPos;i!=size&&i!=-1&&i!=indexOfInitPos;){
        output->sequences[k] = ioRequests[i];
        ++k;
        output->totalMovement += abs(ioRequests[i] - pre);
        pre = ioRequests[i];
        i+=j;
        if(i == size){
            i = 0;
            pre = 0;
        } else if(i == -1){
            i = size;
        }
    }
    return output;
}

display* c_look_alg(int initPos, int *io, size_t size){
    int *ioRequests = (int*)malloc(size * sizeof(int));
    for(size_t i=0;i!=size;++i){
        ioRequests[i]=io[i];
    }
    sort(ioRequests, size);
    size_t indexOfInitPos = find_in_array(ioRequests, size, initPos);
    if(ioRequests[indexOfInitPos]!=initPos){
        exit(1);
    }
    int j = 1;
    if(size-indexOfInitPos>indexOfInitPos){
        j = -1;
    }
    display *output = (display*)malloc(sizeof(display));
    output->sequences = (int*)malloc(sizeof(int)*size);
    output->totalMovement = 0;
    int pre = 0;
    size_t k = 0;
    for(long long i=indexOfInitPos;i!=size&&i!=-1&&i!=indexOfInitPos;){
        output->sequences[k] = ioRequests[i];
        ++k;
        output->totalMovement += abs(ioRequests[i] - pre);
        pre = ioRequests[i];
        i+=j;
        if(i == size-1){
            i = 0;
            pre = 0;
        } else if(i == 0){
            i = size-1;
        }
    }
    return output;
}

int main()
{
    int cPos = 0, ioNum = 0;
    printf("Enter Current location: ");
    scanf("%d", &cPos);
    printf("Enter the I/O Requests : ");
    scanf("%d", &ioNum);
    int i = 0, j = 0, k = ioNum + 1;
    int *requests = (int*)malloc(sizeof(int)*ioNum);
    while(i!=-1&&j!=k){
        if(scanf("%d", &i)!=1){
            break;
        }
        if(j!=ioNum) requests[j] = i;
        ++j;
    }
    if(i!=-1){
        return 1;
    }else if(j!=k){
        ioNum = j;
    }
    printf(". . .\n\n");
    display *elevator = scan_alg(cPos, requests, ioNum);
    display *circularScan = c_scan_alg(cPos, requests, ioNum);
    display *c_look = c_look_alg(cPos, requests, ioNum);
    printf("SCAN\n\n\t");
    for(int i=0;i!=ioNum;++i){
        printf("%d\t", requests[i]);
    }
    printf("\n");
    for(int i=0;i!=ioNum;++i){
        printf("%d:\t", i+1);
        for(int j=0;j!=ioNum;++j){
            if(requests[j]==elevator->sequences[i]){
                printf("#\t");
            }
            else {
                printf("\t");
            }
        }
        printf("\n");
    }
    printf("Total movements: %d\n\n", elevator->totalMovement);
    printf("C-SCAN\n\n\t");
    for(int i=0;i!=ioNum;++i){
        printf("%d\t", requests[i]);
    }
    printf("\n");
    for(int i=0;i!=ioNum;++i){
        printf("%d:\t", i+1);
        for(int j=0;j!=ioNum;++j){
            if(requests[j]==circularScan->sequences[i]){
                printf("#\t");
            }
            else {
                printf("\t");
            }
        }
        printf("\n");
    }
    printf("Total movements: %d\n\n", circularScan->totalMovement);
    printf("C-LOOK\n\n\t");
    for(int i=0;i!=ioNum;++i){
        printf("%d\t", requests[i]);
    }
    printf("\n");
    for(int i=0;i!=ioNum;++i){
        printf("%d:\t", i+1);
        for(int j=0;j!=ioNum;++j){
            if(requests[j]==c_look->sequences[i]){
                printf("#\t");
            }
            else {
                printf("\t");
            }
        }
        printf("\n");
    }
    printf("Total movements: %d\n\n", c_look->totalMovement);
    free(requests);
    free(elevator->sequences);
    free(circularScan->sequences);
    free(c_look->sequences);
    free(elevator);
    free(circularScan);
    free(c_look);
    return 0;
}
