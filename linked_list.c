#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node
{
	struct node *prev;
	int d ;
	struct node *next;
} ;

struct node *build();

struct node *build2();

struct node *build3();

void show(struct node **headref);

void push_front(struct node **headref, int a) ;

void push_tail(struct node **headref, int a) ;

int linked_len(struct node **headref) ;

int count(struct node **headref, int a) ;

int getnth(struct node **headref, int a) ;

void delete_list(struct node **headref) ;

int pop(struct node **headref) ;

void insert_nth(struct node **headref, int pos, int a) ;

void sorted_insert(struct node **headref, struct node* a) ;

void insert_sort(struct node **headref) ;

void append(struct node **headref1, struct node **headref2) ;

struct node *front_back_split(struct node **headref) ;

void remove_duplicate(struct node **headref) ;

void move_node(struct node **destref, struct node **srcref) ;

void alternating_split(struct node **src, struct node **aref, struct node **bref) ;

struct node *shuffle_merge(struct node **a, struct node **b) ;

struct node *sorted_merge(struct node **a, struct node **b) ;

struct node *merge_sort(struct node **a);

struct node *sorted_intersect(struct node **a, struct node **b);

void reverse(struct node **headref);

void recursive_reverse(struct node **headref) ;

int main()
{
	struct node *a = build3(), *b = build2(), *c = NULL;
	show(&a);
	show(&b);
	append(&a,&b);
	show(&a);
	c = merge_sort(&a);
	show(&c);	
}

struct node *build()
{
	struct node *head = (struct node *)calloc(sizeof(struct node),1), *ptr, *buffer;
	head->prev = NULL;
	head->next = NULL;
	head->d = 2;
	buffer = head;
	for(int i = 3; i < 10 ; i++)
	{
		ptr = (struct node *)calloc(sizeof(struct node),1);
		buffer->next = ptr;
		ptr->prev = buffer;
		ptr->next = NULL;
		ptr->d = i;
		buffer = ptr;
	}
	return head;
}

struct node *build2()
{
	struct node *head = (struct node *)calloc(sizeof(struct node),1), *ptr, *buffer;
	head->prev = NULL;
	head->next = NULL;
	head->d = 2;
	buffer = head;
	for(int i = 4; i < 20 ; i=i+2)
	{
		ptr = (struct node *)calloc(sizeof(struct node),1);
		buffer->next = ptr;
		ptr->prev = buffer;
		ptr->next = NULL;
		ptr->d = i;
		buffer = ptr;
	}
	return head;
}

struct node *build3()
{
	struct node *head = (struct node *)calloc(sizeof(struct node),1), *ptr, *buffer;
	head->prev = NULL;
	head->next = NULL;
	head->d = 2;
	buffer = head;
	for(int i = 9; i > 1 ; i--)
	{
		ptr = (struct node *)calloc(sizeof(struct node),1);
		buffer->next = ptr;
		ptr->prev = buffer;
		ptr->next = NULL;
		ptr->d = i;
		buffer = ptr;
	}
	return head;
}

void show(struct node **headref)
{
	if (*headref == NULL)
	{
		printf("\nList Does Not Exist\n");
		return;
	}
	struct node *ptr;
	for(ptr = *headref; ptr->next != NULL;ptr = ptr->next)
	{
		printf("->%d",ptr->d);
	}
	printf("->%d\n",ptr->d );
}

void push_front(struct node **headref, int a)
{
	// create new node
	struct node *ptr = (struct node *)malloc(sizeof(struct node)) ;
	// if empty list
	if (*headref ==  NULL)
	{
		*headref = ptr ;
		ptr->next = NULL;
		ptr->prev = NULL;
	}
	else
	{
		// set the next address of the new node to the existing node
		ptr->next = *headref ;
		// set the previous pointer in current node to new node
		(*headref)->prev = ptr ;
		// set the head to address of new pointer
		*headref = ptr ;
		// input the data
		(*headref)->d = a ;
		//create a NULL
		(*headref)->prev = NULL;
	}
}

