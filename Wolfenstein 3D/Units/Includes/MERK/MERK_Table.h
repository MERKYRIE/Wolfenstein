#ifndef MERK_Table
#define MERK_Table

class CLASS_Table
{
 public:
  typedef std::vector <double> TYPE_Table;
  TYPE_Table Sin,Cos,Tan;
  double ExtAngle;
  void Assign(double MinAngle,double MaxAngle);
  double GetSin(double Angle);
  double GetCos(double Angle);
  double GetTan(double Angle);
};

#endif

















































