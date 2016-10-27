# 加密算法之Playfair及Hill算法
[TOC]

## 1 Playfair算法

### 1.1 简介

Playfair密码（Playfair cipher）是一种替换密码，1854年由英国人查尔斯·惠斯通（Charles Wheatstone）发明。
它有一些不太明显的特征：密文的字母数一定是偶数；任意两个同组的字母都不会相同，如果出现这种字符必是乱码和虚码。

### 1.2 算法

算法依据一个5\*5的字母矩阵组成的密码表。该矩阵使用一个关键词构造，方法是按从左到右、从上到下顺序填入关键词的字母（去除重复字母）后，将字母表其余字母填入。例如，当关键词取为*monarchy*时，字母矩阵为

$$
 \begin{bmatrix}
	M & O & N & A & R \\
	C & H & Y & B & D \\
	E & F & G & I/J & K \\
	L & P & Q & S & T \\
	U & V & W & X & Z
 \end{bmatrix} \tag{1}
$$

密码表里排列有25个字母。如果一种语言字母超过25个，可以去掉使用频率最少的一个。
如，法语一般去掉w或k，德语则是把i和j合起来当成一个字母看待。英语中z使用最少，可以去掉它。

#### 1.2.1 加密

Playfair加密方法是先将明文按两个字母一组进行分组，然后在矩阵中找对应的密文，取密文的规则如下：

1. 若明文分组出现在相同字母在一组，则在重复的明文字母中插入一个填充字母（比如 *k*)进行分割后重新分组（如*balloon*被重新分组为 ba lk lo on)
2. 若分组到最后一组时只有一个字母，则补充字母*k*
3. 若明文字母在矩阵中同行，则循环取其右边字母为密文（如*ar*被加密为*RM*）
4. 若明文字母在矩阵中同列，则循环取其下边字母为密文（如*mu*被加密为*CM*）
5. 若明文字母在矩阵中不同行不同列，则取其同行且与下一字母同列的字母为密文（如*hs*被加密为*BP*，*ea*被加密为*IM*或*JM*）

例如，明文为*I'm maple*，分组成为*Im ma pl ek*（不处理非字母字符）；用上述矩阵加密后的密文为*EA OR QP KT*。

#### 1.2.2 解密

解密规则则与加密规则相反，由于密文中同一分组内没有相同字母，故仅考虑寻找明文情况，取密文规则如下：

1. 若密文字母在矩阵中同行，则循环取其左边字母为密文（如*OR*被解密为*MA*）
2. 若密文字母在矩阵中同列，则循环取其下边字母为密文（如*KT*被加密为*EK*）
3. 若密文字母在矩阵中不同行不同列，则取其同行且与下一字母同列的字母为密文（如*EA*被加密为*IM*）

### 1.3 实践

明白了算法原理后，就可以亲手实践一个加密解密的小程序了。
在动手之前，首先是考虑如何高效的字母矩阵中找到对应的字母。
首先，在分组出现在同行或同列的情况下，会进行循环移动取操作，此时可以将第0列拷贝到第5列，第0行拷贝的第5行的方法来省略求余运算。
另外，如果单纯地使用遍历算法，那么每一次进行加密时就要对每一个分组进行时间复杂度为O($n^2$)的查找操作，明显效率是很低的。为了提高查找效率，在一开始的矩阵初始化中，作者使用了**c++**的关联容器*map*进行操作，初始化代码如下：

