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
## 3.1.1、vector ---连续线性空间 ##
**1、vector和array的区别**  。
&emsp;&emsp;array是静态空间，vector是动态空间，随着元素加入，内部机制会自行扩充空间容纳新元素。  
**2、迭代器----普通指针**   
&emsp;&emsp;vector维护连续线性空间，所以无论其元素型别是什么，普通指针都可以作为vector的迭代器 。vector支持随机存取，而普通指针正有这样的能力，所以vector提供的迭代器为**Random Access Iterators**。  
**3、数据结构**  
&emsp;&emsp;增加新的元素时，如果超过当时的容量，则容量会扩充至两倍。如果两倍容量任不足，就扩张到足够大的容量。空间扩张步骤：**空间重新配置-->元素移动-->释放原空间**。  
**4、动态增加大小**  
&emsp;&emsp;所谓动态增加大小，并不是在原空间之后接续新空间（因为无法保证原空间之后尚有可供配置的空间），而是以原大小的两倍另外配置一块较大的空间，然后将原内容拷贝过来，然后才开始在原内容之后构造新元素，并释放空间。因此，对vector的任何操作，一旦引起空间重新配置，指向原vector的所有迭代器都会失效。  
## 3.1.2、list ---离散空间 ##
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
## 3.1.3、deque ---分段连续空间 ##
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

## 3.1.4、stack ---配接器（adapter） ##
&emsp;&emsp;stack是一种先进后出（First In Last Out，FILO）的数据结构。**以deque为底部结构并封闭其头端开口。**   
&emsp;&emsp;由于stack以底部容器完成所有工作，而具有这种“修改某物接口，形成另一种风貌”的性质的称为adapter（配接器）。因此stack往往不被归纳为container(容器)，而被归纳为 container adapter。  
**1、stack没有迭代器**  
**2、list也具有双端开口的特性，因此也可以作为stack的底层容器**  

## 3.1.5、queue ---配接器（adapter） ##
&emsp;&emsp;queue是一种先进先出（First In Fitst Out，FIFO）的数据结构。**以deque为底部结构并封闭其头端开口。**   
&emsp;&emsp;由于queue以底部容器完成所有工作，而具有这种“修改某物接口，形成另一种风貌”的性质的称为adapter（配接器）。因此stack往往不被归纳为container(容器)，而被归纳为 container adapter。  
**1、queue没有迭代器**  
**2、list也具有双端开口的特性，因此也可以作为queue的底层容器**  

## 3.1.6、heap ---隐式表述（implicit representation）---以array表述tree的方式 ## 
&emsp;&emsp;heap并不归属于STL容器组件，是priority_queue的组手。**priority_queue允许用户以任何次序将任何元素推入容器中，但取出时一定是从优先权最高（也就是数值最高）的元素开始取**。    

**max-heap:**每个元素的键值（key）都大于或等于其子节点键值。因此其最大值在根节点，并总是位于底层vector的起头处。  
**min-heap:**每个元素的键值（key）都小于或等于其子节点键值。因此其最小值在根节点，并总是位于底层vector的起头处。
   
