#ifndef KINEMATICS_H
#define KINEMATICS_H


// --------- CINEMATICA INVERSA (usado para ativar os motores) --------------------------------
float getLeftWheelRPM(float robotLinearSpeed, float robotAngularSpeed, const float wheelRadius, const float wheelsAxisLength)
{
  
}

float getRightWheelRPM(float robotLinearSpeed, float robotAngularSpeed, const float wheelRadius, const float wheelsAxisLength)
{
 // Giro em rad/s
 float radPerS = (robotAngularSpeed * wheelsAxisLength / (2*wheelRadius)) + (robotLinearSpeed/wheelRadius);

 // Giro em rps (rotacao por segundo)
 float rps = radPerS/ (2 * PI);

 // Giro em rpm
 float rpm = rps * 60.0;

 return rpm;
}
// --------------------------------------------------------------------------------------------

// --------- CINEMATICA DIRETA (usado pra estimar a velocidade do robô) -----------------------
float getLinearSpeed(float leftWheelSpeed, float rightWheelSpeed, const float wheelRadius, const float wheelsAxisLength)
{
  
}

float getAngularSpeed(float leftWheelSpeed, float rightWheelSpeed, const float wheelRadius, const float wheelsAxisLength)
{
  
}
// --------------------------------------------------------------------------------------------

#endif