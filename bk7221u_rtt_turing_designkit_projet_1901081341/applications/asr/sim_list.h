#ifndef _MW_SIM_LIST_H_
#define _MW_SIM_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>
#include <pthread.h>
#include "linux_list.h"


typedef void (*sim_list_free_func)(void *data);

//�ڵ�
typedef struct sim_list_node
{
	struct list_head hdr;

	char *data;
	int dlen;
}sim_list_node;

//
typedef struct
{
	int num;
	sim_list_node *pcur;	//��ǰ�Ľڵ㣬��Ҫ���ڱ�����ע��տ�ʼΪNULL

	struct list_head lst;

	sim_list_free_func free_func;
	pthread_mutex_t mutex;
}sim_list_s;

//��ʼ��
int sim_list_init(sim_list_s *li, void (*free_func) (void *));

//��ȫ�ͷţ������ٲ���
void sim_list_free(sim_list_s *li);

//ֻ��սڵ㣬���Լ�������
void sim_list_clear(sim_list_s *li);

//��ӽڵ�
int sim_list_add_node(sim_list_s *p, void *data, int len);

int sim_list_add_node_cpy(sim_list_s *p, char *data, int len);

//ȡ������
void* sim_list_pop_data(sim_list_s *li);
//ȡ��node��������Ҫ�ͷ�node��node->data�������ӽڵ�Ĳ�������
void * sim_list_pop_node(sim_list_s *li);

sim_list_node * sim_list_peek_node(sim_list_s *li);

sim_list_node * sim_list_peek_node_index(sim_list_s *li,int index);


//�������Ƴ������������ͷŴ�����Ҫ�ⲿ�ͷ�
int sim_list_remove_node(sim_list_s *p, sim_list_node *node);


int sim_list_remove_free_node(sim_list_s *li, sim_list_node *node);

//psrc�Ľڵ�ת��pdst
void sim_list_trans(sim_list_s *psrc, sim_list_s *pdst);

//ѭ����ȡ��һ���ڵ��ָ��
sim_list_node *sim_list_next_node(sim_list_s *psal, int *is_loop);

/*
 *������ʽ1
 *����˳�� :
 *	sim_list_loop_init
 *	sim_list_loop_get_data * n ѭ����ȡ�ڵ㣬����NULL˵���ѻ�ȡ���нڵ�
 *	sim_list_loop_deinit
 *
 *sim_list_loop_init �� sim_list_loop_deinit�ֱ�ʹ���˼���/����, �������
 */
void sim_list_loop_init(sim_list_s *li);
void sim_list_loop_deinit(sim_list_s *li);
void *sim_list_loop_get_data(sim_list_s *li);


/*
 *������ʽ2
 *�ص���ʽ��������ÿ���ڵ���ûص�����������ص��������ط�0����ֹ����
 *ע���ڻص��в�Ҫ����sim_list�Ĳ�������
 */
enum
{
	SL_TRAVE_CONTINUE = 0,	//��������
	SL_TRAVE_BREAK//��ֹ����
};
void sim_list_traverse(sim_list_s *li, int (*on_node_func) (void *user_data, void *pdata), void *user_data);
void sim_list_traverse_nolck(sim_list_s *li, int(*on_node_func) (void *user_data, void *pdata), void *user_data);

enum
{
	SL_TRAVE_CONTINUE_TRV = 0,	//��������
	SL_TRAVE_BREAK_TRV,		//��ֹ����
	SL_TRAVE_REMOVE_RETURN,	//ɾ����ǰ�ڵ�,����ֹ����
	SL_TRAVE_REMOVE_CONTINUE//ɾ����ǰ�ڵ�,��������
};
//�����������ûص�����cmp_func������cmp_func����ֵ�����Ƴ��ڵ�(����Ҫ�����û�����,�Ƴ�ֻ����SL_TRAVE_REMOVE_RETURN)���������û�����
void* sim_list_cmp_remove(sim_list_s *li, int (*cmp_func) (void *user_data, void *pdata), void *user_data);
void* sim_list_cmp_remove_nolck(sim_list_s *li, int(*cmp_func) (void *user_data, void *pdata), void *user_data);

void* sim_list_cmp_peek_data(sim_list_s *li,int (*cmp_func) (void *user_data, void *pdata), void *user_data);
////�����������ûص�����cmp_func������cmp_func����ֵ�����Ƴ��ڵ㣬���ͷ��û�����
void sim_list_cmp_remove_free(sim_list_s *li, int(*cmp_func) (void *user_data, void *pdata), void *user_data);


static int sim_list_empty(sim_list_s *p)
{
	struct list_head *head = &p->lst;
	return head->next == head;
}

static int sim_list_count(sim_list_s *p)
{
	int cnt = 0;
	struct list_head *head = &p->lst;
	struct list_head *pos = head->next;
	while(pos != head){
		cnt+=1;
		pos = pos->next;
	}
	return cnt;
}


#ifdef __cplusplus
}
#endif

#endif
