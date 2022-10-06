#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "saved_list.sl"

struct Node {
  int Value;
  struct Node *Next;
};

void print_list(struct Node *beg) {

  if (!beg)
    return;

  printf("\n");

  while (beg) {
    printf("%d ", beg->Value);
    beg = beg->Next;
  }

  printf("\n");

  return;
}

void append(struct Node *head, int val) {

  if (!head)
    return;

  while (head->Next)
    head = head->Next;

  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

  new_node->Value = val;
  new_node->Next = 0;

  head->Next = new_node;

  return;
}

struct Node *prepend(struct Node *head, int val) {

  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  new_node->Value = val;

  new_node->Next = head;

  return new_node;
}

void reverse_list(struct Node **head) {

  struct Node *prev = NULL;
  struct Node *current = *head;
  struct Node *next;

  while (current != NULL) {
    next = current->Next;
    current->Next = prev;
    prev = current;
    current = next;
  }

  *head = prev;
}

struct Node *add_by_index(struct Node *head, int index, int val) {

  if (!head)
    return head;

  struct Node *beg = head;

  if (index == 0) {
    head = prepend(head, val);
    return head;
  }

  struct Node *temp = head;
  int list_size = 0;

  while (temp && (++list_size))
    temp = temp->Next;

  if (index > list_size) {
    append(head, val);
    return head;
  }

  int ctr = 1;

  // no OOB checks
  while (head && (ctr++) < index)
    head = head->Next;

  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  new_node->Value = val;

  new_node->Next = head ? head->Next : head;
  head->Next = new_node;

  return beg;
}

struct Node *remove_by_index(struct Node *head, int index) {

  if (!head)
    return head;

  if (index == 0) {
    struct Node *next = head->Next;
    free(head);
    return next;
  }

  struct Node *temp = head;
  int list_size = 0;

  while (temp && (++list_size))
    temp = temp->Next;

  if (index > list_size - 1)
    return head;

  int ctr = 0;
  struct Node *beg = head;

  while (head && (++ctr) < index)
    head = head->Next;

  struct Node *node_to_free = head->Next;
  head->Next = head->Next->Next;
  free(node_to_free);

  return beg;
}

void sort_list(struct Node *head) {

  int i, j, k, tempValue;
  struct Node *begin = head;
  struct Node *current;
  struct Node *Next;

  int size = 0;

  while (head) {
    head = head->Next;
    ++size;
  }

  k = size;
  head = begin;

  for (i = 0; i < size - 1; i++, k--) {

    current = head;
    Next = head->Next;

    for (j = 1; j < k; j++) {

      if (current->Value > Next->Value) {
        tempValue = current->Value;
        current->Value = Next->Value;
        Next->Value = tempValue;
      }

      current = current->Next;
      Next = Next->Next;
    }
  }
}

int search_val(struct Node *head, int val) {

  int ctr = 0;

  while (head)
    if (head->Value == val)
      return ctr;
    else {
      ++ctr;
      head = head->Next;
    }

  return -1;
}

struct Node *merge_lists(struct Node *list1, struct Node *list2) {

  struct Node *beg = list1;

  while (list1 && list1->Next)
    list1 = list1->Next;

  list1->Next = list2;

  // sort_list(beg);

    return beg;
}

struct DNode {
  int Value;
  struct DNode *Next;
  struct DNode *Prev;
};

struct DNode *traverse_backwards(struct Node *head) {

  if (!head)
    return 0;

  struct DNode *beg, *list, *prev;

  beg = list = prev = (struct DNode *)malloc(sizeof(struct DNode));

  while (head) {

    list->Value = head->Value;

    struct DNode *new_dnode = (struct DNode *)malloc(sizeof(struct DNode));

    if (head && head->Next)
      list->Next = new_dnode;

    else {
      list->Next = 0;
      return list;
    }
    prev = list;
    list = list->Next;

    list->Prev = prev;
    head = head->Next;
  }

  return list;
}

void print_backwards(struct DNode *tail) {

  if (!tail)
    return;

  printf("\n");

  while (tail) {
    printf("%d ", tail->Value);
    tail = tail->Prev;
  }

  printf("\n");

  return;
}



