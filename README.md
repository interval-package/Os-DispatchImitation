# 操作系统实验：多线程下模拟分页虚拟地址与页面置换算法

[TOC]

## 设计目的

1、 增强学生对计算机操作系统基本原理、基本理论、基本算法的理解

2、 提高和培养学生的动手能力

## 需求分析

### 分页虚拟内存

对于我们进程，我们认为其是在自身内部的虚拟逻辑空间进行运行的，在逻辑地址空间内部进行的访问，通过虚拟存储的方式，实现了逻辑地址的扩大。

在本次实验中，我们设计了一种

### 页面置换算法

页面置换算法的基本内容

1.1 页面置换算法是在当进程运行过程中，若其要访问的页面不在内存且内存已满时，要决定将哪个页面换出的算法。常见的页面置换算法包括最佳置换、先进先出置换、最近最久未使用置换和Clock置换等。本次的实验实现的算法包括最佳置换算法（OPT）、先进先出置换算法（FIFO）和最近最久未使用算法（LRU）。

1.2 页面置换算法涉及到一些概念如下： 缺页率：当需要访问的页面不在内存时称为缺页，此时需要将页面调入内存。缺页率就是要访问的页面不在内存中的概率。因此缺页率=缺页次数/要访问的页面总数。需要注意的是，缺页的时候不一定需要进行页面置换（如果内存还没满，直接将页面调入内存即可）。

置换率：置换就是将旧页面调出内存，新页面调进内存，即新页面代替旧页面的过程。置换率就是需要进行页面置换的概率。所以置换率=置换次数/要访问的页面总数。

命中率：就是要访问的页面恰好在内存中的概率。可以发现（缺页率+命中率=1）



## 总体设计

### 结构设计

#### 分页虚拟地址

在本次实验中，主要是分为以下几个大类的结构设计：

- 模拟资源
  - 模拟内存
  - 模拟磁盘
- 模拟进程
- 调度处理类

在本次实验中，我们完全详细地实现了从硬件到操作系统级别操作的设计。

**基于页框在磁盘与内存之间的交换，通过接口表现为内存的重写策略，符合底层硬件的实现。**

总体页表虚拟地址结构如下图：

<div>
    <center>
    <img src=".\pics\xmind\页表机制仿真.png"
         alt="pic error"
         style="zoom:100%"/>
    <br>
	<text>页表机制仿真<text/>
    </center>
</div>
#### 页面置换算法

总体页表置换算法结构如下图：

<div>
    <center>
    <img src=".\pics\xmind\页面置换算法.png"
         alt="pic error"
         style="zoom:100%"/>
    <br>
	<text>页面置换算法<text/>
    </center>
</div>
### 多线程设计

<div>
    <center>
    <img src=".\pics\xmind\多线程模拟进程.png"
         alt="pic error"
         style="zoom:100%"/>
    <br>
	<text>多线程模拟进程<text/>
    </center>
</div>


### 逻辑设计

对于程序的运算过程，我们有以下逻辑过程：

#### 初始化过程

在我们进入程序的过程中，我们先要对基本的环境结构进行

<div>
    <center>
    <img src=".\pics\process\初始化过程.png"
         alt="pic error"
         style="zoom:75%"/>
    <br>
	<text>初始化过程<text/>
    </center>
</div>
#### 运行基础过程



<div>
    <center>
    <img src=".\pics\process\运行过程.png"
         alt="pic error"
         style="zoom:75%"/>
    <br>
	<text>运行过程<text/>
    </center>
</div>
#### 可视化逻辑过程

在本次实验中，我们使用两种进行访问的方式;

- 一次性访问结束模式
- 步进式详细访问

<div>
    <center>
    <img src=".\pics\process\展示流程.png"
         alt="pic error"
         style="zoom:75%"/>
    <br>
	<text>展示流程<text/>
    </center>
</div>


## 算法设计

### 先进先出算法（First-In First-Out, FIFO）

思路：选择在内存驻留时间最长的页面进行置换

实现：维护一个记录所有位于内存中的逻辑页面链表，链表元素按驻留内存的时间排序，链首最长，链尾最短，出现缺页时，选择链首页面进行置换，新页面加到链尾

特点：实现简单；性能较差，调出的页面可能是经常访问的

`Belady`异常：当为进程分配的物理块数增大时，缺页次数不减反增。

### 最近最久未使用算法 (Least Recently Used, LRU)

思路：选择最长时间没有被引用的页面进行置换，因为如果某些页面长时间未被访问，则它们在将来还可能会长时间不会访问

实现：缺页时，**计算内存中每个逻辑页面的上一次访问时间，选择上一次使用到当前时间最长的页面**

