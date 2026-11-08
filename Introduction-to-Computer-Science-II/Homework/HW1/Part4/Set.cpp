#include "Set.h"
#include <iostream>

Set::Set() {
    m_size = 0;
}

bool Set::empty() const {
    if (m_size == 0) {
        return true;
    }
    else {
        return false;
    }
}

int Set::size() const {
    return m_size;
}

bool Set::insert(const ItemType& value) {
    if (contains(value) || DEFAULT_MAX_ITEMS <= m_size) {
        return false;
    }
    else {
        if (m_size == 0) {
            m_set[0] = value;
            m_size++;
            return true;
        }
        else {
            int value_pos = 0;
            while(m_set[value_pos] < value && value_pos < m_size) {
                value_pos++;
            }
            m_size++;
            for (int i = m_size - 1; i >= value_pos; i--) {
                m_set[i] = m_set[i-1];
            }
            m_set[value_pos] = value;
        }
        return true;
    }
}

bool Set::erase(const ItemType& value) {
    for (int i = 0; i < m_size; i++) {
        if (m_set[i] == value) {
            for (int j = i; j < m_size; j++) {
                m_set[j] = m_set[j+1];
            }
            m_size--;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value) const {
    if (m_size == 0) {
        return false;
    }
    for (int i = 0; i < m_size; i++) {
        if (m_set[i] == value) {
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const {
    if (0 <= i && i < size()) {
        value = m_set[m_size - 1 - i];
        return true;
    }
    return false;
}

void Set::swap(Set& other) {
    std::swap(m_set,other.m_set);
    std::swap(m_size,other.m_size);
}
