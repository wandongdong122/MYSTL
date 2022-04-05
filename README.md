# <center>**STL 标准库实现**

![STL六大组件.png](https://s2.loli.net/2022/04/05/lZJiL5gIUyBTSKu.png)

# 一、空间配置器 #  

**空间配置器：**  提供数据存储的空间。  

**空间配置器流程：**  在对象构造前进行空间配置、在对象析构后进行空间释放。  


**空间配置器结构组成：**     

![空间配置器.png](https://s2.loli.net/2022/04/05/Dih34zKO8Wq6rtE.png)  

**一、二级配置器：**  
![STL1_2级配置器.png](https://s2.loli.net/2022/04/05/SMV6mjH97AKCapw.png)  

# 二、迭代器 #

**迭代器的相应性别：**  
1. value type       &emsp;&emsp;&emsp; --迭代器所指对象的型别
2. difference type  &emsp; --两个迭代器之间的距离
3. pointer type
4. reference type
5. iterator catagoly
	1. Input Iterator &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 迭代器所指的对象，不允许外界改变，只读。
	2. Output Iterator  &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;只写
	3. Forward Iterator &emsp;&emsp;&emsp;&emsp;&emsp;允许写入型算法（如replace（））在此种迭代器所形成的区间上进行读写操作。
	4. Bidirectional Iterator&emsp;&emsp;&emsp;&emsp;可双向移动
	5. Random Access Iterator&emsp;&emsp; 随机迭代器，涵盖所有指针算术能力  


**迭代器的分类和从属关系：**     
![迭代器型别.png](https://s2.loli.net/2022/04/05/v62oKLYHuiEfhUR.png)  
任何一个迭代器，其类型应该永远落在“该迭代器所隶属之各种型别中，最强化的那个。  
STL算法的命名规则：以算法所能接受之最低阶迭代器类中，来为其迭代器型别参数命名。

**Traits编程技法：**    
将迭代器对象型别推导出来用作它用