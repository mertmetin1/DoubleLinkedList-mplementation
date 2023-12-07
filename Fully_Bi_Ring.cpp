#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <cassert>

using namespace std;

template <typename Key, typename Info>
class BiRing {


public:
    struct Node {
        Key key;
        Info info;
        Node* next;
        Node* prev;
        Node(Key key, Info info) : key(key), info(info), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    BiRing() : head(nullptr), tail(nullptr) {}

    BiRing* join(BiRing* other) {
        if (!this->head) {
            this->head = other->head;
            this->tail = other->tail;
        }
        else if (other->head) {
            this->tail->next = other->head;
            other->head->prev = this->tail;
            this->tail = other->tail;
        }
        return this;
    }

    Node* push_front(Key key, Info info) {
        Node* new_node = new Node(key, info);
        if (!this->head) {
            this->head = this->tail = new_node;
        }
        else {
            new_node->next = this->head;
            this->head->prev = new_node;
            this->head = new_node;
        }
        return new_node;
    }

    Node* pop_front() {
        if (!this->head) {
            return nullptr;
        }
        Node* front_node = this->head;
        if (this->head == this->tail) {
            this->head = this->tail = nullptr;
        }
        else {
            this->head = this->head->next;
            if (this->head) {
                this->head->prev = nullptr;
            }
        }
        return front_node;
    }

    Node* insert(Node* position, Key key, Info info) {
        Node* new_node = new Node(key, info);
        if (position == nullptr) {
            return this->push_front(key, info);
        }
        else if (position == this->tail) {
            new_node->prev = this->tail;
            this->tail->next = new_node;
            this->tail = new_node;
        }
        else {
            Node* next_node = position->next;
            position->next = new_node;
            new_node->prev = position;
            new_node->next = next_node;
            next_node->prev = new_node;
        }
        return new_node;
    }

    Node* erase(Node* position) {
        if (position == nullptr) {
            return nullptr;
        }
        if (position == this->head) {
            return this->pop_front();
        }
        else if (position == this->tail) {
            Node* removed_node = this->tail;
            this->tail = this->tail->prev;
            if (this->tail) {
                this->tail->next = nullptr;
            }
            else {
                this->head = nullptr;
            }
            return removed_node;
        }
        else {
            Node* prev_node = position->prev;
            Node* next_node = position->next;
            prev_node->next = next_node;
            if (next_node) {
                next_node->prev = prev_node;
            }
            return position;
        }
    }

    BiRing* filter(bool (*pred)(Key)) {
        BiRing* filtered = new BiRing();
        Node* current = this->head;
        while (current) {
            if (pred(current->key)) {
                filtered->push_front(current->key, current->info);
            }
            current = current->next;
        }
        return filtered;
    }
    

    BiRing<Key, Info> unique(std::function<Info(Key, Info, Info)> aggregate) {
        std::unordered_map<Key, Info> unique_dict;
        Node* current = head;
        while (current) {
            if (unique_dict.find(current->key) == unique_dict.end()) {
                unique_dict[current->key] = current->info;
            } else {
                unique_dict[current->key] = aggregate(current->key, unique_dict[current->key], current->info);
            }
            current = current->next;
        }

        std::vector<std::pair<Key, Info>> unique_list;
        for (const auto& pair : unique_dict) {
            unique_list.push_back(pair);
        }
        std::reverse(unique_list.begin(), unique_list.end());

        BiRing<Key, Info> unique_bi_ring;
        for (const auto& pair : unique_list) {
            unique_bi_ring.push_front(pair.first, pair.second);
        }
        return unique_bi_ring;
    }



    
    BiRing* shuffle(int fcnt, BiRing* other, int scnt, int reps) {
        BiRing* shuffled = new BiRing();
        Node* current_self = this->head;
        Node* current_other = other->head;
        while (reps > 0) {
            int count_fcnt = fcnt;
            while (count_fcnt > 0 && current_self) {
                shuffled->push_front(current_self->key, current_self->info);
                current_self = current_self->next;
                count_fcnt -= 1;
            }
            int count_scnt = scnt;
            while (count_scnt > 0 && current_other) {
                shuffled->push_front(current_other->key, current_other->info);
                current_other = current_other->next;
                count_scnt -= 1;
            }
            reps -= 1;
        }
        return shuffled;
    }
};

bool pred(int key) {
    return key % 2 == 0;
}

string aggregate(int key, string info1, string info2) {
    return info1 + info2;
}



int main() {
    // push_front metodunun testi
    {
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

    // pop_front metodunun testi
    {
        BiRing<int, std::string> ring;
        ring.push_front(1, "One");
        BiRing<int, std::string>::Node* frontNode = ring.pop_front();
        assert(frontNode->key == 1);
        assert(frontNode->info == "One");
        delete frontNode;
        std::cout << "pop_front test passed." << std::endl;
    }

    // insert metodunun testi
    {
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

    // erase metodunun testi
    {
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

    // filter metodunun testi
    {
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

    // unique metodunun testi
    {
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

    // shuffle metodunun testi
    {
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

    std::cout << "All tests passed successfully." << std::endl;

    return 0;
}






