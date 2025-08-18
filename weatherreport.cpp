#include <string>
#include <iostream>
#include <assert.h>

using namespace std;

namespace WeatherSpace
{    
    class IWeatherSensor {
    public:
        virtual double TemperatureInC() const = 0;
        virtual int Precipitation() const = 0;
        virtual int Humidity() const = 0;
        virtual int WindSpeedKMPH() const = 0;
    };

    class SensorStub : public IWeatherSensor {
    public:
        double TemperatureInC() const override {
            return 26;   // >25 (warm)
        }
        int Precipitation() const override {
            return 70;   // High precipitation
        }
        int Humidity() const override {
            return 72;   // Arbitrary
        }
        int WindSpeedKMPH() const override {
            return 52;   // High wind speed
        }
    };

    string Report(const IWeatherSensor& sensor)
    {
        int precipitation = sensor.Precipitation();
        string report = "Sunny Day";  // default

        if (sensor.TemperatureInC() > 25)
        {
            if (precipitation >= 20 && precipitation < 60)
                report = "Partly Cloudy";
            else if (sensor.WindSpeedKMPH() > 50)
                report = "Alert, Stormy with heavy rain";
        }
        return report;
    }

    void TestRainy()
    {
        SensorStub sensor;
        string report = Report(sensor);
        cout << "Rainy Test Report: " << report << endl;
        assert(report.find("rain") != string::npos);
    }

    void TestHighPrecipitation()
    {
        SensorStub sensor;
        string report = Report(sensor);
        cout << "High Precipitation Test Report: " << report << endl;

        assert(report != "Sunny Day");

        assert(report.find("rain") != string::npos);
    }
}

void testWeatherReport() {
    cout << "\nWeather report tests\n";
    WeatherSpace::TestRainy();             // will fail
    WeatherSpace::TestHighPrecipitation(); // will fail
    cout << "All is well (maybe)\n";
}

int main() {
    testWeatherReport();
    return 0;
}
