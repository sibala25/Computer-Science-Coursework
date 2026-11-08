#include "newSet.h"
#include <iostream>

Set::Set() {
    m_size = 0;
    m_max = DEFAULT_MAX_ITEMS;
    m_set = new ItemType[m_max];
}

Set::Set(int max) {
    if (max < 0) {
        std::cout << "Integer cannot be negative" << std::endl;
        std::exit(1);
    }
    
    m_size = 0;
    m_max = max;
    m_set = new ItemType[m_max];
}

Set::Set(const Set& other) {
    m_size = other.m_size;
    m_max = other.m_max;
    m_set = new ItemType[m_max];
    
    for (int i = 0; i < m_size; i++) {
        m_set[i] = other.m_set[i];
    }
}

Set& Set::operator=(const Set& other) {
    if (this != &other) {
        Set temp(other);
        swap(temp);
    }
    return *this;
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
    if (contains(value) || m_max <= m_size) {
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
            for (int i = m_size; i >= value_pos; i--) {
                m_set[i] = m_set[i-1];
            }
            m_set[value_pos] = value;
            m_size++;
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
        std::cout << i << " is: " << m_set[i] << std::endl;
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

void Set::swap(Set& other) {  // (Implementation note: The swap function is easily implementable without creating any additional container of many items such as an additional array or an additional Set.)
    std::swap(m_set, other.m_set);
    std::swap(m_size, other.m_size);
    std::swap(m_max, other.m_max);

}

Set::~Set() {
    delete [] m_set;
}
