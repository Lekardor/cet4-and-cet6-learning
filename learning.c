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

/*word portTargetWord[LearnWordNum];//Ŀ�굥�ʽӿ�
wordsline portTargetWordPtr[LearnWordNum];

int InitQueue(LinkQueue *Q);//��ʼ�����С���ͷ���
int EnQueue(LinkQueue *Q, word e);//��Ӳ���
int DeQueue(LinkQueue *Q, word *e);//���Ӳ���

int LearnWordProc();//learning word process
int sourceLoadQueue(word sourceWord[], LinkQueue *destinaQ);//��ѧϰ����Ŀ�굥�ʷ������
int wordByTurns(LinkQueue *unRemQueue);//ѧϰ��ǰ���ʺ���
int showWordInDetail(word beShowedWord);//��ӡ������ϸ��Ϣ
char get_first(void);//ȡ����ĸ
char* getSentenceByNumber(int sentenceNum);//�����������к�ȡ������
void RemWord(word* tempWord,wordsline*base);*/

int InitQueue(LinkQueue *Q)
{   //����һ���ն���Q
    (*Q).front = (*Q).rear = (QueuePtr)malloc(sizeof(QNode));
    if(!(*Q).front) exit(ERROR);//�洢����ʧ��

    (*Q).front->next = NULL;
    (*Q).LengthQueue = 0;

    return OK;
}

int EnQueue(LinkQueue *Q, word e)
{//����Ԫ��eΪQ���µĶ�βԪ��
    QueuePtr p;

    p = (QueuePtr)malloc(sizeof(QNode));
    if(!p) exit(ERROR);//�洢����ʧ��

    p->date = e; p->next = NULL;
    (*Q).rear->next = p; (*Q).rear = p;
    (*Q).LengthQueue++;

    return OK;
}

int DeQueue(LinkQueue *Q, word *e)
{//�����в��գ���ɾ��Q�Ķ�ͷԪ��
    //��e������ֵ��������OK�����򷵻�ERROR
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
{//learning word process��ѧϰ����Ŀ�굥�ʷ������
    LinkQueue unRemQueue;//���δ��ס�ĵ��ʵĶ���
    InitQueue(&unRemQueue);

    sourceLoadQueue(portTargetWord, &unRemQueue);//125
    //printf("%d",unRemQueue.LengthQueue);
    while(unRemQueue.LengthQueue != 0)//����������δ��ס�ĵ��ʣ���������ʳ���
    {
        wordByTurns(&unRemQueue,sentence_base,word_base);
    }

    //�ӿպ���ɱ���ѧϰ����
    printf("finish��\n");
    //����д��csv��������־csv

    return OK;
}

int sourceLoadQueue(word sourceWord[], LinkQueue *destinaQ)
{//��ѧϰ����Ŀ�굥�ʷ������
    int vol = 1;
    for(vol = 1;vol <= LearnWordNum; vol++)
    {
        EnQueue(destinaQ,sourceWord[vol]);
    }

    return OK;
}

int wordByTurns(LinkQueue *unRemQueue,sentence* sentence_base,wordsline* word_base)
{//ȡ����ͷ���ʽ���ѧϰ
    word *tempWord = (word*)malloc(sizeof(word));
    char YesOrNo;

    DeQueue(unRemQueue, tempWord);

    printf("%s\n",(*tempWord).word_info);
    printf("Know this word��\nPlease enter Y or N\n");

    YesOrNo = get_first();
    while (!(YesOrNo == 'Y' || YesOrNo == 'N'))
    {
        printf("Please respond with Y or N\n");
        YesOrNo = get_first();
    }
    if(YesOrNo == 'Y')
    {
        RemWord(tempWord,word_base);//��ס�󵥴ʸ���δ���������Ա�ٴ�����------------------------------------------flag
    }
    else
    {
        //��δ��ס������ԭ���򽫵��ʼ�����ӡ�
        EnQueue(unRemQueue, *tempWord);
    }

    showWordInDetail(*tempWord,sentence_base);
    printf("ʣ�൥�ʸ�����%d\n\n\n",(*unRemQueue).LengthQueue);

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
{//չʾ������ϸ��Ϣ
    printf("������ϸ��Ϣ:\n");
    printf("%s\n���⣺%s\n���ԣ�%s\n",beShowedWord.word_info,beShowedWord.word_meaning,num_to_wordtype(beShowedWord.word_type));
    printf("���䣺 %s\n\n",getSentenceByNumber(beShowedWord.word_sentences_number,sentence_base));

    return OK;
}

char get_first(void)
{//ȡ����ĸ
    int ch;

    ch = getchar();
    fflush(stdin);
    ch = toupper(ch);

    return ch;
}

char* getSentenceByNumber(int sentenceNum,sentence* sentence_base)
{//ȡ����������к�
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
    tempWord->word_rem_times++;//�ı��ס�����ԣ�+1��
    ReInsert(tempWord,words_base);//�Ѽ�ס�ĵ��ʻز嵽���ʿ�
}
