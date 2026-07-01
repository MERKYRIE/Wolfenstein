#ifndef MERK_Core
#define MERK_Core

#include <MERK/MERK_Graph.h>
#include <MERK/MERK_Audio.h>

class CLASS_Core
{
 public:
  CLASS_Graph::TYPE_Atlas HUD,Faces,Tools,Numbers,Hands,Walls,Mechs,Objects; 
  CLASS_Audio::TYPE_Music E1M1; 
  CLASS_Audio::CLASS_Sound Step[4],Select,Fist,Werewolf[5];
  void Bind();
  void Load();
  void Init();
  void Unload();
  void Unbind();
  void Destroy();
  void FillScreen();
  void FlipBuffer();
  void Reset();
  void Prepaire();
  void CheckVerError();
  void PrepaireVerVar();
  void MakeVerStep();
  void SaveObjInfo(int X,int Y,int HitNum,int CellCnt);
  void FindObjXYOffs(double &XOffs,double &YOffs,int CellCnt);
  void FindObjAbsXYOffs(double XOffs,double YOffs,double &AbsXOffs,double &AbsYOffs);
  void FindObjMinMaxOffs(double AbsXOffs,double AbsYOffs,double &MinOffs,double &MaxOffs);
  void FindObjDist(double AbsXOffs,double AbsYOffs,int CellCnt);
  void FindObjDistAngle(double XOffs,double YOffs,double AbsXOffs,double AbsYOffs,double MaxOffs,double &DistAngle);
  void FindObjOffsAngle(double DistAngle,double &OffsAngle);
  void FindObjOffs(double OffsAngle,double &Offs);
  void FindObjSrc(int CellCnt);
  void FindObjDst(double Offs,int CellCnt);
  void AddObj(int X,int Y,int HitNum);
  void FindVerInt();
  void FindVerDist();
  void FindVerOffs();
  void FindVerHitNum();
  void CheckHorError();
  void PrepaireHorVar();
  void MakeHorStep();
  void FindHorInt();
  void FindHorDist();
  void FindHorOffs();
  void FindHorHitNum();
  void Compare();
  void FindDirDist();
  void CorrectDirDist();
  void FindSrc();
  void FindDst();
  void Out();
  void SortObjByDist(int CellCnt);
  void CutObjByDist(int CellCnt);
  void OutObj();
  void Postpaire();
  void Raycasting();
  void DrawHUD();
  void DrawTool();
  void OutHealth();
  void DrawFace();
  void DrawHand();
  void Draw();
  void UpdatePovSide();
  void UpdateKeyState();
  int CheckEscape();
  void CheckW();
  void CheckA();
  void CheckS();
  void CheckD();
  void Check1();
  void Check2();
  void CheckSpace();
  void UpdateMouseState();
  void CheckMouseX();
  void CheckMouseLeft();
  int DetectKey();
};

extern CLASS_Core Core;

#endif

















































