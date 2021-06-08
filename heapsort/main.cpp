//
// Created by pc on 17.04.2021.
//
// i'm done trying
// i've tried before now i'm done

#include <iostream>
#include <ctime>
#include <vector>


/// sort's array using heap algorithm
/// \return sort's given array
/// \param array to sort
template<class T>
void heap_sort(std::vector<T> &array);

/// recursively checks if given index is bigger than it's children
/// used to create heap aut of given array
/// \return creates heap out of array
/// \param array to be hyped
/// \param index to be checked for heap correctness
/// \param array_size virtual array size, due to nature of algorithm array.size() isn't the correct size of used array
template<class T>
void create_heap(std::vector<T> &array, size_t index, size_t array_size);

/// \return left children to the index
/// \param index node to witch children will be found
size_t left(size_t index);

/// \return right children to the index
/// \param index node to witch children will be found
size_t right(size_t index);


/// checks for correct order of nodes 
/// if value of any of children is bigger than value under index
/// in case of incorrect order meaning child has bigger value than father
/// swaps values between father and child
/// \param array to be checked
/// \param index of father in array
/// \param array_size virtual array size, due to nature of algorithm array.size() isn't the correct size of used array
template<class T>
void swap_with_children(std::vector<T> &array, size_t index, size_t array_size);

/// prints given heap onto console using std::cout
/// order of nodes is defined in asd2_problem2.pdf
/// \important given class T must be compatible with sdt::cout 
/// \param array heap to be printed 
/// \param array_size virtual array size, due to nature of algorithm array.size() isn't the correct size of used array
template<class T>
void show_heap(std::vector<T> &array, size_t array_size);


/// main
int main() {
    srand(time(NULL));

    unsigned N;
    std::cin >> N;


    std::vector<int> to_be_sorted;
    for (int i = 0; i < N; i++) {
        int k;
        int sort;
        std::cin >> k ;
        for (int j = 0; j < k; j++) {
            std::cin >>sort;
            to_be_sorted.push_back(sort);


        }
        heap_sort(to_be_sorted);
        for (auto s:to_be_sorted) std::cout << s << "\t";
        std::cout << std::endl;
        std::cout << std::endl;
        to_be_sorted.clear();
    }


}


size_t left(const size_t index) {
    return 2 * index + 1;

}

size_t right(const size_t index) {
    return 2 * index + 2;
}

template<class T>
void heap_sort(std::vector<T> &array) {
    for (int i = array.size(); i >= 1; --i) {

        create_heap(array, 0, i);
        show_heap(array, i);
        std::swap(array[0], array[i - 1]);
    }
}

template<class T>
void swap_with_children(std::vector<T> &array, const size_t index, const size_t array_size) {
    size_t left_index = left(index);
    size_t right_index = right(index);


    if (left_index < array_size)
        if (array[left_index] > array[index]) {
            std::swap(array[left_index], array[index]);
            swap_with_children(array, left_index, array_size);
        }

    if (right_index < array_size)
        if (array[right_index] > array[index]) {
            std::swap(array[right_index], array[index]);
            swap_with_children(array, right_index, array_size);
        }
}

template<class T>
void create_heap(std::vector<T> &array, const size_t index, const size_t array_size) {
    size_t left_index = left(index);
    size_t right_index = right(index);


    if (left_index < array_size)
        create_heap(array, left_index, array_size);

    if (right_index < array_size)
        create_heap(array, right_index, array_size);

    swap_with_children(array, index, array_size);

}

template<class T>
void show_heap(std::vector<T> &array, size_t array_size) {
    if (array_size < 2)return;
    for (int i = 0; i < array_size; i++) {

        std::cout << array[i] << "\t";
    }
    std::cout << std::endl;


}