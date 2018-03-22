#include "head.h"

#define MAX_SENTENCE_LENGTH 200
#define LearnWordNum 10


/*typedef struct QNode
{
    word date;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct LinkQueue
{
    QueuePtr front;
    QueuePtr rear;
    int LengthQueue;
}LinkQueue;*/

/*word portTargetWord[LearnWordNum];//目标单词接口
wordsline portTargetWordPtr[LearnWordNum];

int InitQueue(LinkQueue *Q);//初始化队列、带头结点
int EnQueue(LinkQueue *Q, word e);//入队操作
int DeQueue(LinkQueue *Q, word *e);//出队操作

int LearnWordProc();//learning word process
int sourceLoadQueue(word sourceWord[], LinkQueue *destinaQ);//将学习任务目标单词放入队列
int wordByTurns(LinkQueue *unRemQueue);//学习当前单词函数
int showWordInDetail(word beShowedWord);//打印单词详细信息
char get_first(void);//取首字母
char* getSentenceByNumber(int sentenceNum);//根据例句序列号取到句子
void RemWord(word* tempWord,wordsline*base);*/

int InitQueue(LinkQueue *Q)
{   //构建一个空队列Q
    (*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
    if(!(*Q).front) exit(ERROR);//存储分配失败

    (*Q).front->next = NULL;
    (*Q).LengthQueue = 0;

    return OK;
}

int EnQueue(LinkQueue *Q, word e)
{//插入元素e为Q的新的队尾元素
    QueuePtr p;

    p = (QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(ERROR);//存储分配失败

    p->date = e; p->next = NULL;
    (*Q).rear->next = p; (*Q).rear = p;
    (*Q).LengthQueue++;

    return OK;
}

int DeQueue(LinkQueue *Q, word *e)
{//若队列不空，则删除Q的队头元素
    //用e返回其值，并返回OK，否则返回ERROR
    if((*Q).front == (*Q).rear) return ERROR;

    QueuePtr p;

    p = (*Q).front->next;
    *e = p->date;
    (*Q).front->next = p->next;
    if((*Q).rear == p) (*Q).rear = (*Q).front;
    (*Q).LengthQueue--;

    free(p);
    return OK;
}

int LearnWordProc(sentence* sentence_base,wordsline* word_base, word portTargetWord[])
{//learning word process将学习任务目标单词放入队列
    LinkQueue unRemQueue;//存放未记住的单词的队列
    InitQueue(&unRemQueue);

    sourceLoadQueue(portTargetWord, &unRemQueue);//125
    //printf("%d",unRemQueue.LengthQueue);
    while(unRemQueue.LengthQueue != 0)//队列内仍有未记住的单词，则继续单词出队
    {
        wordByTurns(&unRemQueue,sentence_base,word_base);
    }

    //队空后，完成本次学习任务
    printf("finish！\n");
    //重新写入csv，更新日志csv

    return OK;
}

int sourceLoadQueue(word sourceWord[], LinkQueue *destinaQ)
{//将学习任务目标单词放入队列
    int vol = 1;
    for(vol = 1;vol <= LearnWordNum; vol++)
    {
        EnQueue(destinaQ,sourceWord[vol]);
    }

    return OK;
}

int wordByTurns(LinkQueue *unRemQueue,sentence* sentence_base,wordsline* word_base)
{//取出队头单词进行学习
    word *tempWord = (word*)malloc(sizeof(word));
    char YesOrNo;

    DeQueue(unRemQueue, tempWord);

    printf("%s\n",(*tempWord).word_info);
    printf("Know this word？\nPlease enter Y or N\n");

    YesOrNo = get_first();
    while (!(YesOrNo == 'Y' || YesOrNo == 'N'))
    {
        printf("Please respond with Y or N\n");
        YesOrNo = get_first();
    }
    if(YesOrNo == 'Y')
    {
        RemWord(tempWord,word_base);//记住后单词该如何处理，需与组员再次讨论------------------------------------------flag
    }
    else
    {
        //若未记住或其他原因，则将单词继续入队。
        EnQueue(unRemQueue, *tempWord);
    }

    showWordInDetail(*tempWord,sentence_base);
    printf("剩余单词个数：%d\n\n\n",(*unRemQueue).LengthQueue);

    free(tempWord);


    return OK;
}

char* num_to_wordtype(int typenum)
{
    char *wordtype=(char*)malloc(10*sizeof(char));
    switch(typenum)
    {
    case 1:
        strcpy(wordtype,"n.");
        break;
    case 2:
        strcpy(wordtype,"v.");
        break;
    case 3:
        strcpy(wordtype,"adj.");
        break;
    case 4:
        strcpy(wordtype,"adv.");
        break;
    case 5:
        strcpy(wordtype,"prep.");
        break;
    case 6:
        strcpy(wordtype,"conj.");
        break;
    default:
        strcpy(wordtype,"wrong!");
        break;
    }
    return wordtype;
}

int showWordInDetail(word beShowedWord,sentence* sentence_base)
{//展示单词详细信息
    printf("词语详细信息:\n");
    printf("%s\n词意：%s\n词性：%s\n",beShowedWord.word_info,beShowedWord.word_meaning,num_to_wordtype(beShowedWord.word_type));
    printf("例句： %s\n\n",getSentenceByNumber(beShowedWord.word_sentences_number,sentence_base));

    return OK;
}

char get_first(void)
{//取首字母
    int ch;

    ch = getchar();
    fflush(stdin);
    ch = toupper(ch);

    return ch;
}

char* getSentenceByNumber(int sentenceNum,sentence* sentence_base)
{//取例句根据序列号
    int vol;

    for(vol = 1; vol <= MAXMIUM; vol++)
    {
        if(sentenceNum == sentence_base[vol].sentence_number)
        {
            return sentence_base[vol].sentence_example;
        }
    }


    return NULL;
}

void ReInsert(word*e,wordsline* words_base)
{
    int i;
    for(i=0;i<26;i++)
    {
        if(e->word_info[0]==words_base[i]->nextword->word_info[0])
        {
            word*p;
            p=words_base[i];
            while(p->nextword!=NULL)
                p=p->nextword;
            p->nextword=e;
            e->nextword=NULL;
        }
        break;
    }
}
void RemWord(word* tempWord,wordsline* words_base)
{
    tempWord->word_rem_times++;//改变记住的属性（+1）
    ReInsert(tempWord,words_base);//把记住的单词回插到单词库
}