特点：可能达到最优的效果，维护这样的访问链表开销比较大

**在缺页中断发生时，置换未使用时间最长的页面。**

LRU理论上是可以实现的，但是代价很高。维护一个所有页面的链表，最近最多使用的页面在表头，最近最少使用的页面在表尾。困难的是在每次访问内存时都必须要更新整个链表。

假设用硬件实现：

- 硬件有一个64位计数器C，它在每条指令执行完后自动加1，每个页表项必须有一个足够容纳这个计数器值的域。在每次访问完内存后，将当前的C值保存到被访问页面的页表项中。
- 一旦发生缺页中断，操作系统就检查所有页表项中计数器的值，找到值最小的一个页面，这个页面就是最近最少使用的页面。
- 但是只有非常少的计算机拥有这样的硬件

### 最不常用算法（Least Frequently Used, LFU）

思路：缺页时，置换访问次数最少的页面

实现：每个页面设置一个访问计数，访问页面时，访问计数加1，缺页时，置换计数最小的页面

特点：算法开销大，开始时频繁使用，但以后不使用的页面很难置换

### 时钟置换算法（Clock）

思路：仅对页面的访问情况进行大致统计

实现：

- 在页表项中增加访问位，描述页面在过去一段时间的内访问情况。
- 将各页面组织成环形链表，指针指向最先调入的页面。
- 访问页面时，在页表项记录页面访问情况。（就是如果访问过了，就设置为1）.
- 缺页时，从指针处开始顺序查找未被访问的页面进行置换。（进行一次遍历，如果该位为1，则修改该位为0，进行下一个判断。）

特点：时钟算法是LRU和FIFO的折中

基于算法特性，第二轮扫描中一定会有为0的页表项，所以最多会进行两轮扫描。

### 改进型时钟置换算法（Advanced Clock）

时钟算法没有考虑页是否被修改过，对于同等情况下，为了减少写外存，没有被修改的页要被优先丢弃。

所以我们又加上了修改位，（0，没有，1，有）。

进行四轮扫描：

1. 查找是否有没有被访问，又没有修改的页。（不修改标志
2. 查找（0，1），修改访问位。
3. 查找（0，0），不修改。
4. 查找（0，1），一定找到，不修改。

## 详细设计

### 核心ADT设计

#### `PageFrame`

```c++
class PageFrame {
public:
    static const int PAGE_LENGTH=1024;
//    explicit PageFrame(int _id, int _info=0);
    int info = 0;
    int id =0;

    void disp_self() const;
};

```

#### `PageItem`

```c++
class PageItem {
private:
    std::string info;



//    PageFrame* tar;
// 这里没有处理好，我们是要用什么
public:
// all the objs we must explicitly call the constructor
    explicit PageItem()= default;

// we define the length of every page frame
//    const static int PageLen = 1024;
    int memPhyAd = -1;
    int diskPhyAd = -1;
    bool inMemory = false;

//    使用回写法处理
    int isWritten = false;
//    同时用于判断是否被访问，>0则必为true
//    再调入时，进行初始化，变为0，我们是否访问指的是被调入后是否访问。
    int accessTimes = -1;
    int recentAccess = -1;

    void reset();

    void init_set();

    void accessed_action();

// level means the type of this page, if -1 it means it's page
// if level>0, it's a list
    int level = -1;

    void disp_self() const;
};
```

#### `PageLinkedList`

```c++
// 将会在该函数内部进行调度，算法的实现
// 这里还要实现，内存的申请和分配

class PageLinkedList {
private:
//    我们将目前所有的page项，使用链表进行连接
    typedef struct Node{
        PageItem* data;
        Node* next;
        Node* prior;
    } Node, *pNode;

//    使用这个长度来判断，链表是否为满
    const int _len;
    int WorkSetLen;

//    模拟队列操作，入队出队
    void add_work_node(PageItem* tar);
    void cut_node(pNode pos);
    PageItem* de_work_node();

//    内存对象，目前还没有明确用途
    Memory *mem;

public:
    PageLinkedList(int len, Memory* tar);

//    case 'i': _dsp_FIFO();
//    case 'r': _dsp_LRU();
//    case 'f': _dsp_LFU();
//    case 'c': _dsp_clock();
    char _dsp_type = 'f';

//    做了一个双向链表作为模拟
    Node* head_WorkSet;
    Node* head_StaySet;

//    inner dispatching with detail actions
    PageItem* inner_dispatching(PageItem* tar);

//    void set_dispatch_type(char type);

    ~PageLinkedList();

    void display_cur() const;

private:

//    作为调度算法，要实现的是找到目标的位置
//    在核心调度算法中，我们不做，插入与删除的操作
//    我们所做的,只是找出对应的节点指针,后面的操作交给外部包装函数
//    我们保证,在这里我们的链表一定是满的
    pNode _dsp_FIFO() const;

    pNode _dsp_LRU() const;

    pNode _dsp_LFU() const;

    pNode _dsp_clock() const;

    pNode _dsp_advClock() const;

//    pNode _dsp_WorkSet() const;
//
//    pNode _dsp_wsClock() const;

};
```

