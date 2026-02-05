#include<stdio.h>
#include<stdlib.h>
#define MAX 5

void en_queue();
void de_queue();
void display();

int queue[MAX];
int rear = -1;
int front = -1;

int main(){
	int choice;
	
	printf("===== Circular Queue Program (MAX: %d) =====\n\n", MAX);
	
	while(1){
		printf("\nEnter your choice:\n");
		printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
		printf("Choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 1:
					en_queue();
					break;
			case 2:
					de_queue();
					break;
			case 3:
					display();
					break;
			case 4:
					printf("Exiting...\n");
					exit(0);
			default:
					printf("Invalid choice! Please try again.\n");
		}
		
	}
}
void en_queue(){
	int n;
	if((front == 0 && rear == MAX-1) || (front>0 && rear==front-1)){
		printf("queue overflow\n");
	}
	else if(rear == -1){
		rear = front = 0;
		printf("enter the number: ");
		scanf("%d",&n);
		queue[rear] = n;
		printf("Enqueued %d successfully\n", n);
	}
	else{
		rear = (rear+1) % MAX;
		printf("enter the number: ");
		scanf("%d",&n);
		queue[rear] = n;
		printf("Enqueued %d successfully\n", n);
	}
}
void de_queue(){
	if(rear == -1)
		printf("queue is underflow\n");
	else{
		printf("Dequeued element: %d\n", queue[front]);
		if(front == rear)
			rear = front = -1;
		else
			front = (front + 1) % MAX;
	}
}

void display(){
	int i = front;
	if(rear == -1){
		printf("queue is empty\n");
	}
	else{
		printf("Queue elements: ");
		while(i != rear){
			printf("%d ", queue[i]);
			i = (i+1)%MAX;
		}
		printf("%d\n", queue[i]);
	}
}
