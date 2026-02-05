#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[TABLE_SIZE];
} HashTable;
HashTable* create_table() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}
int hash(int key) {
    return key % TABLE_SIZE;
}
void insert(HashTable* table, int key, int value) {
    int index = hash(key);
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}
int search(HashTable* table, int key) {
    int index = hash(key);
    Node* current = table->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1; // Not found
}
void delete(HashTable* table, int key) {
    int index = hash(key);
    Node* current = table->buckets[index];
    Node* prev = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                table->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
void free_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = table->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table);
}
int main() {
    HashTable* table = create_table();
    insert(table, 1, 10);
    insert(table, 11, 20);
    printf("Value for key 1: %d\n", search(table, 1));
    printf("Value for key 11: %d\n", search(table, 11));
    delete(table, 1);
    printf("Value for key 1 after deletion: %d\n", search(table, 1));
    free_table(table);
    return 0;
}