#### `PageList`

```c++
// 页表
// 认为PageList也是一个页表项
class PageList:public PageFrame{
public:
//    默认初始化函数，使得按照顺序向磁盘进行映射
    explicit PageList();

    explicit PageList(int _len);

    static const int LIST_LENGTH = 16;

    PageItem list[LIST_LENGTH];

    int len;

    PageItem* pageAccess(int ad);

//    void randomly_init_list();

//    void disp_self();

};
```

### 运行ADT设计

#### Process

```c++
typedef std::vector<int> ACTIONS;

class Process {
public:

    Process(Memory *mem, Disk *disk, int workspace_size);

    PageFrame* access_vir_ad_R(int ad);

    PageFrame* access_vir_ad_RW(int ad, bool is_write);

    void run(ACTIONS &tar);

    void run();

    void single_step(int ad, bool is_write);

//    this function is to reset the type of our dispatching method
    void set_dispatch_type(char type);

    int id;
private:
    PageList list;
//    使用页框链表，用于后续的调度算法
    PageLinkedList page_set;

//    获得对应的指针，内存指针应当有两个备份。
    Memory* process_mem;
    Disk* process_disk;

    void dispatching(Exception_Page_Missing& e);

//    使用页表项作为媒介，将内存内部的信息写入
    void write_mem_to_disk(PageItem* mem_item);

    void write_disk_to_mem(PageItem* old_mem, PageItem* new_mem);
};
```

#### Thread_Proc_Wrapper

```c++
#include "../Process/Process.h"

class Thread_Proc_Wrapper {
//    这个是针对对线程特定使用的，封装了互斥访问的内容
public:
    Process main;

//    这里的主要内容还是就是进行一个Process的初始化
    Thread_Proc_Wrapper(Memory *mem, Disk *disk, int workspace_size);

//    for the usage of multi thread
    void operator()();

    void input_ad_series();

    void input_ad_series_detail();

//    外包装的外部调用函数，没有实现线程安全
    static void outer_run(Thread_Proc_Wrapper proc);

//    外包装的外部调度函数，实现线程安全
//    进行优化升级
    static void outer_main(Thread_Proc_Wrapper proc);

    void inner_main();

private:
//    存放我们的过程序列

    struct _acts{
        int ad;
        bool is_write;
    };

    typedef std::vector<_acts> _action;
    ACTIONS acts;
    _action _detail_act;

};
```

### 辅助ADT设计

#### disk

```c++
class Disk {
public:
    Disk();

//    获得磁盘页面实例，当调入内存时使用
    PageFrame &get_disk_frame_instance(int ad);

    void write_disk_frame(int ad, const PageFrame &frame);


    static const int INIT_DISK_SIZE = 2048;

private:
    int d_size = INIT_DISK_SIZE;
    PageFrame body[INIT_DISK_SIZE]{};

};
```

#### Memory

```c++
class Memory {
public:
    static const int INIT_MEMORY_SIZE = 128;

    Memory();

    std::vector<int> free_set;

    PageFrame *access_memory(int phy_ad, int offset);

    void write_mem_frame(int phy_ad, const PageFrame &tar);

//    申请新的内存块
    int req_new_mem();

//    获得某个特定块的实例，用于写回操作
    PageFrame& get_mem_frame_instance(int ad);

//    ~Memory();
private:
    int m_size = INIT_MEMORY_SIZE;
    PageFrame body[INIT_MEMORY_SIZE]{};
};

```

#### Exception_Page_Missing

```c++
class Exception_Page_Missing: public std::exception{
public:
//    缺页中断必须要指出现在我们所希望访问的实际物理地址，用于传参

    explicit Exception_Page_Missing(PageItem *tar, int _ad, int _offset);
//    int tar_phy_ad{};

    PageItem *item;

    int block_ad;
    int offset;
//    includes the error place we try to get
    void disp_err() const;
};
```

#### `Exception_BoundExceed`

```c++
class Exception_BoundExceed:public std::exception {
public:
    explicit Exception_BoundExceed(const char* msg = "bound exceed"){
        std::cerr<<msg<<std::endl;
    }
};
```

# 死锁算法：银行家算法和安全性算法

