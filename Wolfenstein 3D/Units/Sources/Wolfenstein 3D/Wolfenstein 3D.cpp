#include <MERK/MERK_Core.h>

int main(int argc, char* argv[])
{
 Core.Init();
 while (!Core.DetectKey())
 {
  Core.FillScreen();
  Core.Draw();
  Core.FlipBuffer();
 }
 Core.Destroy();
 return 0;
}

















































