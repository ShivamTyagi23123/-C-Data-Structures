#include <stdlib.h>
#include <stdio.h>
#define TABLE_SIZE 10
typedef struct {
    int key;
    int value;
} Entry;
typedef struct {
    Entry* table[TABLE_SIZE];
} HashTable;
HashTable* create_table() {
    HashTable* hash_table = (HashTable*)malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table->table[i] = NULL;
    }
    return hash_table;
}
int hash(int key) {
    return key % TABLE_SIZE;
}
void insert(HashTable* hash_table, int key, int value) {
    int index = hash(key);
    while (hash_table->table[index] != NULL) {
        if (hash_table->table[index]->key == key) {
            hash_table->table[index]->value = value; // Update existing key
            return;
        }
        index = (index + 1) % TABLE_SIZE; // Linear probing
    }
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->key = key;
    new_entry->value = value;
    hash_table->table[index] = new_entry;
}
int search(HashTable* hash_table, int key) {
    int index = hash(key);
    while (hash_table->table[index] != NULL) {
        if (hash_table->table[index]->key == key) {
            return hash_table->table[index]->value;
        }
        index = (index + 1) % TABLE_SIZE; // Linear probing
    }
    return -1; // Not found
}
void delete(HashTable* hash_table, int key) {
    int index = hash(key);
    while (hash_table->table[index] != NULL) {
        if (hash_table->table[index]->key == key) {
            free(hash_table->table[index]);
            hash_table->table[index] = NULL; // Mark as deleted
            return;
        }
        index = (index + 1) % TABLE_SIZE; // Linear probing
    }
}
void free_table(HashTable* hash_table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hash_table->table[i] != NULL) {
            free(hash_table->table[i]);
        }
    }
    free(hash_table);
}
int main() {
    HashTable* hash_table = create_table();
    insert(hash_table, 1, 10);
    insert(hash_table, 11, 20); // Collision with key 1
    insert(hash_table, 2, 30);
    printf("Value for key 1: %d\n", search(hash_table, 1)); // Should print 10
    printf("Value for key 11: %d\n", search(hash_table, 11)); // Should print 20
    printf("Value for key 2: %d\n", search(hash_table, 2)); // Should print 30
    delete(hash_table, 1);
    printf("Value for key 1 after deletion: %d\n", search(hash_table, 1)); // Should print -1
    free_table(hash_table);
    return 0;
}
