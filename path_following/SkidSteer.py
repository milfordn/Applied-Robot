import math

ACCEL_LIMIT = 0.5 #meters/second^2
VEL_LIMIT = 1 #meters/second
BASE_WIDTH = 0.3 #meters

# https://www.mdpi.com/1424-8220/15/5/9681/pdf
# state vector:
# (x, y, theta, vl, vr)

def getInitialState():
    return (0, 0, math.pi / 2, 0, 0)

def step(st, vl, vr, dt):
    (x, y, th, vl_prev, vr_prev) = st
    dvel_actual = ACCEL_LIMIT * dt
    vl = max(-VEL_LIMIT, vl_prev - dvel_actual, vl)
    vl = min(VEL_LIMIT, vl_prev + dvel_actual, vl)

    vr = max(-VEL_LIMIT, vr_prev - dvel_actual, vr)
    vr = min(VEL_LIMIT, vr_prev + dvel_actual, vr)

    v = (vl + vr) / 2
    w = (vr - vl) / BASE_WIDTH

    thNew = th + w * dt
    thAvg = (th + thNew) / 2
    xNew = x + v * math.cos(thAvg) * dt
    yNew = y + v * math.sin(thAvg) * dt

    return (xNew, yNew, thNew, vl, vr)