#ifndef GPSDISTANCE_H
#define GPSDISTANCE_H

#include <cmath>

// http://www.movable-type.co.uk/scripts/latlong.html
// https://github.com/johnmeehan/Distance/blob/master/Distance.cpp

namespace gpsdistance
{

static const double EARTH_RADIUS_KM = 6378.137;
static const double EARTH_RADIUS_METER = EARTH_RADIUS_KM * 1000.0;


template <typename T>
struct LatLng_t
{
    LatLng_t()
        : lat {}
        , lng {}
    {}

    LatLng_t(T latitude, T longitude)
        : lat{latitude}
        , lng{longitude}
    {}

    T lat;
    T lng;
};
typedef LatLng_t<double> LatLng;


template <typename T>
T radians(const T& degree)
{
    return degree * M_PI / 180.0;
}


template <typename T>
LatLng_t<T> radians(const LatLng_t<T>& latlng)
{
    return LatLng_t<T> {
        radians(latlng.lat)
        , radians(latlng.lng)
    };
}
    
    
/*
 *
 *
 */
template <typename T>
T distance(const LatLng_t<T>& from, const LatLng_t<T>& to)
{
    LatLng_t<T> rfrom = radians(from);
    LatLng_t<T> rto = radians(to);

    T dlat = rto.lat - rfrom.lat;
    T dlng = rto.lng - rfrom.lng;

    T a = sin(dlat/2.0)*sin(dlat/2.0) + cos(rfrom.lat) * cos(rto.lat) * sin(dlng/2.0)*sin(dlng/2.0);
    T c = 2 * atan2(sqrt(a), sqrt(1.0 - a));
    T d = EARTH_RADIUS_KM * c;
    
    return d;
}

template<typename T>
LatLng_t<T> latitudinal_point(const LatLng_t<T>& from, T latitudinal_distance)
{
	LatLng_t<T> to;
	to.lng = from.lng ;
	to.lat = from.at - (latitudinal_distance / EARTH_RADIUS_KM);

	return to;
}

} // namespace gpsdistance

#endif // GPSDISTANCE_H
