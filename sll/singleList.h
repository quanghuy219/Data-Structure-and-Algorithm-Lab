

typedef struct {
    node_ph *root;
    node_ph *cur;
} s_list;


node_ph* makeNewNode(PHONE ph){
  node_ph* new = (node_ph*)malloc(sizeof(node_ph));
  new -> Phone = ph;
  new -> next = NULL;
  return new;
}



void insertAfterCur(PHONE ph, s_list *list){
  node_ph* new = makeNewNode(ph);
  new -> next = list -> cur -> next;
  list -> cur -> next = new;
  list -> cur = list -> cur -> next;
}
