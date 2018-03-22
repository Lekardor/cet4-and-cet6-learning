#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1216.Bernstein Xeroxed copies of notes from reporters at the scene.
#define MAXMIUM 217

#define MAX_SENTENCE_LENGTH 200
#define MAX_SENTENCE 216
#define LearnWordNum 10
//****************************
#define morethan 1
#define lessthan -1
#define equal 0

#define LH 1//左高
#define EH 0//等高
#define RH -1//右高

#define Boolean int
#define true 1
#define false 0


typedef int word_extra1;
typedef int word_extra2;
typedef struct word
{
    char word_info[20];//单词字面显示
    char word_meaning[30];//单词释义
    int word_type;//词性
    int word_sentences_number;//出现例句序号
    int word_rem_times;//单词被记住次数（0代表新单词，1 2 3 4代表被记住1 2 3 4次，5代表完全记住）
    struct word* nextword;//指针指向下一个单词
    word_extra1 word_extrachar1;//额外属性1
    word_extra2 word_extrachar2;//额外属性2
}word,*wordsline;



typedef struct sentence
{
    char  sentence_example[100];//例句示例
    int   sentence_number;//例216.Bernstein Xeroxed copies of notes from reporters at the scene. 句序号
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


int InitQueue(LinkQueue *Q);//初始化队列、带头结点
int EnQueue(LinkQueue *Q, word e);//入队操作
int DeQueue(LinkQueue *Q, word *e);//出队操作

int LearnWordProc(sentence* sentence_base,wordsline* word_base, word portTargetWord[]);//learning word process
int sourceLoadQueue(word sourceWord[], LinkQueue *destinaQ);//将学习任务目标单词放入队列
int wordByTurns(LinkQueue *unRemQueue,sentence* sentence_base,wordsline* word_base);//学习当前单词函数
int showWordInDetail(word beShowedWord,sentence* sentence_base);//打印单词详细信息
char get_first(void);//取首字母
char* getSentenceByNumber(int sentenceNum,sentence* sentence_base);//根据例句序列号取到句子
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
    int bf;   //节点的平衡因子
    struct BSTNode *lchild,*rchild;//左右孩子指针
}BSTNode, *BSTree;

void R_Rotate(BSTree p);  //右旋转
void L_Rotate(BSTree p);  //左旋转
void LeftBalance(BSTree t);//左平衡
void RightBalance(BSTree t);//右平衡
int wordcomparing(char* a,char* b);//比较两个单词大小
int InsertAVL(BSTree* t,word a, Boolean *taller);//平衡二叉树的插入操作
BSTree wordsearch(BSTree t,char* a);//单词搜索
BSTree buildBSTree(wordsline line);
BSTree* buildallTree(wordsline wordbase[],int n);
BSTree choosetree(char* a,BSTree alltree[],int n);

#endif // HEAD_H_INCLUDED
