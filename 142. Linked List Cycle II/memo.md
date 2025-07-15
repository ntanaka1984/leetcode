# 142. Linked List Cycle II

https://leetcode.com/problems/linked-list-cycle-ii/description/

与えられたリストが閉路を含む場合、閉路の始点となるノードを返す。閉路がない場合はNULLを返す。
## 実装方針

141 Linked List Cycle I と同様にListNode のポインタをset に格納し、再度訪れるかをチェックする。再訪した場合は格納されていたListNode のポインタを返す。

### 1st step
* 141のレビューを頂く前に書いたものなので`contains`を使わずに`find()`と`end()`の一致で要素がmap にあるかを調べてしまっています。
* ListNode ポインタの情報を格納するのはset にするべきでしたが、始点がリストの何番目にあるのかという情報が必要になるかな？と思い`map<ListNode*, int>`に格納してしまいました。

```c++
#include<map>
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* node = head;
        std::map<ListNode*, int> node_to_pos;
        int pos = 0;
        while (node != NULL) {
            auto it = node_to_pos.find(node);
            if (it != node_to_pos.end()) {
                return(it->first);
            }
            node_to_pos.emplace(node, pos++);
            node = node->next;
        }
        return NULL;
    }
};
```

## 2nd step

### 141. Linked List Cycle I の指摘を受けて以下の項目を修正


* set の要素の有無をcontains()で調べるようにしました。
* node がNULL であるかの判定を`while (node)` で行うようにしました。
* NULL を返すところを`return nullptr;`で返すようにしました。

```c++
#include <set>
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* node = head;
        std::set<ListNode*> visited;
        while (node) {
            if (visited.contains(node)) {
                return node;
            }
            visited.insert(node);
            node = node->next;
        }
        return nullptr;
    }
};

```

### 3rd step

2nd step と変化ありません。

所要時間 1分17秒です。

```c++
#include <set>
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* node = head;
        std::set<ListNode*> visited;
        while (node) {
            if (visited.contains(node)) {
                return node;
            }
            visited.insert(node);
            node = node->next;
        }
        return nullptr;
    }
};

```
