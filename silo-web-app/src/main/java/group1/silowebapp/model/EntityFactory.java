package group1.silowebapp.model;

public class EntityFactory {

    public static Humidity createHumidity(Double reading, String dateTime, Silo silo){
        return new Humidity(reading, dateTime, silo);
    }

    public static Temperature createTemperature(Double reading, String dateTime, Silo silo){
        return new Temperature(reading, dateTime, silo);
    }

    public static GrainHeight createGrainHeight(Double reading, String dateTime, Silo silo){
        return new GrainHeight(reading, dateTime, silo);
    }
}