## 银行家算法

首先，算法的核心在于，每次进程申请资源时，都会进行一次试探性分配，若成功，则真实分配。

### 基本思想：

- 在每个新进程进入系统时，他必须声明在运行过程中，可能需要的每种资源类型的最大单元数目（数目不超过系统拥有的资源总量）。
- 当进程请求一组资源时，系统必须首先在确定是否有足够的资源分配给该进程。
- 若有，在进一步计算将这些资源分配给进程后，是否会使系统处于不安全状态。如果处于安全状态，才将资源分配给他；否则，让进程等待。

### 银行家算法中的数据结构

为实现银行家算法，在系统中必须要有这样四个数据结构，分别用来描述**系统中可利用的资源**，所有**进程对资源的最大需求**，**系统中的资源分配**，以及**所有进程还需要资源的情况**。

**可利用资源 Available**：这是一个含有 m 个元素的数组，其中每一个元素代表一类可利用的资源情况。其初始值是系统所配置的全部可用资源的数目。 如果Available[j] = k，则表示系统中现有 Rj 类资源 k 个。

**最大需求矩阵 Max**：这是一个 nm 的矩阵。它定义了系统中 n 个进程每一个对 m 类资源的最大需求。`如果Max[i,j] = K，则表示进程i需要 Rj 类资源的最大数目为 K。`

**分配矩阵 Allocation**：这也是一个 nm 矩阵，它定义了系统中每一类资源当前已分配给每一类进程的资源。`如果Allocation[i.j]= K，则表示进程 i 已分得 Rj 类资源的数目为 K。`

**需求矩阵 Need**：当前所有进程还需要的资源m的矩阵，用来表示每一个进程尚需的各类资源数，`如果Need[i,j]=K，则表示进程 i 还需要 K 个 Rj 类资源才能完成任务`。

**上述三个矩阵之间存在如下关系：`Need[i, j] = Max[i, j] - Allocation[i, j]。`**

| 名称           |                                               |                      |
| -------------- | --------------------------------------------- | -------------------- |
| 可利用资源向量 | `int  Available[m]`                           | m为资源种类          |
| 最大需求矩阵   | `int  Max [n][m]`                             | n为进程的数量        |
| 分配矩阵       | `int  Allocation[n][m]`                       |                      |
| 还需资源矩阵   | `int  need[i][j]=Max[i][j]- Allocation[i][j]` |                      |
| 申请资源数量   | `int  Request [m]`                            | 会一直更新，暂存申请 |
| 工作向量       | `int  Work[m]    int  Finish[n]`              |                      |

### 算法步骤

#### 1.初始化

#### 2.进程申请资源

（1）数据装入Request

（2）输入合法性判断

如果合计申请超出了之前声明的最大，则报错。如果申请超过了目前可用，则阻塞。

#### 3.试探性分配

```java
for(int i=0;i<m;i++)
{
    available[i] -= request[i];
    allocation[index][i] += request[i];
    need[index][i] -= request[i];
}
```

#### 4.安全检验

调用安全性算法，如果当前状态时安全的，则正式进行分配。否则，回滚状态，阻塞该进程。

## 安全性算法

### 数据结构

**工作向量 Work**，它表示可以提供给进程继续运行所需要的各类的资源数目，它含有 m 个元素，在执行安全算法开始时，`Work = Available`；

**Finish**，它表示系统是否有足够的资源分配给进程，使之运行完成。开始先做`Finish[i] = false`。当有足够资源分配给进程时，再令 `FInish[i] = false`;

### 算法思想

a.从进程集合中找到一个满足下述条件的进程：

```c
Finish[i] = false;
Need[i,j]<=Work[j];
如果找到执行步骤 b，否则执行步骤 c；
```

b.当进程 Pi 获得资源后，可顺利执行，直到完成，并释放它的资源。故应执行：

```c
Work[j] = Work[j] + Allocation[i,j];
Finish[j] =true;
返回执行步骤 a
```

c.如果所有进程的 `Finish[i] = true` 都满足，则表示系统处于安全状态；否则，系统处于不安全状态。

## 部分源代码

见附录文件

## 心得总结

根据实验结果可以看出，对同一种算法，对于不同的访问序列，其缺页率是不同，会有所变化。总的来看，最佳置换算法的缺页率是最低的，然后页面缓冲算法的缺页率要低于其他置换算法。改进型clock算法稍微好于先进先出算法和最近最久未使用算法。先进先出算法和最近最久未使用算法性能相近。

同时对比不同内存块数下的程序运行结果能够看出，算法的缺页率与分配的内存块数有关系，分配的内存块数越多，缺页率越低。
