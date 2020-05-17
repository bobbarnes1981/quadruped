#include "RobotLeg.h"

// 645mg 0.20 sec/60°
// 422   0.16 sec/60°

RobotLeg::RobotLeg(double lengthFemur, double lengthTibia, double dirX, double dirY, RobotServo *hip, RobotServo *thigh, RobotServo *knee) {
  this->lengthFemur = lengthFemur;
  this->lengthTibia = lengthTibia;
  this->dirX = dirX;
  this->dirY = dirY;
  this->hip = hip;
  this->thigh = thigh;
  this->knee = knee;
}

// move the foot to the specified position immediately
// target x=l/r y=f/b z=u/d
void RobotLeg::moveLeg(double x, double y, double z) {
  this->setPosition(
    (x * this->dirX),
    (y * this->dirY),
    z
  ); 
}
void RobotLeg::moveLegRel(double x, double y, double z) {
  this->setPosition(
    this->currentX + (x * this->dirX),
    this->currentY + (y * this->dirY),
    this->currentZ + z
  ); 
}

void RobotLeg::setPosition(double x, double y, double z) {
  this->currentX = x;
  this->currentY = y;
  this->currentZ = z;
  this->solve3DOF(
    this->currentX + this->offsetX,
    this->currentY + this->offsetY,
    this->currentZ + this->offsetZ
  ); 
}

void RobotLeg::setOffset(double x, double y, double z) {
  this->offsetX = x;
  this->offsetY = y;
  this->offsetZ = z;
}

void RobotLeg::solve3DOF(double tx, double ty, double tz) {
  double hipAngle = radToDeg(atan(ty / tx));
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

  if (isnan(S)) {
    return;
  }

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

  double thighAngle = ac_angle + A;
  this->thigh->angle(thighAngle);

  double kneeAngle = B;
  this->knee->angle(kneeAngle);
}

// convert radians to degrees
double RobotLeg::radToDeg(double rad) {
  return rad * (180 / PI);
}
