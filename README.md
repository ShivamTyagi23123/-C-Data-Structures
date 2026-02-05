<div align="center">

# ⚙️ C Data Structures & Algorithms

### Built from Scratch in Pure C

[![C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Data Structures](https://img.shields.io/badge/Topic-Data%20Structures-purple?style=for-the-badge)](https://en.wikipedia.org/wiki/Data_structure)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

**10 implementations** covering stacks, queues, linked lists, trees, and hash tables — all menu-driven with interactive CLI interfaces.

</div>

---

## 📂 What's Inside

| # | File | Data Structure | Lines | Key Concepts |
|---|------|----------------|-------|-------------|
| 1 | [`stack.c`](#-1-stack) | Stack (Array-based) | 73 | LIFO, Overflow/Underflow, `top` pointer |
| 2 | [`queue.c`](#-2-queue) | Queue (Array-based) | 77 | FIFO, `front`/`rear` pointers, Enqueue/Dequeue |
| 3 | [`circular_queue.c`](#-3-circular-queue) | Circular Queue | 88 | Modulo wrapping, Space reuse, `(rear+1)%MAX` |
| 4 | [`priority_queue.c`](#-4-priority-queue) | Priority Queue | 79 | Min-priority deletion, Linear scan for minimum |
| 5 | [`header_list.c`](#-5-header-linked-list) | Header Linked List | 129 | Dummy header node, Insert/Delete at both ends |
| 6 | [`generic_list.c`](#-6-generic-linked-list) | Generic Linked List | 157 | `void*` pointers, Type-tagged nodes, Multi-type storage |
| 7 | [`BST.c`](#-7-binary-search-tree) | Binary Search Tree | 164 | Recursive insert/delete, 3 traversals, `findMin` |
| 8 | [`chaining.c`](#-8-hash-table--chaining) | Hash Table (Chaining) | 13 | Separate chaining, Linked list buckets, `key % SIZE` |
| 9 | [`linearprobing.c`](#-9-hash-table--linear-probing) | Hash Table (Open Addressing) | 77 | Linear probing, Collision resolution, `(index+1)%SIZE` |

---

## 🚀 How to Compile & Run

Every file is a standalone program. Compile and run any file individually:

```bash
gcc stack.c -o stack
./stack
```

**On Windows:**
```bash
gcc stack.c -o stack.exe
stack.exe
```

> **Requirements:** Any C compiler (GCC, Clang, MSVC). No external libraries needed — only `stdio.h` and `stdlib.h`.

---

---

## 📚 1. Stack

**File:** `stack.c` · **73 lines** · Array-based implementation

### What is a Stack?
A **LIFO** (Last In, First Out) data structure — like a stack of plates. You can only add/remove from the **top**.

```
PUSH 10, PUSH 20, PUSH 30:

    |  30  |  ← top (last in, first out)
    |  20  |
    |  10  |
    |______|

POP → removes 30 (the top element)
```

### Operations

| Operation | What it does | Time |
|-----------|-------------|------|
| `push()` | Add element to top | O(1) |
| `pop()` | Remove element from top | O(1) |
| `display()` | Print all elements (top → bottom) | O(n) |

### Key Code
```c
#define MAX 5
int stack[MAX];
int top = -1;           // -1 means stack is empty

void push() {
    if (top >= MAX - 1)  // Stack overflow check
        printf("stack overflow\n");
    else {
        top = top + 1;
        scanf("%d", &stack[top]);
    }
}

void pop() {
    if (top == -1)       // Stack underflow check
        printf("stack is underflow\n");
    else
        top = top - 1;
}
```

### Key Points
- **Overflow** → trying to push when `top == MAX - 1` (stack is full)
- **Underflow** → trying to pop when `top == -1` (stack is empty)
- `top = -1` is the initial state (empty stack)
- Array-based: fixed size of `MAX = 5`

---

## 📚 2. Queue

**File:** `queue.c` · **77 lines** · Array-based implementation

### What is a Queue?
A **FIFO** (First In, First Out) data structure — like a line at a store. First person in line gets served first.

```
ENQUEUE 10, 20, 30:

    front                rear
      ↓                   ↓
    | 10 | 20 | 30 |  |  |

DEQUEUE → removes 10 (the front element)
```

### Operations

| Operation | What it does | Time |
|-----------|-------------|------|
| `en_queue()` | Add element at rear | O(1) |
| `de_queue()` | Remove element from front | O(1) |
| `display()` | Print all elements (front → rear) | O(n) |

### Key Code
```c
int queue[MAX];
int rear = -1;
int front = -1;

void en_queue() {
    if (rear == MAX - 1)      // Queue full
        printf("queue overflow\n");
    else if (rear == -1) {    // First element
        rear = front = 0;
        scanf("%d", &queue[rear]);
    } else {
        rear = rear + 1;
        scanf("%d", &queue[rear]);
    }
}
```

### Key Points
- Uses two pointers: `front` (where to remove) and `rear` (where to add)
- Both start at `-1` (empty queue)
- **Problem:** Once `rear` reaches `MAX - 1`, queue is "full" even if front elements were dequeued — wasted space. **Circular Queue solves this.**

---

## 📚 3. Circular Queue

**File:** `circular_queue.c` · **88 lines** · Fixes the space-waste problem

### What makes it "circular"?
When `rear` reaches the end of the array, it **wraps around** to the beginning using the modulo operator: `rear = (rear + 1) % MAX`.

```
Regular Queue (wasted space):     Circular Queue (space reused):
    [_, _, 30, 40, 50]  FULL!        [60, _, 30, 40, 50]  rear wraps back!
     ↑  ↑                             ↑      ↑
   wasted                           rear    front
```

### Key Code
```c
void en_queue() {
    // Full condition: front and rear are adjacent (circularly)
    if ((front == 0 && rear == MAX-1) || (front > 0 && rear == front-1)) {
        printf("queue overflow\n");
    }
    else {
        rear = (rear + 1) % MAX;    // Wrap around!
        scanf("%d", &queue[rear]);
    }
}

void de_queue() {
    front = (front + 1) % MAX;      // Wrap around!
}
```

### Key Points
- **Full condition:** `(front == 0 && rear == MAX-1)` OR `(rear == front - 1)`
- Uses `% MAX` for both enqueue and dequeue to wrap around
- No wasted space — dequeued positions can be reused
- Same O(1) operations as regular queue but more space-efficient

---

## 📚 4. Priority Queue

**File:** `priority_queue.c` · **79 lines** · Unordered array with min-priority deletion

### What is a Priority Queue?
Like a regular queue, but elements are removed based on **priority** (smallest value = highest priority), not insertion order.

```
Insert: 50, 10, 30, 20

Array: [50, 10, 30, 20]

Delete → scans for minimum → removes 10 (highest priority)
Array after deletion: [50, 30, 20]
```

### Operations

| Operation | What it does | Time |
|-----------|-------------|------|
| `insert()` | Add element at the end | O(1) |
| `deletePQ()` | Find & remove smallest element | O(n) |
| `display()` | Print all elements | O(n) |

### Key Code
```c
void deletePQ() {
    int min = pq[0], pos = 0;

    // Find smallest element (linear scan)
    for (int i = 1; i < n; i++) {
        if (pq[i] < min) {
            min = pq[i];
            pos = i;
        }
    }

    // Shift elements to fill the gap
    for (int i = pos; i < n - 1; i++)
        pq[i] = pq[i + 1];

    n--;
}
```

### Key Points
- **Unordered insert** (O(1)) + **ordered delete** (O(n) — scans for min)
- Alternative approach: ordered insert (O(n)) + O(1) delete
- A **heap-based** priority queue would give O(log n) for both operations
- Smallest value = highest priority in this implementation

---

## 📚 5. Header Linked List

**File:** `header_list.c` · **129 lines** · Singly linked list with a dummy header node

### What is a Header Node?
A **dummy node** at the beginning of the list that doesn't hold real data. It simplifies insert/delete logic because `head` never changes — you always work with `head->next`.

```
Without header:  head → [10] → [20] → [30] → NULL
                 (head changes on insert/delete at beginning)

With header:     head → [HEADER] → [10] → [20] → [30] → NULL
                 (head NEVER changes — always points to header)
```

### Operations

| Operation | What it does | Time |
|-----------|-------------|------|
| `ins_beg()` | Insert after header node | O(1) |
| `ins_end()` | Insert at the end | O(n) |
| `del_beg()` | Delete first real node (after header) | O(1) |
| `del_end()` | Delete last node | O(n) |
| `traverse()` | Print all nodes (skips header) | O(n) |

### Key Code
```c
// Header node created in main()
head = (struct node*)malloc(sizeof(struct node));
head->next = NULL;   // Header node — no real data

// Insert at beginning — simply link after header
void ins_beg(struct node *new1) {
    new1->next = head->next;
    head->next = new1;
}

// Traverse — start from head->next (skip header)
void traverse() {
    struct node *temp = head->next;  // Skip the header!
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}
```

### Key Points
- Header node is allocated in `main()` and **never deleted**
- Insert/delete at beginning is simpler — no need to update `head`
- Traverse starts from `head->next` to skip the dummy node
- Empty list check: `head->next == NULL`

---

## 📚 6. Generic Linked List

**File:** `generic_list.c` · **157 lines** · Stores **int, float, and char** in the same list

### What makes it "generic"?
Each node uses a `void*` pointer for data, allowing it to store **any data type**. A `type` field tracks what kind of data each node holds.

```
Node structure:
    ┌──────┬──────┬──────┐
    │ data │ type │ next │
    │ void*│  int │  *   │
    └──────┴──────┴──────┘

Example list:
    [42 (INT)] → [3.14 (FLOAT)] → ['A' (CHAR)] → NULL
```

### Key Code
```c
#define INT 1
#define FLOAT 2
#define CHAR 3

struct node {
    void *data;    // Can point to ANY type
    int type;      // Remembers what type it is
    struct node *next;
};

// Storing different types
if (datatype == INT) {
    int *p = (int*)malloc(sizeof(int));
    scanf("%d", p);
    new1->data = p;
}
else if (datatype == FLOAT) {
    float *p = (float*)malloc(sizeof(float));
    scanf("%f", p);
    new1->data = p;
}

// Printing requires type-checking and casting
if (temp->type == INT)
    printf("%d ", *(int*)temp->data);
else if (temp->type == FLOAT)
    printf("%.2f ", *(float*)temp->data);
else if (temp->type == CHAR)
    printf("%c ", *(char*)temp->data);
```

### Key Points
- `void*` is C's way of doing "generics" — it can point to any type
- Must **cast** back to the original type when reading: `*(int*)temp->data`
- Each node's `data` is separately `malloc`'d — must be `free()`'d individually
- `del_beg()` and `del_end()` free both the data pointer AND the node

---

## 🌳 7. Binary Search Tree

**File:** `BST.c` · **164 lines** · Full BST with insert, delete (all 3 cases), and 3 traversals

### What is a BST?
A tree where for every node: **left child < node < right child**. This property makes searching very fast.

```
Insert: 50, 30, 70, 20, 40, 60, 80

            50
           /  \
         30    70
        / \   / \
      20  40 60  80

Inorder:   20 30 40 50 60 70 80  (sorted!)
Preorder:  50 30 20 40 70 60 80  (root first)
Postorder: 20 40 30 60 80 70 50  (root last)
```

### Operations

| Operation | What it does | Time (avg) | Time (worst) |
|-----------|-------------|----------|------------|
| `insert()` | Insert preserving BST property | O(log n) | O(n) |
| `deleteNode()` | Delete with all 3 cases handled | O(log n) | O(n) |
| `inorder()` | Left → Root → Right traversal | O(n) | O(n) |
| `preorder()` | Root → Left → Right traversal | O(n) | O(n) |
| `postorder()` | Left → Right → Root traversal | O(n) | O(n) |

### Deletion — The 3 Cases

```
Case 1: NO children (leaf node)
    Simply remove the node → return NULL

Case 2: ONE child
    Replace the node with its child → free the node

Case 3: TWO children (hardest!)
    1. Find the inorder successor (smallest node in the right subtree)
    2. Copy its value to the current node
    3. Delete the inorder successor from the right subtree
```

### Key Code
```c
// Insert — recursive
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);         // Base case: create new node
    if (data < root->data)
        root->left = insert(root->left, data);    // Go left
    else if (data > root->data)
        root->right = insert(root->right, data);  // Go right
    return root;
}

// Find minimum — used for Case 3 deletion
struct Node* findMin(struct Node* root) {
    while (root->left != NULL)
        root = root->left;               // Keep going left
    return root;
}

// Delete — handles all 3 cases
struct Node* deleteNode(struct Node* root, int key) {
    // ... navigate to the node ...
    // Case 1: No children
    if (root->left == NULL && root->right == NULL) {
        free(root);
        return NULL;
    }
    // Case 3: Two children
    struct Node* temp = findMin(root->right);  // Inorder successor
    root->data = temp->data;                    // Copy value
    root->right = deleteNode(root->right, temp->data);  // Delete successor
}
```

### Key Points
- **Inorder traversal** of a BST always gives **sorted** output
- Worst case O(n) happens when the tree becomes a linked list (all inserts in sorted order)
- A **balanced BST** (AVL, Red-Black) guarantees O(log n) operations
- `findMin` goes **as far left as possible** — the leftmost node is the smallest

---

## #️⃣ 8. Hash Table — Chaining

**File:** `chaining.c` · **13 lines** · Compact implementation using separate chaining

### What is Chaining?
When two keys hash to the **same index** (collision), they're stored in a **linked list** at that index.

```
Hash function: key % 10

Insert: 1, 11, 21, 2

Index 0: → NULL
Index 1: → [1] → [11] → [21] → NULL   (all hash to 1 % 10 = 1)
Index 2: → [2] → NULL
Index 3: → NULL
...
```

### Operations

| Operation | What it does | Time (avg) | Time (worst) |
|-----------|-------------|----------|------------|
| `i()` (insert) | Add key-value pair at head of chain | O(1) | O(1) |
| `s()` (search) | Walk the chain at `hash(key)` | O(1) | O(n) |
| `d()` (delete) | Find and unlink node from chain | O(1) | O(n) |
| `p()` (print) | Display all buckets | O(n + m) | — |

### Key Concepts
- **Hash function:** `key % TABLE_SIZE` — maps any key to an index 0–9
- **Collision:** When two different keys map to the same index
- **Chaining:** Each bucket is a linked list — collisions just add to the list
- Average O(1) assumes good hash distribution

---

## #️⃣ 9. Hash Table — Linear Probing

**File:** `linearprobing.c` · **77 lines** · Open addressing collision resolution

### What is Linear Probing?
When a collision occurs, instead of using a linked list, we **check the next slot**, then the next, until we find an empty one.

```
Hash function: key % 10

Insert key 1 → index 1  ✓ (empty)
Insert key 11 → index 1 → COLLISION → try index 2 → ✓ (empty)
Insert key 2 → index 2  → COLLISION → try index 3 → ✓ (empty)

Table:
Index 0: [empty]
Index 1: key=1,  value=10
Index 2: key=11, value=20   (probed from index 1)
Index 3: key=2,  value=30   (probed from index 2)
```

### Key Code
```c
void insert(HashTable* hash_table, int key, int value) {
    int index = hash(key);

    // Linear probing: keep checking next slot
    while (hash_table->table[index] != NULL) {
        if (hash_table->table[index]->key == key) {
            hash_table->table[index]->value = value; // Update existing
            return;
        }
        index = (index + 1) % TABLE_SIZE;  // Move to next slot (wrap around)
    }

    // Found empty slot — insert here
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->key = key;
    new_entry->value = value;
    hash_table->table[index] = new_entry;
}
```

### Key Points
- **No linked lists** — all data stored directly in the array
- Collision resolution: `index = (index + 1) % TABLE_SIZE`
- **Clustering problem:** consecutive occupied slots slow down operations
- Search stops when it finds an empty slot (assuming no deletion gaps)
- Uses `struct Entry { int key; int value; }` — stores key-value pairs

### Chaining vs Linear Probing

| Property | Chaining | Linear Probing |
|----------|----------|---------------|
| **Collision handling** | Linked list at each bucket | Check next slot |
| **Extra memory** | Linked list nodes (pointers) | No extra — uses the array |
| **Clustering** | No clustering | Primary clustering problem |
| **Load factor > 1** | ✅ Works (chains grow) | ❌ Cannot exceed 100% |
| **Cache performance** | Poor (pointer chasing) | Good (contiguous memory) |
| **Deletion** | Simple (unlink node) | Tricky (leaves gaps) |

---

---

## 🔑 Complexity Summary

### Linear Data Structures

| Data Structure | Insert | Delete | Search | Space |
|---------------|--------|--------|--------|-------|
| **Stack** | O(1) | O(1) | O(n) | O(n) |
| **Queue** | O(1) | O(1) | O(n) | O(n) |
| **Circular Queue** | O(1) | O(1) | O(n) | O(n) |
| **Priority Queue** | O(1) | O(n) | O(n) | O(n) |
| **Linked List** | O(1)† / O(n)‡ | O(1)† / O(n)‡ | O(n) | O(n) |

> † at beginning · ‡ at end

### Non-Linear / Hashing

| Data Structure | Insert | Delete | Search | Space |
|---------------|--------|--------|--------|-------|
| **BST (average)** | O(log n) | O(log n) | O(log n) | O(n) |
| **BST (worst)** | O(n) | O(n) | O(n) | O(n) |
| **Hash Table (average)** | O(1) | O(1) | O(1) | O(n) |
| **Hash Table (worst)** | O(n) | O(n) | O(n) | O(n) |

---

## 💡 Key C Concepts Used

### Dynamic Memory Allocation
```c
struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));  // Allocate
free(newNode);                                                     // Deallocate
```
- `malloc()` allocates memory on the **heap**
- Always `free()` when done to prevent **memory leaks**
- Returns `NULL` if allocation fails

### Pointers & Structs
```c
struct Node {
    int data;
    struct Node *next;     // Self-referential — points to another Node
};

root->left = insert(root->left, data);  // Arrow operator for pointer to struct
```

### `void*` — Generic Pointer
```c
void *data;                // Can point to ANY type
*(int*)data;               // Cast back to int before reading
*(float*)data;             // Cast back to float
```

### Modulo for Wrapping
```c
rear = (rear + 1) % MAX;          // Circular queue wrap-around
index = (index + 1) % TABLE_SIZE; // Hash table linear probing
```

---

## 📁 Repository Structure

```
C programming/
├── stack.c              ← Stack (LIFO, array-based)
├── queue.c              ← Queue (FIFO, array-based)
├── circular_queue.c     ← Circular Queue (modulo wrapping)
├── priority_queue.c     ← Priority Queue (min-priority)
├── header_list.c        ← Header Linked List (dummy head node)
├── generic_list.c       ← Generic Linked List (void* multi-type)
├── BST.c                ← Binary Search Tree (full CRUD + traversals)
├── chaining.c           ← Hash Table — Separate Chaining
├── linearprobing.c      ← Hash Table — Linear Probing
└── README.md            ← This file
```

---

<div align="center">

### Built with ⚙️ Pure C | No External Libraries

**Made by [Shivam Tyagi](https://github.com/ShivamTyagi23123)**

</div>
