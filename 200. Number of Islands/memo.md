# 200. Number of Islands

問題：https://leetcode.com/problems/number-of-islands/description/

2次元の文字列が与えられる。"0", を海、"1" を陸とみなしたとき、島の数を数える。

## 方針

いわゆる「グラフの連結成分を数える」という問題なので、深さ優先探索、幅優先探索、Union Find 集合などが思い浮かんだ。再帰で簡単にかけそうなのでひとまずDFSを選択。

## 1st step

ひとまずAC。二次元配列を走査するときのインデックス`i`, `j` を`size_t` にしてしまっていたため、l48=l59における境界条件のチェックで`i - 1`, `j - 1` がアンダーフローしてしまい正しい答えを返さないというミスをしてしまった（`size_t`は原則符号なし整数）。
配列のindex は反射的に`size_t`にしてしまっていたのだが、考えを改めなければいけない（アンダーフローの可能性を毎回考えて決めるくらいなら全部int にしたほうが良いだろうか）。

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
