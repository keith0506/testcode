typedef struct node
{
	int value;
	node * next;
}node;

class stack{
public:
	stack():cnt(0),head(NULL),mhead(NULL){};
	void push(int v);
	int pop();
	int mini();
private:
	int cnt;
	int min;
	node* head;
	node* mhead;
};
void stack::push(int v)
{
	node* p = new(node);
	node* q = new(node);
	p->value = v;
	if(!head)
	{
		head = p;
		head->next = NULL;
		q->value = v;
		min = v;
		mhead = q;
		mhead->next = NULL;
	}
	else
	{
		p->next = head;
		head = p;
		if(v < min)
		{
			q->value = v;
			min = v;
		}
		else
		{
			q->value = min;
		}
		q->next = mhead;
		mhead = q;
	}
	cnt++;
}
int stack::pop()
{
	if(cnt <= 0)
		return -1;
	node *p = head;
	int res = p->value;
	head = head->next;
	delete(p);
	p = NULL;

	node *q = mhead;
	mhead = mhead->next;
	if(mhead)
		min = mhead->value;
	delete(q);
	q = NULL;
	cnt--;
	return res;
}
int stack::mini()
{
	return min;
}