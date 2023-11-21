
#ifndef GPS_H
#define GPS_H

#include <string>

class GPS {
public:
    // Constructor
    GPS();

    // Destructor
    ~GPS();

    // Setters
    void setLatitude(double latitude);
    void setLongitude(double longitude);
    void setAltitude(double altitude);
    void setTime(const std::string& time);
    void setSpeed(double speed);

    // Getters
    double getLatitude() const;
    double getLongitude() const;
    double getAltitude() const;
    std::string getTime() const;
    double getSpeed() const;

    // Other functions
    void start();
    void stop();
    void updateLocation();
    void calculateDistance(const GPS& otherGPS);

private:
    double latitude;
    double longitude;
    double altitude;
    std::string time;
    double speed;
};

#endif // GPS_H
