# Templates-in-Competitive-Programming

自用算法竞赛模板，来源于我自己和网络。

由于代码时间跨度较大，来源较多，代码风格存在差异。

附有 LaTex 生成的 pdf 版本，使用 [ply-template](https://github.com/palayutm/ply-template) 模板生成。

## 数据结构 data structure

+ 树状数组 (Fenwick Tree.cpp)，支持单点修改、前缀和查询
+ 并查集 (Disjoint Set Union.cpp)，支持查询集合、查询集合大小、合并
+ FHQ Treap (FHQ Treap.cpp)，支持插入、删除、按值查询排名、按排名查询值、查询前驱后继
    + 文艺平衡树 (Interval Reverse.cpp)，维护区间翻转
+ ST 表 (ST.cpp)
+ 左偏树 (Lefist Tree.cpp)，可合并堆
+ 主席树
    + 静态区间第 k 小 (Persistent Segment Tree.cpp)
    + 静态区间颜色数 (Static Interval Color.cpp)
    + 静态区间 mex (Static Interval Mex.cpp)

## 数学 math

+ 组合数 (Binom.cpp, with ModInt.cpp)
+ 卢卡斯定理 (Lucas.cpp, with Binom.cpp)
+ 线性筛素数 (Prime Sieve.cpp)
+ 线性求逆元 (1-n Inverse.cpp)
+ 线性基 (Basis.cpp)
+ 高斯消元 (Gaussian Elimination.cpp)
+ 扩展欧几里得算法 (Exgcd.cpp)
+ 平面计算几何 (Computational Geometry.cpp)

## 字符串 string

+ 前缀函数 (KMP.cpp)
+ Manacher 算法 (Manacher.cpp)
+ Trie (Trie.cpp)
+ 字符串哈希 (String Hash.cpp)

## 图论 graph theory

+ 线段树合并 (Segment Tree Merge.cpp)
+ 树上启发式合并 (Dsu On Tree.cpp)
+ 重链剖分 (Heavy-light Decomposition.cpp)
+ 最近公共祖先
    + 倍增做法 (LCA1.cpp)
    + 重链剖分做法 (LCA2.cpp)
+ 树上差分 (Difference On Tree.cpp)
+ 连通性相关
    + 割点 (Tarjan1.cpp)
    + 点双连通分量 (Tarjan2.cpp)
    + 边双连通分量 (Tarjan3.cpp)

## 杂项 various

+ 取模类 (ModInt.cpp)
+ 大整数类 (BigInt.cpp)
+ 对拍 (duipai.cpp)