# Graph-Theory-Final-Project #
 
Topic : Chinese Postman Problem

姓名 : 林聖凱</br>
系級 : 電機系</br>
學號 : N26070059</br>

## How to run ##

#Build</br>
$make</br>
#Run</br>
$./main.out</br>

## Setting ##

我的程式是針對無像且無權重的Graph設計的</br>
Node的數量上限為10</br>

在執行程式前需要先將Node之間的連線關係寫入topo.txt並放置在根目錄</br>
定義Node_A和Node_B之間有一條egde的方式為 : Node_A Node_B</br>

```
topo.txt範例:
a b
a c
b c
b e
c e
c d
d e
```

## Solution ##

1.透過topo.txt存取node、edge資料，建構出Adjacency Matrix</br>
2.挑出order為奇數的node(總數為偶數才能補成尤拉圖)，算出每個odd node之間的"最短路徑"和"路徑長"</br>
3.以(2.)計算出來的資料為基礎，找出總路徑長最小的node配對</br>
4.將(3.)求出的路徑補在圖上，並重新計算Adjacency Matrix</br>
5.將新的Adjacency Matrix放入深度優先搜尋演算法進行運算後得出路徑和總路徑長即為所求</br>

## Algorithms ##

```
從topo.txt得到node個數、node名稱、edge數量、連線關係，將全部彙整後轉換成Adjacency Matrix存入矩陣
將矩陣橫排相加得到對應node order，計算odd node的個數，如果是奇數則題目無解，如果是偶數則需兩兩配成一對，其路徑需再走一次
為了求出最短路徑，戴克斯特拉演算法運算出任2 odd node的距離，並列出實際路徑，將這些資料存入矩陣
使用for迴圈進行排列組合，將路徑長分組統計，找出最短的路徑總和，回傳兩兩配對的node點(可用在odd node總數為2、4、6、8、10的時候)
按照得到的node pair從剛才存放odd node路近的矩陣中取得實踐的路徑，補齊到Graph上，這樣才會使原圖變成尤拉圖以方便之後的運算
從新計算Adjacency Matrix，運用深度優先搜尋演算法找出適當的尤拉圖路徑並計算長度
將路徑和長度輸出成Result.txt檔案
```

## Results ##
以上面所述的topo.txt範例當作輸入

在終端機顯示的結果如下 : 
(#為註解)
```
#列出輸入的Node
==========Node==========
Node[0] = a
Node[1] = b
Node[2] = c
Node[3] = d
Node[4] = e

#列出輸入的Edge
==========Edge==========
a---b
a---c
b---c
b---e
c---e
c---d
d---e
a---d

#列出所有的Endpoint
==========Endpoint List==========
Point[0] = 0
Point[1] = 1
Point[2] = 0
Point[3] = 2
Point[4] = 1
Point[5] = 2
Point[6] = 1
Point[7] = 4
Point[8] = 2
Point[9] = 4
Point[10] = 2
Point[11] = 3
Point[12] = 3
Point[13] = 4
Point[14] = 0
Point[15] = 3

#利用Egde和Endpoint資訊構成的Adjacency Matrix
==========Adjacency Matrix==========
X|a|b|c|d|e|
a|0|1|1|1|0|
b|1|0|1|0|1|
c|1|1|0|1|1|
d|1|0|1|0|1|
e|0|1|1|1|0|

#將每排row的數字加總即為Node Order
==========Node Order==========
Node a Order = 3
Node b Order = 3
Node c Order = 4
Node d Order = 3
Node e Order = 3

#從Node Order中挑出order為奇數的Node
==========Odd Node==========
Node  a
Node  b
Node  d
Node  e
ODD count = 4

#將每個odd node之間的path列出"路徑"與"路徑長"
==========Odd Node Path==========
Node [a] to Node [b] :0---1
path_length [a_to_b] :1

Node [a] to Node [d] :0---3
path_length [a_to_d] :1

Node [a] to Node [e] :0---1---4
path_length [a_to_e] :2

Node [b] to Node [d] :1---0---3
path_length [b_to_d] :2

Node [b] to Node [e] :1---4
path_length [b_to_e] :1

Node [d] to Node [e] :3---4
path_length [d_to_e] :1

#將各odd node之間的路徑長存入matrix
==========Odd Node Path Length==========
X|a|b|c|d|e|
a|X|1|X|1|2|
b|1|X|X|2|1|
c|X|X|X|X|X|
d|1|2|X|X|1|
e|2|1|X|1|X|

#利用上表資訊帶入function找出最短的路徑和的路徑
#Graph應補上這些路徑才是尤拉圖
#取最短路徑才能符合中國郵差問題的題意
==========Shotest Pair Path Comparator==========
ODD_count = 4
Need 2 path
Path1 : 0---1
Path2 : 3---4
Total Length = 2

#補完路徑後重新計算一次Adjacency Matrix
==========NEW Adjacency Matrix==========
X|a|b|c|d|e|
a|0|2|1|1|0|
b|2|0|1|0|1|
c|1|1|0|1|1|
d|1|0|1|0|2|
e|0|1|1|2|0|

#最後透過深度優先搜尋演算法找出路徑並計算出總路徑長
==========Result Output==========
Total Path Length : 10
THE PATH IS : 
a b a c b e c d e d a
```

## Reference ##
[1]Chinese Postman Problem : https://zh.wikipedia.org/wiki/%E9%82%AE%E9%80%92%E5%91%98%E9%97%AE%E9%A2%98</br>
[2]Eulerian path : https://en.wikipedia.org/wiki/Eulerian_path</br>
[3]Depth First Search : http://alrightchiu.github.io/SecondRound/graph-depth-first-searchdfsshen-du-you-xian-sou-xun.html</br>
[4]Dijkstra's algorithm : https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm</br>
[5]Markdown suntax : https://github.com/emn178/markdown</br>
