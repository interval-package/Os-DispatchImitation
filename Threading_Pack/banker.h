//
// Created by Zza on 2022/5/31.
//

#ifndef OS_DISPATCHIMITATION_BANKER_H
#define OS_DISPATCHIMITATION_BANKER_H

// init count of resource type
#define M 3
// init count of process
#define N 2

class banker {
public:

    void test_main();


private:
    typedef struct Condition{
        int available[M];
//    可选的，主要是在开始的时候初始化用
        int max[N][M];
        int need[N][M];
        int allocation[N][M];
        volatile int request[M];
        int cur;
        int n;
        int m;
    } Condition, *pCond;

//int need[i][j] = Max[i][j]- Allocation[i][j]

    typedef struct SafetyWork{
        int work[M];
        bool finished[N];
    } sfWork;

#define ACT_TIMES 10

    typedef struct Actions{
        int processId;
        int request[M];
    }Actions, *acts;

// global var
//static Condition CurCond;

private:
    bool SafetyCertification(pCond cond);

    bool sfWorkInit(sfWork*, pCond);

    bool FindAndAlloc(sfWork* jud, pCond cond);

    bool EndPhaseJudge(sfWork* jud, pCond cond);


private:
    bool InitCond(pCond cond);

    bool DisplayCurCond(pCond cond);

// Banker actions

    bool UpdateCond(pCond, acts);

    bool BankerEvaluate(pCond);

    bool preAllocate(pCond);

    bool RollBack(pCond);

    bool Commit(pCond);
};


#endif //OS_DISPATCHIMITATION_BANKER_H