void push_tail(struct node **headref, int a)
{
	struct node *ptr = NULL ;
	// if empty list
	if (*headref ==  NULL)
	{
		// create new node
		struct node *ptra = (struct node *)malloc(sizeof(struct node)) ;
		*headref = ptra ;
		ptra->d = a;
		ptra->next = NULL;
		ptra->prev = NULL;
		return;
	}

	for( ptr = *headref ; ptr->next != NULL ; ptr = ptr->next)
	{
		// loop to save the address of last node int the linked list
		// can be done with while loop too
		// just experimenting
	}
	// allocate and save the address of the new node
	ptr->next = (struct node *)malloc(sizeof(struct node)) ;
	// set the previous of the new last node to address of current node
	ptr->next->prev = ptr ;
	// input the data
	ptr->next->d = a ;
	//create a NULL
	ptr->next->next = NULL;
}

int linked_len(struct node **headref)
{
	if(*headref == NULL)
	{
		return 0 ;
	}
	int i = 1;
	struct node *ptr = *headref ;
	while( (ptr->next) != NULL )
	{
		ptr = ptr->next;
		i++ ;
	}
	return i ;
}

int count(struct node **headref, int SearchFor)
{
	int i = 0 ;
	struct node *ptr = *headref ;

	if ( ptr == NULL )
	{
		return -1 ;
	}

	do
	{
		if((ptr->d)==SearchFor)
		{
			i++ ;
		}
		ptr = ptr->next;
	}while(ptr->next != NULL);
	// returns the number of times the passed value SearchFor ocurrs
	return i;
}

int getnth(struct node **headref, int a)
{
	struct node *ptr = *headref ;

	if ( *headref == NULL)
	{
		return -1 ;
	}

	for(int i = 0; i<(a) ; i++)
	{
		ptr = ptr->next ;
	}

	return ptr->d ;
}

void delete_list(struct node **headref)
{
	// save the pointer of next element and then delete current node by accesssing the prev pointer in next node
	struct node *ptr = (*headref)->next ;

	// the following while loop terminates when it reaches last element but does not delete the last element
	while((ptr->next) != NULL)
	{
		free(ptr->prev);
		ptr = ptr->next;
	}
	// to free the last node
	free(ptr);
	// intialize head element
	*headref = NULL ;
}

int pop(struct node **headref)
{
	int temp ;

	if(*headref != NULL)
	{
		temp = (*headref)->d ;
		if((*headref)->next == NULL)
		{
			free(*headref);
			*headref = NULL;
			return temp;
		}
		else
		{
			*headref = (*headref)->next ;
			free((*headref)->prev) ;
			(*headref)->prev = NULL ;
			return temp;
		}
	}
	else
	{
		return 0;
	}
}

void insert_nth(struct node **headref, int pos, int a)
{
	if (pos == 0)
	{
		push_front(headref,a);
		return;
	}
	struct node *ptr = NULL ;
	int i = 0 ;
	for( i = 0 , ptr = *headref ; i<(pos) ; ptr = ptr->next , i++ )
	{
		if (ptr->next == NULL)
		{
			//reached end
			push_tail(headref,a);
			return;
		}
		// loop to save the address of node at position pos where pos = index int the linked list
	}
	// now that we have found the required node
	// we doo complex code so that we use only one structure pointer
	// first set the next of prev node of current node to the new node
	ptr->prev->next = (struct node *)calloc(sizeof(struct node),1) ;
	// now coming to new node set its prev to previous of current node
	ptr->prev->next->prev = ptr->prev ;
	// set the next node of the new node to current node
	ptr->prev->next->next = ptr;
	// finally set the prev pointer of the current node to the new node
	ptr->prev = ptr->prev->next ;
	// input the value
	ptr->prev->d = a ;
}

void sorted_insert(struct node **headref, struct node* a)
{
	//printf("ENTERED SORT FOR %d\n", a->d);
	if (*headref == NULL)
	{
		*headref = a ;
		a->next = NULL ;
		a->prev = NULL ;
		return ;
	}
	else
	{
		// pass
	}

	struct node *ptr = *headref ;
	int i = 0 ;
	//printf("ENTERING SORT WHILE\n");
	while( (ptr->d)<(a->d) )
	{
		i++ ;
		//printf("%d\n",ptr->d);
		
		// if we reach end
		if (ptr->next == NULL)
		{
			//printf("PUSHED TAIL\n");
			//show(headref);
			push_tail(headref,a->d);
			// free a since push alocates its own memory
			free(a);
			return;
		}
		ptr = ptr->next ;
	}

	// we need to insert the data after the node that ptr is currently pointing to
	insert_nth(headref,i,a->d) ;
	// free the already allocated node since insert_nth creates new node
	free(a);
}

