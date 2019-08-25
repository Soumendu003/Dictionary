from libc.stdlib cimport calloc
from libcpp cimport bool
cdef extern from "Map.h":

    cdef cppclass Map:
        Map() except +
        Map(int index_size, int bucket_capacity) except +
        void update(int index, char* key, char* value, char* port)
        bool get(int index, char* key, char* val_container, char* port_container)
        int get_index_table_size()
        int get_bucket_size()
        int get_bucket_capacity()
        int get_index_table_length()

cdef class PyMap(object):
    cdef Map cmap;
    cdef int mask;
    cdef int val_size;
    cdef int port_size;
    cdef char* val_container;
    cdef char* port_container;


    def __cinit__(self, index_size = 65536, bucket_capacity = 65536):

        self.cmap = Map(index_size, bucket_capacity);
        self.mask = index_size - 1;
        self.val_size = 12;
        self.port_size = 5;
        self.val_container = <char*> calloc(self.val_size, sizeof(char))
        self.port_container = <char*> calloc(self.port_size, sizeof(char))
    

    def update(self, str key, str value, str port):

        self.cmap.update(hash(key) & self.mask, key.encode('UTF-8'), value.encode('UTF-8'), port.encode('UTF-8'))

    def get(self, str key):

        if(self.cmap.get(hash(key) & self.mask, key.encode('UTF-8'), self.val_container, self.port_container)):
            return self.val_container.decode('UTF-8'), self.port_container.decode('UTF-8')
        else:
            return None
    
    def get_size(self):

        print("Index table size in Bytes = "+str(self.cmap.get_index_table_size()))
        print("Bucket size = "+str(self.cmap.get_bucket_size()))
        #self.cmap.get_bucket_capacity()
        print("Bucket capacity = "+str(self.cmap.get_bucket_capacity()))
        print("Index table size = "+str(self.cmap.get_index_table_length()))