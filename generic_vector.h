#ifndef CUSTOM_GENERIC_VECTOR_H_INCLUDED
#define CUSTOM_GENERIC_VECTOR_H_INCLUDED

#include <cstdint>
#include <vector>

using namespace std;

typedef struct int_vector
{
    int* data;
    size_t size;
    size_t used;

}int_vector;
int_vector* init_int_vector(size_t size);
bool add_in_int_vector(int_vector* x,int element);

typedef struct array_of_int_vector
{
    int_vector** data;
    size_t size;
    size_t used;

}array_of_int_vector;


array_of_int_vector* init_array_of_int_vector(size_t size);
bool add_in_array_of_int_vector(array_of_int_vector* x,int_vector* element);
int_vector* duplicate_int_vector(int_vector* x);
bool element_in_int_vector(std::vector<int> x,int element);

void print_int_vector(int_vector* x);
void print_array_of_vector(array_of_int_vector* x);
int_vector* merge_array_of_vector(array_of_int_vector* x);
int_vector* merge_array_of_vector_2(array_of_int_vector* x,int size);

int* intdup(int* src, size_t len);

typedef struct bit_vector
{
    bool* data;
    size_t size;
    size_t used;

}bit_vector;
bit_vector* init_bit_vector(size_t size);
bool add_in_bit_vector(bit_vector* x,bool element);
void print_bit_vector(bit_vector* x);

typedef struct common_elements_vector
{
    bit_vector* bit_vec;
    int_vector* chain;
    int_vector* distance_from_father;
}common_elements_vector;

common_elements_vector* init_common_elements_vector();
common_elements_vector* init_common_elements_vector_2(size_t size);
common_elements_vector* init_common_elements_vector_3(size_t size,size_t size2);



#endif