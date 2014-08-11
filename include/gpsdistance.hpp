#ifndef GPSDISTANCE_H
#define GPSDISTANCE_H

#include <cmath>

// http://www.movable-type.co.uk/scripts/latlong.html
// https://github.com/johnmeehan/Distance/blob/master/Distance.cpp

namespace gpsdistance
{

static const double EARTH_RADIUS_KM = 6371.0;
static const double EARTH_RADIUS_METER = EARTH_RADIUS_KM * 1000.0;


template <typename T>
struct LatLng
{
	typedef T value_type;
    LatLng()
        : lat {}
        , lng {}
    {}

    LatLng(T latitude, T longitude)
        : lat{latitude}
        , lng{longitude}
    {}

    T lat;
    T lng;
};


template <typename T>
struct Box2D
{
	typedef T value_type;
	Box2D()
	{}

	Box2D(const LatLng<T>& southwest, const LatLng<T>& northeast)
		: southwest(southwest)
		, northeast(northeast)
	{}

	LatLng<T> southwest;
	LatLng<T> northeast;
};


template <typename T>
T radians(const T& degree)
{
    return degree * M_PI / 180.0;
}


template <typename T>
LatLng<T> radians(const LatLng<T>& latlng)
{
    return LatLng<T> {
        radians(latlng.lat)
        , radians(latlng.lng)
    };
}
    

template <typename T>
T degrees(const T& radian)
{
	return radian * 180.0 / M_PI;
}

template <typename T>
LatLng<T> degrees(const LatLng<T>& latlng)
{
	return LatLng<T>(
		degrees(latlng.lat)
		, degrees(latlng.lng)
	);
}




    
/*
 *
 *
 */
template <typename T>
T distance(const LatLng<T>& from, const LatLng<T>& to)
{
    LatLng<T> rfrom = radians(from);
    LatLng<T> rto = radians(to);

    T dlat = rto.lat - rfrom.lat;
    T dlng = rto.lng - rfrom.lng;

    T a = sin(dlat/2.0)*sin(dlat/2.0) + cos(rfrom.lat) * cos(rto.lat) * sin(dlng/2.0)*sin(dlng/2.0);
    T c = 2 * atan2(sqrt(a), sqrt(1.0 - a));
    T d = EARTH_RADIUS_KM * c;
    
    return d;
}


template<typename T>
LatLng<T> latitudinal_point(const LatLng<T>& from, T latitudinal_distance)
{
	LatLng<T> to;
	to.lng = radians(from.lng);
	to.lat = radians(from.lat) + (latitudinal_distance / EARTH_RADIUS_KM);

	return degrees(to);
}


template<typename T>
LatLng<T> longitudinal_point(const LatLng<T>& from, T longitudinal_distance)
{
	LatLng<T> to;
	to.lat = radians(from.lat);
	to.lng = radians(from.lng) + (longitudinal_distance / EARTH_RADIUS_KM / cos(radians(from.lat)));

	return degrees(to);
}

template<typename T>
Box2D<T> extent(const LatLng<T>& center, T latitudinal_distance, T longitudinal_distance)
{
	T lat_diff_degree = latitudinal_point(center, std::abs(latitudinal_distance)).lat - center.lat;
	T lng_diff_degree = longitudinal_point(center, std::abs(longitudinal_distance)).lng - center.lng;

	LatLng<T> southwest(center.lat - lat_diff_degree, center.lng - lng_diff_degree);
	LatLng<T> northeast(center.lat + lat_diff_degree, center.lng + lng_diff_degree);

	return Box2D<T>(
			southwest
			, northeast
	   );
}

} // namespace gpsdistance

#endif // GPSDISTANCE_H
