//
// Created by Zza on 2022/5/31.
//

#include "banker.h"

#include <cstdlib>
#include <cstdio>
//#include <stdbool.h>
//#include <pthread.h>

void banker::test_main(){
    Condition cond;
    InitCond(&cond);
    cond.available[0] = 2;
    cond.available[1] = 4;
    cond.available[2] = 3;
    Actions reqs[] = {
            {0,{2,0,0}},
            {1,{0,1,1}},
            {1,{2,1,2}},
            {1,{0,1,0}},
            {-1,{2,1,0}},
    };
    acts req = reqs;
    while (req->processId >= 0){
        DisplayCurCond(&cond);
        UpdateCond(&cond,req);
        BankerEvaluate(&cond);
        printf("---------\n");
        req++;
    }

}

//======================================================================================================================

bool banker::InitCond(pCond cond){
    cond->cur = 0;
    cond->n = N;
    cond->m = M;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cond->allocation[i][j] = 0;
            cond->max[i][j] = 2;
            cond->need[i][j] = cond->max[i][j] - cond->allocation[i][j];
            cond->available[j]+=cond->max[i][j];
        }
    }
//    数据初始化
    return true;
}

bool banker::DisplayCurCond(pCond cond){
    printf("avail: ");
    for(int j=0;j<cond->m;j++){
        printf("%d\t",cond->available[j]);
    }
    printf("\n");
    return true;
}

//======================================================================================================================

bool banker::BankerEvaluate(pCond cond){
//    输入检验与预分配
    if(!preAllocate(cond))return false;

//    预分配后安全性检验
    if(SafetyCertification(cond)){
        Commit(cond);
        printf("allocation success!\n");
    } else{
        printf("unsafe request, refuse, alloc fail.\n");
        RollBack(cond);
        return false;
    }
    return true;
}

bool banker::preAllocate(pCond cond){
    // 申请检验
    for(int i=0; i<cond->m; i++){
        if(cond->available[i] < cond->request[i] // 是否有剩余的空间给予分配
           ||
           cond->need[cond->cur][i] < cond->request[i]) // 判断是否是合法的申请
        {
            printf("invalid request, allocation fail\n");
            return false;
        }
    }
    // 预分配
    for(int i=0; i<M; i++){
        cond->allocation[cond->cur][i] += cond->request[i];
        cond->need[cond->cur][i] -= cond->request[i];
    }
    return true;
}

bool banker::UpdateCond(pCond cond, acts act){
    cond->cur = act->processId;
    printf("get request of %d:\n",act->processId);
    for(int i=0; i<M; i++){
        printf("%d\t",act->request[i]);
        cond->request[i] = act->request[i];
    }
    printf("\n");
    return true;
}

bool banker::RollBack(pCond cond){
    for(int i=0; i<M; i++){
        cond->allocation[cond->cur][i] -= cond->request[i];
        cond->need[cond->cur][i] += cond->request[i];
    }
    return true;
}

bool banker::Commit(pCond cond){
    for(int i=0; i<M; i++){
        cond->available[i] -= cond->request[i];
    }
    return true;
}

//======================================================================================================================

// safety method

bool banker::SafetyCertification(pCond cond){
    sfWork jud;
    sfWorkInit(&jud, cond);
// 首先是找到一个没有完成的进程，把资源全部分配给它
    while (FindAndAlloc(&jud, cond));
    return EndPhaseJudge(&jud,cond);
}

bool banker::sfWorkInit(sfWork* jud, pCond cond){
    for(int i=0;i<M;i++){
        jud->work[i] = cond->available[i];
    }
    for(int i=0;i<cond->n;i++){
        jud->finished[i] = false;
    }
    return true;
}


bool banker::FindAndAlloc(sfWork* jud, pCond cond){
    for(int i=0, j; i<cond->n; i++){
        if(!jud->finished[i]){
            for(j=0; j<M && cond->need[i][j] < jud->work[j]; j++);
            if(j == M){
                for(j=0; j<M; j++) { jud->work[j] += cond->allocation[i][j]; }
                jud->finished[i] = true;
                return true;
            }
        }
    }
    return false;
}

bool banker::EndPhaseJudge(sfWork* jud, pCond cond){
    for(int i=0; i<cond->n; i++){
        if(!jud->finished[i]){
            return false;
        }
    }
    return true;
}

