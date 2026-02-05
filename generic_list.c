#include<stdio.h>
#include<stdlib.h>

#define INT 1
#define FLOAT 2
#define CHAR 3

struct node{
    void *data;          // generic data pointer
    int type;            // to store type of data
    struct node *next;
};

struct node *head = NULL;
struct node *temp = NULL;

void ins_beg(struct node*);
void ins_end(struct node*);
void del_beg();
void del_end();
void traverse();

int main(){
    int choice, datatype;
    struct node *new1;

    while(1){
        printf("\n1. ins_beg\n2. ins_end\n3. del_beg\n4. del_end\n5. traverse\n6. exit\n");
        scanf("%d",&choice);

        switch(choice){

            case 1:
            case 2:
                new1 = (struct node*)malloc(sizeof(struct node));
                new1->next = NULL;

                printf("Enter data type (1-int, 2-float, 3-char): ");
                scanf("%d",&datatype);
                new1->type = datatype;

                if(datatype == INT){
                    int *p = (int*)malloc(sizeof(int));
                    printf("Enter integer: ");
                    scanf("%d", p);
                    new1->data = p;
                }
                else if(datatype == FLOAT){
                    float *p = (float*)malloc(sizeof(float));
                    printf("Enter float: ");
                    scanf("%f", p);
                    new1->data = p;
                }
                else if(datatype == CHAR){
                    char *p = (char*)malloc(sizeof(char));
                    printf("Enter char: ");
                    scanf(" %c", p);
                    new1->data = p;
                }

                if(choice == 1)
                    ins_beg(new1);
                else
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

            default:
                exit(1);
        }
    }
}

void ins_beg(struct node *new1){
    if(head == NULL)
        head = new1;
    else{
        new1->next = head;
        head = new1;
    }
}

void ins_end(struct node *new1){
    temp = head;
    if(head == NULL)
        head = new1;
    else{
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = new1;
    }
}

void del_beg(){
    struct node *temp = head;
    if(head == NULL)
        printf("No item to delete\n");
    else{
        head = head->next;
        free(temp->data);   // free actual data
        free(temp);
    }
}

void del_end(){
    struct node *temp = head;
    struct node *prev = head;

    if(head == NULL){
        printf("No item to delete\n");
        return;
    }

    while(temp->next != NULL){
        prev = temp;
        temp = temp->next;
    }

    if(temp == head)
        head = NULL;
    else
        prev->next = NULL;

    free(temp->data);
    free(temp);
}

void traverse(){
    temp = head;

    if(head == NULL){
        printf("No item to traverse\n");
        return;
    }

    while(temp != NULL){
        if(temp->type == INT)
            printf("%d ", *(int*)temp->data);
        else if(temp->type == FLOAT)
            printf("%.2f ", *(float*)temp->data);
        else if(temp->type == CHAR)
            printf("%c ", *(char*)temp->data);

        temp = temp->next;
    }
}