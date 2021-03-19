#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct StackNode{
    /** ջ�д洢�Ľڵ� */
  int id;
  struct StackNode *next;
}sNode;

typedef struct LinkStack{
    /** ��ջ */
  sNode* top;
  int size;
}Stack;

Stack* InitStack(){
    /** ��ʼ��ջ */
  Stack* stack = (Stack *)malloc(sizeof(Stack));
  stack->top = NULL;
  stack->size = 0;
  return stack;
}

int StackEmpty(Stack *stack){
    /** �ж�ջ�Ƿ�Ϊ�� */
  return (stack->size == 0);
}

void Push(Stack *stack,int element){
    /** ��һ���ڵ�ѹ��ջ */
    sNode * newNode = (sNode *)malloc(sizeof(sNode));
    if(newNode == NULL){
        printf("OVERFLOW");
        exit(0);
    }
    newNode->id = element;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

void Pop(Stack* stack){
    /** ��һ���ڵ㵯��ջ */
    if(StackEmpty(stack)) return;//��ջֱ�ӷ���
    sNode *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
}

int Top(Stack* stack){
    /** ��ջ���գ�����ջ��ջ��Ԫ�� */
    if(StackEmpty(stack)) return 0;//��ջ����0
    return stack->top->id;
}

/** ʵ������1:�ж�����ĳ�վ����in�Ƿ��������Ľ�վ����outͨ������ջ�õ�
     ���з���1�������з���0
     num �� ��վ���� */
int SeqLegal(int in[],int out[],int num){
    Stack * stack = InitStack();
    int inNum = 1,outNum = 1;
    for(; inNum <= num ; inNum++){
        //���Ҫ��վ������������ϳ�ȥ�����Ƚ�ջ
        if(in[inNum] != out[outNum])  Push(stack,in[inNum]);
        else   outNum++;
        // ���ջ��Ϊ�ղ���ջ���𳵾͵��ڳ�վ�Ļ𳵣���ջ
        while(! StackEmpty(stack) && Top(stack) == out[outNum]){
            Pop(stack);
            outNum++;
        }
        //������Ѿ�ȫ����վ������ȴû����whileѭ����ȫ��������˳���վ��˵�������ܰ������г�վ
        if(inNum == num && ! StackEmpty(stack)) return 0;
    }
    return 1;
}

typedef struct QueueNode{
    /** ���нڵ� */
    int id;
    struct QueueNode* next;
}qNode;

typedef struct Queue{
    /** ���� */
    qNode *front;
    qNode *rear;
    int size;
}Queue;

Queue* InitQueue(){
    /** ��ʼ������ */
    Queue* linkQueue = (Queue*) malloc(sizeof(Queue));
    linkQueue->front = linkQueue->rear = (qNode *)malloc(sizeof(qNode));
    linkQueue->front->next = NULL;
    linkQueue -> size = 0;
    return linkQueue;
}

int QueueEmpty(Queue* linkQueue){
    /** �ж϶����Ƿ�Ϊ�� */
    return (linkQueue->front == linkQueue->rear);
}

void EnQueue(Queue *linkQueue,int element){
    /** ��� */
    qNode * newNode = (qNode *)malloc(sizeof(qNode));
    if(newNode == NULL){
        printf("OVERFLOW");
        exit(0);
    }
    newNode->id = element;
    newNode->next = NULL;
    linkQueue->rear->next = newNode;
    linkQueue->rear = newNode;
    linkQueue->size++;
}

void DeQueue(Queue *linkQueue){
    /** ���� */
    if(QueueEmpty(linkQueue)) return;//�ն���ֱ�ӷ���
    qNode * temp = linkQueue->front;
    linkQueue->front = linkQueue->front->next;
    free(temp);
    linkQueue->size--;
}

int QueueLength(Queue *linkQueue){
    /** ���г��� */
    return linkQueue->size;
}

int GetHead(Queue *linkQueue){
    /** ���ض�ͷ */
    if(QueueEmpty(linkQueue)) return 0;//�ն��з���0
    return linkQueue->front->id;
}

int GetRear(Queue *linkQueue){
    /** ���ض�β */
    if(QueueEmpty(linkQueue)) return 0;//�ն��з���0
    return linkQueue->rear->id;
}

/**  �ҵ�����ʵĻ𳵹�� */
int findClosestQueue(Queue *railQueue[],int usedQueue,int curTrain){

    int closestIdx = 1;
    /**
    *   �ö��ַ��ҵ���һ�������ж�βԪ��ֵ��curTrainС�Ĺ�����
    *   ʹ��������һ���𳵵���ŵݼ�����
    */
    int left = 1;
    int right = usedQueue;
    //�����û���κλ𳵽�վ ���� ���һ����������һ���𳵶������������𳵵���Ŵ���˵��Ҫ�ٿ�һ�����
    if(usedQueue == 0 || GetRear(railQueue[right]) > curTrain) return usedQueue + 1;
    while(left <= right){
        closestIdx = (left+right)/2;
        if(GetRear(railQueue[closestIdx]) > curTrain) left = closestIdx + 1;
        else right = closestIdx - 1;
    }
    return closestIdx;
}

/** ʵ������2:������軺��������Сֵ,���������Сֵ*/
int minBufferQueue(int in[],int num){

    Queue *railQueue[num+1];
    //ָ�����飬��¼���������Ļ𳵣����������ȵĹ����ʱһ������
    for(int i = 1;i <= num;i++){
        railQueue[i] = InitQueue();
    }
    int usedQueue = 0;      //��ʹ�õĹ����

    for(int i = 1;i <= num;i++){
        //���ú�����ȡ����ʷ��õĹ��
        int closetNum = findClosestQueue(railQueue,usedQueue,in[i]);
        //���������ʹ��������ʹ�õĹ�����󣬾ͽ���ʹ�õĹ������1�����ʹ����ֻ���������ù����+1��
        if(closetNum>usedQueue) usedQueue++;
        //���
        EnQueue(railQueue[closetNum],in[i]);
    }

    return usedQueue;
}

int main()
{
    int trainNum;
    int count = 0;
    freopen("Train.in", "r", stdin);
    //trainNum�Ǳ��λ��ܹ�Ҫ��վ������
    while(scanf("%d",&trainNum)!=EOF){
        count++;//���������
        int trainIn[trainNum+1];// �洢�����Ļ𳵱������
        int trainOut[trainNum+1];// �洢��ȥ�Ļ𳵱������
        //���±�1��ʼ����
        for(int i = 1;i <= trainNum;i++){
            //�Ƿ��������
            while(!scanf("%d",&trainIn[i])){
                printf("The input data is illegal,please input again:\n");
                fflush(stdin);
            }
        }
        for(int i = 1;i <= trainNum;i++){
            //�Ƿ��������
            while(!scanf("%d",&trainOut[i])){
                printf("The input data is illegal,please input again:\n");
                fflush(stdin);
            }
        }
        printf("\n============Case %d============\n\n",count);
        printf("Experiment 1 :Judge Possibility:\n");
        // ʵ������1  �𳵰��ո���˳���վ���ж��Ƿ���԰�����˳���վ
        if(SeqLegal(trainIn,trainOut,trainNum)){
            printf("The output train sequence is Possible\n");
        }else{
            printf("The output train sequence is impossible\n");
        }
        // ʵ������2
        printf("-----------------------------------\nExperiment 2:Get MinBuffer:\n");
        printf("The recover the order, %d buffer queue is needed\n",minBufferQueue(trainOut, trainNum));
    }
    fclose(stdin);
    return 0;
}



