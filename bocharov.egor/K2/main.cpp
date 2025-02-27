#include <stdio.h>
#include <stdlib.h>

struct FwdList
{
  int value;
  struct FwdList *next;
};

struct FwdList* createList()
{
  struct FwdList *head = NULL, *tail = NULL;
  for (int i = 0; i < 10; i++)
  {
    struct FwdList *newNode = (struct FwdList*)malloc(sizeof(struct FwdList));
    if (!newNode)
    {
      fprintf(stderr, "Memory allocation error\n");
      exit(1);
    }
    newNode->value = i;
    newNode->next = NULL;
    if (head == NULL)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      tail->next = newNode;
      tail = newNode;
    }
  }
  return head;
}

struct FwdList* insertDuplicates(struct FwdList *head, int index, int count)
{
  struct FwdList *current = head;
  for (int i = 0; i < index && current != NULL; i++)
  {
    current = current->next;
  }
  if (current == NULL)
  {
    return NULL;
  }
  for (int i = 0; i < count; i++)
  {
    struct FwdList *newNode = (struct FwdList*)malloc(sizeof(struct FwdList));
    if (!newNode)
    {
      fprintf(stderr, "Memory allocation error\n");
      exit(1);
    }
    newNode->value = current->value;
    newNode->next = current->next;
    current->next = newNode;
    current = newNode;
  }
  return head;
}

void printList(struct FwdList *head)
{
  struct FwdList *current = head;
  while (current != NULL)
  {
    printf("%d ", current->value);
    current = current->next;
  }
  printf("\n");
}

void freeList(struct FwdList *head)
{
  struct FwdList *current = head;
  while (current != NULL)
  {
    struct FwdList *temp = current;
    current = current->next;
    free(temp);
  }
}

int main()
{
  struct FwdList *head = createList();
  int index, count;
  while (scanf("%d %d", &index, &count) == 2)
  {
    if (index < 0 || index >= 10 || count < 0)
    {
      fprintf(stderr, "Invalid input\n");
      continue;
    }
    head = insertDuplicates(head, index, count);
  }

  printList(head);
  freeList(head);
  return 0;
}
