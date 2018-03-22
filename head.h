#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAXMIUM 217

#define MAX_SENTENCE_LENGTH 200
#define MAX_SENTENCE 217
#define LearnWordNum 10
//****************************
#define morethan 1
#define lessthan -1
#define equal 0

#define LH 1//���
#define EH 0//�ȸ�
#define RH -1//�Ҹ�

#define Boolean int
#define true 1
#define false 0


typedef int word_extra1;
typedef int word_extra2;
typedef struct word
{
    char word_info[20];//����������ʾ
    char word_meaning[30];//��������
    int word_type;//����
    int word_sentences_number;//�����������
    int word_rem_times;//���ʱ���ס������0�����µ��ʣ�1 2 3 4������ס1 2 3 4�Σ�5������ȫ��ס��
    struct word* nextword;//ָ��ָ����һ������
    word_extra1 word_extrachar1;//��������1
    word_extra2 word_extrachar2;//��������2
}word,*wordsline;



typedef struct sentence
{
    char  sentence_example[100];//����ʾ��
    int   sentence_number;//�������
}sentence;


//************************************

typedef struct QNode
{
    word date;
    struct QNode *next;
}QNode, *QueuePtr;

typedef struct LinkQueue
{
    QueuePtr front;
    QueuePtr rear;
    int LengthQueue;
}LinkQueue;


int InitQueue(LinkQueue *Q);//��ʼ�����С���ͷ���
int EnQueue(LinkQueue *Q, word e);//��Ӳ���
int DeQueue(LinkQueue *Q, word *e);//���Ӳ���

int LearnWordProc(sentence* sentence_base,wordsline* word_base, word portTargetWord[]);//learning word process
int sourceLoadQueue(word sourceWord[], LinkQueue *destinaQ);//��ѧϰ����Ŀ�굥�ʷ������
int wordByTurns(LinkQueue *unRemQueue,sentence* sentence_base,wordsline* word_base);//ѧϰ��ǰ���ʺ���
int showWordInDetail(word beShowedWord,sentence* sentence_base);//��ӡ������ϸ��Ϣ
char get_first(void);//ȡ����ĸ
char* getSentenceByNumber(int sentenceNum,sentence* sentence_base);//�����������к�ȡ������
void ReInsert(word*e,wordsline* words_base);
void RemWord(word* tempWord,wordsline* words_base);

//****************************************************

int InitWordsline(wordsline wordsline_abc);
int EnWordsline(word e,wordsline ordsline_abc);
char* CreateNewRoute(char alpha);
void CreateWordsLine(wordsline wordsline_alpha,char alpha);
void CreateWordBase(wordsline* words_base);
void RewriteCSV(wordsline* words_base);
void CreateSentence_base(sentence *sentence_base,int sentencenum);

int delWordLineNode(wordsline LinePtr, int n, word *e);
int emptyLine(wordsline LinePtr);
int chooseWordInBase(wordsline a_to_z[],word portTargetWord[]);

//*******************************************************

typedef struct BSTNode
{
    word wordnord;
    int bf;   //�ڵ��ƽ������
    struct BSTNode *lchild,*rchild;//���Һ���ָ��
    int flag;
}BSTNode, *BSTree;

BSTree R_Rotate(BSTree p);  //����ת
BSTree L_Rotate(BSTree p);  //����ת
BSTree LeftBalance(BSTree t);//��ƽ��
BSTree RightBalance(BSTree t);//��ƽ��
int wordcomparing(char* a,char* b);//�Ƚ��������ʴ�С
BSTree InsertAVL(BSTree t,word a, Boolean *taller,Boolean *same);//ƽ��������Ĳ������
BSTree wordsearch(BSTree t,char* a);//��������
BSTree buildBSTree(wordsline line);
BSTree* buildallTree(wordsline wordbase[],int n);
BSTree choosetree(char* a,BSTree alltree[],int n);

#endif // HEAD_H_INCLUDED
