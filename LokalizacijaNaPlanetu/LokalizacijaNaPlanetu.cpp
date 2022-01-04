// LokalizacijaNaPlanetu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <random>



struct Point2D
{
    int x, y;
};

struct lineSegment
{
    Point2D point1, point2;
};

bool lineSegmentsIntersects(lineSegment d1, lineSegment d2, Point2D* IntersectionPoint);

int main()
{
    std::vector<std::vector<Point2D>> Area;
    std::vector<int> foundRobot;

    int minX = 10000;
    int minY = 10000;
    int ray_StartOffset = -10;
    Point2D ray_StartPoint = { 0, 0 };
    Point2D robot_ActualPosition = { 10, 10 };
    Point2D intersectionPoint = { 0, 0 };

    std::cout << "Greetings traveler!\n";

    Point2D point;
    // Area 1
    Area.push_back(std::vector<Point2D>());
    point = { 0, 15 };
    Area[0].push_back(point);
    point = { 30, 15 };
    Area[0].push_back(point);
    point = { 30, 45 };
    Area[0].push_back(point);
    point = { 0, 70 };
    Area[0].push_back(point);
    // Area 2
    Area.push_back(std::vector<Point2D>());
    point = { 0, 0 };
    Area[1].push_back(point);
    point = { 45, 0 };
    Area[1].push_back(point);
    point = { 30, 15 };
    Area[1].push_back(point);
    point = { 0, 15 };
    Area[1].push_back(point);
    // Area 3
    Area.push_back(std::vector<Point2D>());
    point = { 30, 15 };
    Area[2].push_back(point);
    point = { 45, 0 };
    Area[2].push_back(point);
    point = { 75, 55 };
    Area[2].push_back(point);
    point = { 30, 45 };
    Area[2].push_back(point);
    // Area 4
    Area.push_back(std::vector<Point2D>());
    point = { 0, 70 };
    Area[3].push_back(point);
    point = { 30, 45 };
    Area[3].push_back(point);
    point = { 75, 55 };
    Area[3].push_back(point);
    point = { 75, 70 };
    Area[3].push_back(point);
    // Area 5
    Area.push_back(std::vector<Point2D>());
    point = { 75, 55 };
    Area[4].push_back(point);
    point = { 100, 0 };
    Area[4].push_back(point);
    point = { 100, 70 };
    Area[4].push_back(point);
    point = { 75, 70 };
    Area[4].push_back(point);
    // Area 6
    Area.push_back(std::vector<Point2D>());
    point = { 45, 0 };
    Area[5].push_back(point);
    point = { 100, 0 };
    Area[5].push_back(point);
    point = { 75, 55 };
    Area[5].push_back(point);

    // find min x and min y to define ray source
    // also construct foundRobot vector

    for (int i = 0; i < Area.size(); i++)
    {
        for (int j = 0; j < Area[i].size(); j++)
        {
            if (Area[i][j].x < minX)
            {
                minX = Area[i][j].x;
            }
            if (Area[i][j].y < minY)
            {
                minY = Area[i][j].y;
            }
        }
        foundRobot.push_back(0);
    }

    /*
    std::cout << "\nminx: " << minX;
    std::cout << "\nminy: " << minY;
    */
    ray_StartPoint = { minX + ray_StartOffset, minY + ray_StartOffset };

    /*
    std::cout << "Robot X position: ";
    std::cin >> robot_ActualPosition.x;
    std::cout << "Robot Y position: ";
    std::cin >> robot_ActualPosition.y;
    */

    int atempts = 0;
    bool foundInAllAreas = false;
    while (!foundInAllAreas)
    {

        std::vector<std::vector<Point2D>> Area_IntersectionPoints;

        atempts += 1;

        // randomize robot position
        std::random_device rng_dev;
        std::mt19937 rng(rng_dev());
        std::uniform_int_distribution<std::mt19937::result_type> range100(0, 100);
        std::uniform_int_distribution<std::mt19937::result_type> range70(0, 70);

        robot_ActualPosition.x = range100(rng);
        robot_ActualPosition.y = range70(rng);

        lineSegment ray_LineSegment = { ray_StartPoint, robot_ActualPosition };
        lineSegment areaEdge = { point, point };

        std::cout << "\nRobots actual position: { " << robot_ActualPosition.x << ", " << robot_ActualPosition.y << " }\n";

        for (int i = 0; i < Area.size(); i++)
        {
            Area_IntersectionPoints.push_back(std::vector<Point2D>());
            for (int j = 0; j < Area[i].size(); j++)
            {
                (j < Area[i].size() - 1) ? areaEdge = { Area[i][j], Area[i][j + 1] } : areaEdge = { Area[i][j], Area[i][0] };
                if (lineSegmentsIntersects(ray_LineSegment, areaEdge, &intersectionPoint))
                {
                    if (Area_IntersectionPoints[i].size() > 0)
                    {
                        int Area_IntersectionPoints_Size = Area_IntersectionPoints[i].size();
                        for (int k = 0; k < Area_IntersectionPoints_Size; k++)
                        {
                            if ((intersectionPoint.x == Area_IntersectionPoints[i][k].x) && (intersectionPoint.y == Area_IntersectionPoints[i][k].y))
                            {
                                /*
                                std::cout << "\nPoint already exists!";
                                std::cout << "\nIntersection point: { " << intersectionPoint.x << ", " << intersectionPoint.y << " }";
                                */
                                break;
                            }
                            else
                            {
                                Area_IntersectionPoints[i].push_back(intersectionPoint);
                                /*
                                std::cout << "\nRay intersects with area edge { Area" << i + 1 << ".point" << j << ", Area" << i + 1 << ".point" << j + 1 << " }";
                                std::cout << "\nIntersection point: { " << intersectionPoint.x << ", " << intersectionPoint.y << " }";
                                */
                            }
                        }
                    }
                    else
                    {
                        Area_IntersectionPoints[i].push_back(intersectionPoint);
                        /*
                        std::cout << "\nRay intersects with area edge { Area" << i + 1 << ".point" << j << ", Area" << i + 1 << ".point" << j + 1 << " }";
                        std::cout << "\nIntersection point: { " << intersectionPoint.x << ", " << intersectionPoint.y << " }";
                        */
                    }
                }
            }
        }

        for (int i = 0; i < Area_IntersectionPoints.size(); i++)
        {
            int Area_IntersectionPoints_Size = Area_IntersectionPoints[i].size();
            if (Area_IntersectionPoints_Size > 0)
            {
                if (Area_IntersectionPoints_Size % 2 != 0)
                {
                    std::cout << "Robot is in area O" << i + 1 << "!\n";
                    foundRobot[i] += 1;
                }
            }
        }

        foundInAllAreas = true;
        for (int i = 0; i < foundRobot.size(); i++)
        {
            foundInAllAreas &= (foundRobot[i] > 0);
            std::cout << "found robot in O" << i + 1 << ": " << foundRobot[i] << "x\n";
            //std::cout << "found in all areas: " << foundInAllAreas << "\n";
        }
    }

    std::cout << "\nNumber of attempts needed to find robot in all segments: " << atempts << "\n\n";

    std::cout << "\nPress any key to continue...\n";
    std::cin.get();

}

