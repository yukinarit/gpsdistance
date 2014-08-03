#include <gtest/gtest.h>
#include <gpsdistance.hpp>

TEST(GpsDistanceTest, aaa)
{
    EXPECT_EQ( 5.0, gpsdistance::distance(gpsdistance::LatLng {0.0, 0.0}, gpsdistance::LatLng {0.0, 0.0}) );
}
