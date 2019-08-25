from libc.stdlib cimport calloc
from libcpp cimport bool
from libcpp.string cimport string
from libcpp.vector cimport vector

cdef extern from "Wire.h":
    
    cdef cppclass Wire:
        Wire() except +
        Wire(int index_size, int capacity) except +
        void update_wire(int index, char* key)
        void update_wire_connection(int index, char* key, char* vertex, char* port)
        bool get_wire_connections(int index, char* key, vector[string] vertices, vector[string] ports)

cdef class PyWire(object):
    cdef Wire wire
    cdef int mask
    cdef int val_size
    cdef int port_size
    cdef vector[string] val_container
    cdef vector[string] port_container

    def __cinit__(self, index_size = 65536, bucket_capacity = 65536):
        print("Inside constructor")
        self.wire = Wire(index_size, bucket_capacity)
        self.mask = index_size - 1
        self.val_size = 12
        self.port_size = 5
        
    def update_wire(self, str key):

        self.wire.update_wire(hash(key) & self.mask, key.encode('UTF-8'))

    def update_wire_connection(self, str key, str vertex, str port):

        self.wire.update_wire_connection(hash(key) & self.mask, key.encode('UTF-8'), vertex.encode('UTF-8'), port.encode('UTF-8'))

    '''def get_connections(self, str key):

        cdef int count = self.get_connection_count(hash(key) & self.mask, key.encode('UTF-8'))

        if(count > 0):

            self.val_container = <char**>calloc(count, sizeof(count));
            self.port_container = <char**>calloc(count, sizeof(count));

            for i in range(0, count):

                self.val_container[i] = <char*> calloc(self.val_size, sizeof(char))
                self.port_container[i] = <char*> calloc(self.port_size, sizeof(char))
            
            self.get_wire_connections(hash(key) & self.mask, key.encode('UTF-8'), count, self.val_container, self.port_container)

            lst = []

            for i in range(0, count):

                lst.append((self.val_container[i].decode('UTF-8'), self.port_container[i].decode('UTF-8')))
            
            return lst

        else:
            return None'''

    def get_connections(self, str key):      

        if(self.wire.get_wire_connections(hash(key) & self.mask, key.encode('UTF-8'), self.val_container, self.port_container)):
            lst = []
            for i in range(0, self.val_container.size()):

                print((self.val_container[i].decode('UTF-8'), self.port_container[i].decode('UTF-8')))
            
            self.val_container.clear()
            self.port_container.clear()
            return lst
        
        else:
            return None


            