bool lineSegmentsIntersects(lineSegment d1, lineSegment d2, Point2D *IntersectionPoint)
{
    /*
    line segments must be of the following form: T = {x, y} as in Point2D
    end points of line segments must be of the following form: d = {T1, T2} as in {Point2D, Point2D}
    */
    bool intersect = false;
    struct vector2D
    {
        int x;
        int y;
    };

    vector2D p = { d1.point1.x, d1.point1.y };
    vector2D q = { d2.point1.x, d2.point1.y };
    vector2D r = { d1.point2.x - d1.point1.x, d1.point2.y - d1.point1.y };
    vector2D s = { d2.point2.x - d2.point1.x, d2.point2.y - d2.point1.y };

    // delta
    int delta = r.x * s.y - s.x * r.y;

    if (delta)
    {
        // vector qp = vector q - vector p
        vector2D qp= { q.x - p.x, q.y - p.y };
        double t = double(qp.x * s.y - s.x * qp.y) / delta;
        double u = double(-qp.x * r.y - r.x * -qp.y) / -delta;
        if ((t >= 0 && t <= 1) && (u >= 0 && u <= 1))
        {
            intersect = true;
            IntersectionPoint->x = int(p.x + t * r.x);
            IntersectionPoint->y = int(p.y + t * r.y);
        }
        /*
        double T1x = p.x + t * r.x;
        double T1y = p.y + t * r.y;
        double T2x = q.x + u * s.x;
        double T2y = q.y + u * s.y;
        intersect = intersect;
        */
    }

    return intersect;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
