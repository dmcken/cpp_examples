/**
 * A basic memory management test.
 *
 * Build with:
 * g++ -g 0100_stl_container_ownership.cpp -o 0100_stl_container_ownership
 *
 * Test with:
 * valgrind --leak-check=yes ./0100_stl_container_ownership
 *
 *
 */

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Point {
private:
    int
        x, y, z;

public:
    Point()
    {
        cout << "Point constructor - default" << endl;
        x = 0;
        y = 0;
        z = 0;
    }
    Point(int in_x, int in_y, int in_z)
    {
        x = in_x;
        y = in_y;
        z = in_z;
        cout << "Point constructor - Paramerters: (" << in_x << "," << in_y
             << "," << in_z << ")" << endl;
    }

    ~Point()
    {
        // Destructor
        cout << "Point destructor: " << this << endl;
    }

    void set_x(int new_x) { x = new_x; }
    void set_y(int new_y) { y = new_y; }
    void set_z(int new_z) { z = new_z; }

    friend ostream& operator<<(ostream& os, const Point& pt)
    {
        os << "Point(" << pt.x << ',' << pt.y << ',' << pt.z << ")";
        return os;
    }
};

int main()
{
    vector<Point> p_vec;
    Point center;
    cout << "Starting" << endl;

    center.set_x(5);
    p_vec.push_back(center);
    center.set_y(2);
    p_vec.push_back(center);
    center.set_z(1);

    cout << "Vector[0] : " << p_vec[0] << " - " << &p_vec[0] << endl;
    cout << "Vector[1] : " << p_vec[1] << " - " << &p_vec[1] << endl;
    cout << "Center    : " << center   << " - " << &center   << endl;

    return 0;
}
