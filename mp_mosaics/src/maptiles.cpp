/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas *canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> points;
    map<Point<3>, int> maps;
    for(size_t i = 0; i < theTiles.size(); i++){
        points.push_back(convertToXYZ(theTiles[i].getAverageColor()));
        maps[points[i]] = i;
    }
    KDTree<3> mosaicTree(points);
    for(int i = 0; i < canvas -> getRows(); i++){
        for(int j = 0; j < canvas -> getColumns(); j++){
            canvas -> setTile(i, j, &theTiles[maps[mosaicTree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i, j)))]]);
        }
    }
    return canvas;
}