# 計算量

アルゴリズムの計算量を理解せずに関数を使用したりすると、思わぬところで速度低下を招く

O(1)のアルゴリズムとO(n)のアルゴリズムはn=100の場合、100倍の差が出る

# O記法(ランダウの記号)

アルゴリズム計算量のおおよその速度を表記してくれる

計算のはかり方などは下のqiitaのやつがわかりやすい

図にしたほうがわかりやすいが、描くのがめんどくさいので下の参考URLを見てください

下記にいろいろな種類を表示する

### O(1) - 定数時間

最も早い計算量を示す、入力サイズが何であろうと計算量は同じ

ただし、その関数がそもそも遅い場合は遅いのでO(1)だから早いとは限らない

for文を使ってない場合はこれにあてはまる気がする

    int func(int n)

    {

        return array[n];

    }

### O(log N) - 対数時間

計算量がO(1)に次いで少ないので、安心してつかってもよいアルゴリズムの部類ではある

2分探索などが当てはまる

    int func(int n)

    {

        int sum = 0;

        for (int i = 0; i * i < n; i++)

        {

            sum += i;

        }

        return sum;

    }

### O(N) - 線形時間

入力サイズによって計算量も比例することを示している

array[100]のarray[0]~[99]の値をすべて足して返すなどが当てはまる

入力サイズが小さければ、計算量もやすく。おおきければ高くつくのでわかりやすい

    int func(int n)

    {

        int sum = 0;

        for (int i = 0; i < n; i++)

        {

            sum += i;

        }

        return sum;

    }

### O(N log N)

O(N)よりもコストが高くなる

ソートアルゴリズムでよく使用されるのでソートは重いと認識しておく

リアルタイムで毎フレーム行ったりするのはよしたほうがよい

    int func (int n)

    {

        int sum = 0;

        for (int i =0; i < n; i++)

        {

            sum += i;

        }


        if (n == 1)

        {

            return sum;

        }


        func(n/2);

        func(n-n/2);

    }

### O(N^2) - べき乗時間

みるだけで重い。バブルソートや2重ループでの処理などが当てはまる

普段からネストを深くしないように心がけることで回避できるが、衝突の計算などではつかわないといけない場面などが出てきそう

    int func(int n)

    {

        int sum = 0;

        for (int i = 0; i < n; i++)

        {
            for(int j = 0; j < n; i++)

            {

                sum += j;

            }

        }

        return sum;

    }

### O(2^N) - 指数時間

入力値が少ない場合を除いて、使用するのがためらわれる計算量

    int func(int n)

    {

        int sum = 0;

        int loop = 2 << n;

        for (int i = 0; i < loop; i++)

        {

            sum += i;

        }

        return sum;

    }


### O(N!) - 階乗時間

いままででできた計算コストの中で最も重くなると思われる計算量

ほかのアルゴリズムを考えれるならそちらに切り替えたほうがよい

    int g_sum = 0;


    int func(int n)

    {

        if (n == 0)

        {

            g_sum ++;

            return;

        }



        for (int i = 0; i < n; i++)

        {

            func(n - 1);

        }

    }

# O記法に頼りすぎない

O(1)の関数でもO(N)の関数よりも重くなることはもちろんある

内部で何をしているかが重要

# 参考URL

<https://ja.wikipedia.org/wiki/%E3%83%A9%E3%83%B3%E3%83%80%E3%82%A6%E3%81%AE%E8%A8%98%E5%8F%B7>

<http://ufcpp.net/study/stl/methods.html>

<https://qiita.com/cotrpepe/items/1f4c38cc9d3e3a5f5e9c>

<http://d.hatena.ne.jp/nowokay/20090106>
