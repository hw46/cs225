#include "Image.h"
#include "StickerSheet.h"

using namespace std;

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  
  Image base;
  base.readFromFile("../data/base.png");
  Image i1;
  i1.readFromFile("../data/1.png");
  Image i2;
  i2.readFromFile("../data/2.png");
  Image i3;
  i3.readFromFile("../data/3.png");

  base.scale(5);
  i1.scale(0.9);
  i2.scale(0.993);
  i3.scale(0.875);

  StickerSheet* sheet = new StickerSheet(base, 3);
  sheet->addSticker(i1, 0, 1730);
  sheet->addSticker(i2, 620, 1730);
  sheet->addSticker(i3, 1559, 1685);
  Image result = sheet->render();
  result.writeToFile("myImage.png");

  delete &base;
  delete &i1;
  delete &i2;
  delete &i3;
  delete &result;
  delete sheet;

  return 0;
}