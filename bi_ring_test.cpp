#include "bi_ring_test.h"
#include <cassert> 
void test_push_front() {
    BiRing<int, std::string> ring;
    ring.push_front(1, "One");
    assert(ring.head->key == 1);
    assert(ring.head->info == "One");
    assert(ring.tail->key == 1);
    assert(ring.tail->info == "One");
    std::cout << "push_front test passed." << std::endl;
    std::cout << "BiRing content: ";
    BiRing<int, std::string>::Node* current = ring.head;
    while (current) {
        std::cout << "(" << current->key << ", " << current->info << ") ";
        current = current->next;
    }
    std::cout << std::endl;
}

void test_pop_front() {
    BiRing<int, std::string> ring;
    ring.push_front(1, "One");
    BiRing<int, std::string>::Node* frontNode = ring.pop_front();
    assert(frontNode->key == 1);
    assert(frontNode->info == "One");
    delete frontNode;
    std::cout << "pop_front test passed." << std::endl;
}

void test_insert() {
    BiRing<int, std::string> ring;
    ring.push_front(1, "One");
    ring.push_front(2, "Two");
    BiRing<int, std::string>::Node* position = ring.head;
    ring.insert(position, 3, "Three");
    assert(ring.head->next->key == 3);
    assert(ring.head->next->info == "Three");
    std::cout << "insert test passed." << std::endl;
    std::cout << "BiRing content: ";
    BiRing<int, std::string>::Node* current = ring.head;
    while (current) {
        std::cout << "(" << current->key << ", " << current->info << ") ";
        current = current->next;
    }
    std::cout << std::endl;
}

void test_erase() {
    BiRing<int, std::string> ring;
    ring.push_front(1, "One");
    ring.push_front(2, "Two");
    BiRing<int, std::string>::Node* position = ring.head;
    BiRing<int, std::string>::Node* erasedNode = ring.erase(position);
    assert(erasedNode->key == 2);
    assert(erasedNode->info == "Two");
    delete erasedNode;
    std::cout << "erase test passed." << std::endl;
    std::cout << "BiRing content: ";
    BiRing<int, std::string>::Node* current = ring.head;
    while (current) {
        std::cout << "(" << current->key << ", " << current->info << ") ";
        current = current->next;
    }
    std::cout << std::endl;
}

void test_filter() {
    BiRing<int, std::string> ring;
    ring.push_front(1, "One");
    ring.push_front(2, "Two");
    ring.push_front(3, "Three");
    std::cout << "Original BiRing content: ";
    BiRing<int, std::string>::Node* current = ring.head;
    while (current) {
        std::cout << "(" << current->key << ", " << current->info << ") ";
        current = current->next;
    }
    std::cout << std::endl;

    BiRing<int, std::string>* filtered = ring.filter(pred);
    std::cout << "Filtered BiRing content (even keys): ";
    BiRing<int, std::string>::Node* filtered_current = filtered->head;
    while (filtered_current) {
        std::cout << "(" << filtered_current->key << ", " << filtered_current->info << ") ";
        filtered_current = filtered_current->next;
    }
    std::cout << std::endl;

    delete filtered;
}

void test_unique() {
    BiRing<int, std::string> ring;
    ring.push_front(1, "One");
    ring.push_front(2, "Two");
    ring.push_front(3, "Three");
    ring.push_front(2, "Two");
    ring.push_front(1, "One");
    ring.push_front(4, "Four");

    BiRing<int, std::string> uniqueRing = ring.unique(aggregate);
    std::cout << "Unique BiRing content: ";
    BiRing<int, std::string>::Node* current = uniqueRing.head;
    while (current) {
        std::cout << "(" << current->key << ", " << current->info << ") ";
        current = current->next;
    }
    std::cout << std::endl;
}

void test_shuffle() {
    BiRing<int, std::string> ring1;
    ring1.push_front(1, "One");
    ring1.push_front(2, "Two");
    ring1.push_front(3, "Three");

    BiRing<int, std::string> ring2;
    ring2.push_front(4, "Four");
    ring2.push_front(5, "Five");
    ring2.push_front(6, "Six");

    BiRing<int, std::string>* shuffled = ring1.shuffle(1, &ring2, 2, 2);
    std::cout << "Shuffled BiRing content: ";
    BiRing<int, std::string>::Node* shuffled_current = shuffled->head;
    while (shuffled_current) {
        std::cout << "(" << shuffled_current->key << ", " << shuffled_current->info << ") ";
        shuffled_current = shuffled_current->next;
    }
    std::cout << std::endl;

    delete shuffled;
}

void run_all_tests() {
    test_push_front();
    test_pop_front();
    test_insert();
    test_erase();
    test_filter();
    test_unique();
    test_shuffle();
}

int main() {
    run_all_tests();
    return 0;
}
