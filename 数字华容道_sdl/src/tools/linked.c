#include "../api/base.h"
#include "./linked.h"

//后面添加Node
Link*linkAddNode(Link*head,void*node)
{
 printf("linkAddNode\n");
 Link*temp = linkGetEnd(head);
 if(temp->node!=NULL)
 {
  Link*next = LinkAlloc;
  next->node = node;
  next->prev = temp;
  next->next = NULL;
  temp->next = next;
  return next;
 }
 else
 {
  temp->node = node;
  return temp;
 }
}

//节点获取链接
Link*nodeGetLink(Link*link,void*node)
{
 Link*temp = linkGetHead(link);
 while(temp->node!=node)
 {
  temp = temp->next;
  if(temp==NULL)
  	break;
 }
 return temp;
}

//删除节点
void linkDelLink(Link*temp)
{
 Link*prev = temp->prev;
 Link*next = temp->next;
 if(prev!=NULL)
 	prev->next = next;
 if(next!=NULL)
 	next->prev = prev;
 free(temp);
}

//删除节点
void linkDelNode(Link*link,void*node)
{
 Link*temp = 
 nodeGetLink(link,node);
 linkDelLink(temp);
}

//获取结尾
Link*linkGetEnd(Link*head)
{
 Link*temp = head;
 while(temp->next!=NULL)
 	temp = temp->next;
 return temp;
}

//获取开头
Link*linkGetHead(Link*head)
{
 Link*temp = head;
 while(temp->prev!=NULL)
 	temp = temp->prev;
 return temp;
}

