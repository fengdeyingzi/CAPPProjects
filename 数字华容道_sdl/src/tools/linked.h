#ifndef _LINKED_H_
#define _LINKED_H_
#include "../api/base.h"

typedef struct _Link
{
 void*node;
 
 struct _Link*prev;
 struct _Link*next;
}Link;

typedef struct _LinkD
{
 Link *head;
}LinkD;

//为新的链表申请内存
#define LinkAlloc malloc(sizeof(Link))

//后面添加Node
extern Link*linkAddNode(Link*head,void*node);

//节点获取链接
extern Link*nodeGetLink(Link*link,void*node);

//删除节点
void linkDelLink(Link*temp);
extern void linkDelNode(Link*link,void*node);

//获取结尾
extern Link*linkGetEnd(Link*head);

//获取开头
extern Link*linkGetHead(Link*head);

#endif