**1、heap算法**  
&emsp;&emsp;**1.1、push_heap算法**  
&emsp;&emsp;1、新加入的元素一定要放在最下一层作为叶子节点，并填补在由左至右的第一个空格（complete binary tree），也就是把新元素插入在底层vector的end()处。   
&emsp;&emsp;2、为满足max-heap的条件（每个节点的键值都大于或等于其子节点键值），执行**（percolate up）上溯程序：将新节点拿来与其父节点比较，如果其键值（key）比父节点大，就父子对换位置。如此一直上溯，直到不需对换，或直到根节点为止。**   
&emsp;&emsp;**1.2、pop_heap算法**  
&emsp;&emsp;1、既然是max-heap，最大值必然在根节点。pop操作取走根节点（实际是设至底部容器vector的尾端节点）后，为了满足complete binary tree的条件，必须割舍最下层最右边的叶节点，并将其值重新安插至max-heap（因此有必要重新调整heap结构）。   
&emsp;&emsp;2、为满足max-heap的条件（每个节点的键值都大于或等于其子节点键值），执行**（percolate up）下溯程序：将空间节点和较大子节点“对调”，并持续下放，直到叶节点为止。然后将前述被割舍之元素设给这个“已到达叶层的空洞节点”，再对它执行一次percolate up(上溯)程序**    
&emsp;&emsp;**1.3、sort_heap算法**   
&emsp;&emsp;既然每次pop_heap可获得heap中键值最大的元素，如果持续对整个heap做pop_heap操作，每次将操作范围从后往前缩减一个元素（因为pop_heap会把键值最大的元素放在底部容器的最尾端），当整个程序执行完毕时，我们便有了一个递增序列。  
&emsp;&emsp;**1.4、make_heap算法**   
&emsp;&emsp;这个算法用来将一段现有的数据转换为一个heap，其主要依据是complete binary tree的隐式表述（implicit representation）。 
 
## 3.1.6、priority_queue ---配接器（adapter） ##
&emsp;&emsp;priority_queue是一个拥有权值观念的queue。由于这是一个queue，所以只允许在低端加入元素，并从顶端取出元素，除此之外别无其他存取元素的途径。  
&emsp;&emsp;priority_queue带有权值观念，其内的元素并非依照被推入的次序排序，而是自动按照元素的权值排序（通常权值以实值表示）。权值最高者，排在最前面。  
&emsp;&emsp;由于priority_queue以底部容器完成所有工作，而具有这种“修改某物接口，形成另一种风貌”的性质的称为adapter（配接器）。因此priority_queue往往不被归纳为container(容器)，而被归纳为 container adapter。   


# 3.2、关联式容器 #
&emsp;&emsp;标准的STL关联式容器分为**set（集合）**和 **map（映射表）**两大类，以及这两大类的衍生体 **multiset（多键集合）**和 **multimap（多键映射表）**。这些容器的底层机制均以 **RB-tree（红黑树）**完成。RB-tree也是一个独立的容器，但并不开放给外界使用。  
&emsp;&emsp;此外，SGI STL还提供了一个不在标准规格之列的关联式容器： **hash table（散列表）**，以及以此 hash table 为底层机制而完成的 **hash_set（散列集合）、hash_map（散列映射表）、hash_multiset（散列多键集合）、hash_multimap（散列多键映射表）**。  

&emsp;&emsp;所谓关联式容器：每笔数据（每个元素）都有一个键值(key)和一个实值(value)。当元素被插入到关联式容器中时，容器内部结构（可能是 RB-tree，也可能是 hash-table）便依照其键值大小，以某种特定规则将这个元素放置在合适的位置。关联式容器没有所谓的头尾，只有最大元素和最小元素。  
&emsp;&emsp;一般而言关联式容器内部是一个 balanced binary tree（平衡二叉树），以便获得良好的搜寻效率。blanced binary tree 有很多中类型，包括 AVL-tree、RB-tree、AA-tree。  

---
### 二叉搜索树
&emsp;&emsp;所谓二叉搜索树，可提供对数时间的元素插入和访问。二叉搜索树的节点放置规则是：**任何节点的键值一定大于其左子树中的每一个节点的键值，并小于其右子树中的每一个节点的键值。**  
&emsp;&emsp;**插入一个新元素：从根节点开始，元素值大于根节点的值就往右走，反之往左走，直到尾端，即是插入点；**  
&emsp;&emsp;**删除一个元素：**  
&emsp;&emsp;&emsp;&emsp;**1、如果A只有一个子节点：直接将子节点连接到A的父节点上。**  
&emsp;&emsp;&emsp;&emsp;**2、如果A有两个子节点：找到右子树的最小节点(右子树一直往左)取代A即可。**
---
### 平衡二叉搜索树
#### AVL tree
&emsp;&emsp;AVL tree 是一个“加上了额外平衡条件”的二叉搜索树。其平衡条件的建立是为了确保整棵树的深度为O(logN)。AVL tree要求任何节点的左右子树高度相差最多为1。


	外侧插入：
			插入点位于左子节点的左子树  --左左
			插入点位于右子节点的右子树  --右右
	内侧插入：
			插入点位于左子节点的右子树  --左右
			插入点位于右子节点的左子树  --右左
		
	对于外侧插入使用单旋转解决；
	对于内侧插入使用双旋转解决；
