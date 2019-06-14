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
topo.txt範例:</br>
a b</br>
a c</br>
b c</br>
b e</br>
c e</br>
c d</br>
d e</br>
```

## Solution ##


## Algorithms ##

If your PC is `window 10`, then you need to install the related dependencies. For example, if you are using `VSCode` as your IDE, then you can install the plugin of `C/C++` in your vscode. And then install the following programs/packages:
* mingw
* git

Step by step to create `c_cpp_properties.json` and `tasks.json`:
* `Ctrl+Shift+P` -> `C/C++: Edit Configuration` -> then you have the first JSON file.
* `Ctrl+Shift+P` -> `Tasks: Configure Task` -> then you have the second JSON file.

Here is the setting of `c_cpp_properties.json` and `tasks.json`:
```json
# c_cpp_properties.json (If your mingw installed in another folder, then you have to change the value in `compilterPath`)
{
    "configurations": [
        {
            "name": "MinGW",
            "intelliSenseMode": "gcc-x64",
            "includePath": [
                "$(workspaceFolder)"
            ],
            "compilerPath": "C:/mingw/bin/gcc.exe",
            "cStandard": "c11",
            "cppStandard": "c++11"
        }
    ],
    "version": 4
}

# tasks.json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-g",
                "main.cc",
                "-o",
                "main.exe",
                "-Ifake-mininet/lib",
                "-g3",
                "-L.",
                "-lfakemn_win",
                "-std=c++11"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            }
        }
    ]
}
```

After all the settings have been done, we can press `Ctrl+Shift+B` to run the task, if your settings is correct, then there will have an executable file which named `main.exe`.

Or you can just [DOWNLOAD a pre-built VM images](http://gofile.me/39GpL/XU5tznyO6) provided by TA.

> [Guide of environment setting](https://hackmd.io/-5WZQC-1QqOeV3KUX65tEw?view) on Windows.

## Results ##

## Reference ##
[1]Chinese Postman Problem : https://zh.wikipedia.org/wiki/%E9%82%AE%E9%80%92%E5%91%98%E9%97%AE%E9%A2%98</br>
[2]Eulerian path : https://en.wikipedia.org/wiki/Eulerian_path</br>
[3]Depth First Search : http://alrightchiu.github.io/SecondRound/graph-depth-first-searchdfsshen-du-you-xian-sou-xun.html</br>
[4]Dijkstra's algorithm : https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm</br>
[5]Markdown suntax : https://github.com/emn178/markdown</br>
