# 141. Linked List Cycle
https://leetcode.com/problems/linked-list-cycle/description/

与えられた連結リストがcycle (閉路) を含むかどうかを判定する。
## 実装方針：
* すでに辿ったノードをsetに格納しておき、新しく訪れたノードがそれらのうちの一つに一致すれば閉路が存在すると判定する。
* ただしポインタの値をsetに格納するという発想に至らず、node ごとにユニークという保証のないval を格納してしまったために一度wrong answer となった
* 他の方のコードを参考にして修正したのが以下の1回目のコードです。
## 1回目
```cpp
#include <set>

class Solution {
public:
    bool hasCycle(ListNode *head) {
        std::set<ListNode*> visited_nodes ;

        while (head != NULL) {
            std::set<ListNode*>::iterator is_visited_it = visited_nodes.find(head) ;
            if (is_visited_it != visited_nodes.end()) {
                return true;
            }
            visited_nodes.insert(head) ;
            head = head -> next ;
        }
        return false;
    }
};
```
## 2回目
* この問題を解くためだけならfind の結果を残しておく必要はないので`is_visited_it` を削除
  * サイクルを検知したnode(投げ縄の結び目の部分)の情報が必要になるような拡張を考えると残してよかったかもしれないです
* `head`を`node` に一度格納したのは`head` にはリストの先頭という意味を持たせたいので、値が更新するのは良くないと考えたからです。
  * そう考えると`head` は`const` つきで`hasCycle` に与えたほうがいいかもしれません。
* `visited_nodes`->`visited` と変数名を簡潔にしました。
```cpp
#include <set>

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *node = head;
        std::set<ListNode*> visited;
        while(node != NULL) {
            if (visited.find(node) != visited.end()) {
                return true;
            }
            visited.insert(node);
            node = node->next;
        }
        return false;
    }
};
```
## 3回目
```cpp
#include <set>

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* node = head;
        std::set<ListNode*> visited;
        while (node != NULL) {
            if (visited.find(node) != visited.end()) {
                return true;
            }
            visited.insert(node);
            node = node->next;
        }
        return false;
    }
};
```

