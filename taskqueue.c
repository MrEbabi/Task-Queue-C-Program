#include <stdio.h>
#include <stdlib.h>

struct lst_node_s;
struct tsk_node_s;

int Insert(int value);
int Search(int value);
int Delete(int value);

void Task_queue(int n);;
void Task_enqueue(int task_num, int task_type, int value);
void Task_dequeue();

//helper function to convert command line argument to integer
int myatoi(const char *str) {
    int i, res = 0;
    for (i = 0; str[i] != '\0'; ++i) {
        res = res * 10 + str[i] - '0';
    }
    return res;
}

// Struct for list nodes
struct lst_node_s 
{
	int data; 
	struct lst_node_s *head, *next;
}list;

// Struct for task nodes
struct tsk_node_s 
{
	int task_num; //starting from 0   
	int task_type; // insert:0, delete:1, search:2   
	int value;   
	int countTask;
	struct tsk_node_s *head, *next;
}queue;

//insert function will insert the given value to the list
int Insert(int value)
{
	struct lst_node_s *temp;
	temp=(struct lst_node_s*)malloc(sizeof(struct lst_node_s));
	temp->data=value;
	temp->next=NULL;
	//if the list is empty or the given value is smaller than the head value of the list, add the value at the beginning of the list
	if(!list.head || list.head->data>value)
	{
		temp->next=list.head;
		list.head=temp;
		return value;
	}
	//if list is not empty and the given value is greater than the head value of the list, add the value to the list properly (ascending order)
	else
	{
		if(!Search(value))
		{
			struct lst_node_s *tempL=list.head;
			//while it is not the end of list and the current data is smaller than the given value, keep traversing
			while(tempL->next!=NULL && tempL->next->data<value)
			{
				tempL=tempL->next;
			}
			//traverse is finished, add the given value (element) to the list
			temp->next=tempL->next;
			tempL->next=temp;
			return value;
		}
	}
	return 0;
}

//search functoin will search the given value in the list
int Search(int value)
{
	//a temporary pointer to traverse the whole list for searching the given value
	struct lst_node_s *temp=list.head;
	//traverse until the end of the list
	while(temp!=NULL)
	{
		//if found, return the value
		if(temp->data==value) return value;
		temp=temp->next;
	}
	//if not found, return 0
	return 0;
}

//delete function will delete the given value from the list
int Delete(int value)
{
	//temporary objects are created
	struct lst_node_s *temp=list.head;
	struct lst_node_s *connectList;
	//if there is no element in the list, return
	if(!temp) return 0;
	//if the first element will be deleted, delete it and make the head of the list as next element
	if(temp->data==value)
	{
		temp=temp->next;
		list.head=temp;
		return value;
	}
	//if an element (which is not the first) will be deleted, delete it and connect the list again
	else
	{
		//traverse same as in the search
		while(temp->next!=NULL)
		{
			if(temp->next->data==value)
			{
				connectList=temp->next->next;
				temp->next=connectList;
				list.head=temp;
				//if deleted, return the value
				return value;
			}
			temp=temp->next;
		}
	}
	//if not deleted, return 0
	return 0;
}

//n tasks and values for the functions are generating randomly and after the each task generation the task is pushed (enqueued) to the task queue
void Task_queue(int n)
{	
	//srand function (and rand function) of stdlib.h is used (will be used) to generate random tasks (and values)
	srand(time(NULL));
	int i, random, randomNumber;
	//for loop using given n (number of tasks) to determine random tasks
	for(i=0;i<n;i++)
	{
		random = rand()%3;
		//insert=0
		if(random==0)
		{
			//random value is generating and the insert task for it is enqueued (pushed) to the task queue
			randomNumber = rand()%9+1;
			Task_enqueue(i, 0, randomNumber);
		}
		//search=1
		else if(random==1)
		{
			//random value is generating and the search task for it is enqueued (pushed) to the task queue
			randomNumber = rand()%9+1;
			Task_enqueue(i, 1, randomNumber);
			
		}
		//delete=2
		else if(random==2)
		{
			//random value is generating and the delete task for it is enqueued (pushed) to the task queue
			randomNumber = rand()%9+1;
			Task_enqueue(i, 2, randomNumber);
		}
	}
}

//enqueue fucntion will push the n tasks and numbers that are created before to the queue
void Task_enqueue(int task_num, int task_type, int value)
{
	struct tsk_node_s *temp;
	temp=(struct tsk_node_s*)malloc(sizeof(struct tsk_node_s));
	temp->task_num=task_num;
	temp->task_type=task_type;
	temp->value=value;
	temp->next=NULL;
	//for adding the first task to the queue
	if(!queue.head)
	{
		queue.head=temp;
	}
	else
	{
		//adding the task to the end of the queue
		struct tsk_node_s *tempQ=queue.head;
		//traverse until the end of the queue
		while(tempQ->next!=NULL)
		{
			tempQ=tempQ->next;
		}
		//add at the end of the queue
		tempQ->next=temp;
	}
}

//dequeue function will pull the n tasks and numbers that are created before from the queue
void Task_dequeue()
{
	struct tsk_node_s *temp;
	temp=(struct tsk_node_s*)malloc(sizeof(struct tsk_node_s));
	//error catching if queue is empty
	if(!queue.head)
	{
		printf("Error: The queue is empty. \n");
		return;
	}
	else
	{
		//dequeue (pull) the task from the task queue
		temp=queue.head;
		queue.head=queue.head->next;
	}
	//implement the dequeued (pulled) task from the task queue
	int success;
	printf("task %d-", temp->task_num);
	if(temp->task_type==0)
	{
		//insert task is pulled (dequeued) from the task queue
		printf("insert %d: ", temp->value);
		success=Insert(temp->value);
		if(success)	printf("%d is inserted", success);
		else printf("%d cannot be inserted",temp->value);
	}
	if(temp->task_type==1)
	{
		//search task is pulled (dequeued) from the task queue
		printf("search %d: ", temp->value);
		success=Search(temp->value);
		if(success)	printf("%d is found", success);
		else printf("%d cannot be not found",temp->value);
	}
	if(temp->task_type==2)
	{
		//delete task is pulled (dequeued) from the task queue
		printf("delete %d: ", temp->value);
		success=Delete(temp->value);
		if(success)	printf("%d is deleted", success);
		else printf("%d cannot be deleted",temp->value);
	}
	printf("\n");
	return;
}

//main function
int main(int argc, char **argv)
{
	list.head=NULL;
	queue.head=NULL;
	//using myatoi function, the given command line argument converting to integer
	int task_number = myatoi(argv[1]);
	printf("Generated %d random list tasks...\n", task_number);
	//generating tasks
	Task_queue(task_number);
	//dequeue (pull) tasks one by one until queue becomes empty
	struct tsk_node_s *tempQ=queue.head;
	while(tempQ)
	{
		Task_dequeue();
		tempQ=tempQ->next;
	}
	//display list
	printf("Final List: \n\t-");
	struct lst_node_s *tempL=list.head;
	while(tempL)
	{
		printf(" %d -", tempL->data);
		tempL=tempL->next;
	}
	printf("\n");
	return 0;
}

