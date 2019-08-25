#include "Wire.h"

Wire::Wire (int index_size, int capacity)
{
    index_table = (uint32_t*)calloc(index_size, sizeof(uint32_t));
    this->wire_bucket.reserve(capacity);
    this->port_bucket.reserve(capacity);
    std::cout<<"Invalid index of Wire = "<<update_wire_bucket("INVALID")<<std::endl;
    std::cout<<"Invalid index of Wire = "<<update_connection_bucket("INVALID", "N/A")<<std::endl;
}

void Wire::update_wire(int index, char* key){
    if(index_table[index] == 0)
    {
        index_table[index] = update_wire_bucket(key);
    }
    else{
        insert_wire_bucket(index_table[index], key);
    }
}

uint32_t Wire::update_wire_bucket(char* key){
    key_connect tem;
    strcpy(tem.key, key);
    tem.connect = 0;
    tem.next = 0;
    wire_bucket.push_back(tem);
    return wire_bucket.size() - 1;
}

void Wire::insert_wire_bucket(uint32_t index, char* key){

    if(strcmp(wire_bucket[index].key, key) == 0)
    {
        // Same wire value inserted
        return;
    }
    else if(wire_bucket[index].next == 0)
    {
        wire_bucket[index].next = update_wire_bucket(key);
    }
    else
    {
        insert_wire_bucket(wire_bucket[index].next, key);
    }
    
    return;
}

void Wire::update_wire_connection(int index, char* key, char* vertex, char* port){

    int wire_index = get_wire_index(index_table[index], key);

    if(wire_index < 0){
        update_wire(index, key);
        update_wire_connection(index, key, vertex, port);
    }
    else{
        wire_bucket[wire_index].connect = update_connection(wire_bucket[wire_index].connect, vertex, port);
    }


}

uint32_t Wire::update_connection_bucket(char* vertex, char* port){
    val_port tem;
    strcpy(tem.val, vertex);
    strcpy(tem.port, port);
    tem.next = 0;
    port_bucket.push_back(tem);
    return port_bucket.size() - 1;

}

uint32_t Wire::update_connection(uint32_t index, char* vertex, char* port){

    if(index == 0)
    {
        return update_connection_bucket(vertex, port);
    }
    else{
        insert_connection_bucket(port_bucket[index].next, vertex, port);
        return index;
    }

}

void Wire::insert_connection_bucket(uint32_t index, char* vertex, char* port){
    if(strcmp(port_bucket[index].port, port) == 0 &&  strcmp(port_bucket[index].val, vertex) == 0)
    {
        return;
    }
    else if(port_bucket[index].next == 0)
    {
        port_bucket[index].next = update_connection_bucket(vertex, port);
    }
    else
    {
        insert_connection_bucket(port_bucket[index].next, vertex, port);
    }
    
}


int Wire::get_wire_index(uint32_t index, char* key){

    if(strcmp(wire_bucket[index].key, key) == 0)
    {
        return index;
    }
    else if (wire_bucket[index].next == 0)
    {
        return -1;
    }
    else
    {
        return get_wire_index(wire_bucket[index].next, key);
    }

}

int Wire::get_connection_count(int index, char* key){
    int wire_index = get_wire_index(index, key);
    if(wire_index < 0)
    {
        return 0;
    }
    else if(wire_bucket[wire_index].connect == 0)
    {
        return 0;
    }
    else{
        int count = 0;
        index = wire_bucket[wire_index].connect;
        while(index != 0)
        {
            index = port_bucket[index].next;
            count += 1;
        }
        return count;
    }
}

void Wire::get_wire_connections(int index, char* key,int count, char** vertices, char** ports){
    
    if(count <= 0)
    {
        return;
    }
    else{
        int wire_index = get_wire_index(index, key);
        index = wire_bucket[wire_index].connect;
        int i = 0;
        while (index != 0)
        {
            strcpy(vertices[i], port_bucket[index].val);
            strcpy(ports[i], port_bucket[index].val);
            index = port_bucket[index].next;
            i += 1;
        }
        return;
    }
}

bool Wire::get_wire_connections(int index, char* key, std::vector<std::string> vertices, std::vector<std::string> ports){
    int wire_index = get_wire_index(index, key);
    if(wire_index < 0)
    {
        return false;
    }
    else if(wire_bucket[wire_index].connect == 0)
    {
        return false;
    }
    else{
        index = wire_bucket[wire_index].connect;
        while(index != 0)
        {
            vertices.push_back(std::string(port_bucket[index].val));
            ports.push_back(std::string(port_bucket[index].port));
            index = port_bucket[index].next;
        }
        return true;
    }

}