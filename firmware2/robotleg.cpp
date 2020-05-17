#include "robotleg.h"

RobotLeg::RobotLeg(double lengthFemur, double lengthTibia, double dirX, double dirY, RobotServo *hip, RobotServo *thigh, RobotServo *knee) {
  this->lengthFemur = lengthFemur;
  this->lengthTibia = lengthTibia;
  this->dirX = dirX;
  this->dirY = dirY;
  this->hip = hip;
  this->thigh = thigh;
  this->knee = knee;
}

void RobotLeg::moveLegAbs(int x, int y, int z, int uss) {
  this->currentX = (x * this->dirX);
  this->currentY = (y * this->dirY);
  this->currentZ = z;
  this->solve3DOF(
    this->currentX + this->offsetX,
    this->currentY + this->offsetY,
    this->currentZ + this->offsetZ,
    uss
  );
}

void RobotLeg::moveLegRel(int x, int y, int z, int uss) {
  this->currentX = this->currentX + (x * this->dirX);
  this->currentY = this->currentY + (y * this->dirY);
  this->currentZ = this->currentZ + z;
  this->solve3DOF(
    this->currentX + this->offsetX,
    this->currentY + this->offsetY,
    this->currentZ + this->offsetZ,
    uss
  );
}

void RobotLeg::solve3DOF(double tx, double ty, double tz, int uss) {
//  Serial.println();
//  Serial.println("solving");
//  Serial.print("x ");
//  Serial.println(tx);
//  Serial.print("y ");
//  Serial.println(ty);
//  Serial.print("z ");
//  Serial.println(tz);
//  Serial.println();
  
  double hipAngle = radToDeg(atan(ty / tx));
  
  this->hip->angle(hipAngle, uss);
  double AT = sqrt(pow(tx, 2) + pow(ty, 2));
  solve2DOF(AT, tz, uss);
}

void RobotLeg::solve2DOF(double tx, double ty, int uss) {
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
//  if (AC > sqrt(pow(this->lengthFemur, 2) + pow(this->lengthTibia, 2))) {
  // check if any angle is greater than 90
  if (B > 90 || (ac_angle+A) > 90 || (180-(B+ac_angle+A)) > 90 ) {
    B = 180 - B;
  }
  
  double thighAngle = ac_angle + A;
  this->thigh->angle(thighAngle, uss);

  double kneeAngle = B;
  this->knee->angle(kneeAngle, uss);
}

// convert radians to degrees
double RobotLeg::radToDeg(double rad) {
  return rad * (180 / PI);
}
