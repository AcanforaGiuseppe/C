#define DNODE_PP dlist_node_t **
#define DNODE_P  dlist_node_t *

typedef struct dlist_node
{
	struct dlist_node* prev;
	struct dlist_node* next;
} dlist_node_t;

typedef struct dInt_item
{
	dlist_node_t node;
	int n;
} dInt_item_t;


dlist_node_t* dlist_append(dlist_node_t** head, dlist_node_t* item);
dInt_item_t* dInt_create(const int n);
void dList_remove(dlist_node_t** head, dlist_node_t* item);
int dList_contain(dlist_node_t** head, dlist_node_t* item);
dInt_item_t* dList_shuffle(dlist_node_t** head);
int dList_get_lenght(dInt_item_t* list);
int dList_insert_after(dlist_node_t** head, dlist_node_t* after_this, dlist_node_t* item);
int dList_insert_before(dlist_node_t** head, dlist_node_t* before_this, dlist_node_t* item);
void dList_destroy(dlist_node_t** head);
void dList_print(dInt_item_t* list);