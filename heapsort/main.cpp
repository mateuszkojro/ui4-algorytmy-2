#include <iostream>
#include <vector>

using namespace std;

void heap_sort(vector<int> &array);


void form_heap(vector<int> &tree,  int index,  int tree_size);

int left_child_index(int index);

int right_child_index(int index);

void form_correct_tree(vector<int> &tree,  int index,  int tree_size);

void show_heap(vector<int> &tree, int tree_size);

int main() {


    int no_tests;
    cin >> no_tests;

    vector<int> sort_array;

    int sort_array_size;
    int temp_value;

    for (int i = 0; i < no_tests; i++) {

        cin >> sort_array_size;
        sort_array.reserve(sort_array_size);

        for (int j = 0; j < sort_array_size; j++) {


            cin >> temp_value;
            sort_array.push_back(temp_value);


        }
        heap_sort(sort_array);

        for (auto i:sort_array)
            cout << i << "\t";

        cout << endl;
        cout << endl;
        sort_array.clear();
    }


}


int left_child_index(const int index) {
    return 2 * index + 1;

}

int right_child_index(const int index) {
    return 2 * index + 2;
}


void heap_sort(vector<int> &array) {
    for (int i = array.size(); i >= 1; --i) {

        form_heap(array, 0, i);
        show_heap(array, i);
        swap(array[0], array[i - 1]);
    }
}


void form_correct_tree(vector<int> &tree, const int index, const int tree_size) {


    int left_child = left_child_index(index);
    int right_child = right_child_index(index);


    if (left_child < tree_size)
        if (tree[left_child] > tree[index]) {

            swap(tree[left_child], tree[index]);
            form_correct_tree(tree, left_child, tree_size);

        }

    if (right_child < tree_size)
        if (tree[right_child] > tree[index]) {

            swap(tree[right_child], tree[index]);
            form_correct_tree(tree, right_child, tree_size);

        }
}


void form_heap(vector<int> &tree, const int index, const int tree_size) {
    int left_index = left_child_index(index);
    int right_index = right_child_index(index);


    if (left_index < tree_size)
        form_heap(tree, left_index, tree_size);

    if (right_index < tree_size)
        form_heap(tree, right_index, tree_size);

    form_correct_tree(tree, index, tree_size);

}


void show_heap(vector<int> &tree, int tree_size) {
    if (tree_size < 2) return;
    for (int i = 0; i < tree_size; i++) {

        cout << tree[i] << "\t";
    }
    cout << endl;


}