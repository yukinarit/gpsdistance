#ifndef GPSDISTANCE_H
#define GPSDISTANCE_H

namespace gpsdistance
{

static const double EARTH_RADIUS_KM = 6378.137;
static const double EARTH_RADIUS_METER = EARTH_RADIUS_KM * 1000.0;
    
struct LatLng
{
    LatLng(double latitude, double longitude)
        : lat(latitude)
        , lng(longitude)
    {}
    
    double lat = 0.0;
    double lng = 0.0;
};
    
double radians(double degree);
LatLng radians(const LatLng& latlng);
    
double distance(const LatLng& from, const LatLng& to);
    
} // gpsdistance

#endif // GPSDISTANCE_H