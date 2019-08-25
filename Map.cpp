#include "Map.h"

Map::Map (int index_size, int bucket_capacity)
{
    index_table_size = index_size;
    index_table = (uint32_t*)calloc(index_size, sizeof(uint32_t));
    this->bucket.reserve(bucket_capacity);
    // Sets the first place Invalid
    update_bucket("INVALID", "INVALID", "N/A");
}

void Map::update (int index, char* key, char* value, char* port){
    
    if(index_table[index] == 0)
    {
        index_table[index] = update_bucket(key, value, port);
    }
    else{
        insert_bucket(index_table[index], key, value, port);
    }
}

bool Map::get (int index, char* key, char* val_container, char* port_container){
    int ele_index = get_ele_index(index_table[index], key);
    if(ele_index < 0)
    {
        return false;
    }
    else{
        strcpy(val_container, bucket[ele_index].value);
        strcpy(port_container, bucket[ele_index].port);
        return true;
    }
}

uint32_t Map::update_bucket (char* key, char* value, char* port)
{
    key_val tem;
    strcpy(tem.key, key);
    strcpy(tem.value, value);
    strcpy(tem.port, port);
    tem.next = 0;
    bucket.push_back(tem);
    return bucket.size() - 1;
}

void Map::insert_bucket (uint32_t index, char* key, char* value, char* port)
{
    if(strcmp(bucket[index].key, key) == 0)
    {
        strcpy(bucket[index].value, value);
        strcpy(bucket[index].port, port);
    }
    else if(bucket[index].next == 0)
    {
        bucket[index].next = update_bucket(key, value, port);
    }
    else
    {
        insert_bucket(bucket[index].next, key, value, port);
    }

    return;
    
}

int Map::get_ele_index (uint32_t index, char* key)
{
    if(strcmp(bucket[index].key, key) == 0)
    {
        return index;
    }
    else if (bucket[index].next == 0)
    {
        return -1;
    }
    else
    {
        return get_ele_index(bucket[index].next, key);
    }
    
}


 int Map::get_index_table_size ()
 {
     return sizeof(index_table);
 }

int Map::get_bucket_size()
{
    return bucket.size();
}

int Map::get_bucket_capacity()
{
    //std::cout<< " Bucket capacity = "<<bucket.capacity()<<std::endl;
    return this->bucket.capacity();
}

int Map::get_index_table_length(){
    return index_table_size;
}