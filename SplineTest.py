import matplotlib.pyplot as mpl
import math

# https://gist.github.com/svdamani/1015c5c4b673c3297309

points = [
    (0, 0),
    # (0.01, 1),
    (0.3, 4),
    (0.5, 5),
    (0.7, 6),
    # (0.99, 9),
    (1, 10)
]

def spline(coords):
    n = len(coords) - 1
    h = []
    for i in range(0, n):
        h.append(coords[i+1][0] - coords[i][0])
    
    A = [0.]
    for i in range(1, n):
        calculated = 3. * (coords[i+1][1] - coords[i][1]) / h[i] - 3. * (coords[i][1] - coords[i-1][1]) / h[i-1]
        A.append(calculated)

    l = [1.]
    u = [0.]
    z = [0.]

    for i in range(1, n):
        l.append(2. * (coords[i+1][0] - coords[i-1][0]) - h[i-1] * u[i-1])
        u.append(h[i] / l[i])
        z.append((A[i] - h[i-1] * z[i-1]) / l[i])

    l.append(1.)
    z.append(0.)
    c = [0.] * (n+1)
    b = [0.] * (n+1)
    d = [0.] * (n+1)

    for i in reversed(range(0, n)):
        c[i] = z[i] - u[i] * c[i+1]
        b[i] = (coords[i+1][1] - coords[i][1]) / h[i] - h[i] * (c[i+1] + 2 * c[i]) / 3.
        d[i] = (c[i+1] - c[i]) / (3. * h[i])

    splines = []
    for i in range(0, n):
        polynomial = (coords[i][1], b[i], c[i], d[i])
        splines.append(polynomial)

    return splines

def value(spline, param):
    (a, b, c, d) = spline
    return a + (b * param) + (c * param * param) + (d * param * param * param)

def derivative(spline, param):
    (_, b, c, d) = spline
    return b + (2 * c * param) + (3 * d * param * param)

def heading(spline, param):
    return math.atan(derivative(spline, param))

def dHeading(spline, param):
    (_, _, c, d) = spline
    slope = derivative(spline, param)
    return ((2 * c) + (6 * d * param)) / (slope * slope + 1)

def maxVelocity(spline, param):
    # max linear velocity will be a function of the
    # physical robot constraints and the angular velocity
    angularVel = dHeading(spline, param) #radians per second
    maxWheelVelocity = 5 #feet per second
    wheelWidth = 1 #feet
    requiredSpeedDifferential = abs(wheelWidth * angularVel) #radians/second * feet = feet / second
    return maxWheelVelocity - (requiredSpeedDifferential / 2)
    
def rectify(splines, points, resolution):
    t = 0
    splineIndex = 0
    pointIndex = 0
    distanceTraveled = 0
    values = []
    while(t < points[-1][0]):
        spline = splines[splineIndex]
        param = t - points[pointIndex][0]

        slope = derivative(spline, param) * resolution
        distanceStep = math.sqrt(resolution * resolution + slope * slope)

        # TODO: Calculate this better
        # linearVel = distanceStep / 0.1

        position = value(spline, param)
        angle = heading(spline, param)
        angleVel = dHeading(spline, param)
        maxVel = maxVelocity(spline, param)

        values.append((position, angle, angleVel, distanceTraveled))
        distanceTraveled += distanceStep
        t += resolution
        if t >= points[pointIndex+1][0]:
            splineIndex += 1
            pointIndex += 1

    return values

splines = spline(points)
print(splines)
rectified = rectify(splines, points, 0.01)

mpl.plot(rectified)
mpl.legend(["position", "heading", "angular velocity", "Total distance traveled"])
mpl.show()