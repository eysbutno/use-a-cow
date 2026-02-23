#include <bits/stdc++.h>

using ll = long long;

/**
 * This isn't an actual template, but it like
 * gets the basic trie stuff down...
 * 
 * Binary trie is basically the same thing, just
 * change up some stuff.
 */
struct node {
	int cnt = 0;
	std::array<node*, 26> ch;
};

node* new_node() {
	node* cur = new node;
	(cur -> ch).fill(nullptr);
	return cur;
}

node* root = new_node();
void insert(const std::string &s) {
	node* cur = root;
	for (int i = 0; i < s.size(); i++) {
		int x = s[i] - 'a';
		if ((cur -> ch)[x] == nullptr) {
			(cur -> ch)[x] = new_node();
		}
		cur = (cur -> ch)[x];
		(cur -> cnt)++;
	}
}