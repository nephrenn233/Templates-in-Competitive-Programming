# algorithm-template

自用算法竞赛模板，来源于到处抄。目前正在重构中。

附有 LaTeX 生成的 pdf 版本，使用 [ply-template](https://github.com/palayutm/ply-template) 模板生成。

## Feature
0-indexed、区间左闭右开

## 模板目录

### 数据结构 data structure

+ 树状数组 (fenwick-tree.cpp)，支持单点修改、前缀和查询
+ 并查集 (disjoint-set-union.cpp)，支持查询集合、查询集合大小、合并
+ FHQ Treap (fhq-treap.cpp)，支持插入、删除、按值查询排名、按排名查询值、查询前驱后继
    + 文艺平衡树 (interval-reverse.cpp)，维护区间翻转
+ ST 表 (ST.cpp)
+ 左偏树 (lefist-tree.cpp)，可合并堆
+ 主席树
    + 静态区间第 k 小 (persistent-segment-tree.cpp)
    + 静态区间颜色数 (static-interval-color.cpp)
    + 静态区间 mex (static-interval-mex.cpp)
+ 莫队
    + 普通莫队 (mo.cpp)

### 数学 math

+ 组合数 (binom.cpp, with mod-int.cpp)
+ 卢卡斯定理 (lucas.cpp, with binom.cpp)
+ 线性筛素数 (prime-sieve.cpp)
+ 线性求逆元 (1-n-inverse.cpp)
+ 线性基 (basis.cpp)
+ 高斯消元 (gaussian-elimination.cpp)
+ 扩展欧几里得算法 (exgcd.cpp)
+ 平面计算几何 (computational-geometry.cpp) **待完善**

### 字符串 string

+ 前缀函数 (KMP.cpp)
+ Manacher 算法 (manacher.cpp)
+ Trie (trie.cpp)
+ 字符串哈希 (string-hash.cpp)

### 图论 graph theory

+ 线段树合并 (segment-tree-merge.cpp)
+ 树上启发式合并 (dsu-on-tree.cpp)
+ 重链剖分 (heavy-light-decomposition.cpp)
+ 最近公共祖先
    + 倍增做法 (LCA1.cpp)
    + 重链剖分做法 (LCA2.cpp)
+ 树上差分 (difference-on-tree.cpp)
+ 连通性相关
    + 割点 (tarjan1.cpp)
    + 割边 (tarjan2.cpp)
    + 点双连通分量 (tarjan3.cpp)
    + 边双连通分量 (tarjan4.cpp)

### 杂项 various

+ 取模类 (mod-int.cpp)
+ 大整数类 (big-int.cpp)
+ 对拍 (duipai.cpp)
