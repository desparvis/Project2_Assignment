#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PASSENGERS 20

// Passenger structure
typedef struct {
    char name[32];
    int risk;
} Passenger;

// Global heap (1-based indexing)
Passenger heap[MAX_PASSENGERS];
int heap_size = 0;

// Helper functions
int parent(int i) { return i / 2; }
int left(int i)   { return 2 * i; }
int right(int i)  { return 2 * i + 1; }

void swap(Passenger* a, Passenger* b) {
    Passenger temp = *a;
    *a = *b;
    *b = temp;
}

// Print heap state
void print_heap(const char* title) {
    printf("\n%s (size = %d):\n", title, heap_size);
    if (heap_size == 0) {
        printf("   (empty)\n");
        return;
    }
    printf("   Pos | Name     | Risk\n");
    printf("   ----+----------+------\n");
    for (int i = 1; i <= heap_size; i++) {
        printf("   %3d | %-8s | %4d\n", i, heap[i].name, heap[i].risk);
    }
    printf("\n");
}

// Max-Heapify
void max_heapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;

    if (l <= heap_size && heap[l].risk > heap[largest].risk)
        largest = l;
    if (r <= heap_size && heap[r].risk > heap[largest].risk)
        largest = r;

    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        max_heapify(largest);
    }
}

// Build max-heap (bottom-up)
void build_max_heap() {
    for (int i = heap_size / 2; i >= 1; i--) {
        max_heapify(i);
    }
}

// Insert new passenger
void insert_passenger(const char* name, int risk) {
    if (heap_size >= MAX_PASSENGERS - 1) {
        printf("Heap full!\n");
        return;
    }

    heap_size++;
    int i = heap_size;

    strcpy(heap[i].name, name);
    heap[i].risk = risk;

    // Bubble up
    while (i > 1 && heap[parent(i)].risk < heap[i].risk) {
        swap(&heap[i], &heap[parent(i)]);
        i = parent(i);
    }
}

// Extract max (highest risk passenger)
void extract_max() {
    if (heap_size < 1) return;

    printf("Screening → %s (risk %d)\n", heap[1].name, heap[1].risk);

    // Move last to root
    heap[1] = heap[heap_size];
    heap_size--;

    if (heap_size > 0)
        max_heapify(1);
}

// Remove passenger with specific risk score (for the cleared case)
int remove_by_risk(int target_risk) {
    int idx = -1;
    for (int i = 1; i <= heap_size; i++) {
        if (heap[i].risk == target_risk) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        printf("Passenger with risk %d not found.\n", target_risk);
        return 0;
    }

    // Replace with last
    heap[idx] = heap[heap_size];
    heap_size--;

    if (idx <= heap_size)
        max_heapify(idx);

    return 1;
}

int main() {
    // Initial passengers
    const char* names[] = {"Alice", "Brian", "Chen", "Fatima", "Noah", "Sofia"};
    int risks[] = {65, 82, 91, 44, 78, 53};
    int n = 6;

    printf("*** Airport Security Checkpoint ***\n\n");

    // 1. Load initial passengers
    heap_size = n;
    for (int i = 0; i < n; i++) {
        strcpy(heap[i+1].name, names[i]);
        heap[i+1].risk = risks[i];
    }

    print_heap("Initial passengers (before heapify)");

    // 2. Build max-heap
    build_max_heap();
    print_heap("After building Max-Heap (highest risk at root)");

    // 3. Extract in priority order (screening sequence)
    printf("*** Screening order (highest risk first) ***\n");
    printf("Remaining passengers: %d\n", heap_size);
    while (heap_size > 0) {
        extract_max();
    }
    printf("\nAll initial passengers screened.\n");

    // Reset heap with original data for next part
    heap_size = n;
    for (int i = 0; i < n; i++) {
        strcpy(heap[i+1].name, names[i]);
        heap[i+1].risk = risks[i];
    }
    build_max_heap();

    print_heap("Heap restored for insertion test");

    // 4. New high-risk passenger arrives
    printf("New passenger arrives: Zara (risk 98)\n");
    insert_passenger("Zara", 98);
    print_heap("After inserting Zara (risk 98)");

    // 5. Zara is cleared → remove
    printf("Zara cleared → removing passenger with risk 98\n");
    remove_by_risk(98);
    print_heap("After removing risk 98 and re-heapify");

    printf("Done.\n");
    return 0;
}