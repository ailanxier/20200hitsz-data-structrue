#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 10020
#define maxm 200020
#define INF 2147483647
/**
    ʵ�����ݶ�
*/
int ans[maxn];
typedef struct Edge{
    int to,weight,next;
}Edge;

struct Graph{
    Edge edges[maxm];
    //head[i] ��¼������iΪ���ı߼��е�һ������edges�е�index
    int head[maxn];
    //��ǰ�ڼ�����
    int tot;
};

struct Graph *init_graph(){
    struct Graph *new_grapth = (struct Graph *)malloc(sizeof(struct Graph));
    new_grapth->tot = 0;
    memset(new_grapth->head, -1, sizeof(new_grapth->head));
    return new_grapth;
}

//�ӱߺ���:��ʽǰ���Ǵ洢��ÿ��һ���ߵ�ʱ��ͬһ���ı���next������ʽ�洢
void add_edge(int start, int end, int weight, struct Graph *graph){
    graph->edges[++graph->tot].to = end;
    graph->edges[graph->tot].weight = weight;
    graph->edges[graph->tot].next = graph->head[start];
    graph->head[start] = graph->tot;
}

//���������޻�ͼ��input_array���������ĳ�ʼȨֵ
void forward_propagation(int n_total, int n_input, int n_output, int *input_array, struct Graph *graph){
    memset(ans,0,sizeof(ans));
    int vis[maxn] = {0};//�Ƿ񱻷��ʹ�
    int q[maxn] = {0};//������ز���Ԫ�Ķ���
    int left = 0;//�������
    int right = 0;//�����Ҷ�
    int nowD;
    //���������ÿһ�����,�õ���һ������ز���
    for(int i = 1;i <= n_input;i++) {
        ans[i] = input_array[i];
        for(int j = graph->head[i];j != -1;j = graph->edges[j].next){
            int to = graph->edges[j].to;
            int weight = graph->edges[j].weight;
            ans[to]+=weight*input_array[i];
            //����ý��û�б��������ز㼯���У�ͬʱҲ����������㣬�ͼ��뼯��
            if(!vis[to]&&graph->head[to]!=-1) q[++right] = to,vis[to] = 1;
        }
    }
    //��ÿһ�����ز�����б���
    while(1){
        nowD = q[++left];
        if(nowD ==0) break;//��ȡ�����Ľ��Ϊ0ʱ���������Ϊ��
        for(int i = graph->head[nowD];i != -1;i = graph->edges[i].next){
            int to = graph->edges[i].to;
            int weight = graph->edges[i].weight;
            ans[to]+=weight*ans[nowD];
            //����ý��û�б��������ز㼯���У�ͬʱҲ����������㣬�ͼ��뼯��
            if(!vis[to]&&graph->head[to]!=-1) q[++right] = to,vis[to] = 1;
        }
    }
}

int main(){
    //system("color f9");//��ɫ��������������
    int input[maxn];
    int n_total, m_total, n_input, n_output;
    //�ļ�����ķ�ʽ
    freopen("4_2_input.in", "r", stdin);
    //����������������������������ڵ���
    while (scanf("%d%d%d%d", &n_total, &m_total, &n_input, &n_output) != EOF){
        struct Graph *g = init_graph();
        int start, end, weight;
        //����ߺ�Ȩֵ
        for (int i = 1; i <= m_total; i++){
            scanf("%d%d%d", &start, &end, &weight);
            add_edge(start, end, weight, g);
        }
        //����������ĳ�ʼȨֵ
        for (int i = 1; i <= n_input; i++)
            scanf("%d", &input[i]);

        //���������ȫ�ֱ���ans������
        forward_propagation(n_total, n_input, n_output, input, g);

        //�����������н���ĩȨֵ
        for (int i = n_total - n_output + 1; i <= n_total; i++)
            printf(i < n_total ? "%d " : "%d\n", ans[i]);
    }
    fclose(stdin);
    return 0;
}
