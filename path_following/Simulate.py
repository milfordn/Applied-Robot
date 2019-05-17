import SkidSteer
import Spline
import Controller

def simulate(spline, points, dt=0.01):
    print("Simulating...")
    vState = SkidSteer.getInitialState()
    posns = []
    xBound = points[-1][0]
    yBound = points[-1][1] * 1.1
    i = 0

    while(vState[0] < xBound and vState[1] < yBound and vState[0] >= 0 and vState[1] >= 0):
        (x, y, _, _, _) = vState
        lps = Spline.getLearningParameters(spline, points, (x, y))
        (l, r) = Controller.getControl(lps, vState)
        vState = SkidSteer.step(vState, l, r, dt)
        posns.append((vState[0], vState[1]))

        i += 1
        if True or i % 1000 == 0:
            print(vState)

    print("Done Simulating")

    return posns