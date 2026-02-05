#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node *next;
};

struct node *head = NULL;

// Function Prototypes
void ins_beg(struct node*);
void ins_end(struct node*);
void del_beg();
void del_end();
void traverse();

int main(){

    int choice;
    struct node *new1;

    // Create HEADER node
    head = (struct node*)malloc(sizeof(struct node));
    head->next = NULL;

    while(1){
        printf("\nEnter the choice\n");
        printf("1. Insert Beginning\n2. Insert End\n3. Delete Beginning\n4. Delete End\n5. Traverse\n6. Exit\n");
        scanf("%d",&choice);

        switch(choice){

            case 1:
                new1 = (struct node*)malloc(sizeof(struct node));
                printf("Enter data: ");
                scanf("%d",&new1->data);
                new1->next = NULL;
                ins_beg(new1);
                break;

            case 2:
                new1 = (struct node*)malloc(sizeof(struct node));
                printf("Enter data: ");
                scanf("%d",&new1->data);
                new1->next = NULL;
                ins_end(new1);
                break;

            case 3:
                del_beg();
                break;

            case 4:
                del_end();
                break;

            case 5:
                traverse();
                break;

            case 6:
                exit(0);
        }
    }
}


// ---------------- FUNCTIONS ----------------

void ins_beg(struct node *new1){
    new1->next = head->next;
    head->next = new1;
}

void ins_end(struct node *new1){
    struct node *temp = head;

    while(temp->next != NULL)
        temp = temp->next;

    temp->next = new1;
}

void del_beg(){
    struct node *temp;

    if(head->next == NULL){
        printf("No item to delete\n");
        return;
    }

    temp = head->next;
    head->next = temp->next;
    free(temp);
}

void del_end(){
    struct node *temp = head;
    struct node *temp1 = head;

    if(head->next == NULL){
        printf("No item to delete\n");
        return;
    }

    while(temp1->next != NULL){
        temp = temp1;
        temp1 = temp1->next;
    }

    temp->next = NULL;
    free(temp1);
}

void traverse(){
    struct node *temp = head->next;

    if(temp == NULL){
        printf("List is empty\n");
        return;
    }

    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}