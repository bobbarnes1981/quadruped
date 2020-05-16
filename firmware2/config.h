#ifndef H_CONFIG
#define H_CONFIG

#define LENGTH_FEMUR 59.0
#define LENGTH_TIBIA 122.0

// Rear Left

#define RR_L_DIR_X -1
#define RR_L_DIR_Y -1

#define RR_L_HIP_SERVO 9
#define RR_L_HIP_OFFSET -45
#define RR_L_HIP_DIRECTION 1
#define RR_L_HIP_MIN_PULSE 1000
#define RR_L_HIP_MAX_PULSE 1950
#define RR_L_HIP_MIN_ANGLE -45
#define RR_L_HIP_MAX_ANGLE 45

#define RR_L_THIGH_SERVO 10
#define RR_L_THIGH_OFFSET 0
#define RR_L_THIGH_DIRECTION 1
#define RR_L_THIGH_MIN_PULSE 1100
#define RR_L_THIGH_MAX_PULSE 2450
#define RR_L_THIGH_MIN_ANGLE -38
#define RR_L_THIGH_MAX_ANGLE 90

#define RR_L_KNEE_SERVO 11
#define RR_L_KNEE_OFFSET 90
#define RR_L_KNEE_DIRECTION -1
#define RR_L_KNEE_MIN_PULSE 700
#define RR_L_KNEE_MAX_PULSE 2050
#define RR_L_KNEE_MIN_ANGLE -90
#define RR_L_KNEE_MAX_ANGLE 38

// Rear Right

#define RR_R_DIR_X 1
#define RR_R_DIR_Y -1

#define RR_R_HIP_SERVO 6
#define RR_R_HIP_OFFSET 45
#define RR_R_HIP_DIRECTION -1
#define RR_R_HIP_MIN_PULSE 1100
#define RR_R_HIP_MAX_PULSE 2050
#define RR_R_HIP_MIN_ANGLE -45
#define RR_R_HIP_MAX_ANGLE 45

#define RR_R_THIGH_SERVO 7
#define RR_R_THIGH_OFFSET 0
#define RR_R_THIGH_DIRECTION -1
#define RR_R_THIGH_MIN_PULSE 600
#define RR_R_THIGH_MAX_PULSE 1950
#define RR_R_THIGH_MIN_ANGLE -90
#define RR_R_THIGH_MAX_ANGLE 38

#define RR_R_KNEE_SERVO 8
#define RR_R_KNEE_OFFSET -90
#define RR_R_KNEE_DIRECTION 1
#define RR_R_KNEE_MIN_PULSE 1000
#define RR_R_KNEE_MAX_PULSE 2350
#define RR_R_KNEE_MIN_ANGLE -38
#define RR_R_KNEE_MAX_ANGLE 90

// Front Right

#define FT_R_DIR_X 1
#define FT_R_DIR_Y 1

#define FT_R_HIP_SERVO 3
#define FT_R_HIP_OFFSET -45
#define FT_R_HIP_DIRECTION 1
#define FT_R_HIP_MIN_PULSE 1050
#define FT_R_HIP_MAX_PULSE 1950
#define FT_R_HIP_MIN_ANGLE -45
#define FT_R_HIP_MAX_ANGLE 45

#define FT_R_THIGH_SERVO 4
#define FT_R_THIGH_OFFSET 0
#define FT_R_THIGH_DIRECTION 1
#define FT_R_THIGH_MIN_PULSE 1050
#define FT_R_THIGH_MAX_PULSE 2400
#define FT_R_THIGH_MIN_ANGLE -38
#define FT_R_THIGH_MAX_ANGLE 90

#define FT_R_KNEE_SERVO 5
#define FT_R_KNEE_OFFSET 90
#define FT_R_KNEE_DIRECTION -1
#define FT_R_KNEE_MIN_PULSE 800
#define FT_R_KNEE_MAX_PULSE 2150
#define FT_R_KNEE_MIN_ANGLE -90
#define FT_R_KNEE_MAX_ANGLE 38

// Front Left

#define FT_L_DIR_X -1
#define FT_L_DIR_Y 1

#define FT_L_HIP_SERVO 0
#define FT_L_HIP_OFFSET 45
#define FT_L_HIP_DIRECTION -1
#define FT_L_HIP_MIN_PULSE 1100
#define FT_L_HIP_MAX_PULSE 2000
#define FT_L_HIP_MIN_ANGLE -45
#define FT_L_HIP_MAX_ANGLE 45

#define FT_L_THIGH_SERVO 1
#define FT_L_THIGH_OFFSET 0
#define FT_L_THIGH_DIRECTION -1
#define FT_L_THIGH_MIN_PULSE 650
#define FT_L_THIGH_MAX_PULSE 1950
#define FT_L_THIGH_MIN_ANGLE -90
#define FT_L_THIGH_MAX_ANGLE 38

#define FT_L_KNEE_SERVO 2
#define FT_L_KNEE_OFFSET -90
#define FT_L_KNEE_DIRECTION 1
#define FT_L_KNEE_MIN_PULSE 1000
#define FT_L_KNEE_MAX_PULSE 2350
#define FT_L_KNEE_MIN_ANGLE -38
#define FT_L_KNEE_MAX_ANGLE 90

// walking

#define WALK_X 80
#define WALK_STEP_F 10
#define WALK_STEP_B 100
#define WALK_FLOOR -70
#define WALK_HEIGHT 40

#endif
