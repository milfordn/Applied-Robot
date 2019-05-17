from Spline import getLearningParameters

def getControl(learningParameters, vehicleState):
    heading = learningParameters[0][1]
    (_, _, theta, _, _) = vehicleState
    thErr = theta - heading
    thErr *= 0.01
    c = 0.5
    return c + thErr, c - thErr