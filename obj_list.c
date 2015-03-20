#include "raytracer.h"

int obj_list_length(obj_list* os)
{
	int n = 1;
	while (os != NULL)
	{
		n++;
		os = os->next;
	}
	return n;
}

char* obj_list_tos(obj_list* os)
{
	char* string = malloc(obj_list_length(os)*100);
	while (os != NULL)
	{
		strcat(string, object_tos(os->obj));
		os = os->next;
	}
	return string;
}

obj_list *ol_cons(object o, obj_list *os)
{
	if (os == NULL)
	{
		return ol_singleton(o);
	}
	obj_list* head = malloc(sizeof(obj_list));
	head->obj = o;
	head->next = os;
	return head;
}

obj_list *ol_singleton(object s)
{
	obj_list* head = malloc(sizeof(obj_list));
	head->obj = s;
	head->next = NULL;
	return head;
}

void ol_show(FILE *f, obj_list *os)
{
	fprintf(f, "%s", obj_list_tos(os));
}

void ol_free(obj_list *ss)
{
	if (ss != NULL)
	{
		ol_free(ss->next);
		free(ss);
	}
}

