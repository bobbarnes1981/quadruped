#include "RobotLeg.h"

// TODO: allow commands to move leg to specified xyz

RobotLeg::RobotLeg(double lengthFemur, double lengthTibia, RobotServo *hip, RobotServo *thigh, RobotServo *knee) {
  this->lengthFemur = lengthFemur;
  this->lengthTibia = lengthTibia;
  this->hip = hip;
  this->thigh = thigh;
  this->knee = knee;
}

RobotLeg::~RobotLeg() {
  
}

// target x-side y-forward z-up
void RobotLeg::setPosition(double x, double y, double z) {
  this->solve3DOF(x, y, z); 
}

void RobotLeg::solve3DOF(double tx, double ty, double tz) {
  Serial.print("hip angle: ");
  double hipAngle = radToDeg(atan(ty / tx));
  Serial.println(hipAngle);
  this->hip->angle(hipAngle);
  double AT = sqrt(pow(tx, 2) + pow(ty, 2));
  solve2DOF(AT, tz);
}

void RobotLeg::solve2DOF(double tx, double ty) {
  double cx = tx;
  double cy = ty;

  double AC = sqrt(pow(cx, 2) + pow(cy, 2));
  double ac_angle = radToDeg(atan(cy / cx));

  //s=(AB+BC+AC)/2
  double s = (this->lengthFemur + this->lengthTibia + AC) / 2;

  //S=sqr(s*(s-AB)(s-BC)(s-AC))
  double S = sqrt(s * (s - this->lengthFemur) * (s - this->lengthTibia) * (s - AC));

  //A=asin(2S/(AB*AC))
  double A = radToDeg(asin((2 * S) / (this->lengthFemur * AC)));

  //B=asin(2S/(AB*BC))
  double B = radToDeg(asin((2 * S) / (this->lengthFemur * this->lengthTibia)));

  // Check if Hypoteneuse (AC) is big enough to mean triangle is obtuse
  // as rule of sines doesn't work on obtuse angles, could use rule of
  // cosines
  if (AC > sqrt(pow(this->lengthFemur, 2) + pow(this->lengthTibia, 2))) {
    B = 180 - B;
  }

  Serial.print("thigh angle: ");
  double thighAngle = ac_angle + A; // FIXME: offset ac_angle+A correct for RL
  Serial.println(thighAngle);
  this->thigh->angle(thighAngle);

  Serial.print("knee angle: ");
  double kneeAngle = 90 - B; // FIXME: offset 90-B correct for RL
  Serial.println(kneeAngle);
  this->knee->angle(kneeAngle);
}

double RobotLeg::radToDeg(double rad) {
  return rad * (180 / PI);
}
