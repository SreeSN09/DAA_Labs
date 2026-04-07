#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// A Huffman tree node
struct Node {
    char ch;          // Character
    int freq;         // Frequency
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Compare function for priority queue (min-heap)
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq; // smallest frequency has highest priority
    }
};

// Function to print Huffman codes from the root of the tree
void printCodes(Node* root, string code) {
    if (!root) return;

    // If this is a leaf node, print the character and its code
    if (!root->left && !root->right) {
        cout << root->ch << " : " << code << "\n";
    }

    // Traverse left and right
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

// Function to build Huffman Tree and print codes
void buildHuffmanTree(const vector<char>& chars, const vector<int>& freqs) {
    if (chars.size() != freqs.size() || chars.empty()) {
        cerr << "Invalid input: characters and frequencies must match and be non-empty.\n";
        return;
    }

    // Create a priority queue to store live nodes of Huffman tree
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create a leaf node for each character and push it into the priority queue
    for (size_t i = 0; i < chars.size(); ++i) {
        pq.push(new Node(chars[i], freqs[i]));
    }

    // Iterate until the size of the queue becomes 1
    while (pq.size() > 1) {
        // Remove the two nodes of highest priority (lowest frequency)
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes
        Node* sumNode = new Node('\0', left->freq + right->freq);
        sumNode->left = left;
        sumNode->right = right;

        // Add the new node to the priority queue
        pq.push(sumNode);
    }

    // The remaining node is the root of the Huffman Tree
    Node* root = pq.top();

    cout << "Huffman Codes:\n";
    printCodes(root, "");

    // Cleanup: free allocated memory
    // (In production, use smart pointers to avoid manual deletion)
    // Here we skip deletion for brevity in this simple example
}

int main() {
    int n;
    cout << "Enter number of characters: ";
    if (!(cin >> n) || n <= 0) {
        cerr << "Invalid number of characters.\n";
        return 1;
    }

    vector<char> chars(n);
    vector<int> freqs(n);

    cout << "Enter characters:\n";
    for (int i = 0; i < n; ++i) {
        cin >> chars[i];
    }

    cout << "Enter corresponding frequencies:\n";
    for (int i = 0; i < n; ++i) {
        if (!(cin >> freqs[i]) || freqs[i] <= 0) {
            cerr << "Invalid frequency.\n";
            return 1;
        }
    }

    buildHuffmanTree(chars, freqs);

    return 0;
}