void insert_sort(struct node **headref)
{
	//printf("ENTERED\n");
	if (*headref == NULL)
	{
		// empty list
		//printf("EMPTY\n");
		return;
	}
	else if ((*headref)->next == NULL)
	{
		// one element list
		//printf("ONE\n");
		return;
	}
	else if ((*headref)->next->next == NULL)
	{
		// two element list
		//printf("TWO\n");
		if (((*headref)->d) > ((*headref)->next->d))
		{
			int t = pop(headref);
			push_tail(headref,t);
		}
		return;
	}
	else
	{
		//go ;)
	}
	// code to sort more elements
	//printf("MULTI\n");
	struct node *cur = NULL ;
	struct node *com = NULL ;
	cur = (*headref)->next; // current, start from second node
	com = cur->next; // coming
	while(1)
	{
		// first unlink the current node and link its next and prev elements
		//printf("UNLINKING\n");
		//unlinking
		// the if statement is safeguard for last element's next pointer accessing, we need not worry of first element
		if(cur->next)
		{
			cur->next->prev = cur->prev;
		}
		cur->prev->next = cur->next;
		// unlinked
		//printf("UNLINKED\n");
		//remember that the sort function should be called upon the cur node
		//printf("CALLING\n");
		sorted_insert(headref,cur);
		//printf("CALLED\n");
		//show(headref);
		//printf("\n");
		//getch();
		// also remember that the sort should be called on the next node of cur node i.e com
		// we therefore set the cur accordingly
		cur = com;
		if(cur)
		{
			com = com->next;
		}
		else
		{
			break;
		}
	}

}
void append(struct node **headref1, struct node **headref2)
{
	struct node *ptr = *headref1;

	while(ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	if (*headref2==NULL)
	{
		return;
	}
	ptr->next = *headref2;
	ptr->next->prev = ptr;
	*headref2 = NULL;
}

struct node *front_back_split(struct node **headref)
{
	struct node *evenptr;
	struct node *oddptr;
	struct node *midptr;

	if ((*headref)->next == NULL)
	{
		return *headref;
	}
	else if ((*headref)->next->next == NULL)
	{
		midptr = (*headref)->next;
		(*headref)->next = NULL;
		midptr->prev = NULL;
		return midptr;
	}
	else
	{
		//pass;
	}

	for(oddptr = *headref, evenptr = (*headref)->next, midptr = *headref; ;
	    evenptr = evenptr->next->next, oddptr = oddptr->next->next, midptr = midptr->next)
	{
		// oddptr or even ptr either can encounter a null
		// if even list then evenptr encounter null and oddptr encounters a valid address
		// if odd list then odd ptr encounter null but even ptr could encounter an invalid address
		// so we first check oddptr and then even ptr instead of using && condition in loop header
		if (oddptr->next == NULL)
		{
			break;
		}
		else if (evenptr->next == NULL)
		{
			break;
		}
		else
		{
			continue;
		}
		continue;
	}

	// at the end of this loop the midptr would certainly be pointing to the correct item
	// i.e (n/2)th item if n is even and ((n+1)/2)th item if n is odd

	// now oddptr and evenptr are useless so use them as registers
	oddptr = midptr->next;
	midptr->next = NULL;
	oddptr->prev = NULL;
	return oddptr;
}

void remove_duplicate(struct node **headref)
{
	// remove duplicates from a sorted list

	int p = 0;
	struct node *ptra = *headref , *ptrb = (*headref)->next , *del;

	while((ptra->next->next) != NULL)
	{
		while((ptrb->next) != NULL)
		{
			if ((ptrb->d) == (ptra->d))
			{
				del = ptrb;
				ptrb = ptrb->next;
				del->prev->next = del->next;
				del->next->prev = del->prev;
				free(del);
			}


			ptrb = ptrb->next;
		}
		// to check last node
		if ((ptrb->d) == (ptra->d))
		{
			del = ptrb;
			del->prev->next = del->next;
			free(del);
		}
		ptra = ptra->next;
		ptrb = ptra->next;
	}
	return;
}

void move_node (struct node **dest, struct node **src)
{
	if (src == NULL)
	{
		// empty src
		return;
	}
	if (dest == NULL)
	{
		// empty dest
		*dest = *src;
		*src = (*src)->next;
		if (*src == NULL)
		{
			return;
		}
		else
		{
			(*src)->prev = NULL;
			return;
		}
	}
	//code when src and dest are both non empty
	int t = pop(src);
	push_front(dest,t);
	return;
}

void alternating_split(struct node **src, struct node **aref, struct node **bref)
{
	struct node *ptr = *src;

	while(ptr->next != NULL)
	{
		move_node(aref,src);
		move_node(bref,src);
		ptr = *src;
	}
}

struct node *shuffle_merge(struct node **a, struct node **b)
{
	struct node *ptr = NULL;
	int temp;
	while(1)
	{
		if(*a != NULL)
		{
			temp = pop(a);
			push_tail(&ptr,temp);
		}
		if(*b != NULL)
		{
			temp = pop(b);
			push_tail(&ptr,temp);
		}
		if( (*a == NULL) && (*b == NULL))
		{
			break;
		}
	}
	*a = ptr;
	return ptr;
}

struct node *sorted_merge(struct node **a, struct node **b)
{
	int temp;

	struct node *new_list = NULL;
	if (*a == NULL)
	{
		return (*b);
	}
	else if(*b == NULL)
	{
		return(*a);
	}
	else
	{
		// pass
	}

	while(1)
	{
		if (*a == NULL)
		{
			while(*b != NULL)
			{
				temp = pop(b);
				push_tail(&new_list,temp);
			}
			return(new_list);
		}
		else if(*b == NULL)
		{
			while(*a != NULL)
			{
				temp = pop(a);
				push_tail(&new_list,temp);
			}
			return (new_list);
		}
		else
		{
			// pass
		}

		if(((*a)->d) >= ((*b)->d))
		{
			temp = pop(b);
			push_tail(&new_list,temp);
		}
		else
		{
			temp = pop(a);
			push_tail(&new_list,temp);
		}
	}
}

struct node *merge_sort(struct node **a)
{
	struct node *ptra = *a;
	struct node *ptrb = NULL;
	struct node *ptrc = NULL;

	if((ptra)->next == NULL)
	{
		ptrc = sorted_merge(&ptra,&ptrb);
	}
	else
	{
		ptrb = front_back_split(&ptra);
		ptra = merge_sort(&ptra);
		ptrb = merge_sort(&ptrb);
	}
	ptrc = sorted_merge(&ptra,&ptrb);
	return ptrc;
}

struct node *sorted_intersect(struct node **a, struct node **b)
{
	int i=0, j=0;
	struct node *ptra = *a;
	struct node *ptrb = *b;
	struct node *ptrc = NULL;
	while(( ptra != NULL ) && ( ptrb != NULL ))
	{
		if(ptra->d == ptrb->d)
		{
			push_tail(&ptrc,ptra->d);
			ptra=ptra->next;
			ptrb= ptrb->next;
		}
		else
		{
			while( (ptra->d) < (ptrb->d) )
			{
				ptra=ptra->next;
				if(ptra == NULL)
				{return ptrc;}
			}
			while( (ptra->d) > (ptrb->d) )
			{
				ptrb= ptrb->next;
				if(ptrb == NULL)
				{return ptrc;}
			}

		}
	}
	return ptrc;
}
void reverse(struct node **headref)
{
	struct node *buffer, *ptr;
	if(*headref == NULL)
	{
		// no element
		return;
	}
	else if((*headref)->next == NULL)
	{
		// one element
		return;
	}
	else if((*headref)->next->next == NULL)
	{
		//two elements
		buffer = (*headref)->next;
		*headref = buffer->next;
		(*headref)->prev = NULL;
		(*headref)->next = buffer;
		buffer->prev = *headref;
		buffer->next = NULL;
	}
	else
	{
		//pass
	}
	buffer = *headref;
	ptr = buffer->next;
	// for first element
	buffer->next = NULL;
	buffer->prev = ptr;
	while(ptr->next != NULL)
	{
		ptr->prev = ptr->next;
		ptr->next = buffer;
		buffer = buffer->prev; // list is being reversed
		ptr = ptr->prev; // list is being reversed
	}
	// for last element
	ptr->prev = ptr->next;
	ptr->next = buffer;
	buffer = ptr;
	ptr = ptr->prev;

	*headref = buffer;
	return;
}

void recursive_reverse(struct node **headref)
{
	struct node *buffer = (*headref)->next;
	if ((*headref)->next == NULL)
	{
		(*headref)->next = (*headref)->prev;
		(*headref)->prev = buffer;
		return;
	}
	(*headref)->next = (*headref)->prev;
	(*headref)->prev = buffer;
	(*headref) = (*headref)->prev;
	recursive_reverse(headref);
}