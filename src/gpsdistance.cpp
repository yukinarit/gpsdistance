#include "gpsdistance.hpp"
#include <cmath>


namespace gpsdistance
{
// http://www.movable-type.co.uk/scripts/latlong.html
// https://github.com/johnmeehan/Distance/blob/master/Distance.cpp
    
double radians(double degree)
{
    return degree * M_PI / 180;
}
    
LatLng radians(const LatLng& latlng)
{
    return LatLng {radians(latlng.lat), radians(latlng.lng)};
}
    
double distance(const LatLng& from, const LatLng& to)
{
    LatLng rfrom = radians(from);
    LatLng rto = radians(to);
    
    double dlat = rto.lat - rfrom.lat;
    double dlng = rto.lng - rfrom.lng;
    
    double a = sin(dlat/2.0)*sin(dlat/2.0) + cos(rfrom.lat) * cos(rto.lat) * sin(dlng/2.0)*sin(dlng/2.0);
    double c = 2 * atan2(sqrt(a), sqrt(1.0 - a));
    double d = EARTH_RADIUS_KM * c;
    
    return d;
}
    
    
} // gpsdistance
