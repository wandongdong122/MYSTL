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

# 三、容器 #
# 3.1、序列式容器 #
# 3.1.1、vector ---连续线性空间 #
**1、vector和array的区别**  。
&emsp;&emsp;array是静态空间，vector是动态空间，随着元素加入，内部机制会自行扩充空间容纳新元素。  
**2、迭代器----普通指针**   
&emsp;&emsp;vector维护连续线性空间，所以无论其元素型别是什么，普通指针都可以作为vector的迭代器 。vector支持随机存取，而普通指针正有这样的能力，所以vector提供的迭代器为**Random Access Iterators**。  
**3、数据结构**  
&emsp;&emsp;增加新的元素时，如果超过当时的容量，则容量会扩充至两倍。如果两倍容量任不足，就扩张到足够大的容量。空间扩张步骤：**空间重新配置-->元素移动-->释放原空间**。  
**4、动态增加大小**  
&emsp;&emsp;所谓动态增加大小，并不是在原空间之后接续新空间（因为无法保证原空间之后尚有可供配置的空间），而是以原大小的两倍另外配置一块较大的空间，然后将原内容拷贝过来，然后才开始在原内容之后构造新元素，并释放空间。因此，对vector的任何操作，一旦引起空间重新配置，指向原vector的所有迭代器都会失效。  
# 3.1.2、list ---离散空间 #
&emsp;&emsp;相较于vector的连续线性空间，list就显得复杂很多，它的好处是每次插入或者删除一个元素就配置或释放一个元素空间。因此list对于空间的运用有绝对的精准，一点也不浪费，而且，**对于任何位置元素的插入或者元素移除，list永远是常数时间**。  
**1、list的结点(node)---双向链表**   

	template<class T>
    struct __list_node
	{
		typedef void* void_pointer; // 后续版本中改为 __list_node<T>*  即指向结点的指针
		void_pointer prev;
		void_pointer next;
		T data
	}
 
**2、list的迭代器**  
&emsp;&emsp;由于list是一个双向链表（double linked-list），迭代器必须具备前移、后移的能力。所以list提供的是一个**Bidirectional Iterator**。  
&emsp;&emsp;list的一个重要特征：插入操作(insert) 和拼接操作(splice)都不会造成原有的list迭代器失效。甚至list的元素删除操作(erase)，也会只有“指向被删除元素”的迭代器失效，其他迭代器不受影响。  
**3、list的数据结构---环状双向链表**  
&emsp;&emsp;  list不仅是一个双向链表，而且还是一个环状双向链表。所以它只需要一个指针，便可以完整表现整个链表。**也就是说在只需要定义一个指向末尾结点的指针 end 即可，begin = end->next**;  
**4、list的排序**  
&emsp;&emsp;list不能使用STL的sort()算法，因为**STL的排序算法只接受 Random Access Iterator**。    
# 3.1.3、deque ---分段连续空间 # 
&ensp;&ensp;vector是单向开口的连续线性空间，deque则是一种双向开口的连续线性空间。所谓双向开口，意思是可以在头尾两端分作做元素的插入和删除操作。  
**1、deque和vector的区别**  
&emsp;&emsp;deque允许常数时间内对起头端进行元素的插入或移除操作，二在于deque没有所谓容量(capacity)观念，因为它是动态的以分段          连续空间组成而成，随时可以增加一段新的空间并链接起来，换句话说，像vector那样“因旧空间不足而重新配置一块更大的空间，然后复制元素，再释放旧空间”这样的事情在deque是不会发生的。  
**2、deque的中控器**    
&emsp;&emsp;deque采用一块所谓的map（不是map容器）作为主控。这里所谓的**map是一小块连续空间，其中每个元素（此处称为一个结点，node）都是一个指针，指向另一段（较大的）连续线性空间，称为缓冲区。缓冲区才是deque存储空间主体，**STL允许我们 指定缓冲区的大小，默认值0表示将使用512bytes缓冲区。

	map 定义为 T**，也就是说map是一个指针，所指之物又是一个指针，指向型别为T的一块空间
  
![deque.png](https://s2.loli.net/2022/04/11/n75u1myeBhdEAH4.png)  
**3、deque的迭代器**  

	  // 迭代器所含成员数据
	  value_pointer cur;    // 指向所在缓冲区的当前元素
	  value_pointer first;  // 指向所在缓冲区的头部
	  value_pointer last;   // 指向所在缓冲区的尾部
	  map_pointer   node;   // 缓冲区所在节点
&emsp;&emsp;**通常设置两个迭代器 start iterator  和 finish iterator 分别指向 map 中第一个已经使用的节点和最后一个已经使用的节点。**

![deque迭代器.png](https://s2.loli.net/2022/04/11/3FWeokOH1yRPsqd.png)
**3、deque的数据结构**  
&emsp;&emsp; deque除了维护一个指向map的指针外，也维护start、finish两个迭代器，分别指向第一缓冲区的第一个元素和最后缓冲区的最后一个元素（下一个位置）。此外它必须记住目前的map大小，因为一旦map所提供的节点不足，就必须重新配置更大的一块map。