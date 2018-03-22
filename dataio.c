//#include <iostream>
//using namespace std;
#include "head.h"
//#define LearnWordNum 10
int InitWordsline(wordsline wordsline_abc)
{
    //*wordsline_abc=(word*)malloc(sizeof(word));//????指针和参数搞混了
    if(!(wordsline_abc))
        exit(ERROR);
    else
        (wordsline_abc)->nextword=NULL;
    return OK;
}

int EnWordsline(word e,wordsline wordsline_abc)
{
    wordsline p,q;
    q=wordsline_abc;
    while(q->nextword!=NULL)
    {
        q=q->nextword;
    }
    p=(word*)malloc(sizeof(word));
    if(!p)
        exit(ERROR);
    else
    {
        strcpy(p->word_info,e.word_info);
        strcpy(p->word_meaning,e.word_meaning);
        p->word_rem_times=e.word_rem_times;
        p->word_sentences_number=e.word_sentences_number;
        p->word_type=e.word_type;
        p->word_extrachar1=e.word_extrachar1;
        p->word_extrachar2=e.word_extrachar2;
        q->nextword=p;
        p->nextword=NULL;
    }
    word a = *p;
    word b = *q;
    return OK;
}

char* CreateNewRoute(char alpha)
{

    char *NewRoute=(char*)malloc(4*sizeof(char));
    NewRoute[0]=alpha;
    strcpy(NewRoute+1,".csv");
    return NewRoute;
}
void CreateWordsLine(wordsline wordsline_alpha,char alpha)
{

    InitWordsline(wordsline_alpha);
    word a = *wordsline_alpha;
    FILE*fp;
    char buf[100];
    word mode;
    if((fp=fopen(CreateNewRoute(alpha),"r+"))==NULL)
        exit(ERROR);
    else
    {
        while(fgets(buf,101,fp)!=NULL)
        {
            sscanf(buf,"%[^','],\"%[^\"]\",%d,%d,%d,%d,%d",mode.word_info,mode.word_meaning,&mode.word_type,&mode.word_sentences_number,&mode.word_rem_times,&mode.word_extrachar1,
                   &mode.word_extrachar2);
            EnWordsline(mode,wordsline_alpha);
        }
    }
    fclose(fp);
}



void CreateWordBase(wordsline *words_base)
{
    int i;
    for(i=0;i<26;i++)
    {
    CreateWordsLine(words_base[i],'A'+i);
    word a=*(words_base[i]->nextword);
    }

}

void RewriteCSV(wordsline *words_base)
{
    int i=26;
    char buf[100];
    for(i=0;i<26;i++)
    {
        FILE*fp;
        if((fp=fopen(CreateNewRoute('A'+i),"w+"))==NULL)
            exit(ERROR);
        else
        {
            word* ptr=words_base[i];
            while(ptr!=NULL)
            {
                sprintf(buf,"%s,%s,%d,%d,%d,%d,%d\n",ptr->word_info,ptr->word_meaning,ptr->word_type,ptr->word_sentences_number,ptr->word_rem_times,ptr->word_extrachar1,
                   ptr->word_extrachar2);
                fprintf(fp,"%s",buf);
                ptr=ptr->nextword;
            }
        }
    }
}

void CreateSentence_base(sentence *sentence_base,int sentencenum)//done
{
    FILE*fp;
    char buf[MAX_SENTENCE_LENGTH];
    if((fp=fopen("sentences_base.txt","r+"))==NULL)
    {
        printf("wrong");
        exit(ERROR);
    }
    else
    {
        int i=0;
        while(fgets(buf,MAX_SENTENCE_LENGTH+1,fp)!=NULL&&i<sentencenum)
        {
            sscanf(buf,"%*[0-9].%[^\n]",sentence_base[i].sentence_example);
            sentence_base[i].sentence_number=i+1;
            //printf("%s\n",sentence_base[i].sentence_example);
            i++;
        }
    }
    free(fp);
}

int delWordLineNode(wordsline LinePtr, int n, word *e)
{//删除单链表LinePtr中的第n个元素，并通过e返回其值,若n大于单链表长度，则返回其最后一个值
    wordsline ptr_word_a = LinePtr;
    wordsline ptr_word_b;
    int vol = 1;
    if(emptyLine(LinePtr) == 0)
    {
        while(vol < n)
        {
            if(ptr_word_a->nextword != NULL)
            {
                ptr_word_b = ptr_word_a;
                ptr_word_a = ptr_word_a->nextword;//a走
            }
            else
            {
                *e = *ptr_word_a;
                ptr_word_b->nextword = NULL;

                return OK;
            }
            vol++;
        }
        ptr_word_a = ptr_word_a->nextword;
    //(*e).word_info = (ptr_word_a->nextword).word_info;
        strcpy(e->word_info,ptr_word_a->word_info);
        strcpy(e->word_meaning,ptr_word_a->word_meaning);
        e->word_sentences_number = ptr_word_a->word_sentences_number;
        e->word_type = ptr_word_a->word_type;
        e->word_rem_times = ptr_word_a->word_rem_times;
        e->word_extrachar1 = ptr_word_a->word_extrachar1;
        e->word_extrachar2 = ptr_word_b->word_extrachar2;
        //e->word_info = ptr_word_a->word_info;

        ptr_word_a = ptr_word_a->nextword;

        return OK;
    }

    return ERROR;
}

int emptyLine(wordsline LinePtr)
{//判断链表（含头结点）是否为空，若为空返回1，非空返回0
    if(LinePtr == NULL)
        exit(ERROR);
    if(LinePtr->nextword == NULL)
        return 1;
    else
        return 0;
}

int chooseWordInBase(wordsline a_to_z[],word portTargetWord[])
{//抽词函数
    int vol = 1;
    int i = rand()%24+1;
    int num  = rand()%10+1;
    word temp;
    while(vol <= LearnWordNum)
    {
        if(delWordLineNode(a_to_z[i],num,&temp) == OK )
        {
            portTargetWord[vol] = temp;
            vol++;
        }
        i = i % 25;
        i++;
    }

    return OK;
}