void print_help_message() {
  printf("\n1 - Append\n"
         "2 - Prepend\n"
         "3 - Reverse the list\n"
         "4 - Add by index\n"
         "5 - Remove by index\n"
         "6 - Sort the list\n"
         "7 - Search for value\n"
         "8 - Merge lists\n"
         "9 - Print the list \n"
         "10 - Print the list backwards\n"
         "11 - Save to file\n"
         "12 - Load from file\n"
         "0 - Quit\n");
  return;
}

int get_param(const char *msg) {

  printf("\nPlease choose %s\n", msg);

  int opt;
  scanf("%d", &opt);

  return opt;
}

struct Node *ret_new_list() {

  printf("creating a new list... merging it later with the existing one\nuse "
         "-1 to stop feeding values");

  struct Node *new_list = (struct Node *)malloc(sizeof(struct Node));
  new_list->Value = get_param("a value");

  int opt = get_param("a value");

  while (opt != -1) {
    append(new_list, opt);
    opt = get_param("a value");
  }

  return new_list;
}

void save_to_file(struct Node *list) {

  FILE *out_file = fopen(FILE_NAME, "w");

  if (out_file == NULL) {
    printf("Error! Could not open file\n");
    exit(-1);
  }

  struct Node *temp, *beg;
  beg = temp = (struct Node *)list;

  int sz = 0;

  while (temp) {
    ++sz;
    temp = temp->Next;
  }

  while (list) {

    if (list && list->Next)
      fprintf(out_file, "%d ", list->Value); // write to file
    else
      fprintf(out_file, "%d", list->Value); // write to file

    list = list->Next;
  }

  fclose(out_file);

  // list = beg;

  return;
}

void clear_list(struct Node *list) {

  struct Node *cur, *prev;
  cur = list;

  while (cur) {
    prev = cur;
    cur = cur->Next;
    free(prev);
  }

  return;
}

struct Node *load_from_file(struct Node *prev_list) {

  clear_list(prev_list);

  FILE *in_file = fopen(FILE_NAME, "r");

  if (in_file == NULL) {
    printf("Error! Could not open file\n");
    exit(-1);
  }

  struct Node *beg = (struct Node *)malloc(sizeof(struct Node));
  int val = 0;

  fscanf(in_file, "%d", &val);
  beg->Value = val;
  beg->Next = 0;

  int result = 0;

  while (fscanf(in_file, " %d", &val) == 1)
    append(beg, val);

  fclose(in_file);

  return beg;
}

void handle_user_input() {

  struct Node *beg = (struct Node *)malloc(sizeof(struct Node));
  beg->Value = get_param("an initial value for the list");

  while (1) {

    print_help_message();
    printf("\nPlease choose an option\n");

    int opt;
    scanf("%d", &opt);

    if (opt < 0 || opt > 12) {
      printf("\nwrong option was selected (%d)\n", opt);
      continue;
    }

switch (opt) {
    case 0: {
      return;
      break;
    }
    case 1: {
      append(beg, get_param("a value"));
      break;
    }
    case 2: {
      beg = prepend(beg, get_param("a value"));
      break;
    }
    case 3: {
      reverse_list(&beg);
      break;
    }
    case 4: {
      beg = add_by_index(beg, get_param("an index"), get_param("a value"));
      break;
    }
    case 5: {
      beg = remove_by_index(beg, get_param("an index"));
      break;
    }
    case 6: {
      sort_list(beg);
      break;
    }
    case 7: {
      int ind = search_val(beg, get_param("a value"));
      if (ind != -1)
        printf("The node was found at index %d\n", ind);
      else
        printf("The node was not found inside the list\n");

      break;
    }
    case 8: {
      struct Node *temp = (struct Node *)ret_new_list();
      merge_lists(beg, temp);
      break;
    }
    case 9: {
      print_list(beg);
      break;
    }
    case 10: {
      struct DNode *temp = (struct DNode *)traverse_backwards(beg);
      print_backwards(temp);
      break;
    }
    case 11: {
      save_to_file(beg);
      break;
    }
    case 12: {
      beg = load_from_file(beg);
      break;
    }
    }
  }
}

int main() {

  // test(beg);
  handle_user_input();

  return 0;
}