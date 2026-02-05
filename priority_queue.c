#include <stdio.h>

#define MAX 5

int pq[MAX];
int n = 0;

// Insert (simple, no sorting)
void insert() {
    if (n == MAX) {
        printf("Queue is Full\n");
        return;
    }

    printf("Enter element: ");
    scanf("%d", &pq[n]);
    printf("Element %d inserted at position %d\n", pq[n], n);
    n++;
}

// Delete (remove smallest element)
void deletePQ() {
    if (n == 0) {
        printf("Queue is Empty\n");
        return;
    }

    int min = pq[0];
    int pos = 0;

    // Find smallest element
    for (int i = 1; i < n; i++) {
        if (pq[i] < min) {
            min = pq[i];
            pos = i;
        }
    }

    printf("Deleted (highest priority): %d\n", min);

    // Shift elements
    for (int i = pos; i < n - 1; i++) {
        pq[i] = pq[i + 1];
    }

    n--;
}

// Display
void display() {
    if (n == 0) {
        printf("Queue is Empty\n");
        return;
    }

    printf("Elements: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pq[i]);
    }
    printf("The value of n = %d", n);
}

int main() {
    int choice;

    while (1) {
        printf("\n1.Insert  2.Delete  3.Display  4.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insert(); break;
            case 2: deletePQ(); break;
            case 3: display(); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
}