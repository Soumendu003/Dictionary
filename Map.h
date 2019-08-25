#ifndef MAP_H
#define MAP_H

#include<vector>
#include<cstdlib>
#include<string.h>
#include<iostream>

#define KEY_SIZE 12
#define VAL_SIZE 12
#define PORT_SIZE 5
#define INDEX_TABLE_SIZE 65536

struct key_val{

    char key[KEY_SIZE];
    char value[VAL_SIZE];
    char port[PORT_SIZE];
    uint32_t next;
};


class Map{
    private:
        uint32_t* index_table;
        std::vector<key_val> bucket;
        uint32_t index_table_size;
        uint32_t bucket_capacity_size;

    public:
        explicit Map() {};
        Map(int index_size, int bucket_capacity);
        ~Map() {};
        void update(int index, char* key, char* value, char* port);
        bool get(int index, char* key, char* val_container, char* port_container);
        int get_index_table_size();
        int get_bucket_size();
        int get_bucket_capacity();
        int get_index_table_length();

    private:
        uint32_t update_bucket(char* key, char* value, char* port);
        void insert_bucket(uint32_t index, char* key, char* value, char* port);
        int get_ele_index(uint32_t index, char* key);

};
#endif