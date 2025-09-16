# 200. Number of Islands

問題：https://leetcode.com/problems/number-of-islands/description/

2次元の文字列が与えられる。"0", を海、"1" を陸とみなしたとき、島の数を数える。

## 方針

いわゆる「グラフの連結成分を数える」という問題なので、深さ優先探索、幅優先探索、Union Find 集合などが思い浮かんだ。再帰で簡単にかけそうなのでひとまずDFSを選択。

## 1st step

ひとまずAC。二次元配列を走査するときのインデックス`i`, `j` を`size_t` にしてしまっていたため、l48=l59における境界条件のチェックで`i - 1`, `j - 1` がアンダーフローしてしまい正しい答えを返さないというミスをしてしまった（`size_t`は原則符号なし整数）。
配列のindex は反射的に`size_t`にしてしまっていたのだが、考えを改めなければいけない（アンダーフローの可能性を毎回考えて決めるくらいなら全部int にしたほうが良いだろうか）。

21行目の
```c++
      vector<bool>& is_visited_row(width, false);
      is_visited.push_back(is_visited_row);
```
はpush_back するときにコピーが発生して遅くなりそうなのですが、どう書いたらいいでしょうか？`is_visited.push_back(&is_visited_row)`とするとコンパイラエラーが出ました。


dfs の本体である`walk_island`にわたす引数が多すぎる。`height`, `width`, `is_visited` はメンバ変数にしてよいのではないか。というより、leetcode の制約を無視すれば以下のようにgridもメンバ変数にしてしまったほうがいいと思う。

```cpp
class Grid {
public:
  const vector<vector<char>> data;
  const int width, height;
  vector<vector<bool>> is_visited;
  Grid(const vector<vector<char>>& grid) : data(grid){
    height = data.size();
    if (height > 0) {
      width = data[0].size();
    }
    for (int i; i < height; ++i) {
      vector<bool>& is_visited_row(width, false);
      is_visited.push_back(is_visited_row);
    }
  }
}
```

私は`walk_island` を呼ぶときに`i`, `j` の境界条件を調べているんですが、他の人のコードを読むと呼び出される側で調べている人が多い印象です。ストローストラップの「C++によるプログラミングの原則と実践」に
> それでは、どうすればよいだろうか。もっともな理由がない限り、引数は関数でチェックするようにしよう。(5.5 ランタイムエラー)

とあったので、呼び出される側でチェックしたほうがいいのだと思います。
