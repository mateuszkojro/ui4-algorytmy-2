

#include <iostream>
#include <ctime>
#include <vector>



void heap_sort(std::vector<int> &array);


void create_heap(std::vector<int> &array, size_t index, size_t array_size);


size_t left(size_t index);


size_t right(size_t index);

void swap_with_children(std::vector<int> &array, size_t index, size_t array_size);

void show_heap(std::vector<int> &array, size_t array_size);


/// main
int main() {
    srand(time(NULL));

    unsigned N;
    std::cin >> N;


    std::vector<int> sort_array;
    for (int i = 0; i < N; i++) {

        int sort_array_size;
        int temp_value;
        std::cin >> sort_array_size ;

        for (int j = 0; j < sort_array_size; j++) {


            std::cin >> temp_value;
            sort_array.push_back(temp_value);


        }
        heap_sort(sort_array);

        for (auto s:sort_array)
            std::cout << s << "\t";

        std::cout << std::endl;
        std::cout << std::endl;
        sort_array.clear();
    }


}


size_t left(const size_t index) {
    return 2 * index + 1;

}

size_t right(const size_t index) {
    return 2 * index + 2;
}


void heap_sort(std::vector<int> &array) {
    for (int i = array.size(); i >= 1; --i) {

        create_heap(array, 0, i);
        show_heap(array, i);
        std::swap(array[0], array[i - 1]);
    }
}


void swap_with_children(std::vector<int> &array, const size_t index, const size_t array_size) {


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


void create_heap(std::vector<int> &array, const size_t index, const size_t array_size) {
    size_t left_index = left(index);
    size_t right_index = right(index);


    if (left_index < array_size)
        create_heap(array, left_index, array_size);

    if (right_index < array_size)
        create_heap(array, right_index, array_size);

    swap_with_children(array, index, array_size);

}


void show_heap(std::vector<int> &array, size_t array_size) {
    if (array_size < 2)return;
    for (int i = 0; i < array_size; i++) {

        std::cout << array[i] << "\t";
    }
    std::cout << std::endl;


}