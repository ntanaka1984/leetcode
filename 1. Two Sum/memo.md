# 1. Two Sum

問題：https://leetcode.com/problems/two-sum/submissions/

vector `nums` から2つの整数を選んで足し合わせたとき、 `target` と一致するものをvector のindex の組で答える。ただし、同じindex を2回使ってはいけない。

## 方針

最初、「数値→インデックス」のmap を考えたが同一の数値が2回登場することもあり得るためtest case 2, 3 でwrong answer となった。

複数の数値を取れるよう「数値→インデックスのベクター」を用意した。target - nums[i] の値を取るインデックス(j)を引き出せるようにし、それが今見ているインデックスiと違っていれば[i, j] というベクターを返すようにした。

## 1st step

LeetCode 上はかならず唯一の解があるという設定だったが、解がない場合は[-1, -1]を返すようにした。

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, std::vector<int>> num_to_indices;
        for (int i = 0;i < nums.size();i++) {
            if (!num_to_indices.contains(nums[i])) {
                num_to_indices.insert(std::make_pair(nums[i], std::vector<int>{}));
            }
            num_to_indices.at(nums[i]).push_back(i);
        }
        for (int i = 0;i < nums.size();i++) {
            int rest_num = target - nums[i];
            if (num_to_indices.contains(rest_num)) {
                std::vector<int> rest_num_indices = num_to_indices.at(rest_num);
                for (int j: rest_num_indices) {
                    if (i != j) {
                        return std::vector<int>{i, j};
                    }
                }
            }
        }
        return std::vector<int>{-1, -1};
    }
};

```


## 2nd step

変数名`rest_num` はtarget との差分なので`diff` が良いかと思い変更した。
`rest_num_indices` は冗長で、`indices`まで短くしてもいいと思いそのようにした。

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, std::vector<int>> num_to_indices;

        for (int i = 0;i < nums.size();i++) {
            if (!num_to_indices.contains(nums[i])) {
                num_to_indices.insert(std::make_pair(nums[i], std::vector<int>{}));
            }
            num_to_indices.at(nums[i]).push_back(i);
        }

        for (int i = 0;i < nums.size();i++) {
            int diff = target - nums[i];
            if (num_to_indices.contains(diff)) {
                std::vector<int> indices = num_to_indices.at(diff);
                for (int j: indices) {
                    if (i != j) {
                        return std::vector<int> {i, j};
                    }
               }
            }
        }

        return std::vector<int> {-1, -1};
    }
};
```

## 3rd step

2nd step と同じ。3回とも4~5分でaccepted

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, std::vector<int>> num_to_indices;
        for (int i = 0;i < nums.size();i++) {
            if (!num_to_indices.contains(nums[i])) {
                num_to_indices.insert(std::make_pair(nums[i], std::vector<int>{}));
            }
            num_to_indices.at(nums[i]).push_back(i);
        }
        for (int i = 0;i < nums.size();i++) {
            int diff = target - nums[i];
            if (num_to_indices.contains(diff)) {
                std::vector<int> indices = num_to_indices.at(diff);
                for (int j: indices) {
                    if (i != j) {
                        return std::vector<int>{i, j};
                    }
                }
            }
        }
        return std::vector<int>{-1, -1};
    }
};
```

## 4th step

解を探しに行っている2つめのfor ループのネストが深い気がしたのでearly return することにした。また、`indices` をわざわざ変数に格納する必要もないかと思い、`num_to_indices` をそのまま内側のfor ループで回した。

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, std::vector<int>> num_to_indices;
        for (int i = 0;i < nums.size();i++) {
            if (!num_to_indices.contains(nums[i])) {
                num_to_indices.insert(std::make_pair(nums[i], std::vector<int>{}));
            }
            num_to_indices.at(nums[i]).push_back(i);
        }
        for (int i = 0;i < nums.size();i++) {
            int diff = target - nums[i];
            if (!num_to_indices.contains(diff)) {
                continue;
            }
            for (int j: num_to_indices.at(diff)) {
                if (i != j) {
                    return std::vector<int>{i, j};
                }
            }
        }
        return std::vector<int>{-1, -1};
    }
};
```

## 5th step

先に解かれている方のコードを参照したところ、for ループを1回しか回さずに解いていたので私もそのようにしました。
また、変数名`diff` を`complement` と改めました。

参考にした回答
https://github.com/ryosuketc/leetcode_grind75/pull/1/files/2c5161514b4561a34193852a2a218603b35ca734#diff-fb72ed84c22daaa065dd8aca8a790d2a4a20bd48c4db22d7605117f02be53c40


```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int, int> num_to_index;
        for (int i = 0;i < nums.size();i++) {
            int complement = target - nums[i];
            if (num_to_index.contains(complement)) {
                return {i, num_to_index[complement]};
            }
            num_to_index[nums[i]] = i;
        }
        return {};
    }
};
```

