#include <string>
#include <iostream>
#include "Image.h"
#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

StickerSheet::~StickerSheet() {
    v.clear();
    xc.clear();
    yc.clear();
}
StickerSheet::StickerSheet (const Image &picture, unsigned max){
    max_ = max;
    base = picture;
    v.resize(max_);
    xc.resize(max_);
    yc.resize(max_);
}

StickerSheet::StickerSheet (const StickerSheet &other){
    max_ = other.max_;
    base = other.base;
    v = other.v;
    xc = other.xc;
    yc = other.yc;
}
const StickerSheet& StickerSheet::operator=(const StickerSheet& other){
    this->max_=other.max_;
    this->base=other.base;
    this->v = other.v;
    this->xc = other.xc;
    this->yc = other.yc;
    return *this;
}

void StickerSheet::changeMaxStickers(unsigned max){
    if(max > max_){
        v.resize(max);
        xc.resize(max);
        yc.resize(max);
        max_ = max;
    }
    else if(max == max_){
        return;
    }
    else{
        max_ = max;
        v.resize(max);
        xc.resize(max);
        yc.resize(max);
    }
}
int StickerSheet::addSticker(Image &sticker, int x, int y){
    for (unsigned i = 0; i < v.size(); i++) {
        if (v.at(i) == nullptr) {
            v[i] = &sticker;
            xc[i] = x;
            yc[i] = y;
            return i;
        }
    }
    max_ += 1;
    v.resize(max_);
    xc.resize(max_);
    yc.resize(max_);
    v.push_back(&sticker);
    xc.push_back(x);
    yc.push_back(y);
    return max_-1;
}
int StickerSheet::setStickerAtLayer(Image &sticker, unsigned layer, int x, int y){
    if (layer >= max_ || layer < 0){
        return -1;
    }
    else{
        v[layer] = &sticker;
        xc[layer] = x;
        yc[layer] = y;
        return layer;
    }
}
bool StickerSheet::translate (unsigned index, int x, int y){
    if(index > max_ || index < 0 || v.at(index) == nullptr){
        return false;
    }
    else{
        xc[index] = x;
        yc[index] = y;
        return true;
    }
}
void StickerSheet::removeSticker (unsigned index){
    if (index >= max_ || index < 0 || v.at(index) == nullptr){
        return;
    }
    v[index] = nullptr;
}
Image* StickerSheet::getSticker (unsigned index){
    if (v.at(index) == nullptr || index >= max_ || index < 0){
        return nullptr;
    }
    return v[index];
}
int StickerSheet::layers() const{
    return max_;
}
Image StickerSheet::render() const{
    unsigned maxx = base.width();
    unsigned maxy = base.height();
    int minx = 0;
    int miny = 0;
    for(unsigned i = 0; i < v.size(); i++){
        if(v.at(i) == nullptr){
            continue;
        }
        else{
            if(xc[i]+(int)v[i]->width() > (int)maxx){
                maxx = xc[i]+v[i]->width();
            }

            if(yc[i]+(int)v[i]->height() > (int)maxy){
                maxy = (yc[i]+v[i]->height());
            }

            if(xc[i] < minx){
                minx = xc[i];
            }

            if(yc[i] < miny){
                miny = yc[i];
            }
        }
    }

    Image rendered(0,0);
    rendered.resize(maxx - minx, maxy - miny);


    for(unsigned int x = 0; x < base.width(); x++){
        for(unsigned int y = 0; y < base.height(); y++){
            cs225::HSLAPixel & renderpixel = rendered.getPixel(x-minx,y-miny);
            cs225::HSLAPixel pixel = base.getPixel(x,y);
            renderpixel = pixel;
        }
    }

    for(unsigned int i = 0; i < v.size(); i++){
        if(v.at(i) != nullptr){
            for(unsigned int a = 0; a < v[i]->width(); a++){
                for(unsigned int b = 0; b < v[i]->height(); b++){
                    cs225::HSLAPixel temp = v[i]->getPixel(a,b);
                    if (temp.a == 0) {
                        continue;
                    }
                    cs225::HSLAPixel & stickerpixel = rendered.getPixel(xc[i]+a-minx,yc[i]+b-miny);
                    stickerpixel = temp;
                }
            }
        }
    }

    return rendered;
}