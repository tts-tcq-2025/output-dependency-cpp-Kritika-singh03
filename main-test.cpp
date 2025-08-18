#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

char size(int cms) {
    char sizeName = '\0';
    if (cms < 38) {
        sizeName = 'S';
    } else if (cms > 38 && cms < 42) {
        sizeName = 'M';
    } else if (cms > 42) {
        sizeName = 'L';
    }
    return sizeName;
}

void testTshirtSize() {
    EXPECT_EQ(size(37), 'S');      // ✅ Pass
    EXPECT_EQ(size(38), 'S');      // ❌ Fails (returns '\0')
    EXPECT_EQ(size(40), 'M');      // ✅ Pass
    EXPECT_EQ(size(42), 'M');      // ❌ Fails (returns '\0')
    EXPECT_EQ(size(43), 'L');      // ✅ Pass
}

std::vector<std::string> generateColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    std::vector<std::string> colorMap;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::ostringstream oss;
            // BUG: using minorColor[i] instead of minorColor[j]
            oss << (i * 5 + j) << " | " << majorColor[i] << " | " << minorColor[i];
            colorMap.push_back(oss.str());
        }
    }
    return colorMap;
}

void testPrintColorMap() {
    auto map = generateColorMap();

    EXPECT_EQ(map.size(), 25);                            // ✅ Pass
    EXPECT_EQ(map[0], "0 | White | Blue");                // ❌ Fails
    EXPECT_EQ(map[24], "24 | Violet | Slate");            // ❌ Fails
    EXPECT_EQ(map[7], "7 | Red | Brown");                 // ❌ Fails
}

namespace WeatherSpace {
    class IWeatherSensor {
    public:
        virtual double TemperatureInC() const = 0;
        virtual int Precipitation() const = 0;
        virtual int Humidity() const = 0;
        virtual int WindSpeedKMPH() const = 0;
    };

    class SensorStub : public IWeatherSensor {
    public:
        double TemperatureInC() const override { return 26; }
        int Precipitation() const override { return 70; }
        int Humidity() const override { return 72; }
        int WindSpeedKMPH() const override { return 52; }
    };

    std::string Report(const IWeatherSensor& sensor) {
        int precipitation = sensor.Precipitation();
        std::string report = "Sunny Day";

        if (sensor.TemperatureInC() > 25) {
           
            if (precipitation >= 20 && precipitation < 60)
                report = "Partly Cloudy";
            else if (sensor.WindSpeedKMPH() > 50)
                report = "Alert, Stormy with heavy rain";
        }
        return report;
    }
}

void testWeatherReport() {
    WeatherSpace::SensorStub sensor;
    std::string report = WeatherSpace::Report(sensor);

    EXPECT_NE(report.find("rain"), std::string::npos);

    EXPECT_NE(report, "Sunny Day");
}

TEST(TShirt, Size) {
    testTshirtSize();
}

TEST(ColorMap, Print) {
    testPrintColorMap();
}

TEST(WeatherReport, Report) {
    testWeatherReport();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