```c++
PlayFair::PlayFair(string key)
{
    char letters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    keyMap.clear();//keyMap为PlayFair成员

    for(size_t i = 0; i < key.size(); ++i){//创建矩阵首字符串键对
       keyMap.insert(make_pair(key[i], keyMap.size()));//当前map大小即为字母应在的位置
    }
    for(size_t i = 0; i < 26; ++i){//创建剩余键对
        keyMap.insert(make_pair(letters[i], keyMap.size()));
    }

	/*这里采用让y和z在同一位置的方法，与传统不同*/
    if(keyMap['z'] < keyMap['y'])
        keyMap['y'] = keyMap['z']; //令z与y的位置相同
    else
        keyMap['z'] = keyMap['y']; //令z与y的位置相同

    for(size_t i = 0; i < keyMap.size(); ++i){
        char ch = 'a' + i;
        keyArray[ keyMap[ch] / 5 ][ keyMap[ch] % 5 ] = ch;
    }

    /* 拷贝第0行至第5行，第0列至第5列
	 * 虽然两部分可以合并在一个循环体内，因为rows与cols相同，
	 * 但为了可读性，则用这种方法，并且这种方法仅是增加了i的赋值与判断而已
	 */
    for(size_t i = 0; i < rows; ++i)
        keyArray[i][cols - 1] = keyArray[i][0];
    for(size_t i = 0; i < cols; ++i)
        keyArray[rows - 1][i] = keyArray[0][i];
}
```

而在加密和解密时，算法所依赖的是字母所在矩阵中的行、列坐标值，在此可以将字母的一维值（即将字母所在矩阵当成一维数组看待时的下标值）转换为二维值（字母在矩阵中的行、列坐标值）被保存至*pair*中，从而可以高效的在矩阵中找出对应字母，这时需要另外一个存储字符和对应*pair*的map，创建代码如下：
```c++
//根据keyMap创建矩阵关联容器
void CreateMatrixMap(map<char, size_t> &keyMap, map<char, pair<size_t, size_t>> &matrixMap)
{
    matrixMap.clear();
    for(auto it = keyMap.begin(); it != keyMap.end(); ++it){
        matrixMap.insert(make_pair(it->first,
                                   make_pair(it->second / (PlayFair::rows - 1), 
												it->second % (PlayFair::cols - 1)))
						);
    }
}
```

而在进行字母的搜索时，可以直接使用*pair*对进行查找，代码如下：

```c++
//将ch1和ch2通过矩阵转换为其他字母
void PlayFair::FairTransfer(char &ch1, char &ch2, map<char, pair<size_t, size_t>> &matrixMap)
{
    pair<size_t, size_t> pairCh1, pairCh2;
    pairCh1 = matrixMap[ch1];
    pairCh2 = matrixMap[ch2];

    if(pairCh1.first == pairCh2.first){//行与行相等
        ch1 = keyArray[pairCh1.first][pairCh1.second + 1];
        ch2 = keyArray[pairCh2.first][pairCh2.second + 1];
    }else if(pairCh1.second == pairCh2.second){//列与列相等
        ch1 = keyArray[pairCh1.first + 1][pairCh1.second];
        ch2 = keyArray[pairCh2.first + 1][pairCh2.second];
    }else{//不同行列
        ch1 = keyArray[pairCh1.first][pairCh2.second];
        ch2 = keyArray[pairCh2.first][pairCh1.second];
    }
}
```

处理完再矩阵中查询并替换字母的问题后，就可以继续考虑下一问题——如何进行分组。
分组是很简单的处理过程，只要线性搜索明文，将非字母保留并合并两个待替换字母即可，但同时还要考虑字母数为单数的情况，方法是补字母*k*，代码如下：

```c++
//对明文clear进行加密
void PlayFair::encrypt(std::string &clear)
{
    string tmp;
    if(clear.empty()) return ;//无效的明文

    tmp.reserve(clear.size() * 2);//预分配空间
    str2lowstr(clear);//首先转换为小写字母形式
    map<char, pair<size_t, size_t>> matrixMap;
    CreateMatrixMap(keyMap, matrixMap);//构建矩阵关联容器

    for(size_t i = 0; i < clear.size(); ++i){
        char ch = clear.at(i);
        string norLetter = "";
        if(!isLowLetter(ch))
            tmp.push_back(ch);//不处理非小写字母
        else{
            char ch2;

            while(++i < clear.size() && !isLowLetter(ch2 = clear.at(i))){
                norLetter.push_back(ch2);//如果第一个字母为小写字母，之后的不是小写字母，则不进行处理
            }

            if(i < clear.size()){//当前还有剩余字母
                if(ch2 == ch){//若两字母相同，则赋第二个字母为k，并且使计数字母i减1
                    ch2 = 'k';
                    --i;
                }
            }else{//没有剩余字母，则补充ch2为k
                ch2 = 'k';
            }

            this->FairTransfer(ch, ch2, matrixMap);//转换字符

            /* 将两个字符和非字母字符串添加进字符串 */
            tmp.push_back(ch);
            tmp += norLetter;
            tmp.push_back(ch2);
        }
    }

    clear.swap(tmp);//交换明文为密文
}
```

