#ifndef BI_RING_H
#define BI_RING_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <functional>

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

std::string aggregate(int key, std::string info1, std::string info2) {
    return info1 + info2;
}

#endif
