#include <stdio.h>
#include <stdlib.h>
struct Node{
    int val,key;
    struct Node *next;
};
int main(){
    while (1){
        struct Node* p = malloc(sizeof(struct Node));
        p->val = 1;
        p->key = 0;
        p->next = NULL;
    }
    return 0;
}
