struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
ListNode* getmid(ListNode* head);
ListNode* sortList(ListNode* head);
ListNode* merge(ListNode* head1, ListNode* head2);

ListNode* sortList(ListNode* head) {
    if(head == NULL || head->next == NULL)
        return head;
    ListNode* head1 = head;
    ListNode* head2 = getmid(head);
    head1 = sortList(head1);
    head2 = sortList(head2);
    return = merge(head1, head2);
}
ListNode* getmid(ListNode* head)
{
    ListNode* slow = head;
    ListNode* fast = head->next;
    while(slow != NULL && fast != NULL)
    {
        if(fast != NULL)
            fast = fast->next;
        else
            break;
        if(fast != NULL)
            fast = fast->next;
        else
            break;
        slow = slow -> next;
    }
    fast = slow;
    slow = slow->next;
    fast->next = NULL;
    return slow;
}
ListNode* merge(ListNode* head1, ListNode* head2)
{
    ListNode* head = new ListNode(-1);
    ListNode* tail = head;

    while(head1 != NULL && head2 != NULL)
    {
        if(head1->val >= head2->val)
        {
            tail->next = head1;
            head1 = head1->next;
        }
        else
        {
            tail->next = head2;
            head2 = head2->next;
        }
        tail = tail->next;
        tail->next = NULL;
    }
    if(head1 != NULL)
    {
        tail->next = head1;
    }
    if(head2 != NULL)
    {
        tail->next = head2;
    }
    tail = head;
	head = head->next;
    delete(tail);
    return head;
}