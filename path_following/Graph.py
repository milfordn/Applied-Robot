import matplotlib.pyplot as mpl
import Spline
import SkidSteer
import Simulate

points = [
    (0, 0),
    (0.3, 4),
    (0.5, 5),
    (1, 10)
]

splines = Spline.makeSpline(points)
print(splines)
rectified = Spline.rectify(splines, points, 0.01)
posns = Simulate.simulate(splines, points)

(xs, ys) = zip(*posns)
(yPath, _, _, _) = zip(*rectified)
xPath = list(map(lambda x: x * (points[-1][0] / len(yPath)), range(0, len(yPath))))

print(list(zip(xs, ys)))

mpl.plot(xPath, yPath)
mpl.plot(xs, ys)
mpl.legend(["Path To Follow", "Attempted Following"])
mpl.show()