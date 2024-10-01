/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>
#include <vector>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim)
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] > second[curDim]){
      return false;
    }
    else if(first[curDim] < second[curDim]){
      return true;
    }
    else{
      return (first < second);
    }
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential)
{
    /**
     * @todo Implement this function!
     */
    double curDis = 0;
    double potDis = 0;
    for(int i=0; i<Dim; i++){
      curDis += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      potDis += (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    if(curDis < potDis){
      return false;
    }
    else if(curDis > potDis){
      return true;
    }
    else{
      return (potential < currentBest);
    }
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    vector<Point<Dim>> copy;
    int dim = 0;
    for(unsigned i = 0; i < newPoints.size(); i++){
       copy.push_back(newPoints[i]);
    }
    root = addNodes(0, copy.size(), copy, dim);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::addNodes(int i, int j, vector<Point<Dim>>& copy, int dim){
  if(i >= j){
    return nullptr;
  }
  else if(copy.empty()){
    return nullptr;
  }
  else{
    auto cmp = [dim](Point<Dim>& x, Point<Dim>& y) {return smallerDimVal(x, y, dim);};
    int mid = (i+j-1)/2;
    select(copy.begin() + i, copy.begin() + j, copy.begin() + mid, cmp);
    KDTreeNode* node = new KDTreeNode(copy[mid]);
    node -> left = addNodes(i, mid, copy, (dim+1)%Dim);
    node -> right = addNodes(mid+1, j, copy, (dim+1)%Dim);
    return node;
  }
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  size = other.size;
  copyHelper(other.root, this->root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  clear(this -> root);
  copyHelper(rhs.root, this -> root);
  size = rhs.size;
  return *this;
}

template<int Dim>
void KDTree<Dim>::copyHelper(KDTreeNode *copyroot, KDTreeNode *root) {
  copyroot = new KDTreeNode();
  copyroot -> point = root -> point;
  copyHelper(copyroot -> left, root -> left);
  copyHelper(copyroot -> right, root -> right);
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(this -> root);
}

template <int Dim>
void KDTree<Dim>::clear(KDTreeNode*& subroot) {
  if (subroot != NULL) {
    clear(subroot -> left);
    clear(subroot -> right);
    delete subroot;
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    int dim = 0;
    if(!root){
      return Point<Dim>();
    }
    return findNearestNeighborHelper(query, root, dim);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighborHelper(const Point<Dim>& query, KDTreeNode* subroot, int dim) const{

  if(!subroot -> left && !subroot -> right){
    return subroot -> point;
  }
  bool flagl = true;
  bool flagr = true;
  Point<Dim> best;
  Point<Dim> potential;

  if(smallerDimVal(query, subroot->point, dim)){
    if(subroot -> left){
      best = findNearestNeighborHelper(query, subroot -> left, (dim+1)%Dim);
      flagl = false;
    }
    else{
      best = subroot -> point;
    }
  }
  else{
    if(subroot -> right){
      best = findNearestNeighborHelper(query, subroot -> right, (dim+1)%Dim);
      flagr = false;
    }
    else{
      best = subroot -> point;
    }
  }
  
  if(shouldReplace(query, best, subroot -> point)){
    best = subroot -> point;
  }
  
  double bestdis = 0;
  for(int i = 0; i < Dim; i++){
    bestdis += (best[i]-query[i])*(best[i]-query[i]);
  }
  if(bestdis >= (((query[dim])-(subroot -> point[dim]))*((query[dim])-(subroot -> point[dim])))){
    if(flagl == true && flagr == false && subroot -> left){
      potential = findNearestNeighborHelper(query, subroot -> left, (dim+1)%Dim);
      if(shouldReplace(query, best, potential)){
        best = potential;
      }
      return best;
    }
    if(flagl == false && flagr == true && subroot -> right){
      potential = findNearestNeighborHelper(query, subroot -> right, (dim+1)%Dim);
      if(shouldReplace(query, best, potential)){
        best = potential;
      }
      return best;
    }
    return best;
  } 
  else{
    return best;
  }
}

template <typename RandIter, typename Comparator>
void select(RandIter start, RandIter end, RandIter k, Comparator cmp){
    /**
     * @todo Implement this function!
     */
    if(start == end){
      return;
    }
    RandIter pivot;
    pivot = partition(start, end-1, k, cmp);
    if(k == pivot){
      return;
    }
    else if(k<pivot){
      select(start, pivot, k, cmp);
    }
    else{
      select(pivot+1, end, k, cmp);
    }
}

template <typename RandIter, typename Comparator>
RandIter partition(RandIter start, RandIter end, RandIter pivot, Comparator cmp){
  auto pivotValue = *pivot;
  swap(*pivot, *end);
  RandIter storeIndex = start;
  for(auto i = start; i != end; ++i){
    if(cmp(*i, pivotValue)){
      swap(*storeIndex, *i);
      ++storeIndex;
    }
  }
  swap(*end, *storeIndex);
  return storeIndex;
}