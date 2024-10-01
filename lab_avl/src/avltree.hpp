/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
  return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
  if (subtree == NULL)
    return V();
  else if (key == subtree->key)
    return subtree->value;
  else {
    if (key < subtree->key)
      return find(subtree->left, key);
    else
      return find(subtree->right, key);
  }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
  functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
  // your code here
  if(!t||!t->right){
    return;
  }
  Node* x = t;
  Node* y = t->right;
  t = y;
  x->right = y->left;
  y->left = x;
  x -> height = getHeight(x);
  y -> height = getHeight(y);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
  functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
  // Implemented for you:
  rotateLeft(t->left);
  rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
  functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
  // your code here
  if(!t||!t->left){
    return;
  }
  Node* x = t;
  Node* y = t->left;
  t = y;
  x->left = y->right;
  y->right = x;
  x -> height = getHeight(x);
  y -> height = getHeight(y);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
  functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
  // your code here
  rotateRight(t->right);
  rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
  // your code here
  if (!subtree) {
    return;
  }
  subtree -> height = getHeight(subtree);
  int treeBalance = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);
  if (abs(treeBalance) <= 1){
    return;
  }
  if (treeBalance < 0){
    if (heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right) > 0){
      rotateRightLeft(subtree);
    } 
    else{
      rotateLeft(subtree);
    }
  } 
  else{
    if(heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right) < 0){
      rotateLeftRight(subtree);
    } 
    else{
      rotateRight(subtree);
    }
  }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
  insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
  // your code here
  if (!subtree){
    subtree = new Node(key, value);
  } 
  else if (subtree->key == key) {
    subtree->value = value;
  } 
  else if (key < subtree->key) {
    insert(subtree->left, key, value);
  } 
  else {
    insert(subtree->right, key, value);
  }
  rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
  remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
  if(!subtree){
    return;
  }
  if(key < subtree -> key){
    remove(subtree -> left, key);
  } 
  else if(key > subtree -> key){
    // your code here
    remove(subtree->right, key);
  } 
  else{
    if(!subtree -> left && !subtree -> right){
      /* no-child remove */
      // your code here
      delete subtree;
      subtree = NULL;
    } 
    else if(subtree -> left && subtree -> right){
      /* two-child remove */
      // your code here
      /*Node* tmp = subtree -> left;
      Node* cur = tmp;
      while(true){
        if(tmp -> right == nullptr){
          break;
        }
        cur = tmp;
        tmp = tmp -> right;
      }
      std::swap(tmp -> value, subtree -> value);
      std::swap(tmp -> key, subtree -> key);
      remove(tmp, key);*/
      Node*& tmp = rightMostNode(subtree -> left);
      std::swap(tmp -> value, subtree -> value);
      std::swap(tmp -> key, subtree -> key);
      delete tmp;
      tmp = nullptr;
    }
    else{
      /* one-child remove */
      // your code here
      Node* subtreeNewChild = subtree->left != NULL ? subtree->left : subtree->right;
      delete subtree;
      subtree = subtreeNewChild;
    }
  }
  rebalance(subtree);
}

template <class K, class V>
typename AVLTree<K, V>::Node*& AVLTree<K, V>::rightMostNode(Node*& subtree){
  Node*& subtree0 = subtree;
    while(true){
      if(!(subtree0 -> right)){
        return subtree0;
        break;
      }
      subtree0 = subtree0 -> right;
    }
    //return subtree;
    //return !subtree -> right ? subtree : rightMostNode(subtree -> right);
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node*& subtree) {
  if (!subtree->left && !subtree->right) {
    return 0;
  } else if (subtree->left  == NULL) {
    return subtree->right->height + 1;
  } else if (subtree->right == NULL) {
    return subtree->left->height  + 1;
  } else {
    return max(subtree->right->height, subtree->left->height) + 1;
  }
}