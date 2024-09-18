#include <assert.h>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;

namespace WeatherSpace {
class IWeatherSensor {
 public:
        virtual double TemperatureInC() const = 0;
        virtual int Precipitation() const = 0;
        virtual int Humidity() const = 0;
        virtual int WindSpeedKMPH() const = 0;
};

/// This is a stub for a weather sensor. For the sake of testing
/// we create a stub that generates weather data and allows us to
/// test the other parts of this application in isolation
/// without needing the actual Sensor during development

class SensorStub : public IWeatherSensor {
 public:
    int Humidity() const override {
        return 72;
    }

    int Precipitation() const override {
        return 70;
    }

    double TemperatureInC() const override {
        return 26;
    }

    int WindSpeedKMPH() const override {
        return 52;
    }
};

// This is a function to predict the weather, based on readings
// from a sensor

string Report(const IWeatherSensor& sensor) {
    int precipitation = sensor.Precipitation();
    // precipitation < 20 is a sunny day
    string report = "Sunny day";

    if (sensor.TemperatureInC() > 25) {
        if (precipitation >= 20 && precipitation < 60)
            report = "Partly cloudy";
        else if (sensor.WindSpeedKMPH() > 50)
            report = "Alert, Stormy with heavy rain";
    }
    return report;
}

// Test a rainy day

void TestRainy() {
    SensorStub sensor;
    string report = Report(sensor);
    cout << report << endl;
    assert(report.find("rain") != string::npos);
}

// Test another rainy day

void TestHighPrecipitationAndLowWindspeed() {
    // This instance of stub needs to be different-
    // to give high precipitation (>60) and low wind-speed (<50)
    SensorStub sensor;

    // strengthen the assert to expose the bug
    // (function returns Sunny day, it should predict rain)
    string report = Report(sensor);
    assert(report.length() > 0);

    // Current values are 26, 70, 72, 52 should return "Rainy day"
    assert(report == "Rainy day");
    // Check for "Partly cloudy"
    if (sensor.TemperatureInC() > 25 &&
        sensor.Precipitation() >= 20 &&
        sensor.Precipitation() < 60) {
        assert(report == "Partly cloudy");
    }
    if (sensor.TemperatureInC() > 25 &&
        sensor.WindSpeedKMPH() > 50) {
        assert(report == "Partly cloudy");
    }
    // Check for "Sunny day"
    if (sensor.TemperatureInC() > 25 &&
       (sensor.Precipitation() < 20 ||sensor.Precipitation() >= 60)&&
       sensor.WindSpeedKMPH() <= 50) {
        assert(report == "Sunny day");
    }
}
}  // namespace WeatherSpace

int main() {
    WeatherSpace::TestRainy();
    WeatherSpace::TestHighPrecipitationAndLowWindspeed();
    cout << "All is well (maybe)\n";
    return 0;
}
