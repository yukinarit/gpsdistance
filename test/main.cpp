#include <gtest/gtest.h>

#include <cmath>
#include <gpsdistance.hpp>

using namespace gpsdistance;

typedef LatLng<double> LatLng64;
typedef Box2D<double> Box64;


TEST(GpsDistanceTest, radians)
{
    EXPECT_FLOAT_EQ( 0.0, radians(0.0) );
    EXPECT_FLOAT_EQ( 1.0, radians(180.0 / M_PI) );

    EXPECT_FLOAT_EQ( M_PI, radians(180.0) );
    EXPECT_FLOAT_EQ( -1.0*M_PI, radians(-180.0) );
}

TEST(GpsDistanceTest, degrees)
{
    EXPECT_FLOAT_EQ( 0.0, degrees(0.0) );
    EXPECT_FLOAT_EQ( 180.0 / M_PI, degrees(1.0) );

    EXPECT_FLOAT_EQ( 180.0, degrees(M_PI) );
    EXPECT_FLOAT_EQ( -180.0, degrees(-1.0*M_PI) );
}

TEST(GpsDistanceTest, distance)
{
    LatLng64 HONMACHI_STATION(34.682082, 135.498971); // 34 40 55.4952, 135 29 56.2956ZG
    LatLng64 SHINSAIBASHI_STATION(34.675175, 135.500319); // 34 40 30.63, 135 30 1.14840
    EXPECT_FLOAT_EQ( 0.77785206, distance(HONMACHI_STATION, SHINSAIBASHI_STATION) );
}

TEST(GpsDistanceTest, latitudinal_point)
{
    LatLng64 HONMACHI_STATION(34.682082, 135.498971);
	LatLng64 north = latitudinal_point(HONMACHI_STATION, static_cast<LatLng64::value_type>(2));
    EXPECT_FLOAT_EQ( 34.700069,  north.lat );
    EXPECT_FLOAT_EQ( HONMACHI_STATION.lng, north.lng );

	LatLng64 south = latitudinal_point(HONMACHI_STATION, static_cast<LatLng64::value_type>(-2));
    EXPECT_FLOAT_EQ( 34.664097,  south.lat );
    EXPECT_FLOAT_EQ( HONMACHI_STATION.lng, south.lng );
}

TEST(GpsDistanceTest, longitudinal_point)
{
    LatLng64 HONMACHI_STATION(34.682082, 135.498971);
	LatLng64 east = longitudinal_point(HONMACHI_STATION, static_cast<LatLng64::value_type>(2));
    EXPECT_FLOAT_EQ( HONMACHI_STATION.lat,  east.lat );
    EXPECT_FLOAT_EQ( 135.52084, east.lng );

	LatLng64 west = longitudinal_point(HONMACHI_STATION, static_cast<LatLng64::value_type>(-2));
    EXPECT_FLOAT_EQ( HONMACHI_STATION.lat,  west.lat );
    EXPECT_FLOAT_EQ( 135.4771, west.lng );
}

TEST(GpsDistanceTest, extent)
{
    LatLng64 HONMACHI_STATION(34.682082, 135.498971);

	LatLng64 east = longitudinal_point(HONMACHI_STATION, static_cast<LatLng64::value_type>(2));
	LatLng64 west = longitudinal_point(HONMACHI_STATION, static_cast<LatLng64::value_type>(-2));
	LatLng64 north = latitudinal_point(HONMACHI_STATION, static_cast<LatLng64::value_type>(2));
	LatLng64 south = latitudinal_point(HONMACHI_STATION, static_cast<LatLng64::value_type>(-2));
	Box64 extent2km = extent(HONMACHI_STATION
			, static_cast<LatLng64::value_type>(2)
			, static_cast<LatLng64::value_type>(2)
		);

    EXPECT_FLOAT_EQ( south.lat, extent2km.southwest.lat );
    EXPECT_FLOAT_EQ( west.lng,  extent2km.southwest.lng );
    EXPECT_FLOAT_EQ( north.lat, extent2km.northeast.lat );
    EXPECT_FLOAT_EQ( east.lng,  extent2km.northeast.lng );
}

