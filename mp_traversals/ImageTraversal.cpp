#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "Point.h"

#include "ImageTraversal.h"

namespace Traversals {
  /**
  * Calculates a metric for the difference between two pixels, used to
  * calculate if a pixel is within a tolerance.
  *
  * @param p1 First pixel
  * @param p2 Second pixel
  * @return the difference between two HSLAPixels
  */
  double calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
    double h = fabs(p1.h - p2.h);
    double s = p1.s - p2.s;
    double l = p1.l - p2.l;

    // Handle the case where we found the bigger angle between two hues:
    if (h > 180) { h = 360 - h; }
    h /= 360;

    return sqrt((h*h) + (s*s) + (l*l));
  }
  
  /**
  * Adds a Point for the bfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void bfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_back(point);
  }

  /**
  * Adds a Point for the dfs traversal to visit at some point in the future.
  * @param work_list the deque storing a list of points to be processed
  * @param point the point to be added
  */
  void dfs_add(std::deque<Point> & work_list, const Point & point) {
    /** @todo [Part 1] */
    work_list.push_front(point);
  }

  /**
  * Removes the current Point in the bfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void bfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    Point tmp = work_list.front();
    work_list.pop_front();
  }

  /**
  * Removes the current Point in the dfs traversal
  * @param work_list the deque storing a list of points to be processed
  */
  void dfs_pop(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    Point tmp = work_list.front();
    work_list.pop_front();
  }

  /**
   * Returns the current Point in the bfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point bfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
  }

  /**
   * Returns the current Point in the dfs traversal
   * @param work_list the deque storing a list of points to be processed
   * @return the current Point 
   */
  Point dfs_peek(std::deque<Point> & work_list) {
    /** @todo [Part 1] */
    return work_list.front();
  }

  /**
  * Initializes a ImageTraversal on a given `png` image,
  * starting at `start`, and with a given `tolerance`.
  * @param png The image this traversal is going to traverse
  * @param start The start point of this traversal
  * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
  * it will not be included in this traversal
  * @param fns the set of functions describing a traversal's operation
  */
  ImageTraversal::ImageTraversal(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns) {  
    /** @todo [Part 1] */
    png_ = png;
    start_ = start;
    tolerance_ = tolerance;
    fns_ = fns;
  }

  /**
  * Returns an iterator for the traversal starting at the first point.
  */
  ImageTraversal::Iterator ImageTraversal::begin() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator(png_, start_, tolerance_, fns_);
  }

  /**
  * Returns an iterator for the traversal one past the end of the traversal.
  */
  ImageTraversal::Iterator ImageTraversal::end() {
    /** @todo [Part 1] */
    return ImageTraversal::Iterator();
  }

  /**
  * Default iterator constructor.
  */
  ImageTraversal::Iterator::Iterator() {
    /** @todo [Part 1] */
  }


  ImageTraversal::Iterator::Iterator(const PNG & png, const Point & start, double tolerance, TraversalFunctions fns){
    png_ = png;
    start_ = start;
    fns_ = fns;
    tolerance_ = tolerance;
    fns_.add(work_list_, start_);
    current_ = fns.peek(work_list_);
    marked.resize(png_.width());
    for(unsigned i = 0; i < png.width(); i++){
      marked[i].resize(png_.height());
      for(unsigned j = 0; j < png.height(); j++){
        marked[i][j] = false;
      }
    }
    marked[0][0] = true;
  }


  /**
  * Iterator increment operator.
  *
  * Advances the traversal of the image.
  */
  ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
    /** @todo [Part 1] */
    if(!work_list_.empty()){
      current_ = fns_.peek(work_list_);
      marked[current_.x][current_.y] = true;
      fns_.pop(work_list_);

      while(!work_list_.empty() && marked[fns_.peek(work_list_).x][fns_.peek(work_list_).y]){
        current_ = fns_.peek(work_list_);
        fns_.pop(work_list_);
      }

      Point right = Point(current_.x + 1, current_.y);
      Point down = Point(current_.x, current_.y + 1);
      Point left = Point(current_.x - 1, current_.y);
      Point up = Point(current_.x, current_.y - 1);

      if(right.x < png_.width() && right.x >= 0 && right.y >= 0 && right.y < png_.height()){
        if(marked[right.x][right.y] == false && calculateDelta(png_.getPixel(right.x, right.y), png_.getPixel(start_.x, start_.y)) <= tolerance_){
          fns_.add(work_list_, right);
        }
      }
      if(down.x < png_.width() && down.x >= 0 && down.y >= 0 && down.y < png_.height()){
        if(marked[down.x][down.y] == false && calculateDelta(png_.getPixel(down.x, down.y), png_.getPixel(start_.x, start_.y)) <= tolerance_){
          fns_.add(work_list_, down);
        }
      }
      if(left.x < png_.width() && left.x >= 0 && left.y >= 0 && left.y < png_.height()){
        if(marked[left.x][left.y] == false && calculateDelta(png_.getPixel(left.x, left.y), png_.getPixel(start_.x, start_.y)) <= tolerance_){
          fns_.add(work_list_, left);
        }
      }
      if(up.x < png_.width() && up.x >= 0 && up.y >= 0 && up.y < png_.height()){
        if(marked[up.x][up.y] == false && calculateDelta(png_.getPixel(up.x, up.y), png_.getPixel(start_.x, start_.y)) <= tolerance_){
          fns_.add(work_list_, up);
        }
      }
      if(!work_list_.empty()){
        current_ = fns_.peek(work_list_);
      }
    }
    return *this;
  }

  /**
  * Iterator accessor operator.
  *
  * Accesses the current Point in the ImageTraversal.
  */
  Point ImageTraversal::Iterator::operator*() {
    /** @todo [Part 1] */
    return current_;
  }

  /**
  * Iterator inequality operator.
  *
  * Determines if two iterators are not equal.
  */
  bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
    /** @todo [Part 1] */
    return !(work_list_.empty() && other.work_list_.empty());
  }

  /**
   * Iterator size function.
   *
   * @return size_t the size of the iterator work queue.
   */
  size_t ImageTraversal::Iterator::size() const {
    return work_list_.size();
  }

  /**
   * Iterator empty function.
   *
   * @return bool whether the iterator work queue is empty.
   */
  bool ImageTraversal::Iterator::empty() const {
    return work_list_.empty();
  }
}