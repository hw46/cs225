/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    BST<K, V>::Node*& v = find(root, key);
    if(!v){
        return V();
    }
    else{
        return v -> value;
    }
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if(!subtree){
        return subtree;
    }
    else if(subtree -> key == key){
        return subtree;
    }
    else{
        if(subtree -> key > key){
            return find(subtree -> left, key);
        }
        else{
            return find(subtree -> right, key);
        }
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    insert(root, key, value);
    
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    BST<K, V>::Node*& i = find(root, key);
    if(!i){
        i = new Node(key, value);
    }
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    K tmp_key = first -> key;
    V tmp_val = first -> value;
    first -> key = second -> key;
    first -> value = second -> value;
    second -> key = tmp_key;
    second -> value = tmp_val;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    BST<K, V>::Node*& n = find(subtree, key);
    if(!n){
        return;
    }
    else if(!n -> left && !n -> right){
        subtree = nullptr;
        return;
    }
    else if(!subtree -> left){
        Node* tmp = n -> right;
        delete n;
        n = tmp;
    }
    else if(!subtree -> right){
        Node* tmp = n -> left;
        delete n;
        n = tmp;
    }
    else{
        Node* tmp = n -> left;
        while(tmp -> right){
            tmp = tmp -> right;
        }
        swap(tmp, n);
        remove(n -> left, tmp -> key);
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K, V> tree;
    for(unsigned i = 0; i < inList.size(); i++){
        std::pair<K, V> node = inList[i];
        tree.insert(node.first, node.second);
    }
    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::vector<int> h(inList.size());
    std::sort(inList.begin(), inList.end());
    do{
        BST<K, V> tree = listBuild(inList);
        h[tree.height()]++;
    }
    while(std::next_permutation(inList.begin(), inList.end()));
    return h;
}