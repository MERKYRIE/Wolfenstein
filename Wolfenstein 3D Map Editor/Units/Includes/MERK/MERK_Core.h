#ifndef MERK_Core
#define MERK_Core

class CLASS_Core
{
 public:
  void Assign();
  void Load();
  void Init();
  void Destroy();
  void FillScreen();
  void FlipBuffer();
  void DrawMap();
  void DrawCursor();
  void DrawBorder();
  void OutInfo();
  void Draw();
  void UpdateState();
  int CheckEscape();
  void CheckSpace();
  void CheckTab();
  void CheckAlt();
  void CheckF1();
  void FillBase(unsigned char Num,int XCnt,int YCnt);
  void FillUp(unsigned char Num,int XCnt,int YCnt);
  void FillUpLeft(unsigned char Num,int XCnt,int YCnt);
  void FillLeft(unsigned char Num,int XCnt,int YCnt);
  void FillDownLeft(unsigned char Num,int XCnt,int YCnt);
  void FillDown(unsigned char Num,int XCnt,int YCnt);
  void FillDownRight(unsigned char Num,int XCnt,int YCnt);
  void FillRight(unsigned char Num,int XCnt,int YCnt);
  void FillUpRight(unsigned char Num,int XCnt,int YCnt);
  void FillBar(unsigned char Num);
  void FillMech();
  void CheckF2();
  void CheckUp();
  void CheckLeft();
  void CheckDown();
  void CheckRight();
  void CheckW();
  void CheckA();
  void CheckS();
  void CheckD();
  int DetectKey();
};

extern CLASS_Core Core;

#endif

















































