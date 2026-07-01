#include <MERK/MERK_User.h>

void CLASS_User::Assign(int MovSpd,int Height,int Block)
{
 CLASS_User::X=0;
 CLASS_User::Y=0;
 CLASS_User::MaxBl=Height/Block-1;
 CLASS_User::MaxPx=Height/Block*Block;
 CLASS_User::MovSpd=MovSpd;
}

//eof

















































