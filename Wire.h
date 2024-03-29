#ifndef WIRE_H
#define WIRE_H
#include<vector>
#include<string.h>
#include<cstdlib>
#include<string>
#include<iostream>

#define WIRE_SIZE 12
#define VAL_SIZE 12
#define PORT_SIZE 5

struct key_connect{
    char key[WIRE_SIZE];
    uint32_t connect;
    uint32_t next;
};

struct val_port{
    char val[VAL_SIZE];
    char port[PORT_SIZE];
    uint32_t next;
};


class Wire{
    private:
        uint32_t* index_table;
        std::vector<key_connect> wire_bucket;
        std::vector<val_port> port_bucket;

    public:
        explicit Wire() {};
        Wire(int index_size, int capacity);
        ~Wire() {
            //free(index_table);
        };
        void update_wire(int index, char* key);
        void update_wire_connection(int index, char* key, char* vertex, char* port);
        void get_wire_connections(int index, char* key,int count, char** vertices, char** ports);
        int get_connection_count(int index, char* key);
        bool get_wire_connections(int index, char* key, std::vector<std::string> vertices, std::vector<std::string> ports);

    private:
        uint32_t update_wire_bucket(char* key);
        void insert_wire_bucket(uint32_t index, char* key);
        int get_wire_index(uint32_t index, char* key);
        uint32_t update_connection(uint32_t index, char* vertex, char* port);
        uint32_t update_connection_bucket(char* vertex, char* port);
        void insert_connection_bucket(uint32_t index, char* vertex, char* port);


};

#endif