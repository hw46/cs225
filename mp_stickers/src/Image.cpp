#include <string>
#include "Image.h"
#include <iostream>
#include <cmath>

using namespace std;

Image::Image()
{
  PNG();
}
Image::Image(unsigned int width, unsigned int height)
{
  PNG(width, height);
}
void Image::lighten(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          cs225::HSLAPixel & pixel = this->getPixel(x, y);
          pixel.l += 0.1;
          if (pixel.l > 1){
            pixel.l=1;
          }
      }
    }
  }

  void Image::lighten(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          cs225::HSLAPixel & pixel = this->getPixel(x, y);
          pixel.l += amount;
          if (pixel.l > 1){
            pixel.l=1;
          }
      }
    }
  }

void Image::darken(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          cs225::HSLAPixel & pixel = this->getPixel(x, y);
          pixel.l -= 0.1;
          if (pixel.l < 0) {
            pixel.l=0;
      }
    }
  }
}

void Image::darken(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          cs225::HSLAPixel & pixel = this->getPixel(x, y);
          pixel.l -= amount;
          if (pixel.l < 0) {
            pixel.l=0;
      }
    }
  }
}

void Image::saturate(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          cs225::HSLAPixel & pixel = this->getPixel(x, y);
          pixel.s += 0.1;
          if (pixel.s > 1) {
            pixel.s=1;
      }
    }
  }
}

void Image::saturate(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          cs225::HSLAPixel & pixel = this->getPixel(x, y);
          pixel.s += amount;
          if (pixel.s > 1) {
            pixel.s=1;
      }
    }
  }
}

void Image::desaturate(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          cs225::HSLAPixel & pixel = this->getPixel(x, y);
          pixel.s -= 0.1;
          if (pixel.s < 0) {
            pixel.s = 0;
      }
    }
  }
}

void Image::desaturate(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          cs225::HSLAPixel & pixel = this->getPixel(x, y);
          pixel.s -= amount;
          if (pixel.s < 0) {
            pixel.s = 0;
      }
    }
  }
}

void Image::grayscale(){
  for (unsigned x = 0; x < width(); x++) {
    for (unsigned y = 0; y < height(); y++) {
        cs225::HSLAPixel & pixel = this->getPixel(x, y);
        pixel.s -= 0;
    }
  }
}

void Image::illinify(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          cs225::HSLAPixel & pixel = this->getPixel(x, y);
          if (pixel.h <= 243 && pixel.h >= 114) {
            pixel.h = 216;
          }
          else {
            pixel.h = 11;
      }
    }
  }
}

  void Image::rotateColor(double degrees){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
            cs225::HSLAPixel & pixel = this->getPixel(x, y);
            pixel.h += degrees;
            while(pixel.h > 360){
              pixel.h -= 360;
            }
            while(pixel.h < 0){
              pixel.h += 360;
            }
      }
    }
  }

  void  Image::scale(double factor) {
    Image copy = *this;
    unsigned width = this->width();
    unsigned height = this->height();
    this->resize(factor * this->width(), factor * this->height());
    for (unsigned x = 0; x < this->width(); x++) {
      for (unsigned y = 0; y < this->height(); y++) {
        cs225::HSLAPixel& pixel = this->getPixel(x,y);
        pixel = copy.getPixel(x/factor, y/factor);
      }
    }
  }

void Image::scale (unsigned w, unsigned h){
    double w0 = ((double)(w*1.0)) / ((double)width()*1.0);
    double h0 = ((double)(h*1.0)) / ((double)height()*1.0);
    cout<<w0<<h0<<endl;
    if(w0 < h0){
      scale(w0);
    }
    else{
      scale(h0);
    }
}