#### RB-tree（红黑树）
红黑树规则：  
&emsp;&emsp;1、每个节点不是红色就是黑色  
&emsp;&emsp;2、根节点为黑色  
&emsp;&emsp;3、如果节点为红，其子节点必须为黑  
&emsp;&emsp;4、任一节点至NULL（树尾端）的任何路径，所含黑节点数必须相同。  

![RB-treeNode.png](https://s2.loli.net/2022/04/13/fdVLsAYM6mJ9yRx.png)

## 3.2.1 set
&emsp;&emsp;set的特性是，所有元素都会根据元素的键值自动被排序。set的元素不像map那样可以同时拥有实值（value）和键值（key），set元素的键值就是实值，实值就是键值。set不允许两个元素有相同的键值。  
&emsp;&emsp;不能通过set的迭代器修改set的元素值，因为set Iterator 是一种 constant Iterator。
## 3.2.2 map
&emsp;&emsp;所有元素都会根据元素的键值自动被排序。map的所有元素都是pair，同时拥有实值（value）和键值（key）。pair的第一个元素被视为键值，第二个元素被视为实值。map不允许两个元素拥有相同的键值。  
&emsp;&emsp;不能通过map的迭代器修改map的键值，可以修改实值。
## 3.2.3 multiset
&emsp;&emsp; 与set完全相同，唯一的差别在于它允许键值重复，因为它的插入操作采用的是底层机制RB-tree的 insert_equal()而不是insert_unique()。
## 3.2.4 multimap
&emsp;&emsp;与map完全相同，唯一的差别在于它允许键值重复，因为它的插入操作采用的是底层机制RB-tree的 insert_equal()而不是insert_unique()。  
### hash table
emsp;emsp;二叉搜索树具有对数平均时间（logarithmic average time）的表现，但这样的变现构造在一个假象上：输入数据具有足够的随机性。hash table 在插入、删除、搜寻等操作上也具有“常数平均时间”的表现，而且这种表现是以统计为基础，不需要仰赖输入元素的随机性。  

### hash table 的碰撞问题
&emsp;&emsp;不同的元素被映射到相同的位置（有相同的索引）；  
### hash table 散列函数
&emsp;&emsp;负责将某一个元素映射为一个“**大小可以接收的索引**”。  
### hash table 负载系数（loading factor）
&emsp;&emsp;元素个数除以表格大小。负载系数永远在0~1之间----除非采用开链策略。  
### hash table 线性探测
&emsp;&emsp;当 hash function 计算出某个元素的插入位置，而该位置上的空间已不再可用时，循环往下一一寻找，直到找到一个可用空间为止 -----（表格足够大） （每个元素都够独立）   
### hash table 主集团（primary clustering）
&emsp;&emsp;平均插入成本的成长幅度，远高于负载系数的成长幅度。  
### hash table 二次探测（quadratic probing）
&emsp;&emsp;二次探测主要用来解决主集团问题。 如果hash function计算出新元素的位置为 H，而这个位置实际上已被使用，那么我们就依序尝试 H + 1^2 + 2^2 +...  
### hash table 开链（separate chaining）
&emsp;&emsp;在每个表格元素中维护一个list；hash function为我们分配某一个list，然后我们在那个list身上执行元素的插入、搜寻、删除等操作。
### hash table的桶子（buckets）与节点（nodes）
![hash_table _2_.png](https://s2.loli.net/2022/04/13/VlBzmxn5Aiv8GTP.png)