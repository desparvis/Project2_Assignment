#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 20

// Structure to hold job information
typedef struct {
    char id;
    int priority;
} Job;

// Global heap array (1-based indexing)
Job heap[MAX_SIZE];
int heap_size = 0;

// Helper functions
int parent(int i) { return i / 2; }
int left(int i)   { return 2 * i; }
int right(int i)  { return 2 * i + 1; }

// Swap two jobs in the heap
void swap(Job* a, Job* b) {
    Job temp = *a;
    *a = *b;
    *b = temp;
}

// Print current heap state (level-order / array view)
void print_heap(const char* message) {
    printf("\n%s (size = %d):\n", message, heap_size);
    if (heap_size == 0) {
        printf("   (empty)\n");
        return;
    }

    printf("   Index: ");
    for (int i = 1; i <= heap_size; i++) {
        printf("%2d  ", i);
    }
    printf("\n");

    printf("   Job ID: ");
    for (int i = 1; i <= heap_size; i++) {
        printf(" %c  ", heap[i].id);
    }
    printf("\n");

    printf(" Priority: ");
    for (int i = 1; i <= heap_size; i++) {
        printf("%3d ", heap[i].priority);
    }
    printf("\n\n");
}

// Max-Heapify (assumes subtrees are already max-heaps)
void max_heapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l <= heap_size && heap[l].priority > heap[largest].priority)
        largest = l;
    if (r <= heap_size && heap[r].priority > heap[largest].priority)
        largest = r;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        max_heapify(largest);
    }
}

// Build max-heap from unordered array (bottom-up)
void build_max_heap() {
    // Start from last non-leaf node and go up to root
    for (int i = heap_size / 2; i >= 1; i--) {
        max_heapify(i);
    }
}

// Insert a new job and maintain max-heap property
void insert_job(char id, int priority) {
    if (heap_size >= MAX_SIZE - 1) {
        printf("Heap overflow!\n");
        return;
    }

    heap_size++;
    int i = heap_size;

    heap[i].id = id;
    heap[i].priority = priority;

    // Fix heap property (bubble up)
    while (i > 1 && heap[parent(i)].priority < heap[i].priority) {
        swap(&heap[i], &heap[parent(i)]);
        i = parent(i);
    }
}

// Remove specific job by value (priority 100 in this case)
int remove_job_by_priority(int target_priority) {
    int idx = -1;

    // Find the job with priority 100
    for (int i = 1; i <= heap_size; i++) {
        if (heap[i].priority == target_priority) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Job with priority %d not found.\n", target_priority);
        return 0;
    }

    // Move last element to this position
    heap[idx] = heap[heap_size];
    heap_size--;

    // Restore heap property
    if (idx <= heap_size) {
        max_heapify(idx);
    }

    return 1;
}

int main() {
    // Original priorities
    int priorities[] = {42, 17, 93, 28, 65, 81, 54, 60, 99, 73, 88};
    int n = sizeof(priorities) / sizeof(priorities[0]);

    printf("*** Initial jobs ***\n");

    // 1. Fill heap array (1-based) with jobs
    heap_size = n;
    char id = 'A';
    for (int i = 0; i < n; i++) {
        heap[i+1].id = id++;
        heap[i+1].priority = priorities[i];
    }

    print_heap("Before heapify (array insertion order)");

    // 2. Convert to max-heap
    build_max_heap();
    print_heap("After build_max_heap() → valid Max-Heap");

    // 3. Insert urgent job with priority 100
    printf("\n*** Inserting urgent job with priority 100 ***\n");
    insert_job('L', 100);   // L = next letter after K
    print_heap("After inserting priority 100");

    // 4. Remove the job with priority 100 (aborted)
    printf("\n*** Aborting urgent job (remove priority 100) ***\n");
    remove_job_by_priority(100);
    print_heap("After removing priority 100 and re-heapify");

    printf("Done.\n");
    return 0;
}