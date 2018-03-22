#include "head.h"
#include <stdio.h>
#include <stdlib.h>
/*#define morethan 1
#define lessthan -1
#define equal 0

#define LH 1//���
#define EH 0//�ȸ�
#define RH -1//�Ҹ�

#define Boolean int
#define true 1
#define false 0

typedef struct BSTNode
{
    word wordnord;
    int bf;   //�ڵ��ƽ������
    struct BSTNode *lchild,*rchild;//���Һ���ָ��
}BSTNode, *BSTree;*/

void R_Rotate(BSTree p)  //����ת
{
    BSTree lc;
    lc=p->lchild;
    p->lchild=lc->rchild;
    lc->rchild=p;
    p=lc;
}

void L_Rotate(BSTree p)  //����ת
{
    BSTree rc;
    rc=p->rchild;
    p->rchild=rc->lchild;
    rc->lchild=p;
    p=rc;
}

void LeftBalance(BSTree t)//��ƽ��
{
    BSTree lc;
    BSTree rd;
    lc=t->lchild;
    switch(lc->bf)
    {
    case LH:
        t->bf=lc->bf=EH;
        R_Rotate(t);
        break;
    case RH:
        rd=lc->rchild;
        switch(rd->bf)
        {
        case LH:
            t->bf=RH;
            lc->bf=EH;
            break;
        case EH:
            t->bf=lc->bf=EH;
            break;
        case RH:
            t->bf=EH;
            lc->bf=LH;
            break;
        }
        rd->bf =EH;
        L_Rotate(t->lchild);
        R_Rotate(t);
        break;
    }
}

void RightBalance(BSTree t)//��ƽ��
{
    BSTree rc;
    BSTree ld;
    rc=t->rchild;
    switch(rc->bf)
    {
    case RH:
        t->bf=rc->bf=EH;
        L_Rotate(t);
        break;
    case LH:
        ld=rc->lchild;
        switch(ld->bf)
        {
        case LH:
            t->bf=EH;
            rc->bf=RH;
            break;
        case EH:
            t->bf=rc->bf=EH;
            break;
        case RH:
            t->bf=LH;
            rc->bf=EH;
            break;
        }
        ld->bf =EH;
        R_Rotate(t->rchild);
        L_Rotate(t);
        break;
    }
}

int wordcomparing(char* a,char* b)//�Ƚ��������ʴ�С
{
    int i=0;
    while(a[i]!='\0'&&b[i]!='\0')//���αȽϸ�����ĸ��С
    {
        if(a[i]>b[i])
            {
                return morethan;
            }
        if(a[i]<b[i])
            {
                return lessthan;
            }
        else
            {
                i++;
            }
    }
    if(strlen(a)>strlen(b))
    {
        return morethan;
    }
    if(strlen(a)<strlen(b))
    {
        return lessthan;
    }
    else
    {
        return equal;
    }
}

int InsertAVL(BSTree* t,word a, Boolean *taller)//ƽ��������Ĳ������
{
    word b;
    if(!*t)//�����½ڵ�
    {
        *t=(BSTree)malloc(sizeof(BSTNode));
        (*t)->wordnord=a;
        (*t)->lchild=(*t)->rchild=NULL;
        (*t)->bf=EH;
        *taller=true;
    }
    else
    {
        if(wordcomparing((*t)->wordnord.word_info,a.word_info)==equal)
        {
            *taller=false;
            return 0;
        }
        if(wordcomparing((*t)->wordnord.word_info,a.word_info)==morethan)
        {
            if(!InsertAVL(&((*t)->lchild),a,taller))
            {
                return 0;
            }
            if(*taller)
            {
                switch((*t)->bf)
                {
                case LH:
                    LeftBalance((*t));
                    *taller=false;
                    break;
                case EH:
                    (*t)->bf=LH;
                    *taller=true;
                    break;
                case RH:
                    (*t)->bf=EH;
                    *taller=false;
                    break;
                }
            }

        }
        else
        {
           if(!InsertAVL(&((*t)->rchild),a,taller))
           {
               return 0;
           }
           if(*taller)
            {
                switch((*t)->bf)
                {
                case LH:
                    (*t)->bf=EH;
                    *taller=false;
                    break;
                case EH:
                    (*t)->bf=RH;
                    *taller=true;
                    break;
                case RH:
                    RightBalance((*t));
                    *taller=false;
                    break;
                }
            }
        }
    }
    b=(*t)->wordnord;
    return 1;
}

BSTree buildBSTree(wordsline line)//һ��AVL������
{
    BSTree t;
    t=NULL;
    wordsline copy;
    Boolean *taller=(Boolean*)malloc(sizeof(Boolean));
    *taller=1;
    copy = line;
    word a;
    do
    {
        copy=copy->nextword;
        InsertAVL(&t,*copy,taller);
        a=*copy;
    }while(copy->nextword!=NULL);
   // word a=t->wordnord;
    free(taller);
    return t;
}

BSTree* buildallTree(wordsline wordbase[],int n)
{
    int i;
    BSTree *alltree=(BSTree*)malloc(26*sizeof(BSTree));
    for(i=0;i<n;i++)
    {
        alltree[i]=buildBSTree(wordbase[i]);
    }
    //word a=alltree[0]->wordnord;
    //printf("%d",alltree[0]->wordnord.word_type);
    return alltree;
}
BSTree wordsearch(BSTree t,char* a)//��������
{
    if(wordcomparing((t->wordnord).word_info,a)==equal)
    {
        return t;
    }
    if(wordcomparing(t->wordnord.word_info,a)==morethan)
    {
        return wordsearch(t->lchild,a);
    }
    else
    {
        return wordsearch(t->rchild,a);
    }
}

BSTree choosetree(char* a,BSTree alltree[],int n)
{
 //   printf("c",alltree[0]->wordnord.word_info[0]);
    int i;
    BSTree result = (BSTree)malloc(sizeof(BSTNode));
    for(i=0;i<n;i++)
    {
        if(a[0]==(alltree[i]->wordnord).word_info[0])
        {
            result=wordsearch(alltree[i],a);
            return result;

        }
    }
    free(result);
    return NULL;
}

