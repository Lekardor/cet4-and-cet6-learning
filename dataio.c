//#include <iostream>
//using namespace std;
#include "head.h"
//#define LearnWordNum 10
int InitWordsline(wordsline wordsline_abc)
{
    //*wordsline_abc=(word*)malloc(sizeof(word));//????ָ��Ͳ��������
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
    }//to the end of line
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
    //word a = *wordsline_alpha;
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
            //printf("%s,%s,%d,%d,%d,%d,%d\n",mode.word_info,mode.word_meaning,mode.word_type,mode.word_sentences_number,mode.word_rem_times,mode.word_extrachar1,mode.word_extrachar2);
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
                sprintf(buf,"%s,\"%s\",%d,%d,%d,%d,%d\n",ptr->word_info,ptr->word_meaning,ptr->word_type,ptr->word_sentences_number,ptr->word_rem_times,ptr->word_extrachar1,
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
            //printf("%d%s\n",i+1,sentence_base[i].sentence_example);
            i++;
        }
    }
    free(fp);
}

int delWordLineNode(wordsline LinePtr, int n, word *e)
{//ɾ��������LinePtr�еĵ�n��Ԫ��(�յĽ�㲻��Ԫ��)����ͨ��e������ֵ,��n���ڵ������ȣ��򷵻������һ��ֵ
    wordsline ptr_word_a = LinePtr;
    //wordsline ptr_word_b;
    int vol = 1;
    if(emptyLine(LinePtr) == 0)
    {
        while(vol < n)//
        {
            if(ptr_word_a->nextword->nextword != NULL)
            {
                //ptr_word_b = ptr_word_a;

                ptr_word_a = ptr_word_a->nextword;//a��
            }
            else
            {
                *e = *ptr_word_a->nextword;
               // printf("%s          \\  %s\n",(*e).word_info,(*e).word_meaning);
                ptr_word_a->nextword = NULL;

                return OK;
            }

            vol++;
        }

        *e = *ptr_word_a->nextword;
       // printf("%s            %s\n",(*e).word_info,(*e).word_meaning);
        ptr_word_a->nextword = ptr_word_a->nextword->nextword;

        return OK;
    }

    return ERROR;
}

int emptyLine(wordsline LinePtr)
{//�ж�������ͷ��㣩�Ƿ�Ϊ�գ���Ϊ�շ���1���ǿշ���0
    if(LinePtr == NULL)
        exit(ERROR);
    if(LinePtr->nextword == NULL)
        return 1;
    else
        return 0;
}

int chooseWordInBase(wordsline a_to_z[],word portTargetWord[])
{//��ʺ���
    srand(time(0));

    int vol = 1;
    int i = rand()%25+1;
    int num;
    word temp;
    while(vol <= LearnWordNum)
    {
        num  = rand()%10+1;
        if(delWordLineNode(a_to_z[i],num,&temp) == OK )
        {
            portTargetWord[vol] = temp;
            vol++;
        }

        i = i % 25;
        i++;
    }


    //bianli(a_to_z);
    for(vol = 1;vol <= LearnWordNum;vol++)
    {
       // printf("%s            %s\n",portTargetWord[vol].word_info,portTargetWord[vol].word_meaning);
    }

    return OK;
}
