#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 10020
#define maxm 200020
#define INF 2147483630
/*
    ʵ������1
*/
int ans[maxn];
typedef struct Edge
{
    int to,weight,next;
    //�ñߣ�ͬһ������һ����edgs�д洢���±ꡣ��next��Ϊ��ʽѰ��ͬһ�������б�
}Edge;

struct Graph
{
    Edge edges[maxm];
    //head[i] ��¼������iΪ���ı߼��е�һ������edges�е�index,
    int head[maxn];
    //��ǰ�ڼ�����
    int tot;
};

struct Graph *init_graph()
{
    struct Graph *new_grapth = (struct Graph *)malloc(sizeof(struct Graph));
    new_grapth->tot = 0;
    memset(new_grapth->head, -1, sizeof(new_grapth->head));
    return new_grapth;
}

//�ӱߺ���:��ʽǰ���Ǵ洢��ÿ��һ���ߵ�ʱ��ͬһ���ı���next������ʽ�洢
void add_edge(int start, int end, int weight, struct Graph *graph)
{
    graph->edges[++graph->tot].to = end;
    graph->edges[graph->tot].weight = weight;
    graph->edges[graph->tot].next = graph->head[start];
    graph->head[start] = graph->tot;
}

//�����̴���ʱ��ĺ�����nΪ������
int get_min_time(int n, int startpoint, struct Graph *graph)
{
    memset(ans,0x3f,sizeof(ans));//��ans��Ϊ���ֵ
    int q[maxn] = {0};//���б��������·�Ľڵ�ļ���
    int vis[maxn] = {0};//�ڵ��Ƿ񱻱�����
    q[0] = 0;
    q[1] = startpoint; //���ϴ�����ʼ��
    ans[startpoint] = 0;//��ʼ�㵽�Լ�����Ϊ1
    int tot = 1;//���ϵĵ���
    int cnt = 0;//�����ж��Ƿ��Ѿ����������нڵ�
    int nowD;  //ÿ�α����ĳ�����
    while(1){
        nowD = 0;
        //�ҵ���ǰδ�������ڱ����µĽڵ����·����
        for(int i = 1;i <= tot;i++){
            if(!vis[q[i]]) nowD = ans[nowD]>ans[q[i]]?q[i]:nowD;
        }
        if(nowD == 0) break;
        vis[nowD] = 1;
        cnt++;
        //������nowD������ÿһ���ڽӵ�
        for(int i = graph->head[nowD];i != -1;i = graph->edges[i].next){
            int to = graph->edges[i].to;
            int weight = graph->edges[i].weight;
            //�����nowD��to��һ��ȨֵΪweight�ıߺ󣬱�֮ǰ����ʼ�㵽to�����·����Ҫ�̣���toѹ�뼯����
            if(ans[to] > ans[nowD] + weight){
                ans[to] = ans[nowD] + weight;
                q[++tot] = to;//���뼯��
            }
        }
    }
    if(cnt < n) return -1;//�����ĵ��������ܵ�����˵�����ڹ�����
    int maxTime = 0;//ȡ����ʼ����������·�������ֵ
    for(int i = 1;i <= n;i++) maxTime = maxTime>ans[i]?maxTime:ans[i];
    return maxTime;
}

int main()
{
    //system("color f9");//��ɫ��������������
    int n, m, startpoint, min_time;
    //�ļ�����ķ�ʽ
    freopen("4_1_input.in", "r", stdin);
    //nΪ������mΪ������startpointΪ���
    while (scanf("%d%d%d", &n, &m, &startpoint) != EOF)
    {
        struct Graph *g = init_graph();//���ؿ�ͼ
        int start, end, weight;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &start, &end, &weight);
            add_edge(start, end, weight, g);
        }
        //�����������ɢʱ��
        min_time = get_min_time(n, startpoint, g);
        printf("%d\n", min_time);
    }
    fclose(stdin);
    return 0;
}
