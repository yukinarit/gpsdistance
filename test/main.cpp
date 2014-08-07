#include <gtest/gtest.h>

#include <cmath>
#include <gpsdistance.hpp>

using namespace gpsdistance;

TEST(GpsDistanceTest, distance)
{
    LatLng HONMACHI_STATION {34.682082, 135.498971};
    LatLng SHINSAIBASHI_STATION {34.675175, 135.500319};
    EXPECT_FLOAT_EQ( 0.77872342, distance(HONMACHI_STATION, SHINSAIBASHI_STATION) );
}

TEST(GpsDistanceTest, radians)
{
    EXPECT_FLOAT_EQ( 0.0, radians(0.0) );
    EXPECT_FLOAT_EQ( 1.0, radians(180.0 / M_PI) );

    EXPECT_FLOAT_EQ( M_PI, radians(180.0) );
    EXPECT_FLOAT_EQ( -1.0*M_PI, radians(-180.0) );
}