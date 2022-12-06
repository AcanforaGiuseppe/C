#define NODE (linked_list_node_t *)
#define SET (set_table_t *)
#define SET_NODE (set_node_t *)
#define SET_ADDRESS (set_table_t **)
#define DICTIONARY_NODE (dictionary_node_t *)

typedef union data
{
	uint8_t byte;
	uint16_t bytes_2;
	uint32_t bytes_4;
	uint64_t bytes_8;
	void* pointer;
} data_t;