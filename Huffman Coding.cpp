#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left, * right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = nullptr;
        right = nullptr;
    }
};

struct compare {
    bool operator() (Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void encode(Node* root, string code, unordered_map<char, string>& mp) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        mp[root->ch] = code;
    }

    encode(root->left, code + "0", mp);
    encode(root->right, code + "1", mp);
}

void printHuffmanCodes(string S, int f[]) {
    priority_queue<Node*, vector<Node*>, compare> minHeap;
    unordered_map<char, string> mp;

    int n = S.size();
    for (int i = 0; i < n; i++) {
        Node* node = new Node(S[i], f[i]);
        minHeap.push(node);
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();

        Node* right = minHeap.top();
        minHeap.pop();

        Node* internal = new Node('\0', left->freq + right->freq);
        internal->left = left;
        internal->right = right;
        minHeap.push(internal);
    }

    Node* root = minHeap.top();
    encode(root, "", mp);

    cout << "Huffman codes for the characters in the string: " << endl;
    for (int i = 0; i < n; i++) {
        cout << S[i] << " : " << mp[S[i]] << endl;
    }
}

int main() {
    string S = "abcdef";
    int f[] = { 5, 9, 12, 13, 16, 45 };
    printHuffmanCodes(S, f);
    return 0;
}

