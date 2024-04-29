package group1.silowebapp.schemas;

/*
 * Class used for testing purposes
 * Will be removed before deployment.
 */
public class SensorReading {
    private double temperature;
    private double humidity;
    private double distance;

    public double getTemperature() {
        return temperature;
    }

    public double getHumidity() {
        return humidity;
    }

    public double getDistance() {
        return distance;
    }

    public void setTemperature(double temperature) {
        this.temperature = temperature;
    }

    public void setHumidity(double humidity) {
        this.humidity = humidity;
    }

    public void setDistance(double distance) {
        this.distance = distance;
    }
}
