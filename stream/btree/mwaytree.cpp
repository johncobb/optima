#include <iostream>
#include <fstream>
#include <stack>
#include <ctime>
#include <map>

using namespace std;

struct vrad {
    stack<uint64_t> data;
};

struct Node {
    int count;
    uint64_t data;
    int pos;
    struct Node* child;
};

struct Node* new_node(uint64_t data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->child = NULL;
}

Node* search(Node* node, vrad* data) {

    if (data->data.empty()) {
        return NULL;
    }
    /* 
     * recursive first item will be top
     * all subsequent will be children.
     */
    node = new_node(data->data.top());
    data->data.pop();

    node->child = searchnode(node, data);

    return node;
}

Node* searchnode(Node* node, vrad* data) {
    if (data->data.empty()) {
        return NULL;
    }

    if (node->data < data->data.top()) {

    }
}


// Node* build_tree(uint64_t data) {
//     Node * root = new_node(data);
// }


int main() {
    std::cout << "mway tree example: " << std::endl;
    uint64_t rad_wmi = 100;

    vrad x;
    x.data.push(100);
    x.data.push(100);
    x.data.push(100);

    vrad y;
    y.data.push(100);
    y.data.push(100);
    y.data.push(101);


    vrad z;
    z.data.push(100);
    z.data.push(100);
    z.data.push(102);



    // Node* root = build_tree(rad_wmi);
    Node* root = search(NULL, &x);
}

