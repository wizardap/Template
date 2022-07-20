#include<bits/stdc++.h>
using namespace std;
using ll = int64_t;
///-----------------------------------------------------------------------------------------------------------
const int ALPHABET = 26;
const char firstchar = 'a';
struct Node
{
	Node *child[ALPHABET];
	bool isEnd;
	Node()
	{
		for (int i = 0; i < ALPHABET; i++) child[i] = nullptr;
		isEnd = false;
	}
};
Node *root=new Node;
struct Trie
{
	void insert(string s)
	{
		Node *cur = root;
		for (int i = 0; i < (int)s.size(); i++)
		{
			int c = s[i] - firstchar;
			if (cur->child[c] == nullptr) cur->child[c] = new Node;
			cur = cur->child[c];
		}
		cur->isEnd = true;
	}
	bool search(string s)
	{
		Node *cur = root;
		for (int i = 0; i < (int)s.size(); i++)
		{
			int c = s[i] - firstchar;
			if (cur->child[c] == nullptr) return false;
			cur = cur->child[c];
		}
		return true;

	}
};
int main()
{
	int n, q;
	cin >> n >> q;
	Trie trie;
	for (int i = 1; i <= n; i++)
	{
		string s;
		cin >> s;
		trie.insert(s);
	}
	while (q--)
	{
		string s;
		cin >> s;
		puts(trie.search(s) ? "YES" : "NO");
	}
}
