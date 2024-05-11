package group1.silowebapp.mqtt;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import group1.silowebapp.model.EntityFactory;
import group1.silowebapp.model.GrainHeight;
import group1.silowebapp.model.Humidity;
import group1.silowebapp.model.Temperature;
import group1.silowebapp.repository.GrainHeightRepository;
import group1.silowebapp.repository.HumidityRepository;
import group1.silowebapp.repository.SiloRepository;
import group1.silowebapp.repository.TemperatureRepository;
import group1.silowebapp.webSocketComponent.WebSocketSensorUpdateComponent;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.Message;
import org.springframework.messaging.MessageHandler;
import org.springframework.messaging.MessageHeaders;
import org.springframework.messaging.MessagingException;

import java.io.IOException;

public class SensorsMessageHandler implements MessageHandler {

    private String type;

    @Autowired
    private TemperatureRepository tempRepo;
    @Autowired
    private HumidityRepository humiRepo;
    @Autowired
    private GrainHeightRepository quantityRepo;
    @Autowired
    private SiloRepository siloRepository;

    @Autowired
    private WebSocketSensorUpdateComponent webSocketSensorUpdateComponent;

    public SensorsMessageHandler(String type) {
        this.type = type;
    }

    @Override
    public void handleMessage(Message<?> message) throws MessagingException {
        MessageHeaders headers = message.getHeaders();                  //gets meta-info about message
        headers.forEach((k, v) -> System.out.println(k + "=" + v));
        System.out.println(message.getPayload());
        ObjectMapper mapper = new ObjectMapper();
        JsonNode node = null;

        try {
            node = mapper.readTree(message.getPayload().toString());
        } catch (IOException ex) {
            System.out.printf("Could not parse to JsonNode. Reason: %s%n", ex);
            return;
        }

        Double value = node.get("value").asDouble();
        String dateTime = node.get("dateTime").asText();

        //Adding received values to database 
        //and send through websocket to update the webpage
        switch (type) {
            case "Humidity":
                Humidity humidity = humiRepo.save(EntityFactory.createHumidity(value, dateTime, siloRepository.findById(1L)));
                webSocketSensorUpdateComponent.updateHumidity(humidity);
                break;
            case "Temperature":
                Temperature temperature = tempRepo.save(EntityFactory.createTemperature(value, dateTime, siloRepository.findById(1L)));
                webSocketSensorUpdateComponent.updateTemperature(temperature);
                break;
            case "GrainHeight":
                GrainHeight grainHeight = quantityRepo.save(EntityFactory.createGrainHeight(value, dateTime, siloRepository.findById(1L)));
                webSocketSensorUpdateComponent.updateDistance(grainHeight);
                break;
        }
    }
}