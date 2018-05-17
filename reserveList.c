typedef struct node
{
	int value;
	node * next;
}node;
node* reverse(node* list)
{
	if(!list || !(list->next)) return list;
	node * head = list;
	node * p = list->next;
	node * ppre = list;
	while(p)
	{
		ppre->next = p->next;
		p->next = head;
		head = p;
		p = ppre->next;
	}
	return head;
}