解密过程与加密过程一致，只不过将33行的转换字符方法*FairTranser*改为返回字符方法*FairReturn*。*FairReturn*方法可根据解密原理参照*FairTranser*方法进行修改。详细可参考[playfair.cpp](https://github.com/maple2snow/Encrypt/blob/master/palyfair.cpp).

### 1.4 演示

此部分用于显示我的小程序成果，简单介绍功能部分，如无需进一步了解该算法的朋友可以绕过此节。
该程序基于`QT5开发框架`，运行环境为`windows`。

- 初始界面
	
	程序的初始界面如下图所示，左上角的`Algorithm Frame`为算法选取框，在这里，可以选取的算法有`Playfair`以及即将要介绍的`Hill`算法。算法选取框下面是`Options`框，用于选择是否从文件中读取及是否向文件中写入结果。而在下方的`Button`框，则用于执行**加密**、**解密**、**查看更多信息**及**关闭更多信息**功能。最下方的则是作者的一些介绍。
	右侧的`Key`则是用于填入生成算法矩阵的密钥，如若不填充，则默认以字母序填充矩阵。

	<div align=center>
	<img src="http://i.imgur.com/9ngkw59.png" title="初始界面" />
	</div>

- 输入密钥并生成矩阵

	在选择了`Playfair`算法后，在`Key`处输入密钥*maple*，并点击`More Info`按钮后，即可显示算法矩阵，如下图所示。（当然，如果你没有选择任何一个算法就想显示更多信息的话，是会弹出一个提醒框，表示你没有选择任何算法的，在此不做篇幅介绍）

	<div align=center>
	<img src="http://i.imgur.com/1S8srca.png" title="输入密钥并生成矩阵" />
	</div>

- 加密

	在`Operation`框中，有表示明文的`Clear Text`和密文的`Cipher Text`文本输入框，当向进行加密时，可以在明文框输入明文，在点击加密按钮`Encrypt`后，加密后的明文将会出现在密文框，如下图所示，明文<font color = green>I love maple in autumn!</font>被加密为密文<font color = red>k aqum aplem jh mvozeh!</font>
	
	<div align=center>
	<img src="http://i.imgur.com/uxbHuAv.png" title="加密" />
	</div>

- 解密

	如果看到上述那句话，一般人当然会意思不明所以，而这就需要进行解密了，直接点击解密按钮`Decrypt`，则可以将密文解密并放置于明文框中。如下图所示，密文被解密为<font color = deep green>i</font><font color = green> love maple in autumn!</font>。可以看到大写*I*被改为了小写*i*，这是因为算法矩阵是填充了小写字母的缘故，所有字母都会被相应的小写字母所替代。

	<div align=center>
	<img src="http://i.imgur.com/YCWtz78.png" title="解密" />
	</div>

- 从文件中读取并写入文件

	当勾选了复选框`Read From File`及`Write To File`后（也可以只选其中一个执行部分功能）就可以从文件中读取明文进行加密并将密文存储于文件中。点击加密按钮后便会出现文件选择框，在此，读取一份名为`poem.txt`的文件，里面是一首诗，接下来查看加密情况和加密文件，如下图所示，加密文件被读取到明文框，密文被显示到密文框。

	<div align=center>
	<img src="http://i.imgur.com/w7QFmrs.png" title="加密文件" />
	</div>

	而在点击解密后，也可以将加密文件进行解密并保存在明文文件中，明文同样会被显示到明文框，只不过所有字母都被改为小写，并可能出现在出现同组字母为相同时添加额外字母或最后一个分组只有一个字母的情况，此时都会多补充一个字母'k'。如下图所示。
	
	<div align=center>
	<img src="http://i.imgur.com/Uz6SFYR.png" title="解密文件" />
	</div>

## 2 Hill算法