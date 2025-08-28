#pragma once
#include "Umfeld.h"
#include "PVector.h"

using namespace umfeld;

/*
  This class represents a cubic Bézier curve.

  getPointAtParameter() method works the same as bezierPoint().

  Points returned from this method are closer to each other
  at places where the curve bends and farther apart where the
  curve runs straight.

  On the orther hand, getPointAtFraction() and getPointAtLength()
  return points at fixed distances. This is useful in many scenarios:
  you may want to move an object along the curve at some speed
  or you may want to draw dashed Bézier curves.
*/


class BezierCurve {

    static constexpr int SEGMENT_NUM = 100;

    PVector v0, v1, v2, v3;

    std::vector<float> arcLengths; // there are n segments between n+1 points //@diff(std::vector)

    float curveLength;

public:

    BezierCurve() : v0(0, 0), v1(0, 0), v2(0, 0), v3(0, 0), curveLength(0) {
        arcLengths.resize(SEGMENT_NUM + 1);
    } //@diff(default_constructor)

    BezierCurve(PVector a, PVector b, PVector c, PVector d) {
        v0 = a.copy(); // curve begins here
        v1 = b.copy();
        v2 = c.copy();
        v3 = d.copy(); // curve ends here

        arcLengths.resize(SEGMENT_NUM + 1); // we will have SEGMENT_NUM segments between SEGMENT_NUM + 1 points

        // The idea here is to make a handy look up table, which contains
        // parameter values with their arc lengths along the curve. Later,
        // when we want a point at some arc length, we can go through our
        // table, pick the place where the point is going to be located and
        // interpolate the value of parameter from two surrounding parameters
        // in our table.

        // we will keep current length along the curve here
        float arcLength = 0;

        PVector prev;
        prev.set(v0);

        // i goes from 0 to SEGMENT_COUNT
        for (int i = 0; i <= SEGMENT_NUM; i++) {

            // map index from range (0, SEGMENT_COUNT) to parameter in range (0.0, 1.0)
            float t = (float) i / SEGMENT_NUM;

            // get point on the curve at this parameter value
            PVector point = pointAtParameter(t);

            // get distance from previous point
            float distanceFromPrev = PVector::dist(prev, point); //@diff(static_method)

            // add arc length of last segment to total length
            arcLength += distanceFromPrev;

            // save current arc length to the look up table
            arcLengths[i] = arcLength;

            // keep this point to compute length of next segment
            prev.set(point);
        }

        // Here we have sum of all segment lengths, which should be
        // very close to the actual length of the curve. The more
        // segments we use, the more accurate it becomes.
        curveLength = arcLength;
    }


    // Returns the length of this curve
    float length() {
        return curveLength;
    }


    // note: this is a temporary solution, it should be implemented
    // inside the umfeld
    float bezierPoint(float a, float b, float c, float d, float t) {
        float t1 = 1.0f - t;
        return (a*t1 + 3*b*t)*t1*t1 + (3*c*t1 + d*t)*t*t;
    }

    // Returns a point along the curve at a specified parameter value.
    PVector pointAtParameter(float t) {
        PVector result;
        result.x       = bezierPoint(v0.x, v1.x, v2.x, v3.x, t);
        result.y       = bezierPoint(v0.y, v1.y, v2.y, v3.y, t);
        result.z       = bezierPoint(v0.z, v1.z, v2.z, v3.z, t);
        return result;
    }


    // Returns a point at a fraction of curve's length.
    // Example: pointAtFraction(0.25) returns point at one quarter of curve's length.
    PVector pointAtFraction(float r) {
        float wantedLength = curveLength * r;
        return pointAtLength(wantedLength);
    }


    // Returns a point at a specified arc length along the curve.
    PVector pointAtLength(float wantedLength) {
        wantedLength = constrain(wantedLength, 0.f, curveLength);

        // look up the length in our look up table
        auto it = std::lower_bound(arcLengths.begin(), arcLengths.end(), wantedLength);
        int nextIndex = std::distance(arcLengths.begin(), it);
        float mappedIndex;

        if (nextIndex == 0) {
            mappedIndex = 0;
        } else if (nextIndex == arcLengths.size()) {
            mappedIndex = SEGMENT_NUM;
        } else {
            int prevIndex = nextIndex - 1;
            float prevLength = arcLengths[prevIndex];
            float nextLength = arcLengths[nextIndex];
            mappedIndex = map(wantedLength, prevLength, nextLength, prevIndex, nextIndex);
        }

        // map index from range (0, SEGMENT_COUNT) to parameter in range (0.0, 1.0)
        float parameter = mappedIndex / SEGMENT_NUM;

        return pointAtParameter(parameter);
    }


    // Returns an array of equidistant point on the curve
    std::vector<PVector> equidistantPoints(int howMany) {

        std::vector<PVector> resultPoints(howMany);

        // we already know the beginning and the end of the curve
        resultPoints[0]           = v0.copy();
        resultPoints[howMany - 1] = v3.copy();

        int arcLengthIndex = 1;
        for (int i = 1; i < howMany - 1; i++) {

            // compute wanted arc length
            float fraction     = (float) i / (howMany - 1);
            float wantedLength = fraction * curveLength;

            // move through the look up table until we find greater length
            while (wantedLength > arcLengths[arcLengthIndex] && arcLengthIndex < arcLengths.size()) {
                arcLengthIndex++;
            }

            // interpolate two surrounding indexes
            int   nextIndex   = arcLengthIndex;
            int   prevIndex   = arcLengthIndex - 1;
            float prevLength  = arcLengths[prevIndex];
            float nextLength  = arcLengths[nextIndex];
            float mappedIndex = map(wantedLength, prevLength, nextLength, prevIndex, nextIndex);

            // map index from range (0, SEGMENT_COUNT) to parameter in range (0.0, 1.0)
            float parameter = mappedIndex / SEGMENT_NUM;

            resultPoints[i] = pointAtParameter(parameter);
        }

        return resultPoints;
    }


    // Returns an array of points on the curve.
    std::vector<PVector> points(int howMany) {

        std::vector<PVector> resultPoints(howMany);

        // we already know the first and the last point of the curve
        resultPoints[0]           = v0.copy();
        resultPoints[howMany - 1] = v3.copy();

        for (int i = 1; i < howMany - 1; i++) {

            // map index to parameter in range (0.0, 1.0)
            float parameter = (float) i / (howMany - 1);

            resultPoints[i] = pointAtParameter(parameter);
        }

        return resultPoints;
    }
};
