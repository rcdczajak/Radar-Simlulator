#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

class Target 
{
    private:
        double x;
        double y;
        double vx;
        double vy;
        string name;
        time_t timestamp;

    public:
    Target (double startX, double startY, double velX, double velY, const string& targetName) : x (startX), y (startY), vx (velX), vy (velY), name (targetName), timestamp (time (nullptr)) { }

    void updatePosition ( )
    {
        x += vx;
        y += vy;
    }

    double getX ( ) const {return x;}
    double getY ( ) const {return y;}
    string getName ( ) const {return name;}
    time_t getTimeStamp ( ) const {return timestamp;}
};

class Radar
{
    private: 
        vector <Target> targets;

    public:
        void addTarget (const Target& target)
        {
            targets.push_back (target);
        }

        void updateTargets ( ) 
        {
            for (auto& target : targets)
            {
                target.updatePosition ( );
            }
        }

        void displayTargets ( ) const 
        {
            for (const auto& target : targets)
            {
                time_t timestamp = target.getTimeStamp ( );
                cout << "Target " << target.getName ( ) << " positioned at (" << target.getX ( ) << ", " << target.getY ( ) << ") at approximately: " << asctime (localtime (&timestamp))  << "\n";
            }
        }

        void filterTargets (double threshold) const 
        {
            for (const auto& target : targets)
            {
                if (sqrt (target.getX ( ) * target.getX ( ) + target.getY ( ) * target.getY ( )) <= threshold)
                {
                    cout << "Target " << target.getName ( ) << " within range at (" << target.getX ( ) << ", " << target.getY ( ) << ")\n";

                    time_t timestamp = target.getTimeStamp ( );
                    cout << "Observed at: " << asctime (localtime (&timestamp)) << endl;
                }
            }
        }
};

int main ( ) 
{
    srand (static_cast <unsigned int> (time (0)));

    Radar radar;

    // Add static targets for debugging
    radar.addTarget (Target (0, 0, 1, 1, "Aplpha"));
    radar.addTarget (Target (10, 10, -1, -1, "Beta"));
    radar.addTarget (Target (5, 5, 0.5, 0.5, "Delta"));

    // Simulate and display targets movement over 10 time steps
    for (int i = 0; i < 10; i++)
    {
        cout << "Time step " << i << ":\n";
        radar.updateTargets ( );
        radar.displayTargets ( );
        cout << "\n";
    }

    // Display targets within a range of 10 units
    cout << "Filtered targets within range of 10 units: \n";
    radar.filterTargets (10.0);

    return 0;
}