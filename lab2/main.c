#include <stdio.h>
#include <stdlib.h>
#include "libra.h"
#include "time.h"

int main() {
    srand(time(NULL));
    int n = 0, tend = 0, tcur = 0;
    printf("Example of correct input:\nNUMBER client1.id/client1.ta/client1.ts client2.id/client2.ta/client2.ts ....\n");
    printf("Where NUMBER - is amount of queues, client#x.id - identifier of client #x, client#x.ta and .ts are ");
    printf("his arrival and and service time respectively\n");
    if (scanf("%d", &n) < 1) {
        printf("Incorrect input. Shutting down the program.\n");
        return 0;
    }
    if (n < 1) {
        printf("Incorrect input. Shutting down the program.\n");
        return 0;
    }
    queue *arr = qarr(n);
    client cur;
    if (readclient(&cur, &tend)) {
        printf("Incorrect input. Shutting down the program.\n");
	    free(arr);
        return 0;
    }
    printf("\nCurrent time:%d", tcur);
    printqueue(arr, n);
    while (tcur < tend + 1){
        outqueue(arr, n, tcur, &tend);
        while (cur.ta == tcur) {
            inqueue(arr, n, cur);
            readclient(&cur, &tend);
            printf("\nCurrent time:%d", tcur);
            printqueue(arr, n);
        }
	    tcur++;
    }
    printf("\n");
    clear(arr, n);
    return 0;
}
